#include "ServerScriptingManager.h"


// MARK: lua section

static const std::string KEY_TABLE = "register_key_table";
static const std::string ACCOUNT_TABLE = "account_table";
static const std::string ACCOUNT_STATS_TABLE = "account_stats_table";
static const std::string CHARACTER_BASE_TABLE = "character_base_table";
static const std::string CHARACTER_EXISTANCE_TABLE = "character_existance_table";

static const std::string INSERT = "insert into";

std::vector<unsigned char> salt = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};  // password salt 

std::vector<unsigned char> hashPasswordPBKDF2(const std::string& password, const std::vector<unsigned char>& salt, int iterations = 1000) {
    BCRYPT_ALG_HANDLE hAlgorithm;
    DWORD keyLength = 32;  // 256-bit output

    if (BCryptOpenAlgorithmProvider(&hAlgorithm, BCRYPT_SHA256_ALGORITHM, NULL, BCRYPT_ALG_HANDLE_HMAC_FLAG) != 0) {
        throw std::runtime_error("Failed to open SHA-256 HMAC provider.");
    }

    std::vector<unsigned char> derivedKey(keyLength);
    if (BCryptDeriveKeyPBKDF2(hAlgorithm, (PUCHAR)password.data(), password.size(), (PUCHAR)salt.data(), salt.size(), iterations, derivedKey.data(), keyLength, 0) != 0) {
        BCryptCloseAlgorithmProvider(hAlgorithm, 0);
        throw std::runtime_error("Failed to derive key.");
    }

    BCryptCloseAlgorithmProvider(hAlgorithm, 0);
    return derivedKey;
}


static int serverScriptingCallback(void *NotUsed, int argc, char **argv, char **azColName)
{

    std::cout << "serverScriptingCallback \n";
	

    for(int i = 0 ; i < m_response.data.size() ; i++)
    {
        m_response.data[i].clear();
    }
    m_response.data.clear();

    for(int i = 0; i<m_response.columnNames.size(); i++)
    {
        m_response.columnNames[i].clear();
    }

	for(int i = 0; i<argc; i++) {
		//printf("%s : %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        // std::cout << "index i " << i << "\n";
        lua_getglobal(shared_luaState, "AddColData");
        if (lua_isfunction(shared_luaState, -1))
        {
            std::string colName = azColName[i];
            std::string value = "NULL";
            if (argv[i])
            {
                value = argv[i];
            }
            m_response.columnNames.push_back(colName);
            m_response.data.push_back(value);
            lua_pushstring(shared_luaState, colName.c_str());
            lua_pushstring(shared_luaState, value.c_str());
            if (!LuaManager::Instance()->checkLua(shared_luaState, lua_pcall(shared_luaState, 2, 1, 0)))
            {
                std::cout << "call AddColData failed \n";
            }
        }

	}
	m_response.recordCount = argc;
	printf("\n");
	return 0;
}




std::string genKey(int numberOfRandom)
{
    char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int size = sizeof(a) - 1;
    char p[numberOfRandom + 1];
    for (int i = 0; i < numberOfRandom; i++)
    {
        p[i] = a[rand() % size];
    }
    p[numberOfRandom] = '\0';

    return std::string(p);
}

int lua_SQLCreateStatement(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_SQLCreateStatement) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        std::string query = lua_tostring(L,2);

        sqlite3_stmt * stmt;

        sqlite3_prepare_v2(host->getDB(), query.c_str(),-1, &stmt, nullptr);

        lua_pushlightuserdata(L, stmt);
        return 1;
    }
}


int lua_Packet_getGUID(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Packet_getGUID) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        RakNet::Packet * packet = static_cast<RakNet::Packet*>(lua_touserdata(L, 1));
        lua_pushstring(L, packet->guid.ToString());
        return 1;
    }
}

int lua_SQLBindStatement(lua_State * L)
{
    if (lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_SQLBindStatement) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {

        sqlite3_stmt* stmt =  static_cast<sqlite3_stmt*>(lua_touserdata(L, 1));
        int index = lua_tointeger(L,2);
        std::string val = lua_tostring(L,3);

        std::cout << "lua_SQLBindStatement called corrct \n" ;

        std::cout << "binding index " << index << " with value " << val << "\n";
        int rc = sqlite3_bind_text(stmt, index, val.c_str(), -1, SQLITE_TRANSIENT);
        // sqlite3_bind
        
        char* expanded = sqlite3_expanded_sql(stmt);
        if (expanded) {
            std::cout << "lua_SQLBindStatement Query: " << expanded << std::endl;
            sqlite3_free(expanded);  // Must free memory!
        }

        std::cout << "return values is  " << rc << "\n"; 

        return 0;
    }
}

