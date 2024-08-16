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

function TurnHandler:getActiveList()
    return self.charLists
end

function TurnHandler:addCharacter(character)
    --table.insert(self.charLists,character)
    table.insert(self.totalCharList,character)
end

function TurnHandler:putCharacterIntoList()
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
end

function TurnHandler:display()
    for i = 1, #self.charLists do
        print(self.charLists[i].name .. " " .. self.charLists[i].Dexterity .. " " .. self.charLists[i].hp)
    end

end

function TurnHandler:nextTurn()
    self.currentCharacter = self.charLists[1]
    table.remove(self.charLists,1)
    self:sortCharacter()
end
