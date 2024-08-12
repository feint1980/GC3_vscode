Slot = {

    asset = "./Assets/Textures/circle.png",
    row = 0,
    col = 0,
    side = 1, -- 1 = left, 2 = right
    slotObj = nil,
    dyobj = nil,
    pos_x = 0,
    pos_y = 0,
    state = 0

}

function Slot:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Slot:init(host,tRow,tCol,tSide)

    self.side = tSide
    self.row = tRow
    self.col = tCol
    self.slotObj = cppCreateSlot(host,self.row,self.col,self.side)
end

function Slot:setDyobj(tDyobj)

    self.dyobj = tDyobj
end