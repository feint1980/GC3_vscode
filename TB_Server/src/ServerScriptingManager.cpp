#include "ServerScriptingManager.h"

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

static void to_json(json& j, const CharacterStats& c) 
{
    j = json{
        {"strength", c.strength}, // 1 use to check if all stats are set
        {"vitality", c.vitality}, // 2
        {"dexterity", c.dexterity}, // 3
        {"agility", c.agility}, // 4
        {"intelligence", c.intelligence}, // 5
        {"wisdom", c.wisdom}, // 6
        {"animationPath", c.animationPath}, // 7
        {"portraitPath", c.portraitPath}, // 8
        {"panelPath",c.panelPath}, // 9
        {"action",c.action}, // 10
        {"hp",c.hp}, // 11
        {"mana",c.mana}, // 12
        {"sp",c.sp}, // 13
        {"spCap",c.spCap}, // 14
        {"physicDmg",c.physicDmg}, // 15
        {"physicDef",c.physicDef}, // 16
        {"magicDmg",c.magicDmg}, // 17
        {"magicDef",c.magicDef}, // 18
        {"accurate",c.accurate}, // 19
        {"evadeChance",c.evadeChance}, // 20
        {"critChance",c.critChance}, // 21
        {"hpScale",c.hpScale}, // 22
        {"manaScale",c.manaScale}, // 23
        {"physicDmgScale",c.physicDmgScale}, // 24
        {"magicDmgScale",c.magicDmgScale}, // 25
        {"physicDefScale",c.physicDefScale}, // 26
        {"magicDefScale",c.magicDefScale}, // 27
        {"accurateScale",c.accurateScale}, // 28
        {"evadeChanceScale",c.evadeChanceScale}, // 29
        {"deathDoorSurviveChance",c.deathDoorSurviveChance}, // 30
        {"name",c.name}, // 31
        {"lastName",c.lastName}, // 32
        {"title",c.title}, // 33
        {"side",c.side}, // 34
        {"level",c.level}, // 35
        {"xp", c.xp}, // 36
        {"ID",c.ID}, // 37
        {"price",c.price} // 38
    };
}

// Convert JSON to struct
static void from_json(const json& j, CharacterStats& c) {
    j.at("strength").get_to(c.strength); // 1
    j.at("vitality").get_to(c.vitality); // 2
    j.at("dexterity").get_to(c.dexterity); // 3
    j.at("agility").get_to(c.agility); // 4
    j.at("intelligence").get_to(c.intelligence); // 5
    j.at("wisdom").get_to(c.wisdom); // 6
    j.at("animationPath").get_to(c.animationPath); // 7
    j.at("portraitPath").get_to(c.portraitPath); // 8
    j.at("panelPath").get_to(c.panelPath); // 9
    j.at("action").get_to(c.action); // 10
    j.at("hp").get_to(c.hp); // 11
    j.at("mana").get_to(c.mana); // 12
    j.at("sp").get_to(c.sp); // 13
    j.at("spCap").get_to(c.spCap); // 14
    j.at("physicDmg").get_to(c.physicDmg); // 15
    j.at("physicDef").get_to(c.physicDef); // 16
    j.at("magicDmg").get_to(c.magicDmg); // 17
    j.at("magicDef").get_to(c.magicDef); // 18
    j.at("accurate").get_to(c.accurate); // 19
    j.at("evadeChance").get_to(c.evadeChance); // 20
    j.at("critChance").get_to(c.critChance); // 21
    j.at("hpScale").get_to(c.hpScale);  // 22
    j.at("manaScale").get_to(c.manaScale); // 23
    j.at("physicDmgScale").get_to(c.physicDmgScale); // 24
    j.at("magicDmgScale").get_to(c.magicDmgScale); // 25
    j.at("physicDefScale").get_to(c.physicDefScale); // 26
    j.at("magicDefScale").get_to(c.magicDefScale); // 27
    j.at("accurateScale").get_to(c.accurateScale); // 28
    j.at("evadeChanceScale").get_to(c.evadeChanceScale); // 29
    j.at("deathDoorSurviveChance").get_to(c.deathDoorSurviveChance); // 30
    j.at("name").get_to(c.name); // 31
    j.at("lastName").get_to(c.lastName); // 32
    j.at("title").get_to(c.title); // 33
    j.at("side").get_to(c.side); // 34
    j.at("level").get_to(c.level); // 35
    j.at("xp").get_to(c.xp); // 36
    j.at("ID").get_to(c.ID); // 37
    j.at("price").get_to(c.price); // 38
}

