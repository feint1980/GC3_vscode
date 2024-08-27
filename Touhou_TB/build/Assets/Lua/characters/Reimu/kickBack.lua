package.path = package.path .. ';./Assets/lua/Icons/?.lua;'

require "Icon"


KickBack = Icon:new({
    asset = "./Assets/TB_GUI/spell_1.png",
    name = "Hakurei's Kick",
    description = "",
    turnCost = 0.75,
    manaCost = 0,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    selectedFunct = function() KickBack:selected() end,
    funct = function()  end,
    host = nil,
    selectionSide = 3,
    index = 1,
    requiredSlotCount = 1,
    character = nil
})


function KickBack:init(host,dyobj,character)

    self.host = host
    self.dyobj = dyobj
    self.character = tCharacter
    local retStr = ""
    retStr = "Kick back a target, deals <i><color=#ff1200>"
    retStr = retStr .. tostring( (character.Dexterity * 0.5) + (character.Agility * 0.25) + (character.Strength * 0.25) )
    retStr = retStr .. "</color></i> damage"
    retStr = retStr .. "\nSend the target back <i><color=#00ff1d>1</color></i> distance"

    self.iconObj =  cppCreateIcon(host,self.asset,64,64,self.name,retStr,self.turnCost,self.manaCost,self.turnCostStr,self.manaCostStr, self.specialID)

end

function KickBack:selected()
    print("move selected called")
    setPhase(self.host,2,2)

    -- todo, make the host now able to select the slot to move
end

function KickBack:useFunction(host, character)
    print("KickBack use function called")
end