local commmon_icons = {}
local skill_icons = {}
local item_icons = {}

package.path = package.path .. ';./Assets/lua/Icons/?.lua;'
require "Move"
require "End"


IconGUI = {
    guiHandler = nil,
    selectIcon = nil,
    currentTTD = nil,
    currentIndex = 1,
    selectionField = 1, -- 1 common 2 skill 3 item
    baseLine = -110
}


function IconGUI:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end




function IconGUI:init(host)

    self.guiHandler = cppCreateGUIHandler(host,"./Assets/TB_GUI/selection.png", 68,68)

end

function IconGUI:setFocusColor(host,r,g,b,a)

end

function IconGUI:setSelect(host,value)

end

function IconGUI:selectIcon(host,icon)
    cppSetHandlerSelected(host)
    cppSetPhase(host,icon.selectionSide)
end 

function IconGUI:loadIcons(host,character)


    -- if #commmon_icons > 0 then
    --     -- hide the last icons 
    --     print("hide the last icons")
    --    for k,v in pairs(commmon_icons) do
    --     print("hide icon " .. commmon_icons[k].name)
    --     cppGuiHandlerSetIconPos(host,commmon_icons[k].iconObj,5000,0)
    --     cppGuiHandlerRemoveIcon(host,commmon_icons[k].iconObj)
    --     end
    -- end

    -- if #skill_icons > 0 then
    --     -- hide the last icons
    --     print("hide the last icons")
    --    for k,v in pairs(skill_icons) do
    --     print("hide icon " .. skill_icons[k].name)
    --     cppGuiHandlerSetIconPos(host,commmon_icons[k].iconObj,5000,0)
    --     cppGuiHandlerRemoveIcon(host,skill_icons[k].iconObj)
    --     end
    -- end
    cppGuiHandlerClearIcons(host)

    -- clear icons
    commmon_icons = {}
    tIndex = 0
    print("start loading from " .. character.name)
    for k,v in pairs(character.common_actions) do
        print("loading from " .. k)
        commmon_icons[k] = v
        cppGUIHandlerAddIcon(host,commmon_icons[k].iconObj)
        cppGuiHandlerSetIconPos(host,commmon_icons[k].iconObj,self.baseLine + (70 * tIndex),-300)
        if tIndex == 0 then
            self.selectIcon = cppGuiHandlerSetSelectedIcon(host,commmon_icons[k].iconObj)
        end
        tIndex = tIndex + 1
    end

    skill_icons = {}
    tIndex = 0
    for k,v in pairs(character.skills) do
        print("loading from " .. k)
        skill_icons[k] = v
        cppGUIHandlerAddIcon(host,skill_icons[k].iconObj)
        cppGuiHandlerSetIconPos(host,skill_icons[k].iconObj,-600 +  (70 * tIndex),-300)
        tIndex = tIndex + 1
    end

    --self.baseLine = self.baseLine + 100
    print("end loading")

end

function tablelength(T)
  local count = 0
  for _ in pairs(T) do count = count + 1 end
  return count
end

function IconGUI:onMouseMove(host,x,y,button)
   -- print("mouse move " .. x .. " " .. y)
    for k,v in pairs(commmon_icons) do
        tX,tY = cppGetIconPos(v.iconObj)
        --print("x " .. tX .. " y " .. tY)
        -- each icon dimension is 64x64
        if x > tX - 32 and x < tX + 32 and y > tY - 32 and y < tY + 32 then
            --print("set icon " .. v.name)
            self.selectIcon = cppGuiHandlerSetSelectedIcon(host,v.iconObj)
            self.currentTTD = v
        end
    end    

    for k,v in pairs(skill_icons) do
        tX,tY = cppGetIconPos(v.iconObj)
        --print("x " .. tX .. " y " .. tY)
        -- each icon dimension is 64x64
        if x > tX - 32 and x < tX + 32 and y > tY - 32 and y < tY + 32 then
            --print("set icon " .. v.name)
            self.selectIcon = cppGuiHandlerSetSelectedIcon(host,v.iconObj)
            self.currentTTD = v
        end
    end
    

    if button == 1 then
        if self.currentTTD ~= nil then
            print("select " .. self.currentTTD.name)
            self.currentTTD:selectedFunct()
        end
    end
end

function IconGUI:getCurrentTTD()
    return self.currentTTD
end

function IconGUI:onSignal(host,signal)
   
    --print("original index is " .. self.currentIndex)

    --tCurrentTable = commmon_icons
    tableCount = 1
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


    
    --print("current index is " .. self.currentIndex)
    --print("selection field is " .. self.selectionField)
    if signal == 32 then
        --IssueNextPhase(host)
        if self.currentTTD ~= nil then
            self.currentTTD:selectedFunct()
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
                self.selectIcon = cppGuiHandlerSetSelectedIcon(host,v.iconObj)
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
                self.selectIcon = cppGuiHandlerSetSelectedIcon(host,v.iconObj)
                self.currentTTD = v
            end -- index == self.currentIndex
        end -- loop
    end -- if self.selectionField == 2
end

