package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"

MenuPanels = _G.MenuPanels


---@class Prompt
---@field mainPanel Panel
---@field promptLabel RTLabel
---@field btnTable table of RTLabel
---@field inputBoxes table of EditBox
Prompt = {
    ---@type Panel
    mainPanel = nil,
    ---@type RTLabel
    promptLabel = nil,

    ---@type table of  EditBox 
    inputBoxes = {},

    ---@type table of RTLabel
    btnTable = {},
    guiHost = nil,
}

function Prompt:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description initialize Prompt
---@param GUI_host pointer instance of GUI host
---@param msg string message to show
---@param isStandard boolean default true
function Prompt:init(GUI_host, msg ,isStandard )
    -- isStandard = isStandard or true

    self.guiHost = GUI_host
    self.mainPanel = Panel:new()
    self.mainPanel:init(GUI_host,0,0,0,0,nil)
    self.mainPanel:setAlignment(0.5,0.5)
    self.mainPanel:setSizeStr("30%","25%")
    self.mainPanel:setPosStr("50%","50%")

    self.promptLabel = RTLabel:new()
    self.promptLabel:init(GUI_host,msg,0,0,self.mainPanel.ptr)
    self.promptLabel:setPosStr("50%","20%")
    self.promptLabel:setAlignment(TextAlginment.Center)

    self.btnTable = {}

    -- print("is standard " .. tostring(isStandard) .. " " .. msg)
    if isStandard == true then

        self:addButton("OK",function()
            self.mainPanel:hideWithEffect(PanelShowType.Fade,250)
        end)
    end
    self.mainPanel:setVisible(false)
end

function Prompt:show(value)
    if self.mainPanel == nil then
        print("warning : mainPanel is nil")
        return
    end
    if value then
        self.mainPanel:setVisible(false)
        self.mainPanel:showWithEffect(PanelShowType.Fade,250)
    else
        self.mainPanel:setVisible(true)
        self.mainPanel:hideWithEffect(PanelShowType.Fade,250)
    end
end

function Prompt:setMsg(msg)
    self.promptLabel:setText(msg)
end

function Prompt:addButton(btnText, callback)
    if self.mainPanel == nil then
        print("warning : mainPanel is nil")
        return
    end
    local btn = RTLabel:new()
    btn:init(self.guiHost,btnText,0,0,self.mainPanel.ptr)
    -- btn:setPosStr("50%","80%")
    btn:setAlignment(TextAlginment.Center)
    btn:setHoverable(0,255,0,255,255,255,255,255)
    btn:setOnClickCallback(callback)
    table.insert(self.btnTable,btn)
    -- self.btnCOunt =  #self.btnTable
    -- print("now btn count is " .. #self.btnTable)

    self:arrangeBtns()
    return btn
end

function Prompt:arrangeBtns()
    local btnCount = #self.btnTable
    local spacing = 100/ (btnCount + 1)
    -- print("rearrange button  ????000000000000000000000000000000000000000000" )
    for i = 1, btnCount do
        local x = spacing * i
        local y = "80%"
        if #self.inputBoxes > 0 then
            y = "90%"
        end
        self.btnTable[i]:setPosStr(string.format("%.1f%%",x),y)
    end
end

---@Description get the button based on index
---@param btnIndex number index of the button
function Prompt:getBtn(btnIndex)
    return self.btnTable[btnIndex]
end

function Prompt:addInputBox(name,x,y,width, height)
    if self.mainPanel == nil then
        print("warning : mainPanel is nil")
        return
    end
    local inputBox = EditBox:new()
    inputBox:init(self.guiHost,x,y,width,height,self.mainPanel.ptr)

    -- table.insert(self.inputBoxes,inputBox)
    self.inputBoxes[name] = inputBox

    return inputBox
end

function Prompt:getInputBox(name)
    return self.inputBoxes[name]
end

function Prompt:ShowBtn(index, value)
    if self.btnTable[index] == nil then
        print("warning : btnTable[" .. index .. "] is nil")
        return
    end
    self.btnTable[index]:setVisible(value)
end