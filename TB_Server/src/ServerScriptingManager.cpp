#include "ServerScriptingManager.h"
#include "Json2Struct.h"
using json = nlohmann::json;

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
    // std::cout << "serverScriptingCallback \n";
    for(int i = 0 ; i < m_response.data.size() ; i++)
    {
        m_response.data[i] = "";
    }
    m_response.data.clear();

    for(int i = 0; i<m_response.columnNames.size(); i++)
    {
        m_response.columnNames[i] = "";
    }
    // std::cout << "reset done \n";

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
            int arguments = 2;
            int returnCount = 1;
            if (!LuaManager::Instance()->checkLua(shared_luaState, lua_pcall(shared_luaState, arguments, returnCount, 0)))
            {
                std::cout << "call AddColData failed \n";
            }
        }
	}
	m_response.recordCount = argc;
	printf("\n");
	return 0;
}

void printHex(const std::string& data) {
    for (unsigned char c : data)
        printf("%02X", c);
    printf("\n");
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

int lua_GetTargetPing(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_GetTargetPing) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * target = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 2));
        int pingResult = host->getTargetPing(*target);

        lua_pushinteger(L, pingResult);

        std::cout << "target ping is " << pingResult << "\n";

        return 1;
    }
    return 0;
}

int lua_registerIP(lua_State *L)
{
    if (lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_registerIP) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        std::string guid = lua_tostring(L, 2);
        RakNet::SystemAddress * ip = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 3));
        host->registerIP(guid, ip);
        return 0;
    }
    return 0;
}

int lua_getRegisteredIP(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_getRegisteredIP) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        std::string guid = lua_tostring(L, 2);
        // std::cout << "attemp to get IP with guid " << guid << "\n";
        RakNet::SystemAddress * ip = host->getRegisterIP(guid);

        lua_pushlightuserdata(L, ip);

        return 1;
    }
    return 0;
}


// Read value from lua table, you need to call lua table first
void assignValue(lua_State *L,int index, const std::string & target, float & modVal)
{
    lua_getfield(L,2,target.c_str());
    modVal = lua_tonumber(L,-1);
    lua_pop(L,1);
}
void assignValue(lua_State *L,int index, const std::string & target, std::string & modVal)
{
    lua_getfield(L,2,target.c_str());
    modVal = lua_tostring(L,-1);
    lua_pop(L,1);
}

void assignValue(lua_State *L,int index, const std::string & target, int & modVal)
{
    lua_getfield(L,2,target.c_str());
    modVal = lua_tointeger(L,-1);
    lua_pop(L,1);
}

