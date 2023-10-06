#include "DataManager.h"
#include <iostream>
#include <string>


	DataManager *DataManager::p_Instance = 0;

	DataManager::DataManager()
	{
	}


	DataManager::~DataManager()
	{
	}



	void DataManager::init()
	{
		int rc;
		rc = sqlite3_open("Data/data.db", &m_db);
		if (rc)
		{
			std::cout << "some sheet";
		}
		else
		{
			
		}
	}

	void DataManager::selectData(char *TABLE, char * COL, int(*cb)(void *, int, char **, char ** ), char * condition /*= ""*/)
	{
		std::string sql = "SELECT ";
		sql.append(COL);
		sql.append(" FROM ");
		sql.append(TABLE);
		if (condition != "")
		{
			sql.append(" WHERE ");
			sql.append(condition);
		}
		char * errMSG;
		char * data = "so he he ";
	
		int rc;
		rc = sqlite3_exec(m_db, sql.c_str(), cb,(void *) data ,&errMSG);
		if (rc != SQLITE_OK)
		{
			std::cout << "some shits happened " ;
		}

		sqlite3_close(m_db);
	
		


	}

	void DataManager::insertData(char * TABLE, char * COL, char * value /* remember the ' ' man */)
	{
	
		sqlite3_open("Data/data.db", &m_db);
		std::string sql = "INSERT INTO ";
		sql.append(TABLE);
		sql.append(" (");
		sql.append(COL);
		sql.append(") ");
		sql.append("VALUES (" );
		sql.append(value);
		sql.append(") ");

	
		char * errorMSG = "LOL wot";
		int rc;

		rc = sqlite3_exec(m_db, sql.c_str(), 0, 0, &errorMSG);
		if (rc == SQLITE_OK)
		{
			//std::cout << "fine";
		}
		else
		{
			//std::cout << sql << " not fine" << errorMSG;
		}
		sqlite3_close(m_db);

	}

	void DataManager::deleteData(char * TABLE, char * condition/*= ""*/)
	{
		std::string sql = "DELETE FROM ";
		sql.append(TABLE);
		
	
		if (condition != "")
		{
			sql.append(" WHERE ");
			sql.append(condition);
			
		}
		char * errorMSG = "LOL wot";
		int rc;
		
		rc = sqlite3_exec(m_db, sql.c_str(), 0, 0, &errorMSG);
		
	}

	void DataManager::updateData(char * TABLE, char * COL, char * newValue, char * condition /*= ""*/)
	{
		std::string sql = "UPDATE ";
		sql.append(TABLE);
		sql.append(" set ");
		sql.append(COL);
		sql.append(" = ");
		sql.append(newValue);
		if (condition != "")
		{
			sql.append(" WHERE ");
			sql.append(condition);
		}

		char * errorMSG = "LOL wot";
		int rc;
		

		rc = sqlite3_exec(m_db, sql.c_str(), 0, 0, &errorMSG);
	}

	void DataManager::getTableData(char * query, std::vector<std::string> & datatable)
	{
		sqlite3_stmt *statement;
		sqlite3 * db;
		int rc;
		if (datatable.size() > 0)
		{
			datatable.clear();
		}

		rc = sqlite3_open("Data/data.db", &db);
		if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK)
		{
			int ctotal = sqlite3_column_count(statement);
			int res = 0;

			while (1)
			{
				res = sqlite3_step(statement);

				if (res == SQLITE_ROW)
				{
					for (int i = 0; i < ctotal; i++)
					{
						datatable.push_back((char*)sqlite3_column_text(statement, i));

					}

				}

				if (res == SQLITE_DONE || res == SQLITE_ERROR)
				{

					break;
				}
			}
		}
		else
		{
			std::cout << " sum sheets happended ";
		}
	}

	void DataManager::clearData()
	{
		account_id.clear();
	}

	void DataManager::setPlayerID(std::string ID)
	{
		m_playerID = ID;
	}


	 void DataManager::applyData(std::string target)
	{
		 m_appliedData = account_id;
		
	}



