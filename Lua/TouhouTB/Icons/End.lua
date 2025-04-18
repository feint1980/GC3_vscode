package.path = package.path .. ';../../Lua/TouhouTB/Icons/?.lua;'

require "Icon"

---@class End: Icon

---@Description End inherits from Icon
---@return End
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
    funct = function() End:endTurn(End.host) end,
    host = nil,
    selectionSide = 0,
    index = 2,
    requiredSlotCount = 0,
    slotFlag = 0, --  0 = none, 1 = empty only,2 = has character in slot
    charName = "None",
    turnCostStr = "",
    manaCostStr = ""
})

---@Description: Set the function to be called when the icon is selected/clicked
function End:selected()
    print(" end selected called")
    IssueNextPhase(self.host)
end


---@Description: Set the function to be called when the icon is selected/clicked
function End:endTurn(host)
    print(" end calllllled !!!!!")
end

