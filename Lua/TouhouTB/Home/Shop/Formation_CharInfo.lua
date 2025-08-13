

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

function Formation_CharacterInfo:init(characterID, tIndex, col, row)
    self.characterID = characterID
    self.tIndex = tIndex
    self.col = col
    self.row = row
end