#include "DataBaseHandler.h"


static int record_count;
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
    //  printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   std::cout << "argc is " << argc << " record_count is " << record_count << "\n";
   record_count = argc;
   printf("\n");
   return 0;
}


DataBaseHandler::~DataBaseHandler()
{
	sqlite3_close(m_db);

}

void DataBaseHandler::loadDataBase(const std::string & databasePath)
{
	int rc = sqlite3_open(databasePath.c_str(), & m_db);
	
	if(rc)
	{
	      //std::cout << "|=========================================|\n";
		std::cout << "|            Can't open database          |\n";
	}
	else
	{
		std::cout << "|        Load database successfully       |\n";
	}

}

bool DataBaseHandler::access_user_info(const std::string & id , const std::string & pw)
{
	record_count = 0;
	char * zErrMsg = 0;
	std::string sqlCMD = "select str_id from user_info where str_id = \"" + id + "\" and str_password = \"" + pw +"\";";
	
	int rc = sqlite3_exec(m_db, sqlCMD.c_str(), callback, (void*)data, &zErrMsg);
	
	if(rc != SQLITE_OK)
	{
		std::cout << "SQL query failed \n";
		sqlite3_free(zErrMsg);
	
	}
	{
		std::cout << "Query OK !!! \n";	
	}
	if(record_count ==1)
	{
		return true;
	}
	return false;
}


