package.path = package.path .. ';../../Lua/TouhouTB/Combat/?.lua;' 

require "combatField_wrapper"

CombatField = {
    host = nil

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
                CF_AddSlot(self.host, i,j,s)
            end
        end
    end
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

-- function 

