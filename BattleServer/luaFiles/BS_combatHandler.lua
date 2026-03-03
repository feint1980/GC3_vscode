--- Battle server, lobby section
package.path = package.path .. ";../luaFiles/?.lua" 


require "battleWrapper"
require "BS_global"
require "BS_handle_clients"
require "BS_formation"


ClientPacketHandling[ClientChannel.Combat][CCombatResponse.Combat_ReadyStatus] = function(host, channel, request,data,ip, guid)
    print("Combat_ReadyStatus detected from " .. guid)

end