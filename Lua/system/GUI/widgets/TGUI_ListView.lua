
---@class ListView
---@field host pointer instance of TGUIScriptingManager
---@field ptr pointer instance of TGUI ListView
---@field posX number x position
---@field posY number y position
---@field width number width
---@field height number height
---@filed collumNames table of collum names
---@field parent pointer instance of parent, default nil (main)
ListView = {
    ---@type pointer
    host = nil,
    ---@type pointer
    ptr = nil,
    posX = 0,
    posY = 0,
    width = 0,
    height = 0,
    collumNames = {},
    ---@type pointer
    parent = nil
}

---@Description create new instance of Label
---@return ListView
function ListView:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function ListView:init(host,tPosX,tPosY,tWidth,tHeight,tCollumNames,tCollumsSizes,parent)

    self.host = host
    self.ptr = TGUI_CreateListView(host,tPosX,tPosY,tWidth,tHeight,tCollumNames,tCollumsSizes,parent)
end





---- MARK: Wrapper
--- function wrapper of cpp_ListView_Create
---@Description create new tgui ListView object in cpp
---@param host pointer instance of TGUIScriptingManager
---@param tPosX number x position
---@param tPosY number y position
---@param tWidth number width
---@param tHeight number height
---@param tCollumNames table of collum names
---@param tCollumsSizes table of collum sizes
---@param parent? pointer instance parent, default nil (main)
---@return pointer? instance of TGUI ListView
function TGUI_CreateListView(host,tPosX,tPosY,tWidth,tHeight,tCollumNames,tCollumsSizes,parent)
    parent = parent or nil
    if #tCollumNames ~= #tCollumsSizes then
        print("(TGUI_CreateListView)collum names and collum sizes must have same length")
        return nil
    end
    print("TGUI_CreateListView called")
    print("table check")
    for k,v in pairs(tCollumNames) do
        print(k,v)
    end
    for k,v in pairs(tCollumsSizes) do
        print(k,v)
    end
    cpp_ListView_Create(host,tPosX,tPosY,tWidth,tHeight,tCollumNames,tCollumsSizes,parent)
end