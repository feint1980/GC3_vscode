#include "DataBaseHandler.h"

static int record_count;
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	// uncomment for debug
	// for(i = 0; i<argc; i++) {
	// 	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	// }
	record_count = argc;
	// printf("\n");
	return 0;
}

DataBaseHandler::~DataBaseHandler()
{
	sqlite3_close(m_db);
}

void DataBaseHandler::loadDataBase(const std::string & databasePath)
{
	int rc = sqlite3_open(databasePath.c_str(), & m_db);
	// WAL mode
	sqlite3_exec(m_db, "PRAGMA journal_mode = WAL;", NULL, NULL, NULL);
	if(rc)
	{
		std::cout << "|            Can't open database          |\n";
	}
	else
	{
		std::cout << "|        Load database successfully       |\n";
	}
}
