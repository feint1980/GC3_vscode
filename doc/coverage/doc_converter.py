"""
doc_converter.py
Converts a structured .txt project doc into a styled HTML file.
No internet required.

TXT FORMAT RULES:
=================
- Top/bottom border:     ===...=== (80 chars)
- Section dividers:      ---...--- (80 chars)
- Section headers:       "  N. SECTION TITLE" between dividers
- Sub-headers:           "  Title:" (line ending with colon, indented)
- Bullet items:          "  - key : value"  or  "  - text"
- Sub-section markers:   "  --- TITLE ---"
- Bug tags:              [BUG], [NAMING], [INCONSISTENCY], [DEAD CODE], [FRAGILE], [CLEANUP]
- Status Done block:     "  Done:"  followed by bullet items
- Status WIP block:      "  In Progress:" followed by bullet items
- Code/formula lines:    lines indented with 4+ spaces inside a sub-header block
- Character entries:     Name on its own line + "    Passive: ..." indented below
- Key-value metadata:    lines like "  Author: X" or "  Last Updated: X" in header block
"""

import re
import sys
import os
from html import escape

# ---------------------------------------------------------------------------
# HELPERS
# ---------------------------------------------------------------------------

def is_divider(line, char='=', min_len=40):
    s = line.strip()
    return len(s) >= min_len and all(c == char for c in s)

def is_section_divider(line):
    return is_divider(line, '-', 40)

def is_top_divider(line):
    return is_divider(line, '=', 40)

def is_bullet(line):
    return re.match(r'^\s{2,}-\s+', line)

def is_sub_header(line):
    # "  Title:" but not a bullet, not a section number line
    return re.match(r'^\s{2,4}[A-Z][^-\n]+:\s*$', line) and not re.match(r'^\s+\d+\.', line)

def is_sub_section_marker(line):
    return re.match(r'^\s+---\s+.+\s+---\s*$', line)

def is_character_passive(line):
    return re.match(r'^\s{4,}Passive:', line)

def is_code_line(line):
    return re.match(r'^\s{4,}\S', line) and not is_bullet(line) and not is_character_passive(line)

def strip_indent(line):
    return line.strip()

def parse_bullet(line):
    """Returns (key, value) or (None, text)"""
    m = re.match(r'^\s+-\s+(.+)', line)
    if not m:
        return None, line.strip()
    content = m.group(1)
    if ' : ' in content:
        parts = content.split(' : ', 1)
        return parts[0].strip(), parts[1].strip()
    return None, content.strip()

def parse_bug_tag(line):
    """Returns (tag_type, content) or None"""
    m = re.match(r'^\s+\[(BUG|NAMING|INCONSISTENCY|DEAD CODE|FRAGILE|CLEANUP)\]\s*(.*)', line)
    if m:
        return m.group(1), m.group(2).strip()
    return None

def tag_class(tag):
    if tag in ('BUG',):
        return 'red'
    if tag in ('NAMING', 'INCONSISTENCY', 'FRAGILE'):
        return 'yellow'
    return 'gray'

# ---------------------------------------------------------------------------
# PARSER
# ---------------------------------------------------------------------------

