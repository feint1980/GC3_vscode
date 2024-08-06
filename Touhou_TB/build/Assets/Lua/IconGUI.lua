local commmon_icons = {}
local skill_icons = {}
local item_icons = {}

package.path = package.path .. ';./Assets/lua/Icons/?.lua;'
require "Move"
require "End"

IconGUI = {
   guiHandler = nil,
   selectIcon = nil
}

function IconGUI.init(self,host)

    self.guiHandler = cppCreateGUIHandler(host,"./Assets/TB_GUI/selection.png", 68,68)

    commmon_icons["Move"] = Move
    commmon_icons["Move"].init(commmon_icons["Move"],host)
    
   -- addObject = commmon_icons["Move"].getObject(commmon_icons["Move"])
    cppGUIHandlerAddIcon(host,commmon_icons["Move"].iconObj)
    cppGuiHandlerSetIconPos(host,commmon_icons["Move"].iconObj,200,-350)

    commmon_icons["End"] = End
    commmon_icons["End"].init(commmon_icons["End"],host)
    cppGUIHandlerAddIcon(host,commmon_icons["End"].iconObj)
    cppGuiHandlerSetIconPos(host,commmon_icons["End"].iconObj,270,-350)

end


