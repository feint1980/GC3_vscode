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



