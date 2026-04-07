package.path = package.path .. ';../../Lua/TouhouTB/Combat/?.lua;' 

require "combatField_wrapper"

CombatField = {
    host = nil,
    banner = nil,
}

function CombatField:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function CombatField:init(tHost,col,row)
    self.host = tHost
    for s = 1, 2 do
        for i = 1, col do
            for j = 1, row do
                self:addSlot( i,j,s)
            end
        end
    end
    self.banner = cpp_getBannerInstance(self.host)
end


---@Description Add a slot to the combat field
---@param col number
---@param row number
---@param side number
function CombatField:addSlot(col,row,side)
    CF_AddSlot(self.host, col, row, side)
end

---@Description Get a slot from the combat field
---@param col number
---@param row number
---@param side number
function CombatField:getSlot(col,row,side)
    return CF_GetSlot(self.host, col, row, side)
end

---@Description Add a character to the combat field
---@param col number
---@param row number
---@param side number
---@param animationPath string
---@param portraitPath string
function CombatField:addCharacter(col,row,side,animationPath,portraitPath)
    CF_AddCharacter(self.host, col, row, side, animationPath, portraitPath)
end

---@Description Get a character from the combat field
---@param characterID number
---@param side number
function CombatField:getCharacter(characterID,side)
    return CF_GetCharacter(self.host, characterID, side)
end

function CombatField:showBannerMsg(msg)
    print("CombatField:showBannerMsg called")
    cpp_Banner_SetMsg(self.banner, msg)
end

function CombatField:setBannerVisible(value)
    cpp_Banner_SetVisible(self.banner, value)
end

function CombatField:setBannerMsg(msg)
    cpp_Banner_SetMsg(self.banner, msg)
end

