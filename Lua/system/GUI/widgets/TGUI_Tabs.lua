
-- ---@class Tabs
-- Tabs = {
--     host = nil,
--     ptr = nil,
--     posX = 0,
--     posY = 0,
--     width = 0,
--     height = 0,
--     ---@type pointer?
--     parent = nil
-- }

-- ---@Description create new instance of Tabs
-- ---@return Tabs
-- function Tabs:new(o)
--     o = o or {}
--     setmetatable(o, self)
--     self.__index = self
--     return o
-- end

-- --- MARK: Wrapper

-- --- Wrapper of cpp_Tabs_Create
-- ---@Description create new tgui Tabs object in cpp
-- ---@param host pointer instance of TGUIScriptingManager
-- ---@param numberOfTabs number x position
-- ---@param parent pointer instance TGUI_TabContainer, default nil (main)
-- ---@return pointer instance of TGUI Tabs
-- function TGUI_Tabs_Create(host, posX, posY, 
--     width, height, parent)
--     return cpp_Tabs_Create(host, posX, posY, width, height, parent)
-- end


