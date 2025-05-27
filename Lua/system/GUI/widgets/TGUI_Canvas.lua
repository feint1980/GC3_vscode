-- ---@class (exact) Canvas
-- ---@field host pointer instance of TGUIScriptingManager
-- ---@field ptr pointer instance of TGUI Canvas
-- ---@field posX number x position
-- ---@field posY number y position
-- ---@field width number width
-- ---@field height number height
-- ---@field parent pointer instance of parent, default nil (main)
-- Canvas = {
--     ---@type pointer
--     host = nil,
--     ---@type pointer
--     ptr = nil,
--     posX = 0,
--     posY = 0,
--     width = 0,
--     height = 0,
--     ---@type pointer
--     parent = nil
-- }

-- ---@Description create new instance of Canvas
-- ---@return Canvas
-- function Panel:new(o)
--     o = o or {}
--     setmetatable(o, self)
--     self.__index = self
--     return o
-- end

-- ---@Description create new instance of Canvas

-- function Canvas:init(host , posX, posY, width, height, parent)
--     self.host = host
--     -- self.ptr = --
--     self.posX = posX
--     self.posY = posY
--     self.width = width
--     self.height = height
--     self.parent = parent
-- end



