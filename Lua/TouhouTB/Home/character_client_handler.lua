
package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/Home/Shop/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua'


require "clientWrapper"
require "homeGlobal"

ClientMessageHandling[PacketChannel.TransactionChannel][ShopResponse.ShopCharacter_Buy] = function(host,data, guid)

    -- strip first and last character 
    local tData, tResp = string.match(data, "^|([^|]+)|([^|]+)|$")
    local tCallBack = nil
    if tResp == "BUY_RES_OK" then
        tCallBack = function()
            Shop_CharacterShop = _G.Shop_CharacterShop
            Shop_CharacterShop:setDetailVisible(false)
            SendRequest(PacketChannel.ShopChannel,ShopResponse.ShopChracterInfo , {'get_character_shop_list'}, 5, 0.25)
        end
    end
    Home_Noti_Btn:setOnClickCallback(function()
        Home_Noti_Panel:hideWithEffect(PanelShowType.Fade,250)
        if tCallBack ~= nil then
            tCallBack()
        end
    end)

    Home_showNotification(tData, "OK")
    Home_UpdateInfo()
end

ClientMessageHandling[PacketChannel.UserChannel][UserResponse.OwnedCharacter_Start] = function(host,data, guid)

    local t_guid, tData = string.match(data, "^|([^|]+)|([^|]+)|$")
    print("Data is " .. tData)
    if tData ~= "request_ok" then
        print("K2 F3i117 exception")
        return 
    end
    if t_guid ~= MainInfo.guid then
        print("Ke3 F3i117 exception")
        return
    end

    for k in pairs (Owned_CharacterTable) do
        Owned_CharacterTable[k] = nil
    end

    Owned_CharacterTable = {}

end

local function parseOwnedCharacter(host, characterID,data)
    Home_ClientCharacterHandlerPtr = _G.Home_ClientCharacterHandlerPtr
    if characterID == "S_Reimu" then
        Owned_CharacterTable[characterID] = Reimu:new()
    elseif characterID == "S_Meiling" then
        Owned_CharacterTable[characterID] = Meiling:new()
    elseif characterID == "S_Patchouli" then
        Owned_CharacterTable[characterID] = Patchouli:new()
    elseif characterID == "S_Yukari" then
        Owned_CharacterTable[characterID] = Yukari:new()
    end

    local t_charStats =  Client_ParseCharacterFromJson(host, data)


    -- print("attemp to converse with data" .. data)
    ClientCharacterHandler_fillData(Home_ClientCharacterHandlerPtr,"Owned",characterID,t_charStats)
    Owned_CharacterTable[characterID]:initNonCB(Home_ClientCharacterHandlerPtr,"Owned",characterID,t_charStats)
end

ClientMessageHandling[PacketChannel.UserChannel][UserResponse.OwnedCharacter_Data] = function(host,data, guid)

    local t_guid, characterID, tData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")
    print("compare guid " .. t_guid .. "|" .. MainInfo.guid)
    if t_guid == MainInfo.guid then
        parseOwnedCharacter(host, characterID, tData)
    else
        print("Ke3 F3i117 exception")
        return
    end
    print("check data dump")
    for k,v in pairs(Owned_CharacterTable) do
        print(k .. " " .. v.name)
    end
end




