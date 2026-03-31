package.path = package.path .. ';../../Lua/TouhouTB/skills/?.lua;'

require "homeGlobal"

ClientMessageHandling[PacketChannel.FormationChannel][FormationResponse.Formation_Request] = function(host,data, guid)

    local tData, response = string.match(data, "^|([^|]+)|([^|]+)|$")

    Prompt_UI_Table["Formation_Noti"]:setMsg(tData)
    Prompt_UI_Table["Formation_Noti"]:show(true)

    if response == "close" then
        Prompt_UI_Table["New_Formation"]:show(false)
        Home_RequestFormations()
    end
end

ClientMessageHandling[PacketChannel.FormationChannel][FormationResponse.Formation_Start] = function(host,data, guid)

    local tData = string.match(data, "^|([^|]+)|$")
    local formationInfo, pos, err = JSON_Decode(tData)

    if err then
        print("Ke3 F3i117 exception (PacketChannel.FormationChannel][FormationResponse.Formation_Start)  JSON decode error:", err)
    end
    if formationInfo == nil then
        print("Ke3 F3i117 exception (PacketChannel.FormationChannel][FormationResponse.Formation_Start)")
        return
    end

    if err then 
        print("[PacketChannel.FormationChannel][FormationResponse.Formation_Start] error", err)
        Prompt_UI_Table["New_Formation"]:setMsg("Error !!!!")
        Prompt_UI_Table["New_Formation"]:show(true)
        return
    end

    local nCap = tonumber(formationInfo.cap)
    if nCap == nil then
        return
    end
    EP_SendSignal("FormationInfo")
    Formation_PageCap = nCap / 4
    -- Formation_Page = tonumbercap
    -- -- reset info table
    for k in pairs (Formation_Table) do
        Formation_Table[k] = nil
    end
    Formation_Table = {}

    --- reset preview panel
    for i = 1, 4 do
        if Formation_PreviewPanel[i] ~= nil then
            Formation_PreviewPanel[i]:reset() -- reset all state
        end
    end

    print("formationInfo.formation iterating")
    for k,v in pairs(formationInfo.formation) do
        -- local tFormationIndex = tonumber(v.formationIndex)
        if Formation_Table[v.formationIndex] == nil then  
            Formation_Table[v.formationIndex] = Formation_Info:new()
        end
        local formationCharacterInfo = {}
        for k2,v2 in pairs(v.subData) do 
            formationCharacterInfo[v2.slotIndex] = Formation_CharacterInfo:new()
            formationCharacterInfo[v2.slotIndex]:init(k2, v2.slotIndex, v2.rowPos, v2.colPos)
        end
        Formation_Table[v.formationIndex]:init(v.formationID, v.formationName, v.formationIndex, formationCharacterInfo)
    end
    local currentPage = Formation_Page

    for i = 1, 4 do
        local infoIndex = tostring( i+ (4 * (currentPage -1)))
        -- local infoIndex = tostring( i)
        if Formation_Table[infoIndex] ~= nil then
            local tIndex = tonumber(infoIndex)

            for k,v in pairs(Formation_Table[infoIndex].formationCharacters) do
                print("characterID " .. v.characterID)
            end
            Formation_PreviewPanel[i]:setInfo(Formation_Table[infoIndex].formationCharacters)

            Formation_PreviewPanel[i]:update(Formation_Table[infoIndex].accountID, Formation_Table[infoIndex].formationName)

        else
            print("Formation_Table[" .. infoIndex .. "] is nil")
        end
    end

 
end

ClientMessageHandling[PacketChannel.FormationChannel][FormationResponse.Formation_Data] = function(host,data, guid)

    local formationID, accoundID, formationName, index = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")
    
    print("formationID " .. formationID .. " accoundID " .. accoundID .. " formationName " .. formationName .. " index " .. index)

    Formation_Table[formationID] = Formation_Info:new()
    Formation_Table[formationID]:init(formationID, accoundID, formationName, index)

    Formation_PreviewPanel[tonumber(index)]:update(accoundID, formationName)

end

-- ClientMessageHandling[PacketChannel.FormationChannel][FormationResponse.Formation_End] = function(host,data, guid)
--     local t_guid, tData = string.match(data, "^|([^|]+)|([^|]+)|$")

--     if t_guid == nil or tData == nil then
--         print("Ke3 F3i117 exception (PacketChannel.FormationChannel][FormationResponse.Formation_End)")
--         return
--     end
--     if t_guid == guid then
--         if tData == "request_done" then
--             print("formation request done")
--         end
--     end
-- end

-- ClientMessageHandling[PacketChannel.FormationChannel][FormationResponse.Formation_SubData] = function(host,data, guid)

--     print("fomation sub data called ")

-- end





