-- Note for sqlite3 command
--
-- no variable supported, so I guess we use sqlite3 command

drop table if exists account_table;

create table account_table (
    account_no INTEGER primary key AUTOINCREMENT,
    account_name varchar(128) not null, -- account name, primary key
    account_password varchar(128) not null -- account password

);

