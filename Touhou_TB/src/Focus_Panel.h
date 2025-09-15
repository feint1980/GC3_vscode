#ifndef _FOCUS_PANEL_H_
#define _FOCUS_PANEL_H_


#include "../../TGUI_theme/ThemeCreator.hpp"
#include <set>
#include <vector>


class Focus_Panel 
{
    public:
    Focus_Panel(tgui::Panel::Ptr * panel)
    {
        m_selfPanel = panel;
    }

    Focus_Panel(tgui::Gui * gui)
    {
        m_tgui = gui;
    }

    ~Focus_Panel() 
    {
        
    }

    void addLabel(tgui::Label::Ptr * label) 
    {
        if(label) 
        {
            if(m_labelSet.find(label) == m_labelSet.end())
            {
                m_labelSet.insert(label);
                m_labels.push_back(label);
            }
        }
    }

    void removeLabel(tgui::Label::Ptr * label)
    {
        if(label)
        {
            if(m_labelSet.find(label) != m_labelSet.end())
            {
                m_labelSet.erase(label);
            }
            for(int i = 0; i < m_labels.size(); i++)
            {
                if(m_labels[i] == label)
                {
                    std::swap(m_labels[i],m_labels.back());
                    m_labels.pop_back();
                }
            }
        }
    }

    tgui::Label::Ptr * getFirstLabel()
    {
        if(m_labels.size() > 0)
        {
            m_currentLabelIndex = 0;
            return m_labels[m_currentLabelIndex];
        } 
        return nullptr;
    }

    tgui::Label::Ptr * getNextLabel()
    {
        if(m_labels.size() > 1)
        {
            m_currentLabelIndex = (m_currentLabelIndex + 1) % m_labels.size();
            return m_labels[m_currentLabelIndex];
        } 
        else if (m_labels.size() == 1) 
        {
            m_currentLabelIndex = 0;
            return m_labels[m_currentLabelIndex];
        }
        return nullptr;
    }
    tgui::Label::Ptr * getPreviousLabel()
    {
        if(m_labels.size() > 1)
        {
            m_currentLabelIndex = (m_currentLabelIndex - 1 + m_labels.size()) % m_labels.size();
            return m_labels[m_currentLabelIndex];
        } 
        else if (m_labels.size() == 1) 
        {
            m_currentLabelIndex = 0;
            return m_labels[m_currentLabelIndex];
        }
        
        
        return nullptr;
    }

    int getType() 
    {
        int tType = 0;
        if(m_selfPanel)
        {
            tType |= 1;
        }
        if(m_tgui)
        {
            tType |= 2;
        }
        return tType;
    }

    private:

    tgui::Panel::Ptr * m_selfPanel = nullptr;
    tgui::Gui * m_tgui = nullptr;

    std::set<tgui::Label::Ptr *> m_labelSet;
    std::vector<tgui::Label::Ptr *> m_labels;
    int m_currentLabelIndex = -1;

};


#endif