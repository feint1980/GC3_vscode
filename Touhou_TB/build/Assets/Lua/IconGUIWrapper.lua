-- Manual wrapper because I want to mark all the function expose by C++
-- OCD warning : this file will contain alot of warning 

-- 
--  ||| Wrapper of Touhou Battle (Turn based) |||
--

-- MARK: GUI handler


---@class pointer
---@class vec2




---@Description wrapper of cppCreateGUIHandler
---@param host pointer instace of BattleScene
---@param imagePath string The path to the image file
---@param width number The width of the image
---@param height number The height of the image
---@return pointer instance of created GUIHandler
function TB_CreateGUIHandler(host,imagePath, width, height)
    return cppCreateGUIHandler(host, imagePath, width, height)
end

---@Description wrapper of cppGuiHandlerClearIcons
---@param host pointer instance of BattleScene
function TB_GuiHandlerClearIcons(host)
    cppGuiHandlerClearIcons(host)
end

---@Description wrapper of cppGUIHandlerAddIcon
---@param host pointer instance of BattleScene
---@param icon Icon The icon to add (lua)
function TB_GuiHandlerAddIcon(host,icon)
    cppGUIHandlerAddIcon(host,icon)
end

---@Description wrapper of cppGuiHandlerSetIconPos
---@param host pointer instance of BattleScene
---@param icon Icon The icon to add (lua)
---@param x number The x position of the icon
---@param y number The y position of the icon
function TB_GuiHandlerSetIconPos(host,icon,x,y)
    cppGuiHandlerSetIconPos(host,icon,x,y)
end

---@Description wrapper of cppGuiHandlerSetSelectedIcon
---@param host pointer instance of BattleScene
---@param icon Icon The icon to add (lua)
function TB_GuiHandlerSetSelectedIcon(host,icon)
    return cppGuiHandlerSetSelectedIcon(host,icon)
end

---@Description wrapper of cppGetIconPos
---@param icon Icon The icon to add (lua)
---@return vec2 The position of the icon
function TB_GetIconPos(icon)
    return cppGetIconPos(icon)
end