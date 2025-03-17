print("server connections script started ...")

package.path = package.path .. ";../luaFiles/?.lua"


Clients = {}


--- function AddClient
--- @param client pointer instance of ClientScriptingManager
function AddClient(client)
    table.insert(Clients,client)
end