int lua_UpdateCharacter(lua_State *L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_UpdateCharacter) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        if (!lua_istable(L, 2)) {
            std::cout << "Expected a table!\n"; 
            // lua_pushstring(L, "Expected a table!");
            lua_error(L); // Throws error in Lua
            return 0;
        }
        else
        {
            // std::cout << "got table, here we go \n";
            CharacterStats stats;
            // Strength 1
            assignValue(L,2,"strength", stats.strength); 
            // Vitality 2
            assignValue(L,2,"vitality", stats.vitality);
            // Dexterity 3
            assignValue(L,2,"dexterity", stats.dexterity);
            // Agility 4
            assignValue(L,2,"agility", stats.agility);
            // Intelligence 5
            assignValue(L,2,"intelligence", stats.intelligence);
            // Wisdom 6
            assignValue(L,2,"wisdom", stats.wisdom);
            // animationPath 7
            assignValue(L,2,"animationPath", stats.animationPath);
            // portraitPath 8
            assignValue(L,2,"portraitPath", stats.portraitPath);
            // panelPath 9 
            assignValue(L,2,"panelPath", stats.panelPath);
            // action 10
            assignValue(L,2,"action", stats.action);
            // hp 11
            assignValue(L,2,"hp", stats.hp);
            // mana 12
            assignValue(L,2,"mana", stats.mana);
            // sp 13
            assignValue(L,2,"sp", stats.sp);
            // spCap 14
            assignValue(L,2,"spCap", stats.spCap);
            // physicDmg 15
            assignValue(L,2,"physicDmg", stats.physicDmg);
            // physicDef 16
            assignValue(L,2,"physicDef", stats.physicDef);
            // magicDmg 17
            assignValue(L,2,"magicDmg", stats.magicDmg);
            // magicDef 18
            assignValue(L,2,"magicDef", stats.magicDef);
            // accurate 19
            assignValue(L,2,"accurate", stats.accurate);
            // evadeChance 20
            assignValue(L,2,"evadeChance", stats.evadeChance);
            // critChance 21
            assignValue(L,2,"critChance", stats.critChance);
            // hpScale 22
            assignValue(L,2,"hpScale", stats.hpScale);
            // manaScale 23
            assignValue(L,2,"manaScale", stats.manaScale);
            // physicDmgScale 24
            assignValue(L,2,"physicDmgScale", stats.physicDmgScale);
            // magicDmgScale 25
            assignValue(L,2,"magicDmgScale", stats.magicDmgScale);
            // physicDefScale 26
            assignValue(L,2,"physicDefScale", stats.physicDefScale);
            // magicDefScale 27
            assignValue(L,2,"magicDefScale", stats.magicDefScale);
            // accurateScale 28
            assignValue(L,2,"accurateScale", stats.accurateScale);
            // evadeChanceScale 29
            assignValue(L,2,"evadeChanceScale", stats.evadeChanceScale);
            // deathDoorSurviveChance 30
            assignValue(L,2,"deathDoorSurviveChance", stats.deathDoorSurviveChance);
            // name 31
            assignValue(L,2,"name", stats.name);
            // lastName 32
            assignValue(L,2,"lastName", stats.lastName);
            // title 33
            assignValue(L,2,"title", stats.title);
            // side 34
            assignValue(L,2,"side", stats.side);
            // level 35
            assignValue(L,2,"level", stats.level);
            // xp 36
            assignValue(L,2,"xp", stats.xp);
            // ID 37
            assignValue(L,2,"ID", stats.ID);
            //price 38
            assignValue(L,2,"price", stats.price);
            // std::cout << "Strength: " << stats.strength << "\n";
            json j = stats;
            // std::cout << "JSON: " << j.dump(4) << "\n";
            std::string checkCharacterExist = "select character_id from character_base_table where character_id ='" + stats.ID + "';";
            if(host)
            {
                // std::cout << "query \n";
                // std::cout << checkCharacterExist << "\n";                
                if (host->doQuery(checkCharacterExist))
                {
                    if(m_response.recordCount == 1) // exist
                    {
                        // std::cout << "chacater found ! update ...\n";
                        std::string updateQuery = "update character_base_table set stats = '" + j.dump(4) + "' where character_id ='" + stats.ID + "'";
                        // std::cout << "test query " << updateQuery << "\n";
                        host->doQuery(updateQuery);
                    }
                    else if(m_response.recordCount == 0) // not exist
                    {
                        std::string insertString = "insert into character_base_table (character_id, character_name, stats) values ('" + stats.ID + "', '" + stats.name + " " + stats.lastName +  "', '" + j.dump(4) + "');";
                        // std::cout << "dump " << j.dump(4) << "\n";
                        if(host)
                        {
                            if(host->doQuery(insertString))
                            {
                                std::cout << "added " << stats.ID << " OK !!!\n";
                            }
                        }
                    }
                    else // if this happen you are COOKED !
                    {
                        std::cout << "cooked (multiple record of character found) \n";
                    }
                }
                lua_pushstring(L,j.dump(0).c_str());
                return 1;
            }
            else
            {
                std::cout << "host null \n";
            }
        }
    }
}


int lua_UpdateSkill(lua_State *L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_UpdateCharacter) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        SkillStats stats;
        if (!lua_istable(L, 2)) {
            std::cout << "Expected a table!\n"; 
            // lua_pushstring(L, "Expected a table!");
            lua_error(L); // Throws error in Lua
            return 0;
        }
        else
        {
            // std::cout << "got table, here we go \n";
            
            assignValue(L,2,"name", stats.skillName); 

            assignValue(L,2,"description", stats.description);

            assignValue(L,2,"effectTxt", stats.effect);

            assignValue(L,2,"quoteTxt", stats.quote);

            assignValue(L,2,"iconPath", stats.iconPath);

            assignValue(L,2,"ID", stats.ID);

            assignValue(L,2,"type", stats.skillType);

            // json j = stats;
            // std::cout << "JSON: " << j.dump(4) << "\n";

            // std::cout << j.dump(4) << "\n";

        }
        std::string tID = lua_tostring(L,3);
        if(host)
        {
            host->addSkillStats(tID, stats);
            SkillStats s = host->getSkillStats(tID);
        
            json j = s;
            
            lua_pushstring(L,j.dump(0).c_str());
        return 1;
        }
        else
        {
            std::cout << "host null \n";
            return 0;
        }
        return 0;
    }
    return 0;
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
    return 0;
}