def parse_txt(text):
    lines = text.splitlines()
    doc = {'title': '', 'subtitle': '', 'meta': {}, 'sections': []}

    i = 0
    n = len(lines)

    # --- Parse header block (between first two === lines) ---
    while i < n and not is_top_divider(lines[i]):
        i += 1
    i += 1  # skip opening ===

    header_lines = []
    while i < n and not is_top_divider(lines[i]):
        header_lines.append(lines[i])
        i += 1
    i += 1  # skip closing ===

    for hl in header_lines:
        s = hl.strip()
        if not s:
            continue
        if ':' in s and not doc['title']:
            # Could be metadata like "Author: X"
            pass
        if not doc['title']:
            doc['title'] = s
        elif not doc['subtitle']:
            doc['subtitle'] = s
        else:
            m = re.match(r'^(\w[\w\s]+):\s*(.+)', s)
            if m:
                doc['meta'][m.group(1).strip()] = m.group(2).strip()

    # --- Parse sections ---
    current_section = None
    current_sub = None
    current_block = None  # 'bullets' | 'code' | 'bugs' | 'chars' | 'status_done' | 'status_wip' | 'text'
    pending_char_name = None
    pending_char_tag = None

    def flush_sub():
        nonlocal current_sub, current_block, pending_char_name, pending_char_tag
        if current_sub and current_section:
            current_section['content'].append(current_sub)
        current_sub = None
        current_block = None
        pending_char_name = None
        pending_char_tag = None

    def flush_section():
        nonlocal current_section
        flush_sub()
        if current_section:
            doc['sections'].append(current_section)
        current_section = None

    while i < n:
        line = lines[i]

        # End of document
        if is_top_divider(line):
            flush_section()
            i += 1
            continue

        # Section divider pair
        if is_section_divider(line):
            # peek next line for section title
            j = i + 1
            while j < n and not lines[j].strip():
                j += 1
            if j < n:
                title_line = lines[j].strip()
                m = re.match(r'^(\d+)\.\s+(.+)', title_line)
                if m:
                    flush_section()
                    current_section = {
                        'num': m.group(1),
                        'title': m.group(2).strip(),
                        'content': []
                    }
                    i = j + 1
                    # skip closing divider
                    while i < n and not is_section_divider(lines[i]):
                        i += 1
                    i += 1
                    continue
            i += 1
            continue

        if current_section is None:
            i += 1
            continue

        # Sub-section marker  --- TITLE ---
        if is_sub_section_marker(line):
            flush_sub()
            m = re.match(r'^\s+---\s+(.+?)\s+---', line)
            label = m.group(1) if m else line.strip()
            current_sub = {'type': 'subsection_marker', 'title': label}
            current_section['content'].append(current_sub)
            current_sub = None
            i += 1
            continue

        # Sub-header like "  Key Features:"
        if is_sub_header(line):
            flush_sub()
            title = line.strip().rstrip(':')
            current_sub = {'type': 'subheader', 'title': title, 'items': [], 'code_lines': [], 'text_lines': []}
            # detect if this is a status block
            if title.lower() == 'done':
                current_sub['type'] = 'status_done'
            elif title.lower() == 'in progress':
                current_sub['type'] = 'status_wip'
            current_block = None
            i += 1
            continue

        # Blank line — end char entry if pending
        if not line.strip():
            if pending_char_name and current_sub and current_sub.get('type') == 'chars':
                pass  # keep pending, multi-line passives
            i += 1
            continue

        # Bug tag lines
        bug = parse_bug_tag(line)
        if bug and current_section:
            tag_type, content = bug
            # find or create bugs sub
            if not current_sub or current_sub.get('type') != 'bugs':
                flush_sub()
                current_sub = {'type': 'bugs', 'title': '', 'items': []}
            # continuation line (indented, no tag)
            current_sub['items'].append({'tag': tag_type, 'text': content})
            i += 1
            continue

        # Bug continuation (indented text after a bug line, no tag)
        if current_sub and current_sub.get('type') == 'bugs' and re.match(r'^\s{8,}\S', line):
            if current_sub['items']:
                current_sub['items'][-1]['text'] += ' ' + line.strip()
            i += 1
            continue

        # File label inside bugs (like "  FocusPanel.cpp:")
        if current_sub and current_sub.get('type') == 'bugs' and re.match(r'^\s{2,4}\S.*:\s*$', line):
            current_sub['items'].append({'tag': 'FILE', 'text': line.strip().rstrip(':')})
            i += 1
            continue

        # Bullet items
        if is_bullet(line):
            key, val = parse_bullet(line)
            if current_sub is None:
                current_sub = {'type': 'subheader', 'title': '', 'items': [], 'code_lines': [], 'text_lines': []}
            if current_sub.get('type') in ('status_done', 'status_wip'):
                current_sub.setdefault('items', []).append({'key': key, 'val': val})
            else:
                current_sub.setdefault('items', []).append({'key': key, 'val': val})
            i += 1
            continue

        # Character name detection (non-indented-much, followed by Passive:)
        # Look ahead for passive
        if current_sub is None or current_sub.get('type') in ('chars', 'subheader', None):
            lookahead = i + 1
            while lookahead < n and not lines[lookahead].strip():
                lookahead += 1
            if lookahead < n and is_character_passive(lines[lookahead]):
                name = line.strip()
                if name:
                    if not current_sub or current_sub.get('type') != 'chars':
                        flush_sub()
                        current_sub = {'type': 'chars', 'title': 'Characters', 'items': []}
                    pending_char_name = name
                    i += 1
                    continue

        # Character passive line
        if is_character_passive(line) and pending_char_name:
            passive_text = re.sub(r'^\s+Passive:\s*', '', line)
            # collect continuation lines
            j = i + 1
            while j < n and lines[j].strip() and re.match(r'^\s{8,}\S', lines[j]):
                passive_text += ' ' + lines[j].strip()
                j += 1
            current_sub['items'].append({
                'name': pending_char_name,
                'tag': pending_char_tag or '',
                'passive': passive_text.strip()
            })
            pending_char_name = None
            pending_char_tag = None
            i = j
            continue

        # Numbered flow steps like "  1. Both players ready..."
        if re.match(r'^\s+\d+\.\s+\S', line) and current_sub:
            m = re.match(r'^\s+(\d+)\.\s+(.+)', line)
            if m:
                current_sub.setdefault('flow_steps', []).append({
                    'num': m.group(1),
                    'text': m.group(2).strip()
                })
                # collect continuation
                j = i + 1
                while j < n and lines[j].strip() and re.match(r'^\s{5,}\S', lines[j]) and not re.match(r'^\s+\d+\.', lines[j]):
                    current_sub['flow_steps'][-1]['text'] += ' ' + lines[j].strip()
                    j += 1
                i = j
                continue

        # Code-like indented lines (formulas, etc.)
        if is_code_line(line) and current_sub:
            current_sub.setdefault('code_lines', []).append(line.rstrip())
            i += 1
            continue

        # Plain text paragraph
        s = line.strip()
        if s and current_sub:
            current_sub.setdefault('text_lines', []).append(s)
        elif s and current_section:
            # top-level paragraph before any sub
            current_section.setdefault('intro', [])
            current_section['intro'].append(s)

        i += 1

    flush_section()
    return doc

