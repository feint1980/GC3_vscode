require "character"

TurnHandler = {

    currentCharacter = nil,
    charLists = {},
    totalCharList = {}

}

function TurnHandler:new(o)
    print("new TurnHandler called")
    o = o or {}
    setmetatable(o,self)
    self.__index = self
    return o    
end

function TurnHandler:getCurrentCharacter()
    return self.currentCharacter
end

function TurnHandler:getCurrentCharacterDyobj()
    if self.currentCharacter.dyobj ~= nil then
        return self.currentCharacter.dyobj  
    else
        print("getCurrentCharacterDyobj dyobj is nil ")
        return nil
    end

end

function TurnHandler:getActiveList()
    return self.charLists
end

function TurnHandler:addCharacter(character)
    --table.insert(self.charLists,character)
    if character.dyobj ~= nil then
        print("TurnHandler addCharacter OK ")
    else
        print("TurnHandler dyobj is nil ")
    end
    table.insert(self.totalCharList,character)

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
