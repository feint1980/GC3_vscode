local commmon_icons = {}
local skill_icons = {}
local item_icons = {}

package.path = package.path .. ';./Assets/lua/Icons/?.lua;'
require "Move"
require "End"


IconGUI = {
   guiHandler = nil,
   selectIcon = nil,
   currentIndex = 1
}

function IconGUI.init(self,host)

    self.guiHandler = cppCreateGUIHandler(host,"./Assets/TB_GUI/selection.png", 68,68)

    commmon_icons["Move"] = Move
    commmon_icons["Move"].init(commmon_icons["Move"],host)

    -- addObject = commmon_icons["Move"].getObject(commmon_icons["Move"])
    cppGUIHandlerAddIcon(host,commmon_icons["Move"].iconObj)
    cppGuiHandlerSetIconPos(host,commmon_icons["Move"].iconObj,200,-300)

    commmon_icons["End"] = End
    commmon_icons["End"].init(commmon_icons["End"],host)
    cppGUIHandlerAddIcon(host,commmon_icons["End"].iconObj)
    cppGuiHandlerSetIconPos(host,commmon_icons["End"].iconObj,270,-300)

    self.selectIcon = cppGuiHandlerSetSelectedIcon(host,commmon_icons["Move"].iconObj)
    self.currentIndex = 1
    

end

function tablelength(T)
  local count = 0
  for _ in pairs(T) do count = count + 1 end
  return count
end

function IconGUI.onSignal(host, self,signal)
   
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
    --print("current index is " .. self.currentIndex)
    local index = 0
   
    for k,v in pairs(commmon_icons) do
        index = index + 1
        --print("loop through icon " .. v.name)
        --print("index now is " .. index)
        if index == self.currentIndex then
            --print("set icon " .. v.name)
            self.selectIcon = cppGuiHandlerSetSelectedIcon(host,v.iconObj)
        end
       
    end    
    
end

