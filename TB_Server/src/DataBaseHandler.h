
#ifndef _DATABASE_HANDLER_H_
#define _DATABASE_HANDLER_H_

#include <iostream>
// #include <sqlite3ext.h>
#include <sqlite3.h>

#include <string>

class DataBaseHandler 
{

public : 

	~DataBaseHandler();	
	void loadDataBase(const std::string & databasePath);
	sqlite3 * getDatabase() { return m_db; }
private:
	sqlite3 * m_db;
	const char* data = "Callback function called";
};
#endif




