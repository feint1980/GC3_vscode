
package.path = package.path .. ";../luaFiles/?.lua"
package.path = package.path .. ";../luaFiles/Client/?.lua"

require "serverWrapper"
require "clientEP"
require "SV_global"

---@type Table of ClientEP
ClientEPList = {}

---@type pointer instance of ClientEPHandler
CH_Host = nil

---@Description add a new client to the client list
---@param tSystemAddress pointer instance of systemAddress
---@param guid string guid of the client
---@param name string name of the client
function CH_AddClientEP(tSystemAddress, guid, name)

    print(" add user " .. name .. "|" .. guid .. "|")

    local newClient = ClientEP:new()
    newClient:init(tSystemAddress, guid, name)
    ClientEPList[guid] = newClient
    ClientEPList[guid].name = name

    -- ExistingCharacters[guid] = {} ---- Table of S_Characters

    -- ClientEPList[guid] = ClientEP:new(tSystemAddress, guid, name)
    -- print("total user now ")
    CH_List()
end

function CH_FindClient(guid)
    if ClientEPList[guid] ~= nil then
        return ClientEPList[guid]
    else 
        print("client " .. guid .. " not found")
        return nil
    end
end

function CH_List()

    print("total connected :... " ..GetTableSize(ClientEPList) .. " users")
    print("========================================")
    for k,v in pairs(ClientEPList) do
        print(v.name .. "|" .. k .. "|")
    end
    print("========================================")
end

function GetTableSize(t)
    local count = 0
    for _, _ in pairs(t) do
        count = count + 1
    end
    return count
end

function CH_Init(host)
    CH_Host = host
end

---- C++ Wrappers

---@Description Wrapper of cpp_ClientEPHandler_AddClientEP
---@param ip pointer ip of the systemAddress
---@param guid string guid of the client
---@param name string name of the client
function CH_cpp_addClientEP( ip, guid, name)
    CH_host = _G.CH_Host
    cpp_ClientEPHandler_AddClientEP(CH_host, ip, guid, name)
    
end

