---@class Login_Strip_Order
---@field firstStr string
---@field secondStr string 
Home_Strip_Order = {
    firstStr = "",
    secondStr = ""
    --- todo add more here
}


---@Description create new instance of Home_Strip_Order
---@return Home_Strip_Order
function Home_Strip_Order:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Home_Strip_Order:init(strFirst, strSecond)
    self.firstStr = strFirst
    self.secondStr = strSecond
end


Home_OrderList = {

}

Home_OrderList[Packet_OtherID.USER_DATA_POS] = Home_Strip_Order:new()
Home_OrderList[Packet_OtherID.USER_DATA_POS]:init("|USERDATA_RES_POS_REQUEST|","|USERDATA_RES_POS_END_REQUEST|")


Home_OrderList[Packet_OtherID.USER_DATA_NEG] = Home_Strip_Order:new()
Home_OrderList[Packet_OtherID.USER_DATA_NEG]:init("|USERDATA_RES_NEG_REQUEST|","|USERDATA_RES_NEG_END_REQUEST|")