int lua_GetSystemAddressPort(lua_State *L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_GetSystemAddressPort) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        RakNet::SystemAddress * address = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 1));
        lua_pushinteger(L, address->GetPort());
        return 1;
    }
    return 0;
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
        // std::cout << "lua_SQLBindStatement called corrct \n" ;
        // std::cout << "binding index " << index << " with value " << val << "\n";
        int rc = sqlite3_bind_text(stmt, index, val.c_str(), -1, SQLITE_TRANSIENT);
        // sqlite3_bind
        char* expanded = sqlite3_expanded_sql(stmt);
        if (expanded) {
            // std::cout << "lua_SQLBindStatement Query: " << expanded << std::endl;
            sqlite3_free(expanded);  // Must free memory!
        }
        // std::cout << "return values is  " << rc << "\n"; 
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

int lua_SQLExec(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_SQLExec) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }   
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));

        char * errMsg = nullptr;
        std::string cmd = lua_tostring(L, 2);
            
        int rc =sqlite3_exec(host->getDB(), cmd.c_str(), nullptr, nullptr, &errMsg);
        if(rc != SQLITE_OK) {
            std::cout << "SQL error: " << errMsg << "\n";
            sqlite3_free(errMsg);
        }
        return 1;
    }
    return -1;
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
        //lua_pushstring(L, result.c_str());

    } 
    return 2;
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

int lua_SendWrapMsgToClient(lua_State * L)
{
    // std::cout << "lua_SendWrapMsgToClient called \n";
    if(lua_gettop(L) != 4)
    {
        std::cout << "gettop failed (lua_SendWrapMsgToClient) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * clientId = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 2));
        std::string guid = lua_tostring(L, 3);
        std::string msg = lua_tostring(L, 4);
        // std::cout << "send wrap data \n";
        
        // std::cout << "ip " << clientId << "\n";
        // std::cout << "value " << clientId->ToString(false) << "\n"; 
        uint32_t tResult =  host->sendWrapData(*clientId,guid, msg);
        // std::cout << "send result " << tResult << "\n";
        lua_pushinteger(L, tResult);
        return 1;
    }

    return 0;
}
int lua_SendWrapMsgToBattleServer(lua_State * L)
{

    if(lua_gettop(L) != 4)
    {
        std::cout << "gettop failed (lua_SendWrapMsgToClient) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * clientId = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 2));
        std::string guid = lua_tostring(L, 3);
        std::string msg = lua_tostring(L, 4);
        // std::cout << "send wrap data \n";
        
        // std::cout << "ip " << clientId << "\n";
        // std::cout << "value " << clientId->ToString(false) << "\n"; 
        uint32_t tResult =  host->sendWrapData2BatlleServer(*clientId,guid, msg);
        // std::cout << "send result " << tResult << "\n";
        lua_pushinteger(L, tResult);
        return 1;
    }
    return 0;
}


int lua_SendToClient(lua_State * L)
{
    // std::cout << "lua_SendToClient called \n";
    if (lua_gettop(L) < 3 || lua_gettop(L) > 4)
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
        bool isEncrypted = lua_toboolean(L,4);
        
        uint32_t tResult =  host->sendData(*clientId, msg,isEncrypted);
        
        lua_pushinteger(L, tResult);
        return 1;
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

int lua_Packet_getIPAsString(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_Packet_getIPAsString) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        RakNet::Packet * p = static_cast<RakNet::Packet*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * clientId = &p->systemAddress;
        std::string ip = clientId->ToString(false);
        lua_pushstring(L, ip.c_str());
        return 1;
    }
    return 0;
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

int lua_addCryptor(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_addCryptor) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        std::string key = lua_tostring(L, 2);
        host->addCryptor(key);
        return 0;
    }
}

int lua_removeCryptor(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_removeCryptor) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        std::string key = lua_tostring(L, 2);
        host->removeCryptor(key);
        return 0;
    }
}


int lua_addClientOnlineSession(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_addClientOnlineSession) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        
        std::string guid = lua_tostring(L, 1);
        std::string id = lua_tostring(L, 2);
        RakNet::SystemAddress * ip = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 3));
        bool result = ServerDataRegister::GetInstance()->addClientOnlineSession(guid, id, ip);
        lua_pushboolean(L, result);
        return 1;
    }
    return 0;
}

int lua_removeClientOnlineSessionByGUID(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_removeClientOnlineSession) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        std::string guid = lua_tostring(L, 1);
        bool result =  ServerDataRegister::GetInstance()->removeClientOnlineSessionByGUID(guid);
        lua_pushboolean(L, result);
        return 1;
    }
    return 0;
}

int lua_removeClientOnlineSessionByID(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_removeClientOnlineSession) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        std::string id = lua_tostring(L, 1);
        bool result = ServerDataRegister::GetInstance()->removeClientOnlineSessionByID(id);
        lua_pushboolean(L, result);
        return 1;
    }
    return 0;
}

