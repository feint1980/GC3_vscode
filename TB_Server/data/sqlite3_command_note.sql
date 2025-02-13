-- Note for sqlite3 command
--
-- no variable supported, so I guess we use sqlite3 command

drop table if exists account_table;


create table register_key_table(
    key_no INTEGER PRIMARY key AUTOINCREMENT,
    key_str_val CHARACTER(12),
    key_ready BOOLEAN
);

create table account_table (
    account_no INTEGER primary key AUTOINCREMENT,
    account_id varchar(64) not null, -- account name, primary key
    account_password varchar(64) not null, -- account password
    account_lvl INTEGER DEFAULT 0 -- include admin ( for inquiry ) 

);

create table account_stats_table (
    account_stat_id varchar(64) primary key, -- primary key
    gold DOUBLE, 
    account_id varchar(64) not null,
    CONSTRAINT fk_account FOREIGN KEY (account_id)
    REFERENCES account_table(account_id)

);

create table character_base_table (
    character_id varchar(128) primary key,
    character_name varchar(128) not null,
    character_title varchar(128)

);

create table character_existance_table(
    world_character_id varchar(128) PRIMARY KEY, 
    character_id varchar(128) not null,
    account_stat_id varchar(128) not null,
    character_props TEXT,
    CONSTRAINT fk_account_stat FOREIGN KEY (account_stat_id)
    REFERENCES account_stats_table(account_stat_id),
    CONSTRAINT fk_character FOREIGN KEY (character_id)
    REFERENCES character_base_table(character_id)
);


select "created tables :";
.tables

.print "todo, add the data insertion here !!! "

.output c:/data.sql
.dump account_table account_stats character_table account_own_character
.print "end ! o_O"


--- insert phase

insert into account_table(account_id,account_password,account_lvl) values ('feint','ok',2);
insert into account_table(account_id,account_password,account_lvl) values ('belai','okk',1);
insert into account_table(account_id,account_password) values ('chamas','123');