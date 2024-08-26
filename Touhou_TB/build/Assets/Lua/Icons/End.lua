package.path = package.path .. ';./Assets/lua/Icons/?.lua;'

require "Icon"

End = Icon:new({
    asset = "./Assets/TB_GUI/End.png",
    name = "End",
    description = "End the character turn",
    turnCost = 0,
    manaCost = 0,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    selectedFunct = function() End:selected() end,
    funct = function() End:endTurn() end,
    host = nil,
    selectionSide = 0,
    index = 2,
    requiredSlotCount = 0,
    charName = "None",
    turnCostStr = "",
    manaCostStr = ""
})

function End:selected()
    print(" end selected called")
    IssueNextPhase(host)
end



function End:endTurn(host)
    print(" end calllllled !!!!!")
end

