PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE register_key_table(
    key_no INTEGER PRIMARY key AUTOINCREMENT,
    key_str_val CHARACTER(12),
    key_ready BOOLEAN
);
INSERT INTO register_key_table VALUES(1,'F98ER24S8UR3',0);
INSERT INTO register_key_table VALUES(2,'ZPZXH0DA1YOJ',0);
INSERT INTO register_key_table VALUES(3,'E8760XLSLS7E',1);
INSERT INTO register_key_table VALUES(4,'9TH4LPCV7UVH',1);
INSERT INTO register_key_table VALUES(5,'32X6K7VHLVZW',1);
INSERT INTO register_key_table VALUES(6,'ELOGAKEOEEOJ',1);
INSERT INTO register_key_table VALUES(7,'O78O47VUJXAK',1);
INSERT INTO register_key_table VALUES(8,'A68692YDCT3K',1);
INSERT INTO register_key_table VALUES(9,'57J6G4L8HEJG',1);
CREATE TABLE account_table (
    account_no INTEGER primary key AUTOINCREMENT,
    account_id varchar(64) not null, -- account name, primary key
    account_password varchar(64) not null, -- account password
    account_lvl INTEGER DEFAULT 0 -- include admin ( for inquiry ) 

);
INSERT INTO account_table VALUES(7,'testdata','38df562ea277489ce6ae90f05dd3f955',0);
INSERT INTO account_table VALUES(8,'feint','95372b148c6f360dfa9bc283775a8036',2);
CREATE TABLE account_stats_table (
    account_stat_id varchar(64) primary key, -- primary key
    mon DOUBLE,
    soul DOUBLE, 
    account_id varchar(64) not null,
    CONSTRAINT fk_account FOREIGN KEY (account_id)
    REFERENCES account_table(account_id)

);
CREATE TABLE character_base_table (
    character_id varchar(128) primary key,
    character_name varchar(128) not null

);
CREATE TABLE character_existance_table(
    world_character_id varchar(128) PRIMARY KEY, 
    character_id varchar(128) not null,
    account_stat_id varchar(128) not null,
    character_props TEXT,
    CONSTRAINT fk_account_stat FOREIGN KEY (account_stat_id)
    REFERENCES account_stats_table(account_stat_id),
    CONSTRAINT fk_character FOREIGN KEY (character_id)
    REFERENCES character_base_table(character_id)
);
DELETE FROM sqlite_sequence;
INSERT INTO sqlite_sequence VALUES('account_table',8);
INSERT INTO sqlite_sequence VALUES('register_key_table',9);
COMMIT;
