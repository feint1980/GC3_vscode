package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"
require "Formation_Preview_Panel"
require "Prompt"
require "Formation_Edit"

MenuPanels = _G.MenuPanels

---@type Panel
FormationPanel = nil

---@type number
Formation_Page = 1
Formation_PageCap = 1

---@type Label
Formation_page_label = nil

---@type Panel 
Formation_preview_panel = nil

---@type table of FormationPreviewPanel
Formation_PreviewPanel = {}

---@type Panel
Formation_Edit_Panel = nil

---@type Formation_Edit
Formation_Edit_Instance = nil

---@type ScrollablePanel
Formation_CharacterList = nil

---@type number formation Selection
Formation_Selection = 0

local listCount = 0

function InitFormationMenu(host)
    -- Init main panel
    if FormationPanel == nil then 
        FormationPanel = Panel:new() 
        FormationPanel:init(host,TGUI_ScreenWidth/2 - 300,TGUI_ScreenHeight/2 - 200,600,400)
        FormationPanel:setSizeStr("80%", "80%")
        FormationPanel:setAlignment(0.5, 0.5)
        FormationPanel:setPosStr("50%", "50%")

        local closeLabel = Label:new()
        closeLabel:init(host,"X",FormationPanel.width - 20,0,FormationPanel.ptr)
        closeLabel:setPosStr("99%","1%")
        closeLabel:setAlignment(TextAlginment.Center)
        closeLabel:setHoverable(0,255,0,255,255,255,255,255)
        closeLabel:setOnClickCallback(function()
            FormationPanel:hideWithEffect(PanelShowType.Fade,250)
        end)

        local nextPageButton = Label:new()
        nextPageButton:init(host,">>",FormationPanel.width/2,0,FormationPanel.ptr)
        nextPageButton:setAlignment(TextAlginment.Center)
        nextPageButton:setPosStr("64%","2%")
        nextPageButton:setHoverable(0,255,0,255,255,255,255,255)
        nextPageButton:setOnClickCallback(function()
            FormationUpdatePage(1)
        end)

        local prevPageButton = Label:new()
        prevPageButton:init(host,"<<",FormationPanel.width/2,0,FormationPanel.ptr)
        prevPageButton:setAlignment(TextAlginment.Center)
        prevPageButton:setPosStr("36%","2%")
        prevPageButton:setHoverable(0,255,0,255,255,255,255,255)
        prevPageButton:setOnClickCallback(function()
            FormationUpdatePage(-1)
        end)

        Prompt_UI_Table["New_Formation_Page"] = Prompt:new()
        Prompt_UI_Table["New_Formation_Page"]:init(host,"Unlock new formation page for 5".. Tag.icon_soul .. "?" ,true)

        local newPageButton = Label:new()
        newPageButton:init(host,"New page",FormationPanel.width/2,0,FormationPanel.ptr)
        newPageButton:setAlignment(TextAlginment.Center)
        newPageButton:setPosStr("90%","2%")
        newPageButton:setHoverable(0,255,0,255,255,255,255,255)
        newPageButton:setOnClickCallback(function()
            Prompt_UI_Table["New_Formation_Page"]:show(true)
        end)

        if Formation_page_label == nil then
            Formation_page_label = Label:new()
            Formation_page_label:init(host,"",FormationPanel.width/2,0,FormationPanel.ptr)
            Formation_page_label:setAlignment(TextAlginment.Center)
            Formation_page_label:setPosStr("50%","1%")
            FormationUpdatePage(0)
        end

        if Formation_preview_panel == nil then
            Formation_preview_panel = Panel:new()
            Formation_preview_panel:init(host,0,0,600,400,FormationPanel.ptr)
            Formation_preview_panel:setAlignment(0.5,0.5)
            Formation_preview_panel:setPosStr("50%","26%")
            Formation_preview_panel:setSizeStr("95%","35%")
            -- Formation_preview_panel:setVisible(false)
        end

            --- init Formation Preview
        for i = 1, 4 do
            if Formation_PreviewPanel[i] == nil then
                Formation_PreviewPanel[i] = FormationPreviewPanel:new()
                Formation_PreviewPanel[i]:init(host,Formation_preview_panel.ptr,i)
            end
        end

        Prompt_UI_Table["Formation_Noti"] = Prompt:new()
        Prompt_UI_Table["Formation_Noti"]:init(host,"Notification",true)

        Prompt_UI_Table["New_Formation"] = Prompt:new()
        Prompt_UI_Table["New_Formation"]:init(host,"Name your Formation",false)

        Prompt_UI_Table["New_Formation"]:addInputBox("FormationName",100,100,300,40)
        Prompt_UI_Table["New_Formation"]:addButton("Create",function()
            local t_data =  Prompt_UI_Table["New_Formation"]:getInputBox("FormationName"):getText()

            if t_data == "" then
                print("empty ")
                Prompt_UI_Table["Formation_Noti"]:setMsg("it can't be empty")
                Prompt_UI_Table["Formation_Noti"]:show(true)
            else
                Formation_Request_Add(t_data)
                Home_RequestFormations() --- request update formation
            end
        end)

        Prompt_UI_Table["New_Formation"]:addButton("Cancel",function()
            Prompt_UI_Table["New_Formation"]:show(false)
        end)

        Prompt_UI_Table["Delete_Formation_Confirm"] = Prompt:new()
        Prompt_UI_Table["Delete_Formation_Confirm"]:init(host,"Delete this Formation?",false)

        Prompt_UI_Table["Delete_Formation_Confirm"]:addButton("Yes",function()
            Formation_Request_Remove(Formation_PreviewPanel[Formation_Selection].formationName)
            Prompt_UI_Table["Delete_Formation_Confirm"]:show(false)
            Home_RequestFormations() -- update formation
            Prompt_UI_Table["Formation_Noti"]:setMsg("Formation deleted")
            Prompt_UI_Table["Formation_Noti"]:show(true)
        end)

        Prompt_UI_Table["Delete_Formation_Confirm"]:addButton("Cancel",function()
            Prompt_UI_Table["Delete_Formation_Confirm"]:show(false)
        end)

        Prompt_UI_Table["Formation_Rename"] = Prompt:new()
        Prompt_UI_Table["Formation_Rename"]:init(host,"New formation name",false)

        Prompt_UI_Table["Formation_Rename"]:addInputBox("FormationNewName",100,100,300,40)
        Prompt_UI_Table["Formation_Rename"]:addButton("OK",function()
            local t_data =  Prompt_UI_Table["Formation_Rename"]:getInputBox("FormationNewName"):getText()

            if t_data == "" then
                print("empty ")
                Prompt_UI_Table["Formation_Noti"]:setMsg("New name can't be empty !")
                Prompt_UI_Table["Formation_Noti"]:show(true)

            elseif t_data == Formation_PreviewPanel[Formation_Selection].formationName then
                Prompt_UI_Table["Formation_Noti"]:setMsg("New name can't be the same as old name")
                Prompt_UI_Table["Formation_Noti"]:show(true)

            else
                Formation_Request_Rename(Formation_PreviewPanel[Formation_Selection].formationName,t_data)
                Prompt_UI_Table["Formation_Rename"]:show(false)
                Home_RequestFormations() --- request update formation
                Prompt_UI_Table["Formation_Noti"]:setMsg("Formation updated !")
                Prompt_UI_Table["Formation_Noti"]:show(true)
            end
        end)

        Prompt_UI_Table["Formation_Rename"]:addButton("Cancel",function()
            Prompt_UI_Table["Formation_Rename"]:show(false)
        end)

        if Formation_Edit_Panel == nil then
            Formation_Edit_Panel = Panel:new()
            Formation_Edit_Panel:init(host,0,0,600,400,FormationPanel.ptr)
            Formation_Edit_Panel:setAlignment(0.5,0.5)
            Formation_Edit_Panel:setPosStr("26.5%","72%")
            Formation_Edit_Panel:setSizeStr("48%","48%")
            Formation_Edit_Instance = Formation_Edit:new()
            Formation_Edit_Instance:init(host,Formation_Edit_Panel.ptr)
        end

        if Formation_CharacterList == nil then
            Formation_CharacterList = ScrollablePanel:new()
            Formation_CharacterList:init(host,0,0,600,400,FormationPanel.ptr)
            Formation_CharacterList:setAlignment(0.5,0.5)
            Formation_CharacterList:setPosStr("74.5%","72%")
            Formation_CharacterList:setSizeStr("46%","48%")
        end

    FormationPanel:setVisible(false)

    end

    -- Send To Get Formation Data from Server

    ---@type table
    -- MainInfo = _G.MainInfo

    -- print("Main info " .. MainInfo.guid .. " " .. MainInfo.id)

    -- SendRequest(PacketChannel.UserChannel, UserResponse.Formation_Request, {MainInfo.guid, MainInfo.id,"request"}, 5, 0.8,0.25)

    -- FormationPanel:hideWithEffect(PanelShowType.Fade,250)

