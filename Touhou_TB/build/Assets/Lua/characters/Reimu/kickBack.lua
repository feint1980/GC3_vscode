package.path = package.path .. ';./Assets/lua/Icons/?.lua;'

require "Icon"


KickBack = Icon:new({
    asset = "./Assets/TB_GUI/spell_1.png",
    name = "KickBack",
    description = "Kick a target deal <i><color=#00ff1d>75 </color></i> damage.." ,
    turnCost = 0.75,
    manaCost = 0,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    selectedFunct = function() KickBack:selected() end,
    funct = function()  end,
    host = nil,
    selectionSide = 1,
    index = 1,
    requiredSlotCount = 1,
    charName = "None"
})


function KickBack:workOnString()
    
end

function KickBack:selected()
    print("move selected called")
    setPhase(self.host,2,2)

    -- todo, make the host now able to select the slot to move
end

function KickBack:useFunction(host, character)
    print("KickBack use function called")
end