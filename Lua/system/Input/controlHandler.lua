Input_host = nil

Signal = {
    left = 1,
    right = 2,
    up = 4,
    down = 8,
    enter = 16,
    escape = 32,
    mouseLeft = 64,
}

---@type table of Panel
SignalReceivers = {
    stack = {},
    focusIndex = 0,
}



---@type table Label/Panel that can be focus switched
Parentless_Widgets = {

}
Parentless_WidgetsIndex = 0


function ControlHandler_Parentless_ChangeIndex(value)
    Parentless_WidgetsIndex = Parentless_WidgetsIndex + value
    if Parentless_WidgetsIndex > #Parentless_Widgets then
        Parentless_WidgetsIndex = 1
    elseif Parentless_WidgetsIndex < 1 then
        Parentless_WidgetsIndex = #Parentless_Widgets
    elseif #Parentless_Widgets == 0 then
        Parentless_WidgetsIndex = 0
    end
end

Panel_Widgets = {
    mainPanel = nil,
    subPanels = {},
    subLabels = {},
    currentSelection = 0
}

function Panel_Widgets:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Panel_Widgets:init(panel)
    self.mainPanel = panel
end

function Panel_Widgets:addLabel(label)
    -- print("")
    table.insert(self.subLabels,label)
end

function Panel_Widgets:removeLabel(label)
    for i = 1, #self.subLabels do
        if self.subLabels[i] == label then
            table.remove(self.subLabels,i)
        end
    end
end

function Panel_Widgets:autoFocus()
    if #self.subLabels > 0 then
        self.currentSelection = 1
    end
end
---@type table of Panel_Widgets
Panel_Focus_List = {

}

Dispatch_Recievers = {}

function ControlHandler_Init(host)
    Input_host = host

    print("ControlHandler_Init called")
end

function ControlHandler_DispatchSignal(host,tguiHost,signal)
    print("Get signal " .. signal)
    for k,v in pairs(Dispatch_Recievers) do
        if v ~= nil then
            v(host,tguiHost,signal)
        end
    end
    -- for i = 1, #SignalReceivers.stack do
    --     if SignalReceivers.stack[i] ~= nil then
    --         --- esc/B button hit
    --         if signal == 32 then
    --             TGUI_Panel_SetVisible(SignalReceivers.stack[i],true)
    --             TGUI_Panel_HideWithEffect(SignalReceivers.stack[i],0,250)
    --         elseif signal == 16 then
    --             ControlHandler_setCursorPos(0,0)
    --         end
    --         --- consider handle left/right/up/down
    --         --- todo here
    --     end
    -- end
end


function ControlHandler_registerPanel(panel)
    print("ControlHandler_registerPanel called ")
    local currentPanel = Panel_Widgets:new()
    currentPanel:init(panel)
    Panel_Focus_List[panel] = currentPanel
end

---@Description add the panel to focusable stack (now it will be focused)
function ControlHandler_reciever_push(GUI_Host,panel)
    print("ControlHandler_reciever_push called")
    --- check if the panel is already in the stack
    -- for i = 1, #SignalReceivers.stack do
    --     if SignalReceivers.stack[i] == panel then
    --         print("ControlHandler_reciever_push panel already in the stack, switched to " .. i)
    --         SignalReceivers.focusIndex = i
    --         return
    --     end
    -- end
    -- table.insert(SignalReceivers.stack, panel)
    -- SignalReceivers.focusIndex = #SignalReceivers.stack
    -- print("ControlHandler_reciever_push pushed " .. #SignalReceivers.stack)
    -- local panel = SignalReceivers.stack[SignalReceivers.focusIndex]
    -- ControlHandler_registerPanel(panel)

    --- new implement
    cpp_FocusStack_SetFocus(GUI_Host,panel)
end


function ControlHandler_reciever_pop()
    if #SignalReceivers.stack > 0 then
        table.remove(SignalReceivers.stack, #SignalReceivers.stack)
        SignalReceivers.focusIndex = #SignalReceivers.stack
    else
        print("stack is empty")
    end
end
function ControlHandler_reciever_remove(TGUIHost,panel)
    -- for i = 1, #SignalReceivers.stack do
    --     if SignalReceivers.stack[i] == panel then
    --         print("ControlHandler_reciever_remove removed " .. i)
    --         table.remove(SignalReceivers.stack, i)
    --         SignalReceivers.focusIndex = #SignalReceivers.stack
    --         return
    --     end
    -- end


    --- new implement
    cpp_FocusStack_RemovePanel(TGUIHost,panel)
end

function ControlHandler_reciever_getTop()
    if #SignalReceivers.stack == 0 then
        return nil
    end
    return SignalReceivers.stack[SignalReceivers.focusIndex]
end

function ControlHandler_receiver_switchFocus(panel)
    for i = 1, #SignalReceivers.stack do
        if SignalReceivers.stack[i] == panel then
            SignalReceivers.focusIndex = i
            print("switched to " .. i)
            return
        end
    end
end

---@Description set the cursor position 
---@param host pointer instance of TGUIScriptingManager
---@param x number x position
---@param y number y position
function ControlHandler_setCursorPos(host,x,y)
    print("ControlHandler_setCursorPos called ")
    if host == nil then
        print("Input_host is nil")
        return
    else
        cpp_ControlHandler_Cursor_Set(host,x,y)
    end
    -- TGUI_Panel_SetMousePos(Input_host,x,y)
end

---@Description get the cursor position 
---@return number x position, y position
function ControlHandler_getCursorPos()
    return cpp_ControlHandler_Cursor_Get()
end

---@Description fire left click event
---@param host pointer instance of TGUIScriptingManager
---@param times number (optional) times of fire
---@param x number (optional) x position
---@param y number (optional) y position
function Controller_fireLeftClickEvent(host,times,x,y)
    cpp_ControlHandler_Cursor_SendLeftClickEvent(host,times,x,y)
end

function ControlHandler_AddFocusableWidget(host,widget,parent)
    print("ControlHandler_AddFocusableWidget called")
    
    -- if parent == nil then
    --     print("parentless detected")
    --     table.insert(Parentless_Widgets,widget)
    --     if #Parentless_Widgets > 0 then
    --         Parentless_WidgetsIndex = 1
    --     end
    -- else
    --     print("parented detected")
    --     if Panel_Focus_List[parent] ~= nil then 
    --         print("panel detected")
    --         Panel_Focus_List[parent]:addLabel(widget)
    --     else
    --         ControlHandler_registerPanel(parent)
    --         Panel_Focus_List[parent]:addLabel(widget)
    --     end
    -- end

    --- new implement 
    cpp_FocusStack_AddFocusableLabel(host,widget,parent)
end

function ControlHandler_RemoveFocusableWidget(widget,parent)
    if parent == nil then
        for i = 1, #Parentless_Widgets do
            if Parentless_Widgets[i] == widget then
                table.remove(Parentless_Widgets,i)
                return
            end
        end
    else
        if Panel_Focus_List[parent] ~= nil then 
            Panel_Focus_List[parent]:removeLabel(widget)
        end
    end
end

function ControlHandler_Info()
    print("parentless widget sizes " .. #Parentless_Widgets)
    print("current parentless index " .. Parentless_WidgetsIndex)
    print("stack size " .. #SignalReceivers.stack)
    print("focus index " .. SignalReceivers.focusIndex)
    -- for i = 1, #Panel_Widgets do
    --     print("Panel " .. i .. " size " .. #Panel_Widgets[i].buttons)
    -- end
end