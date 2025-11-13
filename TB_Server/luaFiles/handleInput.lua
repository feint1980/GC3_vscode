package.path = package.path .. ";../luaFiles/?.lua" 

require "serverWrapper"
require "SV_global"

HandleInputCMD["help"] = function(host, command, args)
    print("command list :")
    for k,v in pairs(HandleInputCMD) do
        print(k .. "\t - " .. CMDDescription[k]) 
    end
end
CMDDescription["help"] = "list all available commands"


HandleInputCMD["ls"] = function(host, command,args)
    for k,v in pairs(args) do
        print(v)
    end
    CH_List()
end
CMDDescription["ls"] = "list all connected client"

HandleInputCMD["pingall"] = function(host, command,args)

    local option = args[1]
    print("pingall " .. option .. " ...")

    if option == "c" or option == "client" then
        for k,v in pairs(ClientEPList) do
            print("ID : " .. v.name .. " \t|IP: " .. SV_GetIPString(v.IP) .. "\t|Ping: " .. SV_GetTargetPing(v.IP) )
        end
    end

    if option == "bs" or option == "server" then
        for k,v in pairs(BSEP_List  ) do
            print("ID : " .. v.name .. " \t|IP: " .. SV_GetIPString(v:getIP()) .. "\t|Ping: " .. SV_GetTargetPing(v:getIP()) )
        end
    end
end
CMDDescription["pingall"] = "ping all the ping from server or client"