int lua_getClientOnlineSessionByGUID(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_getClientOnlineSessionByGUID) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        std::string guid = lua_tostring(L, 1);
        if(!ServerDataRegister::GetInstance()->getClientOnlineSessionByGUID(guid))
        {
            std::cout << "online session for guid " << guid << " not found \n"; 
        }
        RakNet::SystemAddress * ip = &ServerDataRegister::GetInstance()->getClientOnlineSessionByGUID(guid)->address;

        if(ip == nullptr)
        {
            std::cout << "ip is null \n"; 
            return -1;
        }

        std::cout << "C++ side data check, ip is" << ip->ToString(false) << "\n";

        lua_pushlightuserdata(L, ip);
        return 1;
    }
    return 0;
}

int lua_getClientOnlineSessionByID(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_getClientOnlineSessionByID) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        std::string id = lua_tostring(L, 1);
        if(!ServerDataRegister::GetInstance()->getClientOnlineSessionByID(id))
        {
            std::cout << "online session for id " << id << " not found \n"; 
        }
        RakNet::SystemAddress * ip = &ServerDataRegister::GetInstance()->getClientOnlineSessionByID(id)->address;
        lua_pushlightuserdata(L, ip);
        return 1;
    }
}


ServerScriptingManager::ServerScriptingManager()
{


}
ServerScriptingManager::~ServerScriptingManager()
{

}

void ServerScriptingManager::handleMessage()
{

    while(!m_responseQueue.empty()) // handle 1 response at the time
    {
        MSGResponse response = m_responseQueue.front();
        // RakNet::Packet * p = response.m_packet;
        // PacketCode requestCode = response.m_requestCode;
        // lua_getglobal(m_script, "HandleMessage");
        // if (lua_isfunction(m_script, -1))
        // {
        //     lua_pushlightuserdata(m_script, this); // host

        //     //std::cout << "Issue next task pointer " << object << "\n";

        //     lua_pushlightuserdata(m_script, response.packet);
        //     //lua_pushlightuserdata(m_script, m_guiHandler);

        //     lua_pushnumber(m_script, response.requestCode);

        //     // lua_pushlightuserdata(m_script, entity->getTargetSlot());

        //     if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 3, 1, 0)))
        //     {
        //         std::cout << "call HandleMessage failed \n";
        //     }
        // }
        m_responseQueue.pop();
    }
}

void ServerScriptingManager::handleCommonMSG()
{
    while(!m_commonResponseQueue.empty()) // handle 1 response at the time
    {
        CommonResponse response = m_commonResponseQueue.front();
        lua_getglobal(m_script, "HandleCommon");
        if (lua_isfunction(m_script, -1))
        {
            lua_pushlightuserdata(m_script, this); // host

            lua_pushlightuserdata(m_script, response.packet);

            lua_pushnumber(m_script, response.packetIdentifier);

            // lua_pushlightuserdata(m_script, entity->getTargetSlot());

            int arguments = 3;
            int returnCount = 1;
            if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, arguments, returnCount, 0)))
            {
                std::cout << "call HandleCommon failed \n";
            }
        }
        m_commonResponseQueue.pop();
    }
}

void ServerScriptingManager::update(float deltaTime)
{
    handleWrapDataQueue(deltaTime);
    handleBattleServerQueue(deltaTime);
  //  handleMessage();
//   /  handleCommonMSG();
}


std::string ServerScriptingManager::getMegFromPackget(RakNet::Packet *p)
{
    // std::string retVal = "";
    std::string tMsg;
    for(int i = 0 ;i < (p->length -1); i++)
    {
        tMsg.push_back(p->data[i]);
    }
    

    // return m_cryptor.decrypt(tMsg, iv); // old
    if(m_cryptors[p->guid.ToString()])
    {
        return m_cryptors[p->guid.ToString()]->decrypt(tMsg);
    }
    else
    {
        std::cout << "no cryptor for guid " << p->guid.ToString() << "\n";
        return "";//
    }
}

uint32_t ServerScriptingManager::getTargetPing(const RakNet::SystemAddress & target)
{
    return m_server->GetAveragePing(target);
}

std::string ServerScriptingManager::getDecryptMessage(const std::string & data, const std::string & guid)
{
    // std::cout << 
    if(m_cryptors[guid])
    {
        return m_cryptors[guid]->decrypt(data);
    }
    
    std::cout << "no cryptor for guid " << guid << "\n";
    return "";
    //return m_cryptor.decrypt(tMsg, iv); //old
}

SkillStats ServerScriptingManager::getSkillStats(const std::string & skillName)
{
    
    return m_skillStatsMap[skillName];
}

