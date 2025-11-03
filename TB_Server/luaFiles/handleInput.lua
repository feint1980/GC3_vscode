package.path = package.path .. ";../luaFiles/?.lua" 

require "serverWrapper"
require "SV_global"


HandleInputCMD["help"] = function(host, command)

    print("command list :")
    for k,v in pairs(HandleInputCMD) do
        print(k)
    end
end

HandleInputCMD["ls"] = function(host, command)
    CH_List()
end