# ---------------------------------------------------------------------------
# HTML RENDERER
# ---------------------------------------------------------------------------

CSS = """
<style>
:root {
  --bg:#0a0c10;--bg2:#0f1318;--bg3:#141920;
  --border:#1e2d3d;--accent:#00e5ff;--accent2:#ff4d6d;
  --accent3:#b9ff66;--text:#c9d1d9;--text2:#8b949e;--text3:#58a6ff;
}
*{margin:0;padding:0;box-sizing:border-box;}
body{background:var(--bg);color:var(--text);font-family:'Rajdhani',sans-serif;
  font-size:16px;line-height:1.7;min-height:100vh;}
body::before{content:'';position:fixed;inset:0;
  background:repeating-linear-gradient(0deg,transparent,transparent 2px,rgba(0,0,0,0.03) 2px,rgba(0,0,0,0.03) 4px);
  pointer-events:none;z-index:1000;}
.page{max-width:960px;margin:0 auto;padding:40px 24px 80px;}
/* Header */
.hdr{border-bottom:1px solid var(--border);padding-bottom:32px;margin-bottom:48px;position:relative;}
.hdr::before{content:'';position:absolute;bottom:-1px;left:0;width:120px;height:2px;
  background:var(--accent);box-shadow:0 0 12px var(--accent);}
.hdr-tag{font-family:'Share Tech Mono',monospace;font-size:11px;color:var(--accent);
  letter-spacing:3px;text-transform:uppercase;margin-bottom:12px;opacity:.8;}
h1{font-size:42px;font-weight:700;color:#fff;line-height:1.2;}
h1 span{color:var(--accent);}
.subtitle{color:var(--text2);font-size:15px;margin-top:10px;font-family:'Share Tech Mono',monospace;}
.meta-row{margin-top:8px;font-family:'Share Tech Mono',monospace;font-size:11px;color:var(--text2);}
.badges{display:flex;flex-wrap:wrap;gap:8px;margin-top:20px;}
.badge{font-family:'Share Tech Mono',monospace;font-size:11px;padding:4px 10px;
  border:1px solid var(--border);color:var(--text2);background:var(--bg2);}
/* Sections */
.section{margin-bottom:52px;}
.sec-hdr{display:flex;align-items:center;gap:14px;margin-bottom:22px;}
.sec-num{font-family:'Share Tech Mono',monospace;font-size:11px;color:var(--accent);opacity:.6;min-width:32px;}
h2{font-size:21px;font-weight:700;letter-spacing:2px;text-transform:uppercase;color:#fff;}
.sec-line{flex:1;height:1px;background:var(--border);}
/* Intro text */
.intro{color:var(--text);font-size:15px;margin-bottom:18px;line-height:1.7;}
/* Sub-section marker */
.ssm{font-family:'Share Tech Mono',monospace;font-size:11px;color:var(--accent2);
  letter-spacing:3px;text-transform:uppercase;margin:28px 0 14px;opacity:.8;}
/* Subheader card */
.card{background:var(--bg2);border:1px solid var(--border);border-left:3px solid var(--accent);
  padding:18px 22px;margin-bottom:14px;}
.card:hover{border-left-color:var(--accent2);}
.card-title{font-family:'Share Tech Mono',monospace;font-size:11px;color:var(--accent);
  letter-spacing:2px;text-transform:uppercase;margin-bottom:10px;}
/* Bullet list */
.blist{list-style:none;margin:8px 0;}
.blist li{padding:4px 0;border-bottom:1px solid var(--border);font-size:14px;
  display:flex;gap:8px;align-items:baseline;}
.blist li:last-child{border-bottom:none;}
.blist li::before{content:'';width:5px;height:5px;border-radius:50%;
  background:var(--accent);flex-shrink:0;margin-top:6px;}
.bkey{color:var(--text3);font-family:'Share Tech Mono',monospace;font-size:12px;
  min-width:140px;flex-shrink:0;}
/* Code block */
.code{background:var(--bg3);border:1px solid var(--border);border-left:3px solid var(--accent3);
  padding:14px 18px;font-family:'Share Tech Mono',monospace;font-size:12px;
  color:var(--accent3);margin:12px 0;overflow-x:auto;line-height:1.8;white-space:pre;}
/* Characters grid */
.char-grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(270px,1fr));gap:14px;margin-bottom:14px;}
.char-card{background:var(--bg2);border:1px solid var(--border);border-top:2px solid var(--accent);
  padding:18px;transition:transform .2s,border-color .2s;}
.char-card:hover{transform:translateY(-2px);border-color:var(--accent);}
.char-name{font-size:17px;font-weight:700;color:#fff;letter-spacing:1px;}
.char-passive-lbl{font-family:'Share Tech Mono',monospace;font-size:10px;
  color:var(--accent);letter-spacing:2px;margin:10px 0 4px;}
.char-passive{font-size:14px;color:var(--text);line-height:1.6;}
/* Flow */
.flow{display:flex;flex-direction:column;gap:0;margin:12px 0;}
.flow-step{background:var(--bg2);border:1px solid var(--border);border-left:3px solid var(--border);
  padding:12px 18px;font-size:14px;transition:border-left-color .2s;}
.flow-step:hover{border-left-color:var(--accent);}
.flow-num{font-family:'Share Tech Mono',monospace;font-size:10px;color:var(--accent);margin-bottom:3px;}
.flow-arrow{text-align:center;color:var(--border);font-size:16px;line-height:1;padding:1px 0;}
/* Status */
.status-grid{display:grid;grid-template-columns:1fr 1fr;gap:14px;}
.status-card{background:var(--bg2);border:1px solid var(--border);padding:16px 18px;}
.status-title{font-family:'Share Tech Mono',monospace;font-size:11px;letter-spacing:2px;margin-bottom:10px;}
.status-title.done{color:var(--accent3);}
.status-title.wip{color:#ffd700;}
.status-item{font-size:14px;color:var(--text);padding:4px 0;
  border-bottom:1px solid var(--border);display:flex;align-items:center;gap:8px;}
.status-item:last-child{border-bottom:none;}
.status-item::before{content:'';width:6px;height:6px;border-radius:50%;flex-shrink:0;}
.status-item.done::before{background:var(--accent3);}
.status-item.wip::before{background:#ffd700;box-shadow:0 0 5px #ffd700;}
/* Bugs */
.bug-list{display:flex;flex-direction:column;gap:10px;}
.bug-item{background:var(--bg2);border:1px solid var(--border);
  padding:12px 16px;display:flex;gap:12px;align-items:flex-start;}
.bug-tag{font-family:'Share Tech Mono',monospace;font-size:10px;padding:3px 8px;
  white-space:nowrap;font-weight:700;letter-spacing:1px;flex-shrink:0;margin-top:2px;}
.bug-tag.red{background:rgba(255,77,109,.15);color:var(--accent2);border:1px solid var(--accent2);}
.bug-tag.yellow{background:rgba(255,215,0,.1);color:#ffd700;border:1px solid #ffd700;}
.bug-tag.gray{background:rgba(139,148,158,.1);color:var(--text2);border:1px solid var(--border);}
.bug-tag.file{background:transparent;color:var(--text3);border:none;font-size:12px;padding:0;}
.bug-desc{font-size:14px;color:var(--text);flex:1;}
.bug-file-row{font-family:'Share Tech Mono',monospace;font-size:12px;color:var(--text3);
  padding:8px 0 4px;letter-spacing:1px;}
/* text lines */
.txt-line{font-size:14px;color:var(--text);margin-bottom:4px;}
@media(max-width:600px){h1{font-size:28px;}.char-grid{grid-template-columns:1fr;}.status-grid{grid-template-columns:1fr;}}
</style>
"""

