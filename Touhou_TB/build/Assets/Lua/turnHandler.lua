require "character"

---@Description of TurnHandler: This class controls handle turns in games
---@class TurnHandler
TurnHandler = {

    ---@type instance of Character
    currentCharacter = nil,
    charLists = {},
    totalCharList = {}

}

---@Description create a new instance of TurnHandler
---@return TurnHandler 
function TurnHandler:new(o)
    print("new TurnHandler called")
    o = o or {}
    setmetatable(o,self)
    self.__index = self
    return o    
end

---@Description: return the in turn character
---@return instance of Character
function TurnHandler:getCurrentCharacter()
    return self.currentCharacter
end

---@Description: Return the pointer of Character's dyobj | why this exist, I still do not know | May be it has null check ? 
---@return pointer of Character dyobj
function TurnHandler:getCurrentCharacterDyobj()
    if self.currentCharacter.dyobj ~= nil then
        return self.currentCharacter.dyobj  
    else
        print("getCurrentCharacterDyobj dyobj is nil ")
        return nil
    end
end


---@Description: return the list of Character
---@return table list of Character
function TurnHandler:getActiveList()
    return self.charLists
end


---@Decription: add Character into TurnHandler
---@param character instance of Character
function TurnHandler:addCharacter(character)
    --table.insert(self.charLists,character)
    if character.dyobj ~= nil then
        print("TurnHandler addCharacter OK ")
    else
        print("TurnHandler dyobj is nil ")
    end
    table.insert(self.totalCharList,character)

end

---@Description: get Character from dyobj
---@param dyobj pointer of Character dyobj
---@return instance of Character
function TurnHandler:getCharacterFromDyobj(dyobj)
    print("getCharacterFromDyobj called")
    for i = 1, #self.totalCharList do
        if self.totalCharList[i].dyobj == dyobj then
            print("found " .. self.totalCharList[i].name)
            return self.totalCharList[i]
        end
    end
    return nil
end

function TurnHandler:putCharacterIntoList()
    self.charLists = {}
    print("putCharacterIntoList called")
    for i = 1, #self.totalCharList do
        table.insert(self.charLists,self.totalCharList[i])
    end

    self:sortCharacter()
end

function TurnHandler:sortCharacter()

    print("sortCharacter called")

    table.sort(self.charLists, function(a,b) return a.Dexterity > b.Dexterity end)

    self.currentCharacter = self.charLists[1]
    print("check self.currentCharacter dyobj " )
    if self.currentCharacter.dyobj ~= nil then
        print("dyobj is not nil ")
    else
        print("dyobj is nil ")
    end
    for i = 1, #self.charLists do 
        portrait = cppGetEntityPortrait(self.charLists[i].dyobj)
        cppSetPortraitPos(portrait, i * 100, 400)

    end

end

function TurnHandler:display()
    for i = 1, #self.charLists do
        print(self.charLists[i].name .. " " .. self.charLists[i].Dexterity .. " " .. self.charLists[i].hp)
    end

end

function TurnHandler:nextTurn()
    if #self.charLists > 1 then
        self.currentCharacter = self.charLists[1]
        portrait = cppGetEntityPortrait(self.currentCharacter.dyobj)
        cppSetPortraitPos(portrait, -2000, 400)
        table.remove(self.charLists,1)
        self:sortCharacter()
        
    end
  
end
