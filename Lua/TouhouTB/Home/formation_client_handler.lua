package.path = package.path .. ';../../Lua/TouhouTB/skills/?.lua;'

require "homeGlobal"


ClientMessageHandling[PacketChannel.UserChannel][UserResponse.Formation_Request] = function(host,data, guid)

    local tData, response = string.match(data, "^|([^|]+)|([^|]+)|$")

    Prompt_UI_Table["Formation_Noti"]:setMsg(tData)
    Prompt_UI_Table["Formation_Noti"]:show(true)

    if response == "close" then
        Prompt_UI_Table["New_Formation"]:show(false)
    end
end


ClientMessageHandling[PacketChannel.UserChannel][UserResponse.Formation_Start] = function(host,data, guid)

    local t_guid,tData, cap = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")
    print("recieve data " .. tData .. " from " .. t_guid .. " cap " .. cap  )


    if t_guid == nil or tData == nil or cap == nil then
        print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.Formation_Start)")
        return
    end

    print(tData)
    if tData == "request_ok" then
        print(cap)
        -- Prompt_UI_Table["New_Formation"]:show(true)
    else
        -- Prompt_UI_Table["New_Formation"]:show(false)
    end

    print("number of page reset")
    local nCap = tonumber(cap)
    if nCap == nil then
        return 
    end
    Formation_PageCap = nCap / 4
    -- Formation_Page = tonumbercap

    print("Formation_PageCap " .. Formation_PageCap)

    -- reset table
    for k in pairs (Formation_Table) do
        Formation_Table[k] = nil
    end
    Formation_Table = {}

    for i = 1, 4 do
        if Formation_PreviewPanel[i] ~= nil then
            Formation_PreviewPanel[i]:reset() -- reset all state
        end
    end

end

ClientMessageHandling[PacketChannel.UserChannel][UserResponse.Formation_Data] = function(host,data, guid)

    local formationID, accoundID, formationName, index = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")
    
    print("formationID " .. formationID .. " accoundID " .. accoundID .. " formationName " .. formationName .. " index " .. index)

    Formation_Table[formationID] = Formation_Info:new()
    Formation_Table[formationID]:init(formationID, accoundID, formationName, index)

    Formation_PreviewPanel[tonumber(index)]:update(accoundID, formationName)

end

ClientMessageHandling[PacketChannel.UserChannel][UserResponse.Formation_End] = function(host,data, guid)
    local t_guid, tData = string.match(data, "^|([^|]+)|([^|]+)|$")

    if t_guid == nil or tData == nil then
        print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.Formation_End)")
        return
    end
    if t_guid == guid then
        if tData == "request_done" then
            print("formation request done")
        end
    end

end