FONTS = '<link href="https://fonts.googleapis.com/css2?family=Share+Tech+Mono&family=Rajdhani:wght@400;600;700&display=swap" rel="stylesheet">'

def render_bullets(items):
    if not items:
        return ''
    html = '<ul class="blist">'
    for item in items:
        if item.get('key'):
            html += f'<li><span class="bkey">{escape(item["key"])}</span><span>{escape(item["val"])}</span></li>'
        else:
            html += f'<li><span>{escape(item["val"])}</span></li>'
    html += '</ul>'
    return html

def render_flow(steps):
    if not steps:
        return ''
    html = '<div class="flow">'
    for idx, step in enumerate(steps):
        html += f'<div class="flow-step"><div class="flow-num">0{step["num"]}</div>{escape(step["text"])}</div>'
        if idx < len(steps) - 1:
            html += '<div class="flow-arrow">↓</div>'
    html += '</div>'
    return html

def render_code(lines):
    if not lines:
        return ''
    # Dedent
    min_indent = min((len(l) - len(l.lstrip())) for l in lines if l.strip())
    stripped = [l[min_indent:] for l in lines]
    return f'<div class="code">{escape(chr(10).join(stripped))}</div>'

def render_chars(items):
    html = '<div class="char-grid">'
    for c in items:
        html += f'''<div class="char-card">
  <div class="char-name">{escape(c["name"])}</div>
  <div class="char-passive-lbl">// passive</div>
  <div class="char-passive">{escape(c["passive"])}</div>
</div>'''
    html += '</div>'
    return html

