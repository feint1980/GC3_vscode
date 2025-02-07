PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE account_table (
    account_no INTEGER primary key AUTOINCREMENT,
    account_id varchar(128) not null, -- account name, primary key
    account_password varchar(128) not null -- account password

);
INSERT INTO account_table VALUES(1,'feint','ok');
CREATE TABLE account_stats_table (
    account_stat_id varchar(128) primary key, -- primary key
    gold DOUBLE, 
    account_id varchar(128) not null,
    CONSTRAINT fk_account FOREIGN KEY (account_id)
    REFERENCES account_table(account_id)

);
CREATE TABLE character_base_table (
    character_id varchar(128) primary key,
    character_name varchar(128) not null,
    character_last_name varchar(128) not null,
    character_title varchar(128)

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
INSERT INTO sqlite_sequence VALUES('account_table',1);
COMMIT;
