#pragma once
#include <sqlite3.h>
#include <vector>
#include <string>



	class DataManager
	{
	public:
		DataManager();

		static DataManager *Instance()
		{
			if (p_Instance == 0)
			{
				p_Instance = new DataManager;
				return p_Instance;
			}
			return p_Instance;
		}
		~DataManager();
		void init();
		void selectData(char *TABLE, char * COL, int (*cb)(void * , int , char ** , char **),  char * condition = "");
		void insertData(char * TABLE, char * COL, char * value);
		void deleteData(char * TABLE, char * condition = "");
		void updateData(char * TABLE, char * COL, char * newValue, char * condition = "");
		void getTableData(char * query, std::vector<std::string> & datatable);
		std::string getPlayerID() const { return m_playerID; }
		void clearData();
		void setPlayerID(std::string ID);
		 std::string getAccountID() { return m_appliedData; }
		std::vector<std::string> account_currency;
		
		void applyData(std::string target);

		
	

	private:

		std::string m_appliedData;

		std::string account_id;
		std::string m_playerID = "";
		static DataManager *p_Instance;
		sqlite3 * m_db;
	};