int lua_SQLStepStatement(lua_State * L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_SQLStepStatement) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        sqlite3_stmt* stmt =  static_cast<sqlite3_stmt*>(lua_touserdata(L, 2));

        
        char* expanded = sqlite3_expanded_sql(stmt);
        if (expanded) {
            std::cout << "Expanded Query: " << expanded << std::endl;
            sqlite3_free(expanded);  // Must free memory!
        }
        int rc = sqlite3_step(stmt);
        lua_pushinteger(L, rc);
        return 1;
        
    }
    return 0;
}

int lua_SQLGetResultColumnCount(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_SQLGetResultColumnCount) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }   
    else
    {
        sqlite3_stmt* stmt =  static_cast<sqlite3_stmt*>(lua_touserdata(L, 1));
        int rc = sqlite3_column_count(stmt);
        lua_pushinteger(L, rc);
        return 1;
    }
    return 0;
}

int lua_SQLGetResultInt(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_SQLGetResultInt) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }   
    else
    {
        sqlite3_stmt* stmt =  static_cast<sqlite3_stmt*>(lua_touserdata(L, 1));
        int index = lua_tointeger(L,2);
        int rc = sqlite3_column_int(stmt, index);
        lua_pushinteger(L, rc);
        return 1;
    }
    return 0;
}

int lua_SQLGetResultString(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_SQLGetResultString) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }   
    else
    {
        sqlite3_stmt* stmt =  static_cast<sqlite3_stmt*>(lua_touserdata(L, 1));
        int index = lua_tointeger(L,2);
        const char* rc = (const char*)sqlite3_column_text(stmt, index);
        lua_pushstring(L, rc);
        return 1;
    }
    return 0;
}

int lua_SQLFinalizeStmt(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_SQLFinalizeStmt) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }   
    else
    {
        sqlite3_stmt* stmt =  static_cast<sqlite3_stmt*>(lua_touserdata(L, 1));
        sqlite3_finalize(stmt);
        return 0;
    }
    return 0;
}


int lua_GenKey(lua_State * L)
{
    if (lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_GenKey) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        int numberOfRandom = lua_tointeger(L, 1);
        std::string key = genKey(numberOfRandom);
        std::cout << "c++ side: key: " << key << "\n";
        lua_pushstring(L, key.c_str());
    }

    return 1;
}

int lua_GetQueryResults(lua_State * L)
{
    if (lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_GetQueryResults) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        int resultCode = m_response.rc;
        int recordCount = m_response.recordCount;

        
        lua_pushinteger(L, resultCode);
        lua_pushinteger(L, recordCount);
       // lua_pushstring(L, result.c_str());

    }
    return 3;
}

int lua_DoQuery(lua_State * L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_DoQuery) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        std::string queryCmd = lua_tostring(L, 2);

        host->doQuery(queryCmd);
        return 0;
    }

    return 0;
}

int lua_DoQuerySTMT(lua_State * L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_DoQuerySTMT) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        sqlite3_stmt * stmt = static_cast<sqlite3_stmt *>(lua_touserdata(L,2));
        // std::string queryCmd = lua_tostring(L, 2);

        host->doQuery(stmt);
        return 0;
    }

}

int lua_getEncryptedPW(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_getEncryptedPW) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        std::string msg = lua_tostring(L, 2);
        std::string result = host->getEncryptPW(msg);
        lua_pushstring(L, result.c_str());
        return 1;
    }
    return 0;
}

int lua_SendToClient(lua_State * L)
{
    // std::cout << "lua_SendToClient called \n";
    if (lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_SendToClient) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * clientId = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 2));
        std::string msg = lua_tostring(L, 3);
        //std::cout << "msg send is |" << msg << "|\n"; 
       // msg += "\0";
        host->sendData(*clientId, msg);
        // host->sendToClient(clientId, requestCode);
        return 0;
    }

    return 0;
}

int lua_Packet_getData(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_Packet_getData) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        RakNet::Packet * p = static_cast<RakNet::Packet*>(lua_touserdata(L, 2));
        std::string msg = host->getMegFromPackget(p);

        lua_pushstring(L, msg.c_str());
        return 1;
    }
}

