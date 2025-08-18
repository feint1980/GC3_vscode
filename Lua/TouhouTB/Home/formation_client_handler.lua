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
    
    -- reset table
    for k in pairs (Formation_Table) do
        Formation_Table[k] = nil
    end
    Formation_Table = {}
    
    
end


ClientMessageHandling[PacketChannel.UserChannel][UserResponse.Formation_Data] = function(host,data, guid)

    local formationID, accoundID, formationName, index = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")
    
    print("formationID " .. formationID .. " accoundID " .. accoundID .. " formationName " .. formationName .. " index " .. index)
    
    Formation_Table[formationID] = Formation_Info:new()
    Formation_Table[formationID]:init(formationID, accoundID, formationName, index)

end



