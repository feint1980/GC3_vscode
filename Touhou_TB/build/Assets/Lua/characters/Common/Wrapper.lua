-- Manual wrapper because I want to mark all the function expose by C++
-- OCD warning : this file will contain alot of warning 

-- 
--  ||| Wrapper of Touhou Battle (Turn based) |||
--

-- MARK: Slot_handle


--- function wrapper of cppCreateSlotHandler
---@Description: Creates a new slot handler (SlotHandler)
---@param host pointer instace of BattleScene
---@return pointer instance of created SlotHandler
function TB_CreateSlotHandler(host)
    return cppCreateSlotHandler(host)
end

--- fucntion wrapper of cppCreateSlot
---@Description: Creates a new slot (Slot)
---@param host pointer instace of BattleScene
---@param row number The row of the slot
---@param col number The column of the slot
---@param side number 1 = left, 2 = right
---@return pointer instance of created Slot
function TB_CreateSlot(host,row,col,side)
    return cppCreateSlot(host,row,col,side)
end


--- fucntion wrapper of cppSetSlothandlerActive
---@Description: Set the active state of the slot handler (SlotHandler)
---@param host pointer instace of BattleScene
---@param value boolean The active state
function TB_SetSlothandlerActive(host,value)
    cppSetSlothandlerActive(host , value)
end

--- function wrapper of cppSelectHoverSlot
---@Description: Set the hover state of the slot (Slot) using handler (SlotHandler)
---@param slotHandler pointer instace of SlotHandler
---@param slot pointer instance of Slot
function TB_SelectHoverSlot(slotHandler, slot)
    cppSelectHoverSlot(slotHandler, slot)
end

--- function wrapper of cppIsSlotEmpty
---@Description: Check if the slot (Slot) is empty
---@param host pointer instace of BattleScene
---@param slot pointer instance of Slot
---@return boolean True if the slot is empty
function TB_IsSlotEmpty(host,slot)
    return cppIsSlotEmpty(host,slot)
end

--- function wrapper of cppSlotHandlerSetValidTarget
---@Description: Set the valid target state of the slot handler (SlotHandler)
---@param host pointer instace of BattleScene
---@param value boolean The valid target state
function TB_SlotHandlerSetValidTarget(host, value)
    cppSlotHandlerSetValidTarget(host, value)
end 


-- MARK: Slot

--- fucntion wrapper of cppGetSlotPos
---@Description: Get the position of the slot (Slot)
---@param slot pointer instance of Slot
---@return glm::vec2 The position of the slot
function TB_GetSlotPos(slot)
    return cppGetSlotPos(slot)
end

--- function wrapper of cppGetSlotRow
---@Description: Get the row of the slot (Slot)
---@param slot pointer instance of Slot
---@return number The row of the slot
function TB_GetSlotRow(slot)
    return cppGetSlotRow(slot)
end

--- function wrapper of cppGetSlotCol
---@Description: Get the column of the slot (Slot)
---@param slot pointer instance of Slot
---@return number The column of the slot
function TB_GetSlotCol(slot)
    return cppGetSlotCol(slot)
end

--- function wrapper of cppGetSlotEntity
---@Description: Get the entity (F_Lua_BaseEntity) of the slot (Slot)
---@param host pointer instace of BattleScene
---@param slot pointer instance of Slot
---@return pointer instance of F_Lua_BaseEntity
function TB_GetSlotEntity(host,slot)
    return cppGetSlotEntity(host,slot)
end

-- MARK: Entity

--- function wrapper of cppCreateEntity
---@Description: Creates a new entity (F_Lua_BaseEntity)
---@param host pointer instace of BattleScene
---@param animationPath string The path to the animation file
---@param slot pointer instance of Slot (created by TBD)
---@param portraitPath string (optional) The path to the portrait file
---@param side number (optional) 1 = left, 2 = right
---@param scale number (optional) The scale of the entity (both x and y)
---@param scaleY number (optional) only avaiable if you want x and y different scale
---@return pointer instance of created F_Lua_BaseEntity
function TB_CreateEntity(host,animationPath , slot, portraitPath, side,scale , scaleY)
    portraitPath = portraitPath or ""
    side = side or 1
    scale = scale or 1.0
    scaleY = scaleY or 1.0
    return cppCreateEntity(host,animationPath,slot,portraitPath,side,scale,scaleY)
end


--- function wrapper of cppMoveEntity
---@Description: Move an entity (F_Lua_BaseEntity)
---@param host pointer instace of BattleScene
---@param entity pointer instance of F_Lua_BaseEntity
---@param posX number The x position of the entity
---@param posY number The y position of the entity
---@param time number The time to complete the move
function TB_MoveEntity(host, entity, posX, posY, time)
    cppMoveEntity(host, entity, posX, posY, time)
end


--- funcion wrapper of cppSetAttribute
---@Description: Set the attribute of an entity (F_Lua_BaseEntity)
---@param entity pointer instance of F_Lua_BaseEntity
---@param attribute string The attribute to set
---@param value number The value to set
function TB_SetAttribute( entity, attribute, value)
    cppSetAttribute( entity, attribute, value)
end


-- function wrapper of cppSetStrAttribute
---@Description: Set the string attribute of an entity (F_Lua_BaseEntity)
---@param entity pointer instance of F_Lua_BaseEntity
---@param attribute string The attribute to set
---@param value string The value to set
function TB_SetStrAttribute( entity, attribute, value)
    cppSetStrAttribute( entity, attribute, value)
end

-- function wrapper of cppPickActiveEntity
---@Description: Pick an active entity (F_Lua_BaseEntity)
---@param host pointer instace of BattleScene
---@param entity pointer instance of F_Lua_BaseEntity will be picked
function TB_PickActiveEntity( host, entity)
    cppPickActiveEntity( host, entity)
end

-- MARK: Icon

--- function wrapper of cppCreateIcon
---@Description: Create an icon (Icon)
---@param host pointer instace of BattleScene
---@param iconPath string The path to the icon file
---@param slot pointer instance of Slot (created by TBD)
---@return pointer instance of created Icon
function TB_CreateIcon(host,assetPath,dimX, dimY,name,description,turnCost,manaCost)
    return cppCreateIcon(host,iconPath,slot)
end

