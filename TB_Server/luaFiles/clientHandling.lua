
package.path = package.path .. ";../luaFiles/?.lua"

require "serverWrapper"


---@class (exact) ClientEP
---@field systemAddress pointer instance of systemAddress
---@field GUID string
---@field IP string
---@field name string
ClientEP = 
{
    systemAddress = nil,
    GUID = "",
    name = ""
}

--- Constructor
--- @return ClientEP
function ClientEP:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

--- initialize ClientEP
---@param tSystemAddress pointer instance of systemAddress
---@param guid string guid of the client
---@param name string name of the client
function ClientEP:init(tSystemAddress, guid, name)
    self.systemAddress = tSystemAddress
    self.GUID = guid
    self.name = name
end

---@type Table of ClientEP
ClientEPList = {}


---@Description add a new client to the client list
---@param tSystemAddress pointer instance of systemAddress
---@param guid string guid of the client
---@param name string name of the client
function CH_AddClientEP(tSystemAddress, guid, name)

    print(" add user " .. name .. "|" .. guid .. "|")
    local newClient = ClientEP:new()
    newClient:init(tSystemAddress, guid, name)
    ClientEPList[guid] = newClient
    -- ClientEPList[guid] = ClientEP:new(tSystemAddress, guid, name)
    print("total user now ")
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
    print("list start ...")
    for k,v in pairs(ClientEPList) do
        print(v.name .. "|" .. k .. "|")
    end
    print("list end !!!")
end

