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




