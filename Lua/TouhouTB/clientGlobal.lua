
SceneIndex = {

    Login = 0,
    Home = 1,
    Test = 2,
    Lobby = 3
}

MenuPanels = {}

MenuMainPanels = {}

---@class S_Characters_Info
---@field data string
---@field isOwned boolean
Characters_Info = {
    data = "",
    isOwned  = false
}

function Characters_Info:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Characters_Info:init(tData, tIsOwned)
    self.data = tData
    self.isOwned = tIsOwned
end

S_Characters_Info = {}
Shop_CharacterTable = {}

Owned_CharacterTable = {}
Owned_CharacterPannels = {}

Formation_Table = {}
Formation_OwnedCharacterPannels = {}

Skill_Serialized_Table = {}
Skill_Table = {}

---@table of Prompt
Prompt_UI_Table = {}

MainInfo = {
    id = "",
    guid = "",
    pw = ""
}



LobbyScene_isReady = false

---- Global variables section end ---- 

---

--- wrapper for Info Holder


--- wrapper for Info Holder
--- @Desciption: set the string value by key
--- @param key string key
--- @param value string
function InfoHolder_setStrVal(key, value)
    cpp_infoHolder_setStrValue(key, value)
end


--- wrapper for Info Holder
--- @Desciption: get the string value by key
--- @param key string key
--- @return string
function InfoHolder_getStrVal(key)
    return cpp_infoHolder_getStrValue(key)
end

--- wrapper for Info Holder
--- @Desciption: set the number value by key
--- @param key string key
--- @param value number
function InfoHolder_setNumberVal(key, value)
    cpp_infoHolder_setNumberValue(key, value)
end

--- wrapper for Info Holder
--- @Desciption: get the number value by key
--- @param key string key
--- @return number
function InfoHolder_getNumberVal(key)
    return cpp_infoHolder_getNumberValue(key)
end


--- wrapper for Info Holder
--- @Desciption: set the pointer value by key
--- @param key string key
--- @param value pointer
function InfoHolder_setPointerVal(key, value)
    cpp_infoHolder_setPointerValue(key, value)
end


--- wrapper for Info Holder
--- @Desciption: get the pointer value by key
--- @param key string key
--- @param value pointer
function InforHolder_setPointerVal(key, value)
    cpp_infoHolder_getUserLightData(key, value)
end

--- wrapper for Info Holder
--- @Desciption: get the pointer value by key
--- @param key string key
--- @return pointer
function InfoHolder_getPointerVal(key)
    return cpp_infoHolder_setUserLightData(key)
end