static void to_json(json& j, const SkillStats& s)
{
    j = json{
        {"skillName", s.skillName},
        {"description", s.description},
        {"effect", s.effect},
        {"quote", s.quote},
        {"iconPath", s.iconPath},
        {"ID", s.ID}
    };
}

static void from_json(const json& j, SkillStats& s)
{
    j.at("skillName").get_to(s.skillName);
    j.at("description").get_to(s.description);
    j.at("effect").get_to(s.effect);
    j.at("quote").get_to(s.quote);
    j.at("iconPath").get_to(s.iconPath);
    j.at("ID").get_to(s.ID);
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
            assignValue(L,2,"Strength", stats.strength); 
            // Vitality 2
            assignValue(L,2,"Vitality", stats.vitality);
            // Dexterity 3
            assignValue(L,2,"Dexterity", stats.dexterity);
            // Agility 4
            assignValue(L,2,"Agility", stats.agility);
            // Intelligence 5
            assignValue(L,2,"Intelligence", stats.intelligence);
            // Wisdom 6
            assignValue(L,2,"Wisdom", stats.wisdom);
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

            // json j = stats;
            // std::cout << "JSON: " << j.dump(4) << "\n";

            // std::cout << j.dump(4) << "\n";

        }
        std::string tID = lua_tostring(L,3);
        if(host)
        {
            host->addSkillStats(tID, stats);
        }
        else
        {
            std::cout << "host null \n";
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

int lua_SendWrapMsgToClient(lua_State * L)
{
    std::cout << "lua_SendWrapMsgToClient called \n";
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_SendWrapMsgToClient) \n";
        std::cout << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        ServerScriptingManager * host = static_cast<ServerScriptingManager*>(lua_touserdata(L, 1));
        RakNet::SystemAddress * clientId = static_cast<RakNet::SystemAddress*>(lua_touserdata(L, 2));

        std::string msg = lua_tostring(L, 3);
        std::cout << "send wrap data \n";
        
        std::cout << "ip " << clientId << "\n";
        std::cout << "value " << clientId->ToString(false) << "\n"; 
        uint32_t tResult =  host->sendWrapData(*clientId, msg);
        std::cout << "send result " << tResult << "\n";
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
  //  handleMessage();
//   /  handleCommonMSG();
}

