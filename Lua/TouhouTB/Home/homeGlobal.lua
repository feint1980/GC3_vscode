MenuPanels = {}

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

