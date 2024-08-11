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
    currentIndex = 1
}

function IconGUI:init(host)

    self.guiHandler = cppCreateGUIHandler(host,"./Assets/TB_GUI/selection.png", 68,68)

    -- commmon_icons["Move"] = Move
    -- commmon_icons["Move"].init(commmon_icons["Move"],host)

    -- -- addObject = commmon_icons["Move"].getObject(commmon_icons["Move"])
    -- cppGUIHandlerAddIcon(host,commmon_icons["Move"].iconObj)
    -- cppGuiHandlerSetIconPos(host,commmon_icons["Move"].iconObj,200,-300)

    -- commmon_icons["End"] = End
    -- commmon_icons["End"].init(commmon_icons["End"],host)
    -- cppGUIHandlerAddIcon(host,commmon_icons["End"].iconObj)
    -- cppGuiHandlerSetIconPos(host,commmon_icons["End"].iconObj,270,-300)

    -- self.selectIcon = cppGuiHandlerSetSelectedIcon(host,commmon_icons["Move"].iconObj)
    -- self.currentIndex = 1
    

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
    -- clear icons
    commmon_icons = {}
    tIndex = 0
    print("start loading from " .. character.name)
    for k,v in pairs(character.common_actions) do
        print("loading from " .. k)
        commmon_icons[k] = v
      
        cppGUIHandlerAddIcon(host,commmon_icons[k].iconObj)
        cppGuiHandlerSetIconPos(host,commmon_icons[k].iconObj,200 + (70 * tIndex),-300)
        if tIndex == 0 then
            self.selectIcon = cppGuiHandlerSetSelectedIcon(host,commmon_icons[k].iconObj)
        end
        tIndex = tIndex + 1
    end

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
    if button == 1 then
       
        if self.currentTTD ~= nil then
            print("select " .. self.currentTTD.name)
            self.currentTTD.funct()
        end
    end
end

function IconGUI:onSignal(host,signal)
   
    --print("original index is " .. self.currentIndex)
    tableCount = tablelength(commmon_icons)
    --print("got signal " .. signal)
    if signal == 1 then
        self.currentIndex = self.currentIndex - 1
    elseif signal == 2 then
        self.currentIndex = self.currentIndex + 1
    end
    if self.currentIndex > tableCount then
        self.currentIndex = 1
    end
    if self.currentIndex < 1 then
        self.currentIndex = tableCount
    end

    if signal == 32 then
        if self.currentTTD ~= nil then
            self.currentTTD.funct()
        end
    end

    --print("current index is " .. self.currentIndex)
    local index = 0
   
    for k,v in pairs(commmon_icons) do
        index = index + 1
        --print("loop through icon " .. v.name)
        --print("index now is " .. index)
        if index == self.currentIndex then
            --print("set icon " .. v.name)
            self.selectIcon = cppGuiHandlerSetSelectedIcon(host,v.iconObj)
            self.currentTTD = v
        end
       
    end    
    
end

