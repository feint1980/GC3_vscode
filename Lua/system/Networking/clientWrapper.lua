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
    ShopItemInfo = 2
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

RequestPacket = {
    channel = 255, 
    request = 255,
    data = "",
    retries = 5,
    sendTime = 0,
    delay = 50,
}

function RequestPacket:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

RequestQueue = {

}
RequestQueueIndex = 0

---@Description: create a send request and retries it
---@param host pointer instance of ClientScriptingManager
---@param typeOfRequest number type of request
---@param channel number channel
---@param request number request
---@param data string data
function SendRequestAttempt(host, typeOfRequest , channel, request, data )
    -- Reque
end

function ProcessRequestQueue(host)
    for k,v in pairs(RequestQueue) do
        
    end
end


-- for i = 1, #v do
--     local channel = v[i][1]
--     local request = v[i][2]
--     local data = v[i][3]
--     SV_SendWrapMsg(host, channel, request, data)
-- end


function Send(channel, request, data)
    -- Simulate send (replace with real function)
    -- Return 0 on failure, 1 on success
    return math.random() > 0.3 and 1 or 0 -- 70% success
end

-- Add request
function AddRequest(channel, request, data, retries)
    table.insert(RequestQueue, {
        channel = channel,
        request = request,
        data = data,
        retries = retries or 5,
        nextSendTime = os.clock(),
    })
end

function UpdateRequests()
    local now = os.clock()

    for i = #RequestQueue, 1, -1 do
        local req = RequestQueue[i]

        if now >= req.nextSendTime then
            local success = Send(req.channel, req.request, req.data)

            if success == 1 then
                print("[✔] Request sent:", req.channel, req.request)
                table.remove(RequestQueue, i)
            else
                req.retries = req.retries - 1
                if req.retries <= 0 then
                    print("[✘] Request failed after retries:", req.channel, req.request)
                    table.remove(RequestQueue, i)
                else
                    print("[↻] Retry scheduled:", req.channel, req.request, "retries left:", req.retries)
                    req.nextSendTime = now + RETRY_DELAY
                end
            end
        end
    end
end