-- Note for sqlite3 command
--
-- no variable supported, so I guess we use sqlite3 command

drop table if exists account_table;

create table account_table (
    account_no INTEGER primary key AUTOINCREMENT,
    account_id varchar(128) not null, -- account name, primary key
    account_password varchar(128) not null -- account password

);

create table account_stats (
    account_stat_id varchar(128) primary key, -- primary key
    mm_rate INTEGER, 
    gold DOUBLE, 
    account_id varchar(128) not null,
    CONSTRAINT fk_account FOREIGN KEY (account_id)
    REFERENCES account_table(account_id)

);

create table character_base_table (
    character_id varchar(128) primary key,
    character_name varchar(128) not null,
    character_last_name varchar(128) not null,
    character_title varchar(128),

);

create table character_table (
    character_id varchar(128) primary key, -- primary key
    character_name varchar(128) not null,
    character_last_name varchar(128) not null,
    character_title varchar(128)

);

create table account_own_character (
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



select "created tables :";
.tables

.print "todo, add the data insertion here !!! "

.output c:/data.sql
.dump account_table account_stats character_table account_own_character
.print "end ! o_O"