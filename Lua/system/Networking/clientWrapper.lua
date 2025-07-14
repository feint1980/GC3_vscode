--- Classes declare

--- for CLient
PacketChannel ={
    AccountChannel = 1,
    UserChannel = 2,
    ShopChannel =3,
    TransactionChannel = 3
}

AccountResponse = {
    Alogin = 1,
    Aregister = 2,
    ARequesKey = 3
}

UserResponse = {
    MainInfo = 1,
    CharacterInfo = 2,
    ItemInfo = 3
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

    -- print("WrapRequest called ")
    local returnValue = ""
    returnValue = string.char(channel) .. string.char(request) .. "|"
    for i = 1, #list do
        returnValue = returnValue .. list[i] .. "|"
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
