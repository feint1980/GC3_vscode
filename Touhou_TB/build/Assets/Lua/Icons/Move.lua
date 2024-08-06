
Move = {

    asset = "./Assets/TB_GUI/move.png",
    name = "Move",
    description = "Move to selected slot (0.5 turn per distance )",
    turnCost = 0.5,
    iconObj = nil,
    specialID = 1
}


function Move.init(self,host)
    --self.iconObj = 
    self.iconObj =  cppCreateIcon(host,self.asset,64,64,self.name,self.description,self.turnCost, self.specialID)

end

function Move.getObject(self)
    return self.iconObj
end