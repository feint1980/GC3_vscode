package.path = package.path .. ';./Assets/lua/Icons/?.lua;'

require "Icon"

Move = Icon:new({
    asset = "./Assets/TB_GUI/move.png",
    name = "Icon",
    description = "baseIcon",
    turnCost = 0.5,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    funct = function() Move:move() end,
    host = nil,
    index = 1
})


function Move:move()
    print("calllllled")
    -- todo, make the host now able to select the slot to move
end

