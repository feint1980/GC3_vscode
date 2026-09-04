package.path = package.path .. ';../../Lua/TouhouTB/Combat/?.lua;' 

-- require "clientGlobal" ---- this line is dangerous, caused the Lua to act stupid 
require "combatCharacter"
require "combatField_wrapper"

CombatField = {}
CombatField.__index = CombatField

function CombatField:new()
    local o = setmetatable({}, self)
    o.host = nil
    o.banner = nil
    o.dock = nil

    o.currentSelectedCharacter = nil -- a lua object of combatCharacter(Lua)
    o.characterWrappers = {}       -- keyed by "characterID_side" string
    o.characterWrappersByPtr = {}  -- keyed by raw cpp pointer

    o.currentInTurnCharacter = nil

    -- o.playerSide = 
    o.playerSideTable = {}

    self.__index = self
    return o
end

---@Description Set the player side into table
function CombatField:setPlayerSide(playerID,side)
    self.playerSideTable[playerID] = side
end

function CombatField:getCurrentSelectedCharacter()
    return self.currentSelectedCharacter
end

function CombatField:setCurrentCharacterInTurn(ownerID, characterID)

    local side = self.playerSideTable[ownerID]
    self.currentInTurnCharacter = self:getCharacter(characterID, side)

end

function CombatField:getCurrentCharacterInTurn()
    return self.currentInTurnCharacter
end

function CombatField:init(tHost,col,row)
    self.host = tHost
    -- self.playerSide = InfoHolder_getNumberVal("Player_Index")

    for s = 1, 2 do
        for i = 1, col do
            for j = 1, row do
                self:addSlot( i,j,s)
            end
        end
    end
    self.banner = cpp_getBannerInstance(self.host)
    self.dock = cpp_getDockInstance(self.host)
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
---@param characterID string
---@param portraitPath string
function CombatField:addCharacter(col,row,side,characterID,portraitPath)
    local charPtr = CF_AddCharacter(self.host, col, row, side, characterID, portraitPath)
    local wrapper = CombatCharacter:new(charPtr, characterID, side, self.host)

    local key = characterID .. "_" .. tostring(side)
    self.characterWrappers[key] = wrapper
    self.characterWrappersByPtr[charPtr] = wrapper

    return wrapper
end

---@Description Get a character from the combat field
---@param characterID number
---@param side number
function CombatField:getCharacter(characterID,side)

    -- Old
    -- local charPtr = CF_GetCharacter(self.host, characterID, side)
    -- if not charPtr then
    --     return nil
    -- end
    -- return CombatCharacter:new(charPtr, characterID, side, self.host)

    -- Cached : 
    local key = characterID .. "_" .. tostring(side)
    local cached = self.characterWrappers[key]
    if cached then
        return cached
    end

    -- if no cache, try to get from C++ side ( most likely you won't reach this)
    local charPtr = CF_GetCharacter(self.host, characterID, side)
    if not charPtr then
        return nil -- even in C++ side does not has it, it is obviously a null
    end

    -- if the pointer exist and it missed cache, add to cache

    local wrapper = CombatCharacter:new(charPtr, characterID, side, self.host)
    self.characterWrappers[key] = wrapper
    self.characterWrappersByPtr[charPtr] = wrapper
    return wrapper

end

---@Description Resolve a raw cpp CombatCharacter pointer back to its cached Lua wrapper.
---@param charPtr pointer
function CombatField:getCharacterByPointer(charPtr)
    return self.characterWrappersByPtr[charPtr]
end



function CombatField:showBannerMsg(msg)
    cpp_Banner_SetMsg(self.banner, msg)
end

function CombatField:setBannerVisible(value)
    cpp_Banner_SetVisible(self.banner, value)
end

function CombatField:setBannerMsg(msg)
    cpp_Banner_SetMsg(self.banner, msg)
end

function CombatField:setCharacterStats(characterID, side, characterStats)
    CF_SetCharacterStats(self.host, characterID, side, characterStats)
end

function CombatField:selectCharacterByMouse(posX, posY)
    print("CombatField:SelectCharacterByMouse - " .. posX .. "," .. posY)
    local charPtr = CF_SelectCharacterByMouse(self.host, posX, posY)
    if not charPtr then
        self.currentSelectedCharacter = nil
        print(" no selection found")
        return
    end

    self.currentSelectedCharacter = self:getCharacterByPointer(charPtr)
    -- print("CombatField:SelectCharacterByMouse - )
    print("selected " .. self.currentSelectedCharacter.key)
    if not self.currentSelectedCharacter then
        print("CombatField:SelectCharacterByMouse - pointer returned but not found in cache (character created outside addCharacter?)")
    end
end

function CombatField:FieldInfo_ListAll()
    CF_FieldInfo_ListAll(self.host)
end

function CombatField:selectCharacter(characterID,side)
    local key = characterID .. "_" .. tostring(side)
    self.currentSelectedCharacter = self.characterWrappers[key]
    if self.currentSelectedCharacter == nil then
        print("CombatField:selectCharacter - character not found: " .. tostring(characterID))
    end

end


-- =========================================================
-- Action presentation: step sequences
-- =========================================================

---@Description Run a single presentation step. Fire-and-forget steps (move/anim)
---start immediately and return; wait steps block the coroutine until the
---matching CC_Event fires.
---@param step table { type = "move"|"anim"|"waitMove"|"waitAnim", characterID, side, ... }
function CombatField:runStep(step)
    local character = self:getCharacter(step.characterID, step.side)
    if not character then
        print("CombatField:runStep - character not found: " .. tostring(step.characterID))
        return
    end

    if step.type == "move" then
        character:moveToCell(step.col, step.row, step.duration)

    elseif step.type == "anim" then
        character:playAnimation(step.animName, step.loop)

    elseif step.type == "waitMove" then
        character:waitMoveComplete()

    elseif step.type == "waitAnim" then
        character:waitAnimComplete()

    else
        print("CombatField:runStep - unknown step type: " .. tostring(step.type))
    end
end

---@Description Run an ordered sequence of steps as one coroutine.
---Steps with no wait between them effectively run concurrently
---(e.g. "move" then "anim" back to back both start the same tick).
---@param steps table array of step tables, executed in order
---@param onComplete function|nil called with no args once every step is done
function CombatField:playSequence(steps, onComplete)
    coroutine.wrap(function()
        for _, step in ipairs(steps) do
            self:runStep(step)
        end
        if onComplete then
            onComplete()
        end
    end)()
end

---@Description Example / test call: move a character to a cell with full animation sequencing.
---@param characterID string
---@param side number
---@param col number
---@param row number
---@param duration number seconds
function CombatField:testMoveSequence(characterID, side, col, row, duration)

    local steps = {
        { type = "move", characterID = characterID, side = side, col = col, row = row, duration = duration },
        { type = "anim", characterID = characterID, side = side, animName = "move", loop = false },
        { type = "waitMove", characterID = characterID, side = side },

        { type = "anim", characterID = characterID, side = side, animName = "stopAnimation", loop = false },
        { type = "waitAnim", characterID = characterID, side = side },

        { type = "anim", characterID = characterID, side = side, animName = "idle", loop = true },
    }


    self:playSequence(steps, function()
        print("testMoveSequence: " .. characterID .. " finished moving to (" .. col .. "," .. row .. ")")
    end)


end