
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
    self.ptr = TGUI_ListView_Create(host,tPosX,tPosY,tWidth,tHeight,tCollumNames,tCollumsSizes,parent)
end

function ListView:remove()
    cpp_tgui_remove_widget(self.host, self.ptr)
end


function ListView:setPos(x,y)
    TGUI_ListView_SetPos(self.ptr,x,y)
end

function ListView:setPosStr(x,y)
    TGUI_ListView_SetPosStr(self.ptr,x,y)
end

function ListView:setSize(width,height)
    TGUI_ListView_SetSize(self.ptr,width,height)
end

function ListView:setSizeStr(width,height)
    TGUI_ListView_SetSizeStr(self.ptr,width,height)
end

function ListView:getSize()
    return TGUI_ListView_GetSize(self.ptr)
end

---@param columnSizes table of collum sizes
function ListView:setColumnSizeRatios(columnSizes)
    TGUI_ListView_SetColumnSizeRatios(self.ptr,columnSizes)
end

function ListView:clearItems()
    TGUI_ListView_ClearItems(self.ptr)
end

function ListView:setDoubleClickCallBack(callback)
    TGUI_ListView_SetDoubleClickCallBack(self.ptr,callback)
end

---@param index number collum Index
function ListView:getSelectItemValue(index)
    index = index or 0
    return TGUI_ListView_GetSelectedItemValue(self.ptr,index)
end

---@Description add item to list
---@param item table of collum values
function ListView:addItem(item)
    TGUI_ListView_AddItem(self.ptr,item)
end

---@Description add item to list
---@
function ListView:addItemWithDataStr(item,data)
    TGUI_ListView_AddItemWithStrData(self.ptr,item,data)
end

---@Description get item data as string
---@param index number collum Index
function ListView:getItemDataStr(index)
    return TGUI_ListView_GetItemDataAsStr(self.ptr,index)
end

---@Description get selected item index
---@return number
function ListView:getSelectedItemIndex()
    return TGUI_ListView_GetSelectedItemIndex(self.ptr)
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
function TGUI_ListView_Create(host,tPosX,tPosY,tWidth,tHeight,tCollumNames,tCollumsSizes,parent)
    parent = parent or nil
    if #tCollumNames ~= #tCollumsSizes then
        print("(TGUI_ListView_Create)collum names and collum sizes must have same length")
        return nil
    end
    -- print("TGUI_ListView_Create called")
    -- print("table check")
    -- for k,v in pairs(tCollumNames) do
    --     print(k,v)
    -- end
    -- for k,v in pairs(tCollumsSizes) do
    --     print(k,v)
    -- end
    return cpp_ListView_Create(host,tPosX,tPosY,tWidth,tHeight,tCollumNames,tCollumsSizes,parent)
end

---@Description wrapper of cpp_ListView_SetPos
---@param listView pointer instance of TGUI ListView
---@param x number x position
---@param y number y position
function TGUI_ListView_SetPos(listView,x,y)
    cpp_ListView_SetPos(listView,x,y)
end


---@Description wrapper of cpp_ListView_SetPosStr
---@param listView pointer instance of TGUI ListView
---@param x string x position
---@param y string y position
function TGUI_ListView_SetPosStr(listView,x,y)
    cpp_ListView_SetPosStr(listView,x,y)
end

---@Description wrapper of cpp_ListView_SetSize
---@param listView pointer instance of TGUI ListView
---@param x number width
---@param y number height
function TGUI_ListView_SetSize(listView,x,y)
    cpp_ListView_SetSize(listView,x,y)
end

---@Description wrapper of cpp_ListView_SetSizeStr
---@param listView pointer instance of TGUI ListView
---@param x string width
---@param y string height
function TGUI_ListView_SetSizeStr(listView,x,y)
    cpp_ListView_SetSizeStr(listView,x,y)
end

---@Description wrapper of cpp_ListView_GetSize
---@param listView pointer instance of TGUI ListView
---@return number width
---@return number height
function TGUI_ListView_GetSize(listView)
    return cpp_ListView_GetSize(listView)
end

---@Description wrapper of cpp_ListView_SetColumnSizes
---@param listView pointer instance of TGUI ListView
---@param tCollumsSizes table of collum sizes
function TGUI_ListView_SetColumnSizeRatios(listView,tCollumsSizes)
    cpp_ListView_SetColumnSizeRatios(listView,tCollumsSizes)
end

---@Description wrapper of cpp_ListView_ClearItems
---@param listView pointer instance of TGUI ListView
function TGUI_ListView_ClearItems(listView)
    cpp_ListView_ClearItems(listView)
end

---@Description wrapper of cpp_ListView_AddItem
---@param listView pointer instance of TGUI ListView
---@param item pointer table of string
function TGUI_ListView_AddItem(listView,item)
    cpp_ListView_AddItem(listView,item)
end

---@Description wrapper of cpp_ListView_AddItemWithStrData
---@param listView pointer instance of TGUI ListView
---@param item pointer table of string
---@param data pointer string (data stored)
function TGUI_ListView_AddItemWithStrData(listView,item,data )
    cpp_ListView_AddItemWithStrData(listView,item,data)
end

---@Description wrapper of cpp_ListView_GetItemDataAsStr
---@param listView pointer instance of TGUI ListView
---@param index number
function TGUI_ListView_GetItemDataAsStr(listView,index)
    return cpp_ListView_GetItemDataAsStr(listView,index)
end

---@Description wrapper of cpp_ListView_SetDoubleClickCallBack
function TGUI_ListView_SetDoubleClickCallBack(listView,callback)
    cpp_ListView_SetDoubleClickCallBack(listView,callback)
end 

---@Description wrapper of cpp_ListView_GetSelectedItemValue
---@param listView pointer instance of TGUI ListView
---@param collumnIndex number
function TGUI_ListView_GetSelectedItemValue(listView,collumnIndex)
    local tCollumnIndex = collumnIndex or 0
    return cpp_ListView_GetSelectedItemValue(listView,tCollumnIndex)
end


---@Description wrapper of cpp_ListView_GetSelectedItemIndex
---@param listView pointer instance of TGUI ListView
function TGUI_ListView_GetSelectedItemIndex(listView)
    return cpp_ListView_GetSelectedItemIndex(listView)
end