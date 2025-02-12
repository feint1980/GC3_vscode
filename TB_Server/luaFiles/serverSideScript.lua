print("server side script started ...")

---@class Table
Table = {
    register_key = "register_key_table",
    account = "account_table";
    account_stats = "account_stats_table";
    character_base = "character_base_table";
    character_exisance = "character_existance_table";
}

T_Host = nil


PacketCode = {
    login = 35
}


ResponseHandle = {}


ResponseHandle[PacketCode.login] = function(host, message)
    print("login response found, processing")
    local pattern_start = "|LOGIN_REQUEST|"
    local firstIndex = string.find(message, pattern_start)
    local beginP = firstIndex + string.len(pattern_start)

    local pattern_end = "|LOGIN_END_REQUEST|"
    local endIndex = string.find(message, pattern_end)
    local endP = endIndex + string.len(pattern_end)

    local processResult = string.sub(message, beginP, endIndex - 1)
    --- dump 
    --- split id and account by the sigh | 
    -- local id = string.sub(processResult, string.find(processResult, "|") + 1)    
    -- local pw = string.sub(processResult, string.find(processResult, "|", string.find(processResult, "|") + 1) + 1)
    -- print("account name is " .. id)
    print("pw is " .. pw)


end

function Init(host)
    T_Host = host
end

function HandleMessage(host,message,requestCode)
    print("relay message")
    print(message)
    print("request code : " .. requestCode)

    if ResponseHandle[requestCode] ~= nil then
        ResponseHandle[requestCode](host, message)
    end

end

print("server side script ended ...")