uint32_t ServerScriptingManager::sendWrapData(const RakNet::SystemAddress & target,const std::string & guid, const std::string & data)
{
    // std::cout << "C++ sendWrapData called \n";
    if (data.size() < 2) // headers
    {
        std::cout << "sendWrapData failed (data size < 2)\n";
        return 0;
    }

    uint8_t channel = static_cast<uint8_t>(data[0]);
    uint8_t request = static_cast<uint8_t>(data[1]);
    int payLoadIndex = 2;

    std::string payLoad(data.begin() + payLoadIndex, data.end());
    std::string tData = m_cryptors[guid]->encrypt(payLoad);

    // Build BitStream safely
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)ID_TH_TB);     // custom message ID
    bsOut.Write(channel);                         // 1 byte
    bsOut.Write(request);                         // 1 byte
    bsOut.WriteAlignedBytes(
        reinterpret_cast<const unsigned char*>(tData.data()), 
        (const unsigned int)tData.size()
    );

    // Safe send (BitStream handles memory ownership)
    return m_server->Send(
        &bsOut, 
        HIGH_PRIORITY, 
        RELIABLE_ORDERED, 
        channel, 
        target, 
        false
    );
    // std::cout << "send with  || " << sendBuf.size() << " bytes\n"; 
}   

uint32_t ServerScriptingManager::sendWrapData2BatlleServer(const RakNet::SystemAddress & target, const std::string & guid, const std::string & data)
{
        // std::cout << "C++ sendWrapData called \n";
    if (data.size() < 2) // headers
    {
        std::cout << "sendWrapData failed (data size < 2)\n";
        return 0;
    }

    uint8_t channel = static_cast<uint8_t>(data[0]);
    uint8_t request = static_cast<uint8_t>(data[1]);
    int payLoadIndex = 2;

    std::string payLoad(data.begin() + payLoadIndex, data.end());
    std::string tData = m_cryptors[guid]->encrypt(payLoad);

    // Build BitStream safely
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)ID_TH_INTERNAL);     // custom message ID
    bsOut.Write(channel);                         // 1 byte
    bsOut.Write(request);                         // 1 byte
    bsOut.WriteAlignedBytes(
        reinterpret_cast<const unsigned char*>(tData.data()), 
        (const unsigned int)tData.size()
    );

    // Safe send (BitStream handles memory ownership)
    return m_server->Send(
        &bsOut, 
        HIGH_PRIORITY, 
        RELIABLE_ORDERED, 
        channel, 
        target, 
        false
    );    
}



uint32_t ServerScriptingManager::sendData(const RakNet::SystemAddress & target, const std::string & data, bool isEncrypted)
{
    // encrypt 
    std::string sendStr;
    //sendStr.push_back(ID_TH_TB);
    if(isEncrypted)
    {
        

    }
    else
    {
        sendStr = std::move(data);
    }

    // if(m_server->GetGuidFromSystemAddress(target) != RakNet::UNASSIGNED_RAKNET_GUID)
    // {
    return m_server->Send(sendStr.c_str(), sendStr.size() + 1, HIGH_PRIORITY,  RELIABLE_ORDERED,0, target,false);
    // }
    // return 0;
}


unsigned int ServerScriptingManager::handleCommon(RakNet::Packet *p)
{
    unsigned char packetIdentifier = GetPacketIdentifier(p);

    //m_commonResponseQueue.push(CommonResponse(p, packetIdentifier));

    // std::cout << "handleCommon called #########" << (int)packetIdentifier << "#############\n";
    lua_getglobal(m_script, "HandleCommon");
    if (lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this); // host

        lua_pushlightuserdata(m_script, p);

        lua_pushnumber(m_script, packetIdentifier);

        // lua_pushlightuserdata(m_script, entity->getTargetSlot());

        int arguments = 3;
        int returnCount = 1;
        if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, arguments, returnCount, 0)))
        {
            std::cout << "call HandleMessage failed \n";
        }
    }
    return 666;
}

void ServerScriptingManager::addWrapDataPacket(RakNet::Packet *original)
{
    // RakNet::Packet* original = p;
    auto copy = new RakNet::Packet(*original); // shallow copy
    copy->data = new unsigned char[original->length];
    memcpy(copy->data, original->data, original->length);
    copy->length = original->length;

    m_wrapDataQueue.push( std::move(copy));
}

void ServerScriptingManager::addBattleServerPacket(RakNet::Packet *original)
{
    // RakNet::Packet* original = p;
    auto copy = new RakNet::Packet(*original); // shallow copy
    copy->data = new unsigned char[original->length];
    memcpy(copy->data, original->data, original->length);
    copy->length = original->length;

    m_battleServerPacketQueue.push( std::move(copy));
}

void ServerScriptingManager::handleWrapDataQueue(float deltaTime)
{
    while (!m_wrapDataQueue.empty())
    {
        RakNet::Packet *p = m_wrapDataQueue.front();
        handleWrapData(p);
        delete[] p->data;
        delete p;
        m_wrapDataQueue.pop();
    }
}