int lua_Packet_getIP(lua_State * L)
{

    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Packet_getIP) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        RakNet::Packet * p = static_cast<RakNet::Packet*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * clientId = &p->systemAddress;
        // this may cause memory leak in future or idk, just test
        //clientId = new RakNet::SystemAddress(*clientId);

        lua_pushlightuserdata(L,clientId);
        return 1;
    }
}

int lua_Packet_extract(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Packet_getIP) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        RakNet::Packet * p = static_cast<RakNet::Packet*>(lua_touserdata(L, 1));
        std::string msg((const char *)p->data);
        RakNet::SystemAddress * clientId = &p->systemAddress;

        lua_pushstring(L, msg.c_str());
        lua_pushlightuserdata(L,clientId);
        
        return 2;
    }
    return -1;

}


ServerScriptingManager::ServerScriptingManager()
{

}
ServerScriptingManager::~ServerScriptingManager()
{

}


void ServerScriptingManager::update(float deltaTime)
{

}


std::string ServerScriptingManager::getMegFromPackget(RakNet::Packet *p)
{
    //p->systemAddress
    //p->systemAddress

    // std::string retVal = "";

    unsigned char iv[AES_IV_SIZE];
    for(int i = 0 ; i < AES_IV_SIZE ; i++)
    {
        iv[i] = p->data[(p->length -1) - (AES_IV_SIZE - i)]; 
    }



    std::vector<unsigned char> tMsg;
    for(int i = 0 ;i < (p->length -1) - AES_IV_SIZE; i++)
    {
        tMsg.push_back(p->data[i]);
    }

    // retVal =  m_cryptor.decrypt(tMsg, iv);

    return m_cryptor.decrypt(tMsg, iv);;

}

uint32_t ServerScriptingManager::sendData(const RakNet::SystemAddress & target, const std::string & data)
{
    
    // encrypt 
    
    unsigned char iv[AES_IV_SIZE] = {};
    m_cryptor.generateRandomIV(iv);
    // std::string tData = m_cryptor.getStringFromEncrypt(m_cryptor.encrypt(data,iv));

    auto tData = m_cryptor.encrypt(data,iv);

    for(int i = 0 ; i < AES_IV_SIZE;i++)
    {
        tData.push_back(iv[i]);
    }

    std::string sendStr;
    for(int i = 0 ; i < tData.size() ; i++)
    {
        sendStr.push_back((tData[i]));
    } 

    m_server->Send(sendStr.c_str(), sendStr.size() + 1, HIGH_PRIORITY, RELIABLE_SEQUENCED,12, target,false);

    // free iv 

    return 0;
}

unsigned int ServerScriptingManager::handleCommon(RakNet::Packet *p)
{
    unsigned char packetIdentifier = GetPacketIdentifier(p);

    std::cout << "handleCommon called #########" << (int)packetIdentifier << "#############\n";
    lua_getglobal(m_script, "HandleCommon");
    if (lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this); // host

        lua_pushlightuserdata(m_script, p);

        lua_pushnumber(m_script, packetIdentifier);

        // lua_pushlightuserdata(m_script, entity->getTargetSlot());

        if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 3, 1, 0)))
        {
            std::cout << "call HandleMessage failed \n";
        }
    }

    return 666;
}

ClientRequestCode ServerScriptingManager::handleCommand(RakNet::Packet *p)
{
    PacketCode requestCode = getSpecialRequestCode(p);
    // send relay data to lua to process
    std::string msg = getMegFromPackget(p);

    lua_getglobal(m_script, "HandleMessage");
    if (lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this); // host

        //std::cout << "Issue next task pointer " << object << "\n";

        lua_pushlightuserdata(m_script, p);
        //lua_pushlightuserdata(m_script, m_guiHandler);

        lua_pushnumber(m_script, requestCode);

        // lua_pushlightuserdata(m_script, entity->getTargetSlot());

        if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 3, 1, 0)))
        {
            std::cout << "call HandleMessage failed \n";
        }
    }

    // switch (requestCode)
    // {
    //     case PacketCode::LOGIN:
    //     {
    //         std::cout << "Login request found !!!\n";
    //         // todo : verify login
    //         std::string cData((const char*) p->data);
            
    //         return ClientRequestCode::Login;
    //     }
    //     break;
    //     default :
    //         return ClientRequestCode::Client_Invalid;
    //     break;
    // }
    return ClientRequestCode::Client_Invalid;
}

