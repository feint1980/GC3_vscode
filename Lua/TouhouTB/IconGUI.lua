local commmon_icons = {}
local skill_icons = {}
local item_icons = {}

package.path = package.path .. ';../../Lua/Icons/?.lua;'

require "IconGUIWrapper"

---@class instance

---@class IconGUI
---@field guiHandler? pointer instance of GuiHandler
---@field selectIcon? pointer instance of Icon
---@field currentTTD? Icon icon object
---@field currentIndex number
IconGUI = {
    guiHandler = nil,
    selectIcon = nil,
    currentTTD = nil,
    currentIndex = 1,
    selectionField = 1, -- 1 common 2 skill 3 item
    baseLine = -110
}

---@class INPUT_type
INPUT_type = {
    Keyboard = 1,
    Mouse = 2
}

T_CurrentInputType = INPUT_type.Mouse

---@Description create a new instance of IconGUI
---@return IconGUI
function IconGUI:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description init IconGUI
---@param host pointer instance of BattleScene
function IconGUI:init(host)
    self.guiHandler = TB_CreateGUIHandler(host,"./Assets/TB_GUI/selection.png", 68,68)
end

---@Description load icons from character
---@param host pointer instance of BattleScene
---@param character pointer instance of Character
function IconGUI:loadIcons(host,character)

    TB_GuiHandlerClearIcons(host)

    -- clear icons
    commmon_icons = {}
    local tIndex = 0
    print("start loading from " .. character.name)
    for k,v in pairs(character.common_actions) do
        print("loading from " .. k)
        commmon_icons[k] = v
        TB_GuiHandlerAddIcon(host,commmon_icons[k].iconObj)
        TB_GuiHandlerSetIconPos(host,commmon_icons[k].iconObj,self.baseLine + (70 * tIndex),-300)
        if tIndex == 0 then
            self.selectIcon = TB_GuiHandlerSetSelectedIcon(host,commmon_icons[k].iconObj)
        end
        tIndex = tIndex + 1
    end

    skill_icons = {}
    tIndex = 0
    for k,v in pairs(character.skills) do
        print("loading from " .. k)
        skill_icons[k] = v
        TB_GuiHandlerAddIcon(host,skill_icons[k].iconObj)
        TB_GuiHandlerSetIconPos(host,skill_icons[k].iconObj,-600 +  (70 * tIndex),-300)
        tIndex = tIndex + 1
    end

    --self.baseLine = self.baseLine + 100
    print("end loading")

end


---@Description get the length of a table
---@param T table
---@return number
function tablelength(T)
    local count = 0
    for _ in pairs(T) do count = count + 1 end
    return count
end


---@Description handle mouse move
---@param host pointer instance of BattleScene
---@param x number
---@param y number
---@param button number
function IconGUI:onMouseMove(host,x,y,button)
    T_CurrentInputType = INPUT_type.Mouse
    -- print("mouse move " .. x .. " " .. y)
    for k,v in pairs(commmon_icons) do
        local tX,tY = TB_GetIconPos(v.iconObj)
        --print("x " .. tX .. " y " .. tY)
        -- each icon dimension is 64x64
        if x > tX - 32 and x < tX + 32 and y > tY - 32 and y < tY + 32 then
            --print("set icon " .. v.name)
            self.selectIcon = TB_GuiHandlerSetSelectedIcon(host,v.iconObj)
            self.currentTTD = v
        end
    end

    for k,v in pairs(skill_icons) do
        local tX,tY = TB_GetIconPos(v.iconObj)
        --print("x " .. tX .. " y " .. tY)
        -- each icon dimension is 64x64
        if x > tX - 32 and x < tX + 32 and y > tY - 32 and y < tY + 32 then
            --print("set icon " .. v.name)
            self.selectIcon = TB_GuiHandlerSetSelectedIcon(host,v.iconObj)
            self.currentTTD = v
        end
    end

    if button == 1 then
        if self.currentTTD ~= nil then
            print("select " .. self.currentTTD.name)
            self.currentTTD:selected(host,T_turnHandler:getCurrentCharacter().dyobj)
        end
    end
end

---@Description get the current TTD (icon)
---@return Icon
function IconGUI:getCurrentTTD()
    return self.currentTTD
end

---@Description handle signal (keyboard/gamepad from C++)
function IconGUI:onSignal(host,signal)
    T_CurrentInputType = INPUT_type.Keyboard
    --print("original index is " .. self.currentIndex)

    --tCurrentTable = commmon_icons
    local tableCount = 1
    if self.selectionField == 1 then
        tableCount = tablelength(commmon_icons)
    elseif self.selectionField == 2 then
        tableCount = tablelength(skill_icons)
    end
    --print("got signal " .. signal)
    if signal == 1 then
        self.currentIndex = self.currentIndex - 1
    elseif signal == 2 then
        self.currentIndex = self.currentIndex + 1
    end
    if self.currentIndex > tableCount then
        self.currentIndex = 1
        self.selectionField = self.selectionField + 1

    end
    if self.currentIndex < 1 then
        self.currentIndex = tableCount
        self.selectionField = self.selectionField - 1

    end
    if self.selectionField > 2 then -- 2 for now, items isn't yet implemented
        self.selectionField = 1
    end
    if self.selectionField < 1 then
        self.selectionField = 2
    end

    if signal == 32 then
        --IssueNextPhase(host)
        if self.currentTTD ~= nil then
            self.currentTTD:selected(host,T_turnHandler:getCurrentCharacter())
        end
    end

    local index = 0
    if self.selectionField == 1 then
        for k,v in pairs(commmon_icons) do
            index = index + 1
            --print("loop through icon " .. v.name)
            --print("index now is " .. index)
            if index == self.currentIndex then
                --print("set icon " .. v.name)
                self.selectIcon = TB_GuiHandlerSetSelectedIcon(host,v.iconObj)
                self.currentTTD = v
            end -- index == self.currentIndex 
        end -- loop
    end -- if self.selectionField == 1

    if self.selectionField == 2 then
        for k,v in pairs(skill_icons) do
            index = index + 1
            --print("loop through icon " .. v.name)
            --print("index now is " .. index)
            if index == self.currentIndex then
                --print("set icon " .. v.name)
                self.selectIcon = TB_GuiHandlerSetSelectedIcon(host,v.iconObj)
                self.currentTTD = v
            end -- index == self.currentIndex
        end -- loop
    end -- if self.selectionField == 2
end