void ServerScriptingManager::handleBattleServerQueue(float deltaTime)
{
    while (!m_battleServerPacketQueue.empty())
    {
        RakNet::Packet *p = m_battleServerPacketQueue.front();
        handleBattleServerPacket(p);
        delete[] p->data;
        delete p;
        m_battleServerPacketQueue.pop();
    }
}

uint32_t ServerScriptingManager::handleBattleServerPacket(RakNet::Packet *p)
{
    RakNet::BitStream bsIn(p->data, p->length, false);
    RakNet::MessageID msgId;
    uint8_t channel, request;

    bsIn.Read(msgId);
    if (msgId != ID_TH_INTERNAL)
    {
        printf("Unexpected message ID: %u\n", msgId);
        return 0;
    }

    bsIn.Read(channel);
    bsIn.Read(request);

    unsigned int remainingBytes = bsIn.GetNumberOfUnreadBits() / 8;
    std::string encData(remainingBytes, '\0');
    bsIn.ReadAlignedBytes(reinterpret_cast<unsigned char*>(&encData[0]), remainingBytes);

    std::string payLoad = getDecryptMessage(encData, p->guid.ToString());

    // std::cout << "payload " << payLoad << "\n";
    // printf("SERVER recv bytes=%u\n", p->length);
    // for (unsigned int i = 0; i < std::min<unsigned int>(64, (unsigned int)p->length); ++i) printf("%02X ", (unsigned char)p->data[i]);
    // printf("\n");

    // decrypt the payload only
    // payLoad = getDecryptMessage(payLoad, );

    // std::cout << "payload is " << payLoad << "\n";

  //  std::cout << "decrypted payload " << payLoad << "\n";

    lua_getglobal(m_script, "HandleBattleServerMessage");
    if (lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this); // host
        lua_pushnumber(m_script, channel);
        lua_pushnumber(m_script, request);
        lua_pushstring(m_script, payLoad.c_str());  
        lua_pushlightuserdata(m_script, &p->systemAddress);
        lua_pushstring(m_script, p->guid.ToString());
        //std::cout << "Issue next task pointer " << object << "\n";
        //lua_pushlightuserdata(m_script, p->);
        //lua_pushlightuserdata(m_script, m_guiHandler);
        // lua_pushnumber(m_script, p->);
        // lua_pushlightuserdata(m_script, entity->getTargetSlot());
        int arguments = 6;
        int returnCount = 1;
        if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, arguments, returnCount, 0)))
        {
            std::cout << "call HandleBattleServerMessage failed \n";
        }
    }

    // retVal =  m_cryptor.decrypt(tMsg, iv);
    return 0;
}

uint32_t ServerScriptingManager::handleWrapData(RakNet::Packet *p)
{
    RakNet::BitStream bsIn(p->data, p->length, false);
    RakNet::MessageID msgId;
    uint8_t channel, request;

    bsIn.Read(msgId);
    if (msgId != ID_TH_TB)
    {
        printf("Unexpected message ID: %u\n", msgId);
        return 0;
    }

    bsIn.Read(channel);
    bsIn.Read(request);

    unsigned int remainingBytes = bsIn.GetNumberOfUnreadBits() / 8;
    std::string encData(remainingBytes, '\0');
    bsIn.ReadAlignedBytes(reinterpret_cast<unsigned char*>(&encData[0]), remainingBytes);

    std::string payLoad = getDecryptMessage(encData, p->guid.ToString());

    // printf("SERVER recv bytes=%u\n", p->length);
    // for (unsigned int i = 0; i < std::min<unsigned int>(64, (unsigned int)p->length); ++i) printf("%02X ", (unsigned char)p->data[i]);
    // printf("\n");

    // decrypt the payload only
    // payLoad = getDecryptMessage(payLoad, );

    // std::cout << "payload is " << payLoad << "\n";

  //  std::cout << "decrypted payload " << payLoad << "\n";

    lua_getglobal(m_script, "HandleWrapMessage");
    if (lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this); // host
        lua_pushnumber(m_script, channel);
        lua_pushnumber(m_script, request);
        lua_pushstring(m_script, payLoad.c_str());  
        lua_pushlightuserdata(m_script, &p->systemAddress);
        lua_pushstring(m_script, p->guid.ToString());
        //std::cout << "Issue next task pointer " << object << "\n";
        //lua_pushlightuserdata(m_script, p->);
        //lua_pushlightuserdata(m_script, m_guiHandler);
        // lua_pushnumber(m_script, p->);
        // lua_pushlightuserdata(m_script, entity->getTargetSlot());
        int arguments = 6;
        int returnCount = 1;
        if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, arguments, returnCount, 0)))
        {
            std::cout << "call HandleWrapMessage failed \n";
        }
    }

    // retVal =  m_cryptor.decrypt(tMsg, iv);
    return 0;
}