std::string ServerScriptingManager::getMegFromPackget(RakNet::Packet *p)
{
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

std::string ServerScriptingManager::getDecryptMessage(const std::string & data)
{
    unsigned char iv[AES_IV_SIZE];
    for(int i = 0 ; i < AES_IV_SIZE ; i++)
    {
        iv[i] = data[(data.size() -1) - (AES_IV_SIZE - i)]; 
    }

    std::vector<unsigned char> tMsg;
    for(int i = 0 ;i < (data.size() -1) - AES_IV_SIZE; i++)
    {
        tMsg.push_back(data[i]);
    }

    return m_cryptor.decrypt(tMsg, iv);
}


uint32_t ServerScriptingManager::sendWrapData(const RakNet::SystemAddress & target, const std::string & data)
{
    std::cout << "C++ sendWrapData called \n";
    if(data.size() < 2 ) // headers
    {
        std::cout << "sendWrapData failed (data size < 2) \n";
        return 0;
    }
    uint8_t channel = static_cast<uint8_t>(data[0]);
    uint8_t request = static_cast<uint8_t>(data[1]);

    // std::cout << "sendWrapData channel " << channel << " request " << request << "\n";
    // todo , special request add here
    int payLoadIndex = 2;

    std::string payLoad = std::string(data.begin() + payLoadIndex, data.end());
    unsigned char iv[AES_IV_SIZE] = {};
    m_cryptor.generateRandomIV(iv);
    
    auto tData = m_cryptor.encrypt(payLoad,iv);
    for(int i = 0 ; i < AES_IV_SIZE;i++)
    {
        tData.push_back(iv[i]);
    }
    std::string sendStr;
    sendStr.push_back(ID_TH_TB); // move to append ID_TH_TB here
    sendStr.push_back(channel);
    sendStr.push_back(request);

    for(int i = 0 ; i < tData.size() ; i++)
    {
        sendStr.push_back((tData[i]));
    }
    
    // std::cout << "send data \n ";
    // std::cout << sendStr << "\n";

    return m_server->Send(sendStr.c_str(), sendStr.size() + 1, HIGH_PRIORITY,  RELIABLE_ORDERED,channel, target,false);

}   

uint32_t ServerScriptingManager::sendData(const RakNet::SystemAddress & target, const std::string & data, bool isEncrypted)
{
    // encrypt 
    std::string sendStr;
    //sendStr.push_back(ID_TH_TB);
    if(isEncrypted)
    {
        unsigned char iv[AES_IV_SIZE] = {};
        m_cryptor.generateRandomIV(iv);
        // std::string tData = m_cryptor.getStringFromEncrypt(m_cryptor.encrypt(data,iv));
    
        auto tData = m_cryptor.encrypt(data,iv);
    
        for(int i = 0 ; i < AES_IV_SIZE;i++)
        {
            tData.push_back(iv[i]);
        }
    
        for(int i = 0 ; i < tData.size() ; i++)
        {
            sendStr.push_back((tData[i]));
        } 
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

void ServerScriptingManager::addWrapDataPacket(RakNet::Packet *p)
{
    m_wrapDataQueue.push(p);
}

void ServerScriptingManager::handleWrapDataQueue(float deltaTime)
{
    while (!m_wrapDataQueue.empty())
    {
        RakNet::Packet *p = m_wrapDataQueue.front();
        handleWrapData(p);
        m_wrapDataQueue.pop();
    }
}


uint32_t ServerScriptingManager::handleWrapData(RakNet::Packet *p)
{
    int indexStart = 1;
    if ((unsigned char)p->data[0] == ID_TIMESTAMP)
    {
        RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
        indexStart += sizeof(RakNet::MessageID) + sizeof(RakNet::Time);
    }
    uint8_t channel = static_cast<uint8_t>(p->data[indexStart]);
    uint8_t request = static_cast<uint8_t>(p->data[indexStart + 1]);


    std::string rawData =  std::string(reinterpret_cast<const char*>(p->data), p->length);

    std::cout << "rawData " << rawData << "\n";

    std::cout << "channel " << channel << " request " << request << "\n";

    // hand special request here
    unsigned int payLoadIndex = indexStart + 2;

    std::string payLoad = std::string(reinterpret_cast<const char*>(p->data + payLoadIndex), p->length - payLoadIndex);
    std::cout << "payload " << payLoad << "\n";

    // decrypt the payload only
    payLoad = getDecryptMessage(payLoad);

    std::cout << "decrypted payload " << payLoad << "\n";

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
    m_charDesc.writeData("./patchy.json");

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
    lua_register(m_script, "cppSendWrapMsgToClient", lua_SendWrapMsgToClient);


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
    lua_register(m_script, "cppPacket_extract", lua_Packet_extract);
    lua_register(m_script, "cppPacket_getGUID", lua_Packet_getGUID);

    // misc
    lua_register(m_script, "cpp_getEncrypedPW", lua_getEncryptedPW);

    // Update Characters it belongs here because the server read and update it to database
    lua_register(m_script, "cpp_updateCharacter", lua_UpdateCharacter);
    lua_register(m_script, "cpp_updateSkill", lua_UpdateSkill);

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

    std::string tStr1;
    
    std::string tStr2;


    for(int i = 0 ; i < 16 ; i++)
    {
        tStr1.push_back(t1[i]);
    }

    // std::cout << "tStr1:|" <<  tStr1 << "|\n"; 

    for(int i = 0 ; i < 8 ; i++)
    {
        tStr2.push_back(t2[i]);
    }
    
    // std::cout << "tStr2:|" << tStr2 << "|\n";

    m_cryptor.init(tStr1, tStr2);   

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

  //  m_handleMessgeThread = std::thread(&ServerScriptingManager::handleMessage, this);

//    m_handleCommonThread = std::thread(&ServerScriptingManager::handleCommon, this);

    // auto t = std::thread(&ServerScriptingManager::handleMessage, this);
    // //m_threads.push_back(std::move(t));

    // auto f = std::thread(&ServerScriptingManager::handleCommonMSG, this);

    // t.join();
    // f.join();
    //m_threads.push_back(std::move(t));

    // lua_getglobal(m_script, "Server_CheckCharacterData");
    // if(lua_isfunction(m_script, -1))
    // {
    //     lua_pushlightuserdata(m_script, this);
    //     const int argc = 1;
    //     const int returnCount = 0;
    //     if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
    //     {
    //         std::cout << "Call Server_CheckCharacterData from C++ OK \n";
    //     }
    // }
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
    std::cout << "dump stat \n";
    std::cout << j.dump(4,'.') << "\n";
}
