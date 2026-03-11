PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE register_key_table(
    key_no INTEGER PRIMARY KEY AUTOINCREMENT,
    key_str_val CHAR(12) NOT NULL,
    key_ready INTEGER CHECK (key_ready IN (0,1)) NOT NULL
);
INSERT INTO register_key_table VALUES(1,'F98ER24S8UR3',0);
INSERT INTO register_key_table VALUES(2,'ZPZXH0DA1YOJ',0);
INSERT INTO register_key_table VALUES(3,'E8760XLSLS7E',0);
INSERT INTO register_key_table VALUES(4,'9TH4LPCV7UVH',0);
INSERT INTO register_key_table VALUES(5,'32X6K7VHLVZW',1);
INSERT INTO register_key_table VALUES(6,'ELOGAKEOEEOJ',1);
INSERT INTO register_key_table VALUES(7,'O78O47VUJXAK',1);
INSERT INTO register_key_table VALUES(8,'A68692YDCT3K',1);
INSERT INTO register_key_table VALUES(9,'57J6G4L8HEJG',1);
CREATE TABLE account_table (
    account_id VARCHAR(64) PRIMARY KEY,  -- Unique user identifier
    account_password VARCHAR(64) NOT NULL, 
    account_lvl INTEGER DEFAULT 0
);
INSERT INTO account_table VALUES('feint','b81e79006c48754188243d6130e5c46787e2096c0e97941bcce56490902e024a',2);
INSERT INTO account_table VALUES('belai101','cd0a600aa3f0478684667f1687e7cbfd816d93f385b4400a3ed532501a725456',0);
INSERT INTO account_table VALUES('huyen12','52bff3fcc133e3398ca69e56c66ab986df03a6ac4678fba916cfa17bc0b2633d',0);
INSERT INTO account_table VALUES('huyen13','52bff3fcc133e3398ca69e56c66ab986df03a6ac4678fba916cfa17bc0b2633d',0);
INSERT INTO account_table VALUES('belai102','52bff3fcc133e3398ca69e56c66ab986df03a6ac4678fba916cfa17bc0b2633d',0);
CREATE TABLE account_stats_table (
    account_id VARCHAR(64) NOT NULL,
    mon DOUBLE DEFAULT 0,
    souls DOUBLE DEFAULT 0,
    formmations INTEGER DEFAULT 0,
    CONSTRAINT fk_account FOREIGN KEY (account_id) REFERENCES account_table(account_id) ON DELETE CASCADE
);
INSERT INTO account_stats_table VALUES('feint',500.0,250.0,4);
INSERT INTO account_stats_table VALUES('belai101',100.0,150.0,4);
INSERT INTO account_stats_table VALUES('huyen12',172.0,160.0,4);
INSERT INTO account_stats_table VALUES('feint',500.0,250.0,4);
INSERT INTO account_stats_table VALUES('belai101',100.0,150.0,4);
INSERT INTO account_stats_table VALUES('huyen12',172.0,160.0,4);
INSERT INTO account_stats_table VALUES('huyen13',100.0,160.0,0);
INSERT INTO account_stats_table VALUES('belai102',100.0,150.0,0);
CREATE TABLE character_base_table (
    character_id VARCHAR(128) PRIMARY KEY, 
    character_name VARCHAR(128) NOT NULL,
    stats TEXT
);
INSERT INTO character_base_table VALUES('S_Reimu','Hakurei Reimu',replace('{\n    "ID": "S_Reimu",\n    "accurate": 0.8500000238418579,\n    "accurateScale": 0.03099999949336052,\n    "action": 0.0,\n    "agility": 10.0,\n    "animationPath": "./Assets/F_AObjects/reimu_tb.xml",\n    "critChance": 0.02500000037252903,\n    "deathDoorSurviveChance": 0.2800000011920929,\n    "dexterity": 11.0,\n    "evadeChance": 0.18000000715255737,\n    "evadeChanceScale": 0.023000000044703484,\n    "hp": 80.0,\n    "hpScale": 8.0,\n    "intelligence": 8.0,\n    "lastName": "Hakurei",\n    "level": 1,\n    "magicDef": 6.800000190734863,\n    "magicDefScale": 0.44999998807907104,\n    "magicDmg": 12.0,\n    "magicDmgScale": 1.2000000476837158,\n    "mana": 120.0,\n    "manaScale": 9.0,\n    "name": "Reimu",\n    "panelPath": "./Assets/TB_GUI/panels/reimu_panel.png",\n    "physicDef": 6.0,\n    "physicDefScale": 0.5,\n    "physicDmg": 14.0,\n    "physicDmgScale": 1.5,\n    "portraitPath": "./Assets/TB_GUI/faces/Reimu_face.png",\n    "price": 40,\n    "side": 1,\n    "sp": 0.0,\n    "spCap": 100.0,\n    "strength": 7.0,\n    "title": "Hakurei Miko",\n    "vitality": 6.0,\n    "wisdom": 8.0,\n    "xp": 0\n}','\n',char(10)));
INSERT INTO character_base_table VALUES('S_Marisa','Kirisame Marisa','');
INSERT INTO character_base_table VALUES('S_Yukari','Yakumo Yukari',replace('{\n    "ID": "S_Yukari",\n    "accurate": 0.8500000238418579,\n    "accurateScale": 0.03099999949336052,\n    "action": 0.0,\n    "agility": 5.0,\n    "animationPath": "./Assets/F_AObjects/yukari_tb.xml",\n    "critChance": 0.02500000037252903,\n    "deathDoorSurviveChance": 0.25999999046325684,\n    "dexterity": 7.0,\n    "evadeChance": 0.12999999523162842,\n    "evadeChanceScale": 0.02500000037252903,\n    "hp": 140.0,\n    "hpScale": 7.0,\n    "intelligence": 13.0,\n    "lastName": "Yakumo",\n    "level": 1,\n    "magicDef": 7.800000190734863,\n    "magicDefScale": 0.75,\n    "magicDmg": 14.0,\n    "magicDmgScale": 2.4000000953674316,\n    "mana": 150.0,\n    "manaScale": 10.0,\n    "name": "Yukari",\n    "panelPath": "./Assets/TB_GUI/panels/yukari_panel.png",\n    "physicDef": 14.0,\n    "physicDefScale": 0.6000000238418579,\n    "physicDmg": 7.0,\n    "physicDmgScale": 1.5,\n    "portraitPath": "./Assets/TB_GUI/faces/Yukari_face.png",\n    "price": 45,\n    "side": 1,\n    "sp": 0.0,\n    "spCap": 100.0,\n    "strength": 6.0,\n    "title": "Youkai of Boundaries",\n    "vitality": 10.0,\n    "wisdom": 15.0,\n    "xp": 0\n}','\n',char(10)));
INSERT INTO character_base_table VALUES('S_Patchouli','Patchouli Knowledge',replace('{\n    "ID": "S_Patchouli",\n    "accurate": 0.800000011920929,\n    "accurateScale": 0.03099999949336052,\n    "action": 0.0,\n    "agility": 6.0,\n    "animationPath": "./Assets/F_AObjects/patchouli_tb.xml",\n    "critChance": 0.02500000037252903,\n    "deathDoorSurviveChance": 0.25,\n    "dexterity": 6.0,\n    "evadeChance": 0.14000000059604645,\n    "evadeChanceScale": 0.02500000037252903,\n    "hp": 30.0,\n    "hpScale": 6.0,\n    "intelligence": 20.0,\n    "lastName": "Knowledge",\n    "level": 1,\n    "magicDef": 7.699999809265137,\n    "magicDefScale": 0.800000011920929,\n    "magicDmg": 17.0,\n    "magicDmgScale": 1.7000000476837158,\n    "mana": 250.0,\n    "manaScale": 12.0,\n    "name": "Patchouli",\n    "panelPath": "./Assets/TB_GUI/panels/patchouli_panel.png",\n    "physicDef": 3.0,\n    "physicDefScale": 0.20000000298023224,\n    "physicDmg": 4.0,\n    "physicDmgScale": 0.5,\n    "portraitPath": "./Assets/TB_GUI/faces/Patchouli_face.png",\n    "price": 40,\n    "side": 1,\n    "sp": 0.0,\n    "spCap": 100.0,\n    "strength": 3.0,\n    "title": "Unmoving Library",\n    "vitality": 4.0,\n    "wisdom": 19.0,\n    "xp": 0\n}','\n',char(10)));
INSERT INTO character_base_table VALUES('S_Meiling','Meiling Hong',replace('{\n    "ID": "S_Meiling",\n    "accurate": 0.8100000023841858,\n    "accurateScale": 0.03200000151991844,\n    "action": 0.0,\n    "agility": 9.0,\n    "animationPath": "./Assets/F_AObjects/meiling_tb.xml",\n    "critChance": 0.02199999988079071,\n    "deathDoorSurviveChance": 0.30000001192092896,\n    "dexterity": 11.0,\n    "evadeChance": 0.12999999523162842,\n    "evadeChanceScale": 0.028999999165534973,\n    "hp": 140.0,\n    "hpScale": 11.0,\n    "intelligence": 4.0,\n    "lastName": "Hong",\n    "level": 1,\n    "magicDef": 3.299999952316284,\n    "magicDefScale": 0.699999988079071,\n    "magicDmg": 8.0,\n    "magicDmgScale": 0.800000011920929,\n    "mana": 70.0,\n    "manaScale": 6.0,\n    "name": "Meiling",\n    "panelPath": "./Assets/TB_GUI/panels/meiling_panel.png",\n    "physicDef": 8.5,\n    "physicDefScale": 1.2000000476837158,\n    "physicDmg": 12.0,\n    "physicDmgScale": 1.7000000476837158,\n    "portraitPath": "./Assets/TB_GUI/faces/Meiling_face.png",\n    "price": 35,\n    "side": 1,\n    "sp": 0.0,\n    "spCap": 100.0,\n    "strength": 12.0,\n    "title": "Gatekeeper of Scarlet Devil Mansion",\n    "vitality": 14.0,\n    "wisdom": 5.0,\n    "xp": 0\n}','\n',char(10)));
CREATE TABLE player_character_table (
    player_character_id INTEGER PRIMARY KEY AUTOINCREMENT, 
    account_id VARCHAR(64) NOT NULL, 
    character_id VARCHAR(128) NOT NULL, 
    level INTEGER DEFAULT 1,
    exp INTEGER DEFAULT 0,
    stats TEXT NOT NULL, -- JSON storing all stats dynamically
    CONSTRAINT fk_account FOREIGN KEY (account_id) REFERENCES account_table(account_id) ON DELETE CASCADE,
    CONSTRAINT fk_character FOREIGN KEY (character_id) REFERENCES character_base_table(character_id) ON DELETE CASCADE
);

