package.path = package.path .. ';../../Lua/TouhouTB/skills/?.lua;'

require "homeGlobal"


ClientMessageHandling[PacketChannel.FormationChannel][FormationResponse.Formation_Request] = function(host,data, guid)

    local tData, response = string.match(data, "^|([^|]+)|([^|]+)|$")

    Prompt_UI_Table["Formation_Noti"]:setMsg(tData)
    Prompt_UI_Table["Formation_Noti"]:show(true)

    if response == "close" then
        Prompt_UI_Table["New_Formation"]:show(false)
    end
end


ClientMessageHandling[PacketChannel.FormationChannel][FormationResponse.Formation_Start] = function(host,data, guid)

    -- local t_guid,tData, data = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")
    -- print("recieve data " .. tData .. " from " .. t_guid .. " data " .. data  )


    local tData = string.match(data, "^|([^|]+)|$")

    print("got data " .. tData)

    local formationInfo, pos, err = JSON_Decode(tData)

    if err then
        print("Ke3 F3i117 exception (PacketChannel.FormationChannel][FormationResponse.Formation_Start)  JSON decode error:", err)
    end
    if formationInfo == nil then
        print("Ke3 F3i117 exception (PacketChannel.FormationChannel][FormationResponse.Formation_Start)")
        return
    end


    print("data start ----")
    print("guid " .. formationInfo.guid)
    print("id " .. formationInfo.id)
    print("cap " .. formationInfo.cap)

    for k,v in pairs(formationInfo.formation) do
        print("formationID " .. v.formationID)
        print("accountID " .. v.accountID)
        print("formationName " .. v.formationName)
        print("formationIndex " .. v.formationIndex)
        local size = GetTableSize(v.subData)
        print("sub data size " .. size)
        for k2,v2 in pairs(v.subData) do
            print(" charracterID : " .. k2)
            print(" slotIndex " .. v2.slotIndex)
            print(" rowPos " .. v2.rowPos)
            print(" colPos " .. v2.colPos)
        end
    end

    print("data end ")
    
    -- if t_guid == nil or tData == nil or cap == nil then
    --     print("Ke3 F3i117 exception (PacketChannel.FormationChannel][FormationResponse.Formation_Start)")
    --     return
    -- end

    -- print(tData)
    -- if tData == "request_ok" then
    --     print(cap)
    --     -- Prompt_UI_Table["New_Formation"]:show(true)
    -- else
    --     -- Prompt_UI_Table["New_Formation"]:show(false)
    -- end

    -- print("number of page reset")
    -- local nCap = tonumber(cap)
    -- if nCap == nil then
    --     return 
    -- end
    -- Formation_PageCap = nCap / 4
    -- -- Formation_Page = tonumbercap

    -- print("Formation_PageCap " .. Formation_PageCap)

    -- -- reset table
    -- for k in pairs (Formation_Table) do
    --     Formation_Table[k] = nil
    -- end
    -- Formation_Table = {}

    -- for i = 1, 4 do
    --     if Formation_PreviewPanel[i] ~= nil then
    --         Formation_PreviewPanel[i]:reset() -- reset all state
    --     end
    -- end

end

ClientMessageHandling[PacketChannel.FormationChannel][FormationResponse.Formation_Data] = function(host,data, guid)

    local formationID, accoundID, formationName, index = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")
    
    print("formationID " .. formationID .. " accoundID " .. accoundID .. " formationName " .. formationName .. " index " .. index)

    Formation_Table[formationID] = Formation_Info:new()
    Formation_Table[formationID]:init(formationID, accoundID, formationName, index)

    Formation_PreviewPanel[tonumber(index)]:update(accoundID, formationName)

end

ClientMessageHandling[PacketChannel.FormationChannel][FormationResponse.Formation_End] = function(host,data, guid)
    local t_guid, tData = string.match(data, "^|([^|]+)|([^|]+)|$")

    if t_guid == nil or tData == nil then
        print("Ke3 F3i117 exception (PacketChannel.FormationChannel][FormationResponse.Formation_End)")
        return
    end
    if t_guid == guid then
        if tData == "request_done" then
            print("formation request done")
        end
    end
end

ClientMessageHandling[PacketChannel.FormationChannel][FormationResponse.Formation_SubData] = function(host,data, guid)

    print("fomation sub data called ")

end





