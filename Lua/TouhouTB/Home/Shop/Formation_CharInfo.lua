

---@class Formation_CharacterInfo
---@field characterID string
---@field tIndex number
---@field col number
---@field row number
Formation_CharacterInfo = {
    characterID = "",
    tIndex = 0,
    col = 0,
    row = 0
}

function Formation_CharacterInfo:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Formation_CharacterInfo:init(characterID, tIndex, row,col)
    self.characterID = characterID
    self.tIndex = tIndex
    self.row = row
    self.col = col

    -- print("init was call self.characterID " .. self.characterID)
    -- print("init was call self.tIndex " .. self.tIndex)
    -- print("init was call self.row " .. self.row)
    -- print("init was call self.col " .. self.col)

end

---@class Formation_Info
---@field formationID number
---@field formationName string
---@field formationIndex number
---@field formationCharacters table of Formation_CharacterInfo
Formation_Info = {
    formationID = 0,
    formationName = "",
    formationIndex = 0,

    ---@type table of Formation_CharacterInfo
    formationCharacters = {}
}

function Formation_Info:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Desciption : Initialize Formation_Info
---@param formationID number 
---@param formationName string
---@param formationIndex number
---@param formationCharacters table of Formation_CharacterInfo
function Formation_Info:init(formationID, formationName, formationIndex, formationCharacters)
    self.formationID = formationID
    self.formationName = formationName
    self.formationIndex = formationIndex
    self.formationCharacters = formationCharacters
end