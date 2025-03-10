PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE register_key_table(
    key_no INTEGER PRIMARY key AUTOINCREMENT,
    key_str_val CHARACTER(12),
    key_ready BOOLEAN
);
INSERT INTO register_key_table VALUES(1,'F98ER24S8UR3',0);
INSERT INTO register_key_table VALUES(2,'ZPZXH0DA1YOJ',0);
INSERT INTO register_key_table VALUES(3,'E8760XLSLS7E',0);
INSERT INTO register_key_table VALUES(4,'9TH4LPCV7UVH',0);
INSERT INTO register_key_table VALUES(5,'32X6K7VHLVZW',1);
INSERT INTO register_key_table VALUES(6,'ELOGAKEOEEOJ',0);
CREATE TABLE account_table (
    account_no INTEGER primary key AUTOINCREMENT,
    account_id varchar(64) not null, -- account name, primary key
    account_password varchar(64) not null, -- account password
    account_lvl INTEGER DEFAULT 0 -- include admin ( for inquiry ) 

);
INSERT INTO account_table VALUES(1,'feint','ok',2);
INSERT INTO account_table VALUES(2,'belai','okk',1);
INSERT INTO account_table VALUES(3,'chamas','123',0);
INSERT INTO account_table VALUES(4,'hoang','123',0);
INSERT INTO account_table VALUES(5,'test1234','123456',0);
CREATE TABLE account_stats_table (
    account_stat_id varchar(64) primary key, -- primary key
    gold DOUBLE, 
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
INSERT INTO sqlite_sequence VALUES('account_table',5);
INSERT INTO sqlite_sequence VALUES('register_key_table',6);
COMMIT;