def render_bugs(items):
    html = '<div class="bug-list">'
    for item in items:
        if item['tag'] == 'FILE':
            html += f'<div class="bug-file-row">// {escape(item["text"])}</div>'
        else:
            cls = tag_class(item['tag'])
            html += f'''<div class="bug-item">
  <span class="bug-tag {cls}">{escape(item["tag"])}</span>
  <span class="bug-desc">{escape(item["text"])}</span>
</div>'''
    html += '</div>'
    return html

def render_status(done_items, wip_items):
    html = '<div class="status-grid">'
    if done_items:
        html += '<div class="status-card"><div class="status-title done">// completed</div>'
        for it in done_items:
            html += f'<div class="status-item done">{escape(it["val"])}</div>'
        html += '</div>'
    if wip_items:
        html += '<div class="status-card"><div class="status-title wip">// in progress</div>'
        for it in wip_items:
            html += f'<div class="status-item wip">{escape(it["val"])}</div>'
        html += '</div>'
    html += '</div>'
    return html

def render_sub(sub, collected_status):
    t = sub.get('type', 'subheader')

    if t == 'subsection_marker':
        return f'<div class="ssm">// {escape(sub["title"])}</div>'

    if t == 'chars':
        return render_chars(sub.get('items', []))

    if t == 'bugs':
        return render_bugs(sub.get('items', []))

    if t in ('status_done', 'status_wip'):
        collected_status[t] = sub.get('items', [])
        return None  # handled later together

    # Generic subheader card
    html = '<div class="card">'
    if sub.get('title'):
        html += f'<div class="card-title">{escape(sub["title"])}</div>'

    for tl in sub.get('text_lines', []):
        html += f'<p class="txt-line">{escape(tl)}</p>'

    if sub.get('items'):
        html += render_bullets(sub['items'])

    if sub.get('code_lines'):
        html += render_code(sub['code_lines'])

    if sub.get('flow_steps'):
        html += render_flow(sub['flow_steps'])

    html += '</div>'
    return html

