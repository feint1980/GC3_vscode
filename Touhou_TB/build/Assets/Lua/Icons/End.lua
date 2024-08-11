package.path = package.path .. ';./Assets/lua/Icons/?.lua;'

require "Icon"

End = Icon:new({
    asset = "./Assets/TB_GUI/End.png",
    name = "End",
    description = "baseIcon",
    turnCost = 0.5,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    funct = function() End:endTurn() end,
    host = nil,
    selectionSide = 0,
    index = 2
})


function End:endTurn()
    print(" end  calllllled")
end