bool ServerScriptingManager::doQuery(const std::string & queryCmd)
{
    char * zErrMsg = 0;
    m_response.rc = sqlite3_exec(m_dbh->getDatabase(), queryCmd.c_str(), serverScriptingCallback, (void*)m_response.rawData, &zErrMsg);

    if(m_response.rc != SQLITE_OK)
    {
        //std::cout << "ServerScriptingManager doQuery failed: " << zErrMsg << "\n";
        //std::cout << "The query tried to be: " << queryCmd << "\n";
        sqlite3_free(zErrMsg);
        return false;
    }
    else
    {
        //std::cout << "ServerScriptingManager doQuery OK! , check the response\n";
        return true;
    }
    return false;
}


bool ServerScriptingManager::doQuery(sqlite3_stmt * stmt)
{

    // std::string queryCmd =  sqlite3_sql(stmt);

    // std::cout <<" doquery stmt called |" << queryCmd << "|\n"; 
    char * zErrMsg = 0;

    std::cout << "print start \n";

    // sqlite3_bind_text(stmt, 1, "feint",-1, SQLITE_STATIC);
    // sqlite3_bind_text(stmt, 2, "ok", -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int columnCount = sqlite3_column_count(stmt);
        for(int i = 0 ;i < columnCount ; i++)
        {
            std::cout << sqlite3_column_name(stmt, i) << ": "
            << sqlite3_column_text(stmt, i) << std::endl;

            lua_getglobal(shared_luaState, "AddColData");
            if (lua_isfunction(shared_luaState, -1))
            {
                std::string colName = sqlite3_column_name(stmt, i);
                std::string value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            
                m_response.columnNames.push_back(colName);
                m_response.data.push_back(value);
                lua_pushstring(shared_luaState, colName.c_str());
                lua_pushstring(shared_luaState, value.c_str());
                if (!LuaManager::Instance()->checkLua(shared_luaState, lua_pcall(shared_luaState, 2, 1, 0)))
                {
                    std::cout << "call AddColData failed \n";
                }
            }

        }

        /* code */
    }


    std::cout << "print end \n";
    
    return true;
    // m_response.rc = sqlite3_exec(m_dbh->getDatabase(), queryCmd.c_str(), serverScriptingCallback, (void*)m_response.rawData, &zErrMsg);

    // if(m_response.rc != SQLITE_OK)
    // {
    //     //std::cout << "ServerScriptingManager doQuery failed: " << zErrMsg << "\n";
    //     //std::cout << "The query tried to be: " << queryCmd << "\n";
    //     sqlite3_free(zErrMsg);
    //     return false;
    // }
    // else
    // {
    //     //std::cout << "ServerScriptingManager doQuery OK! , check the response\n";
    //     return true;
    // }
    // return false;
}