def render_doc(doc):
    # Title — split on first word for accent color
    title_words = doc['title'].split(' ', 1)
    title_html = f'<span>{escape(title_words[0])}</span>'
    if len(title_words) > 1:
        title_html += f' {escape(title_words[1])}'

    meta_html = ''
    for k, v in doc['meta'].items():
        meta_html += f'<div class="meta-row">{escape(k)}: {escape(v)}</div>'

    sections_html = ''
    for sec in doc['sections']:
        body = ''
        # Intro paragraphs
        for para in sec.get('intro', []):
            body += f'<p class="intro">{escape(para)}</p>'

        collected_status = {}
        rendered = []
        for sub in sec.get('content', []):
            r = render_sub(sub, collected_status)
            if r is not None:
                rendered.append(r)

        body += ''.join(rendered)

        # Render status grid if we collected done/wip
        if collected_status:
            body += render_status(
                collected_status.get('status_done', []),
                collected_status.get('status_wip', [])
            )

        sections_html += f'''
<div class="section">
  <div class="sec-hdr">
    <span class="sec-num">0{escape(sec["num"])}</span>
    <h2>{escape(sec["title"])}</h2>
    <div class="sec-line"></div>
  </div>
  {body}
</div>'''

    return f"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>{escape(doc['title'])}</title>
{FONTS}
{CSS}
</head>
<body>
<div class="page">
  <div class="hdr">
    <div class="hdr-tag">// project documentation</div>
    <h1>{title_html}</h1>
    <div class="subtitle">{escape(doc['subtitle'])}</div>
    {meta_html}
  </div>
  {sections_html}
</div>
</body>
</html>"""

# ---------------------------------------------------------------------------
# MAIN
# ---------------------------------------------------------------------------

def main():
    if len(sys.argv) < 2:
        print("Usage: python doc_converter.py <input.txt> [output.html]")
        sys.exit(1)

    input_path = sys.argv[1]
    if not os.path.exists(input_path):
        print(f"[ERROR] File not found: {input_path}")
        sys.exit(1)

    output_path = sys.argv[2] if len(sys.argv) > 2 else os.path.splitext(input_path)[0] + '.html'

    with open(input_path, 'r', encoding='utf-8') as f:
        text = f.read()

    print(f"[INFO] Parsing: {input_path}")
    doc = parse_txt(text)
    print(f"[INFO] Found {len(doc['sections'])} sections")

    html = render_doc(doc)

    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(html)

    print(f"[DONE] Output: {output_path}")

if __name__ == '__main__':
    main()