ClientRequestCode ServerScriptingManager::handleCommand(RakNet::Packet *p)
{
    PacketCode requestCode = getSpecialRequestCode(p);
    // send relay data to lua to process
    std::string msg = getMegFromPackget(p);

    //if(requestCode != PacketCode::INVALID)
   // {
        // only push to queue when the request code is valid
        //m_responseQueue.push(MSGResponse(std::move( p), requestCode));
    //}
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

    return ClientRequestCode::Client_Invalid;
}

bool ServerScriptingManager::doQuery(const std::string & queryCmd)
{
    char * zErrMsg = 0;
    m_response.rc = sqlite3_exec(m_dbh->getDatabase(), queryCmd.c_str(), serverScriptingCallback, (void*)m_response.rawData, &zErrMsg);

    if(m_response.rc != SQLITE_OK)
    {
        std::cout << "ServerScriptingManager doQuery failed: " << zErrMsg << "\n";
        std::cout << "The query tried to be: " << queryCmd << "\n";
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

    // sqlite3_bind_text(stmt, 1, "feint",-1, SQLITE_STATIC);
    // sqlite3_bind_text(stmt, 2, "ok", -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int columnCount = sqlite3_column_count(stmt);
        for(int i = 0 ;i < columnCount ; i++)
        {
            // std::cout << sqlite3_column_name(stmt, i) << ": "
            // << sqlite3_column_text(stmt, i) << std::endl;

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
    // test path 
    // m_charDesc.writeData("./patchy.json");

    std::cout << "|=========================================|\n";
    std::cout << "|     Init Server Scripting Manager       |\n";
    m_server = server;
    m_dbh = dbh;
    std::cout << "|     Init Server Scripting Manager OK    |\n";
    std::cout << "|=========================================|\n";

    m_clientEPHandler = new ClientEPHandler();
    m_characterManager = new CharacterManager();

    m_script = luaL_newstate();

    luaL_openlibs(m_script);
    // register lua functions
    
    lua_register(m_script, "cppGetQueryResults", lua_GetQueryResults);
    lua_register(m_script, "cppGenKey", lua_GenKey);
    lua_register(m_script, "cppSendToClient", lua_SendToClient);
    lua_register(m_script, "cppSendWrapMsgToClient", lua_SendWrapMsgToClient);
    lua_register(m_script, "cppSendWrapMsgToBattleServer", lua_SendWrapMsgToBattleServer);

    // management of battle server
    
    // intraction 
    lua_register(m_script, "cppGetTargetPing", lua_GetTargetPing);
    lua_register(m_script, "cpp_registerIP", lua_registerIP);
    lua_register(m_script, "cpp_getRegisteredIP", lua_getRegisteredIP);

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
    lua_register(m_script, "cppSqlite_exec", lua_SQLExec);

    // extract data from packet
    lua_register(m_script, "cppPacket_getData", lua_Packet_getData);
    lua_register(m_script, "cppPacket_getIP", lua_Packet_getIP);
    lua_register(m_script, "cppPacket_getIPAsString", lua_Packet_getIPAsString);
    lua_register(m_script, "cppPacket_extract", lua_Packet_extract);
    lua_register(m_script, "cppPacket_getGUID", lua_Packet_getGUID);

    // RakNet System Address
    lua_register(m_script, "cppGetSystemAddressPort", lua_GetSystemAddressPort);

    // misc
    lua_register(m_script, "cpp_getEncrypedPW", lua_getEncryptedPW);
    lua_register(m_script, "cpp_addCryptor", lua_addCryptor);
    lua_register(m_script, "cpp_removeCryptor", lua_removeCryptor);

    // Update Characters it belongs here because the server read and update it to database
    lua_register(m_script, "cpp_updateCharacter", lua_UpdateCharacter);
    lua_register(m_script, "cpp_updateSkill", lua_UpdateSkill);

    // client handler 
    lua_register(m_script, "cpp_addClientOnlineSession", lua_addClientOnlineSession);
    lua_register(m_script, "cpp_removeClientOnlineSessionByGUID", lua_removeClientOnlineSessionByGUID);
    lua_register(m_script, "cpp_removeClientOnlineSessionByID", lua_removeClientOnlineSessionByID);
    lua_register(m_script, "cpp_getClientOnlineSessionByGUID", lua_getClientOnlineSessionByGUID);
    lua_register(m_script, "cpp_getClientOnlineSessionByID", lua_getClientOnlineSessionByID);

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../luaFiles/serverSideScript.lua")))
    {
        std::cout << "ServerScriptingManager Run script serverSideScript.lua OK \n";
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

    // cryptor 
    // crypto_kx_keypair(m_server_pk, m_server_sk);

    m_cryptors.reserve(3000);

    // std::cout << "pwCryptor init \n";

    // std::string tData = "Test data hahaha ";
    // unsigned char iv[AES_IV_SIZE];
    // std::cout << tData << "\n";
    // auto ct = m_cryptor.encrypt(tData,iv);
    // for (unsigned char byte : ct)
    // {
    //     printf("%02x", byte);
    // }
    // std::cout << "\n";

    // std::cout << "decrypt back : \n";
    // std::cout << m_cryptor.decrypt(ct,iv) << "\n";

    
    std::string tpwData = "da0feb2427bf1bf";

    passwordSalt = new unsigned char[AES_IV_SIZE];

    for(int i = 0 ; i < tpwData.size() ; i++)
    {
        passwordSalt[i] = tpwData[i];
    }
    
    // std::cout << "password salt: ";
    // for (int i = 0 ; i <  tpwData.size() ; i++)
    // {
    //     printf("%02x", passwordSalt[i]);
    // };

    // std::cout << "\nversion " << sqlite3_libversion() << "\n";

    lua_getglobal(m_script, "Server_LoadData");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Call Server_LoadData from C++ OK \n";
        }
    }

    // client EPHandling here

    m_clientEPHandler->init(m_script);
    m_characterManager->init(m_script);


}



void ServerScriptingManager::addCryptor(const std::string & guid)
{

    if(m_cryptors.find(guid) != m_cryptors.end())
    {
        std::cout << "cryptor for guid " << guid << " already exist \n";
        return;
    }
    Feintgine::F_Cryptor_sodium * cryptor = new Feintgine::F_Cryptor_sodium();

    // unsigned char server_rx[crypto_kx_SESSIONKEYBYTES];
    // unsigned char server_tx[crypto_kx_SESSIONKEYBYTES];

    cryptor->init("BNML is real", guid);
    m_cryptors[guid] = cryptor;

    std::cout << "add cryptor for guid " << guid << "\n";
}

void ServerScriptingManager::removeCryptor(const std::string & guid)
{
    if(m_cryptors.find(guid) != m_cryptors.end())
    {
        delete m_cryptors[guid];
        m_cryptors.erase(guid);
        // std::cout << "removed cryptor for guid " << guid << "\n";
    }
    else
    {
        std::cout << "no cryptor for guid " << guid << "\n";
    }

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
    std::cout << "getSpecialRequestCode " << cData << "\n";
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

    // 1 part finder
    if(cData.find("|REQUEST_CHARACTERLIST|") != std::string::npos)
    {
        // if(cData.find("|CHARACTER_LIST_RES_POS_END_REQUEST|") != std::string::npos)
        // {
            return PacketCode::REQUEST_CHARACTER;
        // }
    }

    // if(cData.find("|CHARACTER_LIST_RES_DONE_REQUEST|") != std::string::npos)
    // {
    //     // if(cData.find("|CHARACTER_LIST_RES_DONE_END_REQUEST|") != std::string::npos)
    //     // {
    //         return PacketCode::REQUEST_CHARACTER_DONE;

    //     // }
    // }

    //std::cout << "Not a request, normal message : \n";
    return PacketCode::INVALID;
}
void ServerScriptingManager::addSkillStats(const std::string & skillName, const SkillStats & skillAtt)
{ 
    m_skillStatsMap[skillName] = skillAtt;
    //test data
    json j = m_skillStatsMap[skillName];
    // std::cout << "dump stat \n";
    // std::cout << j.dump(4,'.') << "\n";
}

void ServerScriptingManager::handleInput(const std::string & command)
{
    std::cout << "handle input called \n";
    lua_getglobal(m_script, "HandleInput");
    if (lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this); // host
        lua_pushstring(m_script, command.c_str());
        int arguments = 2;
        int returnCount = 1;
        if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, arguments, returnCount, 0)))
        {
            std::cout << "call AddColData failed \n";
        }
    }
}

void ServerScriptingManager::registerIP(const std::string & guid, RakNet::SystemAddress * ip)
{
    
    RakNet::SystemAddress * copy = new RakNet::SystemAddress(*ip); 
    // stored a copy
    m_registerIPMap[guid] = copy;
}

RakNet::SystemAddress * ServerScriptingManager::getRegisterIP(const std::string & guid)
{
    
    if(m_registerIPMap.find(guid) != m_registerIPMap.end())
    {
        return m_registerIPMap[guid];
    }

    std::cout << "no ip for guid " << guid << "\n";
    return nullptr;
}