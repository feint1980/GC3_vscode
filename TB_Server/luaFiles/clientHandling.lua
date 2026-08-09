
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

    ClientEPList[guid] = ClientEP:new()
    ClientEPList[guid]:init(tSystemAddress, guid, name)
    -- ClientEPList[guid] = newClient
    ClientEPList[guid].name = name
    ClientEPList[guid].IP = tSystemAddress
    SV_addClientOnlineSession_CPP(guid, name, tSystemAddress)

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


---@Description check if the user valid (3 steps) 1: msgGUID/selfGUID 2: connectedGUID, 3: userID
---@param msgGUID string guid of the msg extracted 
---@param selfGUID string guid of the packet
---@param userID string userID extracted
---@param ip pointer instance of RakNet::SystemAddress
function CH_check_userValid(msgGUID , selfGUID ,userID,ip)

    -- print("msgGUID " .. msgGUID)
    -- print("selfGUID " .. selfGUID)
    -- print("userID " .. userID)
    --- guid check
    if msgGUID ~= selfGUID then
        print("invalid guid/selfGUID,  warning, craft packet found from ip " .. SV_GetIPString(ip) .. " " .. msgGUID .. "/" .. selfGUID)
        
        return false
    else
        -- print("guid check OK")
    end

    --- connected guid check 
    if CH_FindClient(msgGUID) == nil then
        print("client not found, warning, craft packet found from ip " .. SV_GetIPString(ip))
        return false
    else
        -- print("client found " .. CH_FindClient(msgGUID).name .. "|" .. SV_GetIPString(ip))
    end

    -- check if id and t_id match
    if userID ~= CH_FindClient(msgGUID).name then
        print("invalid user,  warning, craft packet found from ip " .. SV_GetIPString(ip))
        return false
    else
        -- print("user check OK")
    end
    return true
end


---@Description check if the data is extracted OK
---@param data table of data extracted
---@param channel number channel
---@param request number request 
function ExtractDataCheck(data, channel, request)

    -- print("data need to be check has size " .. #data)
    for i = 1, #data do
        if data[i] == nil then
            print("data " .. i .. " is nil, error from channel " .. channel .. " request " .. request)
            return false
        end
    end
    return true
end