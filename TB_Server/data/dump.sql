PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE account_table (
    account_no INTEGER primary key AUTOINCREMENT,
    account_id varchar(128) not null, -- account name, primary key
    account_password varchar(128) not null -- account password

);
CREATE TABLE account_stats (
    account_stat_id varchar(128) primary key, -- primary key
    mm_rate INTEGER, 
    gold DOUBLE, 
    account_id varchar(128) not null,
    CONSTRAINT fk_account FOREIGN KEY (account_id)
    REFERENCES account_table(account_id)

);
CREATE TABLE character_table (
    character_id varchar(128) primary key, -- primary key
    character_name varchar(128) not null,
    character_last_name varchar(128) not null,
    character_titla varchar(128),
    character_str INTEGER,
    character_vit INTEGER,
    character_dex INTEGER,
    character_agi INTEGER,
    character_int INTEGER,
    character_wis INTEGER
);
CREATE TABLE account_own_character (
    count_id INTEGER primary key AUTOINCREMENT,
    additional_str INTEGER,
    additional_vit INTEGER,
    additional_dex INTEGER,
    additional_agi INTEGER,
    additional_int INTEGER,
    additional_wis INTEGER,
    character_level INTEGER,
    character_exp DOUBLE,
    account_stat_id varchar(128) not null,
    character_id varchar(128) not null,
    CONSTRAINT fk_account_stat FOREIGN KEY (account_stat_id)
    REFERENCES account_stats(account_stat_id),
    CONSTRAINT fk_character FOREIGN KEY (character_id)
    REFERENCES character_table(character_id)
    
);
DELETE FROM sqlite_sequence;
COMMIT;