CREATE TABLE formation_table (
    formation_id INTEGER PRIMARY KEY AUTOINCREMENT,
    account_id VARCHAR(64) NOT NULL,
    formation_name VARCHAR(64) NOT NULL,
    formation_index INTEGER NOT NULL,
    CONSTRAINT uq_account_formation UNIQUE (account_id, formation_index),
    CONSTRAINT fk_account FOREIGN KEY (account_id)
        REFERENCES account_table(account_id)
        ON DELETE CASCADE
);

CREATE TABLE formation_info_table(
    account_id VARCHAR(64) NOT NULL,
    formation_index INTEGER NOT NULL,
    character_id VARCHAR(128) NOT NULL,
    slot_index TINYINT NOT NULL,
    row_pos TINYINT NOT NULL,
    col_pos TINYINT NOT NULL,
    CONSTRAINT fk_formation FOREIGN KEY (account_id, formation_index)
        REFERENCES formation_table(account_id, formation_index)
        ON DELETE CASCADE,
    CONSTRAINT fk_character FOREIGN KEY (character_id)
        REFERENCES player_character_table(character_id)
        ON DELETE CASCADE,
    CONSTRAINT uq_formation_character UNIQUE (account_id, formation_index,slot_index)
);

DELETE FROM sqlite_sequence;
INSERT INTO sqlite_sequence VALUES('register_key_table',9);
INSERT INTO sqlite_sequence VALUES('player_character_table',8);
INSERT INTO sqlite_sequence VALUES('formation_table',17);
COMMIT;
