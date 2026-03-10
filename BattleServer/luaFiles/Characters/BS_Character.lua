package.path = package.path .. ";../../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"


BS_Character = {
    userID = "",
    id = "",
    slotIndex = 0,
    rowPos = 0,
    colPos = 0,
    stats = nil,
    cHp = 0,    -- current hp
    cMana = 0,  -- current mana
    cSp = 0,    -- current sp
    cAction = 0 -- current action
}

function BS_Character:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function BS_Character:init(userID,tId, tSlotIndex, tRowPos, tColPos)
    self.userID = userID
    self.id = tId
    self.slotIndex = tSlotIndex
    self.rowPos = tRowPos
    self.colPos = tColPos

    print("BS_Character stat about to init")
    if ClientOwnedCharacters[userID] == nil then
        print("ClientOwnedCharacters[" .. userID .. "] is nil")
        return
    else
        if ClientOwnedCharacters[userID][tId] == nil then
            print("ClientOwnedCharacters[" .. userID .. "][" .. tId .. "] is nil")
            return
        else
            print("ClientOwnedCharacters[" .. userID .. "][" .. tId .. "] is valid")
            self.stats =  ClientOwnedCharacters[userID][tId]
            for k,v in pairs(self.stats) do
                print("stat " .. k .. " value " .. v)
            end
        end
    end
end

function BS_Character:getPhysicDmg()
    local strength = self.stats.strength
    local physicDmg = self.stats.physicDmg
    local physicDmgScale = self.stats.physicDmgScale

    return physicDmg + (strength * physicDmgScale)
    -- return self.stats
end