end

function FormationUpdatePage(value)
    Formation_Page = Formation_Page + value
    if(Formation_Page > Formation_PageCap) then
        Formation_Page = 1
    end
    if (Formation_Page < 1) then
        Formation_Page = Formation_PageCap
    end
    Formation_page_label:setText("Page " .. Formation_Page .. "/" .. Formation_PageCap)
end

function Formation_Request_Add(name)

    local id, guid = MainInfo.id, MainInfo.guid

    print("Formation_Request_Add " .. id .. " " .. guid .. " " .. name .. " Index " .. Formation_Selection)

    SendRequest(PacketChannel.UserChannel, UserResponse.Formation_Add, {guid,id, name, tostring(Formation_Selection * Formation_Page )}, 5, 0.25)

end

function Formation_Request_Remove(name)

    local id, guid = MainInfo.id, MainInfo.guid

    print(" Formation_Selection * Formation_Page " .. (Formation_Selection * Formation_Page))
     SendRequest(PacketChannel.UserChannel, UserResponse.Formation_Remove, {guid,id, name, tostring(Formation_Selection * Formation_Page )}, 5, 0.25)
    print("name " .. name)
end

function Formation_Request_Rename(oldName, newName)
    local id, guid = MainInfo.id, MainInfo.guid

    SendRequest(PacketChannel.UserChannel, UserResponse.Formation_Rename, {guid,id, oldName, newName, tostring(Formation_Selection * Formation_Page )}, 5, 0.25)

