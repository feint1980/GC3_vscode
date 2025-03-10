---@class Login_Strip_Order
---@field firstStr string
---@field secondStr string 
Login_Strip_Order = {
    firstStr = "",
    secondStr = ""
    --- todo add more here
}


---@Description create new instance of Login_Strip_Order
---@return Login_Strip_Order
function Login_Strip_Order:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Login_Strip_Order:init(strFirst, strSecond)
    self.firstStr = strFirst
    self.secondStr = strSecond
end


OrderList = {

}

OrderList[Packet_OtherID.ID_LOGIN_NEG] = Login_Strip_Order:new()
OrderList[Packet_OtherID.ID_LOGIN_NEG]:init("|LOGIN_RES_NEG_REQUEST|","|LOGIN_RES_NEG_END_REQUEST|")

OrderList[Packet_OtherID.ID_LOGIN_POS] = Login_Strip_Order:new()
OrderList[Packet_OtherID.ID_LOGIN_POS]:init("|LOGIN_RES_POS_REQUEST|","|LOGIN_RES_POS_END_REQUEST|")

OrderList[Packet_OtherID.ID_REGISTER_NEG] = Login_Strip_Order:new()
OrderList[Packet_OtherID.ID_REGISTER_NEG]:init("|REGISTER_RES_NEG_REQUEST|","|REGISTER_RES_NEG_END_REQUEST|")

OrderList[Packet_OtherID.ID_REGISTER_POS] = Login_Strip_Order:new()
OrderList[Packet_OtherID.ID_REGISTER_POS]:init("|REGISTER_RES_POS_REQUEST|","|REGISTER_RES_POS_END_REQUEST|")