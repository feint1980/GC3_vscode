
#ifndef _DATABASE_HANDLER_H_
#define _DATABASE_HANDLER_H_

#include <iostream>
#include <sqlite3.h>
#include <string>

class DataBaseHandler 
{

public : 

	~DataBaseHandler();	
	void loadDataBase(const std::string & databasePath);
	bool access_user_info(const std::string & id, const std::string & pw);

private:
	sqlite3 * m_db;
	const char* data = "Callback function called";

};




#endif