end

function Formation_Request_InfoUpdate(name,data,size)
    local id, guid = MainInfo.id, MainInfo.guid


    local dataBuffer = "#"
    for i = 1, #data do
        dataBuffer = dataBuffer .. tostring(data[i]) .. "@"
        
    end

    dataBuffer = dataBuffer .. "#"
    dataBuffer = tostring(dataBuffer)
    print("databuffer " .. dataBuffer)

    SendRequest(PacketChannel.UserChannel, UserResponse.Formation_InfoUpdate, {guid,id ,name,tostring(Formation_Selection * Formation_Page ),size,dataBuffer} , 5,
    0.25)
    -- SendRequest(PacketChannel.UserChannel, UserResponse.Formation_InfoUpdate, 

    

    -- {guid,id, name, tostring(Formation_Selection * Formation_Page ), size, data }, 5, 0.25)

end


function FomrationUpdatePreviews(host)
    
end

local displayOwnedCharacterTable = {}

function FormationUpdateCharacterList(host)
    for k,v in pairs(Owned_CharacterTable) do
        print(k )
    end

    for k,v in pairs(displayOwnedCharacterTable) do
        table.remove(displayOwnedCharacterTable,k)
    end
    displayOwnedCharacterTable = {}
    listCount = 0

    for k,v in pairs(Owned_CharacterTable) do
        table.insert(displayOwnedCharacterTable,v)
    end

    table.sort(displayOwnedCharacterTable, function(a,b) return a.ID < b.ID end)
    for k,v in pairs(displayOwnedCharacterTable) do
        Formation_AddCharacterPanel(host,v.ID)
    end
end

function FormationSetPageCap(value)
    Formation_PageCap = value
end

function Formation_AddCharacterPanel(host, characterID)
        print("addCharPanel " .. characterID)
    local panelHeight = 80
    local pWidth, pHeight = Formation_CharacterList:getSize()

    if  Formation_OwnedCharacterPannels[characterID] == nil then
        Formation_OwnedCharacterPannels[characterID]= OwnedCharacterPanel:new()
    end
    print("Formation_OwnedCharacterPannels[characterID].init")
    Formation_OwnedCharacterPannels[characterID]:init(host,Formation_CharacterList,0,(listCount * panelHeight) + 5,pWidth,panelHeight ,characterID)

    Formation_OwnedCharacterPannels[characterID]:setHovereColor(0,255,0,255, 255,255,255,255)
    Formation_OwnedCharacterPannels[characterID]:setHoverableStop()

    Formation_OwnedCharacterPannels[characterID]:setOnClickCallback(function ()

        Formation_SelectCharacter(characterID)
    
    end)

    listCount = listCount + 1
end

function Formation_UpdateInfo(pageIndex)

end

function Formation_SelectCharacter(characterID)
    
    print("selected " .. characterID)

    -- Formation_Selection = characterID
    if Formation_Edit_Instance:hasSelected() then
        local selected = Formation_Edit_Instance:getSelected()
        if selected ~= nil then
            _G.Formation_Edit_Instance:updateList(characterID,selected.row,selected.col)
            -- selected:setCharacterID(characterID)
        end
    end
end

function Formation_MainUpdate(tguiHost)
    print("Formation_MainUpdate called")
    if Formation_Edit_Instance:hasSelected() then
        for k,v in pairs(Formation_OwnedCharacterPannels) do
            v:setHovereColor(255,255,0,255, 0,255,0,255)
        end
    else
        for k,v in pairs(Formation_OwnedCharacterPannels) do
            v:setHovereColor(0,255,0,255, 255,255,255,255)
            v:setHoverableStop()
        end
    end
    print("end")
end

MenuPanels["Formation"] = function(host)
    -- NexusCharacterTab:updateCharacters()
    FormationPanel:showWithEffect(PanelShowType.Fade,250)
    FomrationUpdatePreviews(host) 
    FormationUpdateCharacterList(host)
end