void ServerScriptingManager::init(RakNet::RakPeerInterface * server,DataBaseHandler * dbh)
{
    srand( (unsigned)time(NULL) );

    std::cout << "|=========================================|\n";
    std::cout << "|     Init Server Scripting Manager       |\n";
    m_server = server;
    m_dbh = dbh;
    std::cout << "|     Init Server Scripting Manager OK    |\n";
    std::cout << "|=========================================|\n";

    m_script = luaL_newstate();

    luaL_openlibs(m_script);

    // register lua functions
    

    lua_register(m_script, "cppGetQueryResults", lua_GetQueryResults);
    lua_register(m_script, "cppGenKey", lua_GenKey);
    lua_register(m_script, "cppSendToClient", lua_SendToClient);

    // Sqlite 
    lua_register(m_script, "cppSqlite_CreateStatement",lua_SQLCreateStatement );
    lua_register(m_script, "cppSqlite_BindStatement", lua_SQLBindStatement);
    lua_register(m_script, "cppDoQuery", lua_DoQuery);
    lua_register(m_script, "cppDoQuerySTMT", lua_DoQuerySTMT);
    lua_register(m_script, "cppSqlite_StepStatement", lua_SQLStepStatement);
    lua_register(m_script, "cppSqlite_GetResultColumnCount", lua_SQLGetResultColumnCount);
    lua_register(m_script, "cppSqlite_gettResultInt", lua_SQLGetResultInt);
    lua_register(m_script, "cppSqlite_gettResultString", lua_SQLGetResultString);
    lua_register(m_script, "cppSqlite_finalizeStmt", lua_SQLFinalizeStmt);


    // extract data from packet
    lua_register(m_script, "cppPacket_getData", lua_Packet_getData);
    lua_register(m_script, "cppPacket_getIP", lua_Packet_getIP);
    lua_register(m_script, "cppPacket_extract", lua_Packet_extract);
    lua_register(m_script, "cppPacket_getGUID", lua_Packet_getGUID);


    // misc
    lua_register(m_script, "cpp_getEncrypedPW", lua_getEncryptedPW);


    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../luaFiles/serverSideScript.lua")))
    {
        std::cout << "Run script OK \n";
    }

    lua_getglobal(m_script, "ServerSide_Init");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Call ServerSide_Init from C++ OK \n";
        }
    }

    shared_luaState = m_script;

    int t1[16] = {
        7, 12, 5, 7,
        8, 33, 51, 21,
        77, 71, 22, 43,
        12, 15, 99, 4
    };
    int t2[8] = {
        12, 6, 7, 2,
        9, 12, 91, 42
    } ;

    int t3[8] = {
        5, 10, 11, 4, 
        44, 12, 8, 92
    };

    std::string tStr1;
    
    std::string tStr2;

    std::string tStr3;
    
    for(int i = 0 ; i < 16 ; i++)
    {
        tStr1.push_back(t1[i]);
    }

    
    // std::cout << "tStr1:|" <<  tStr1 << "|\n"; 

    for(int i = 0 ; i < 8 ; i++)
    {
        tStr2.push_back(t2[i]);
    }

    for(int i = 0 ; i < 8 ; i++)
    {
        tStr3.push_back(t3[i]);
    }
    // std::cout << "tStr2:|" << tStr2 << "|\n";


    m_cryptor.init(tStr1, tStr2);   


    std::cout << "pwCryptor init \n";

    std::string tData = "Test data hahaha ";
    unsigned char iv[AES_IV_SIZE];
    std::cout << tData << "\n";
    auto ct = m_cryptor.encrypt(tData,iv);
    for (unsigned char byte : ct)
    {
        printf("%02x", byte);
    }
    std::cout << "\n";

    std::cout << "decrypt back : \n";
    std::cout << m_cryptor.decrypt(ct,iv) << "\n";

    
    std::string tpwData = "da0feb2427bf1bf";

    passwordSalt = new unsigned char[AES_IV_SIZE];

    for(int i = 0 ; i < tpwData.size() ; i++)
    {
        passwordSalt[i] = tpwData[i];
    }
    
    std::cout << "password salt: ";
    for (int i = 0 ; i <  tpwData.size() ; i++)
    {
        printf("%02x", passwordSalt[i]);
    };

    std::cout << "\nversion " << sqlite3_libversion() << "\n";

}

std::string ServerScriptingManager::getEncryptPW(const std::string & pw)
{

    std::string retVal;

    std::vector<unsigned char> hashed = hashPasswordPBKDF2(pw, salt);

    std::ostringstream oss;
    for (unsigned char byte : hashed) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    retVal = oss.str();

    return retVal;
}

PacketCode ServerScriptingManager::getSpecialRequestCode(RakNet::Packet *p)
{
 //   std::cout << "getSpecialRequestCode called \n";

    std::string cData = getMegFromPackget(p);
    if(cData.find("|LOGIN_REQUEST|") != std::string::npos)
    {
        if(cData.find("|LOGIN_END_REQUEST|") != std::string::npos)
        {
            return PacketCode::LOGIN;
        }
    }

    if(cData.find("|REQUEST_KEY_REQUEST|") != std::string::npos)
    {
        if(cData.find("|REQUEST_KEY_END_REQUEST|") != std::string::npos)
        {
            return PacketCode::REQUEST_KEY;
        }
    }

    if(cData.find("|REGISTER_REQUEST|") != std::string::npos)
    {
        if(cData.find("|REGISTER_END_REQUEST|") != std::string::npos)
        {
            return PacketCode::REGISTER;
        }
    }

    if(cData.find("|USERDATA_REQUEST|") != std::string::npos)
    {
        if(cData.find("|USERDATA_END_REQUEST|") != std::string::npos)
        {
            return PacketCode::USERDATA;
        }
    }

    //std::cout << "Not a request, normal message : \n";
    return PacketCode::INVALID;
}