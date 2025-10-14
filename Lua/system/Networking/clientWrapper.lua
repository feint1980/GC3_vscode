---- include Lua libraries

package.path = package.path .. ";../../Lua/include/?.lua"

local json = require ("dkjson")


--- Classes declare

--- for CLient
PacketChannel ={
    AccountChannel = 1,
    UserChannel = 2,
    ShopChannel =3,
    TransactionChannel = 4,
    FormationChannel = 5
}

AccountResponse = {
    Alogin = 1,
    Aregister = 2,
    ARequesKey = 3
}

UserResponse = {
    MainInfo = 1,  --- account info (mon,souls)
    CharacterInfo = 2,
    SkillInfo = 3,
    SkillInfo_Start = 4,
    SkillInfo_Data = 5,
    SkillInfo_End = 6,
    OwnedCharacter_Request = 7,
    OwnedCharacter_Start = 8,
    OwnedCharacter_Data = 9,
    OwnedCharacter_End = 10,

}

FormationResponse = {
    Formation_Request = 1, ---- use for notification
    Formation_Start = 2,
    Formation_Data = 3,
    Formation_SubData = 4,
    Formation_End = 5,
    Formation_Add = 6,
    Formation_Remove = 7,
    Formation_Rename = 8,
    Formation_Info_Update = 9,
}


ShopResponse = {
    ShopChracterInfo = 1,
    ShopItemInfo = 2,
    ShopCharacterInfo_Begin = 3,
    ShopCharacterInfo_Data = 4,
    ShopCharacterInfo_End = 5,
    ShopCharacter_Buy = 6
}

---@Description combines packet
---@param type string type of packet to wrap
---@param list table data to wrap
---@return string
function CombinePackage(type,list)
    ----
    local returnValue = "|"
    returnValue = returnValue .. type .. "_REQUEST|" 
    for i = 1, #list do
        returnValue = returnValue .. list[i] .. "|"
    end
    returnValue = returnValue .. type .. "_END_REQUEST|"
    return returnValue
end

---@Description wraps packet
---@param channel number channel 
---@param request number type of packet to wrap
---@param list table data to wrap
---@return string
function WrapRequest(channel, request, list)


    local returnValue = ""
    returnValue = string.char(channel) .. string.char(request) .. "|"
    for i = 1, #list do
        returnValue = returnValue .. tostring(list[i]) .. "|"
    end
    -- returnValue = returnValue .. "|"
    return returnValue
end

--- split data into multiple part with special character and no of split
---@return table table of string data split
function SplitMessgae(message, character, no_of_split)
    local tTable;
    tTable = {};
    for str in string.gmatch(message, "([^" .. character .. "]+)") do
        table.insert(tTable, str);
    end
    return tTable
end

--- return client guid
--- @return string
function ClientGetGUID(host)
    return cppGetClientGUID(host)
end

---@ Description: encode table to json
---@param t table table to encode
---@param isIndent boolean indent or not
function JSON_Encode(t,isIndent)
    isIndent = isIndent or false
    return json.encode(t, { indent = isIndent })
end

---@Description: decode json to table
---@param data string 
---@return table decoded Lua table
---@return number position in the string after parsing finished
---@return number error if decode failed (nil if OK)
function JSON_Decode(data)
    
    local tbl, pos, err = json.decode(data)
    return tbl, pos, err
end
