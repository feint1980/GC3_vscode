PRAGMA foreign_keys=ON;
BEGIN TRANSACTION;


-- Register Key Table
CREATE TABLE register_key_table(
    key_no INTEGER PRIMARY KEY AUTOINCREMENT,
    key_str_val CHAR(12) NOT NULL,
    key_ready INTEGER CHECK (key_ready IN (0,1)) NOT NULL
);

INSERT INTO register_key_table VALUES(1,'F98ER24S8UR3',1);
INSERT INTO register_key_table VALUES(2,'ZPZXH0DA1YOJ',1);
INSERT INTO register_key_table VALUES(3,'E8760XLSLS7E',1);
INSERT INTO register_key_table VALUES(4,'9TH4LPCV7UVH',1);
INSERT INTO register_key_table VALUES(5,'32X6K7VHLVZW',1);
INSERT INTO register_key_table VALUES(6,'ELOGAKEOEEOJ',1);
INSERT INTO register_key_table VALUES(7,'O78O47VUJXAK',1);
INSERT INTO register_key_table VALUES(8,'A68692YDCT3K',1);
INSERT INTO register_key_table VALUES(9,'57J6G4L8HEJG',1);

-- Account Table
CREATE TABLE account_table (
    account_id VARCHAR(64) PRIMARY KEY,  -- Unique user identifier
    account_password VARCHAR(64) NOT NULL, 
    account_lvl INTEGER DEFAULT 0
);

INSERT INTO account_table VALUES('feint','b81e79006c48754188243d6130e5c46787e2096c0e97941bcce56490902e024a',2);
-- Player Stats (Mon, Souls)
CREATE TABLE account_stats_table (
    account_id VARCHAR(64) NOT NULL,
    mon DOUBLE DEFAULT 0,
    souls DOUBLE DEFAULT 0,
    CONSTRAINT fk_account FOREIGN KEY (account_id) REFERENCES account_table(account_id) ON DELETE CASCADE
);


INSERT INTO account_stats_table VALUES('feint',500,25);
-- Base Character Table (Preset Characters)
CREATE TABLE character_base_table (
    character_id VARCHAR(128) PRIMARY KEY, 
    character_name VARCHAR(128) NOT NULL
);

INSERT INTO character_base_table VALUES('T_REIMU','Hakurei Reimu');
INSERT INTO character_base_table VALUES('T_MARISA','Kirisame Marisa');
INSERT INTO character_base_table VALUES('T_YUKARI','Yakumo Yukari');
INSERT INTO character_base_table VALUES('T_PATCHY','Patchouli Knowledge');

-- Player-Specific Characters (JSON-Based Stats)
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
-- DELETE FROM sqlite_sequence;
-- INSERT INTO sqlite_sequence VALUES('account_table',9);
-- INSERT INTO sqlite_sequence VALUES('register_key_table',9);
COMMIT;