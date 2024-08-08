
End = {

    asset = "./Assets/TB_GUI/end.png",
    name = "End",
    description = "End the character's turn",
    turnCost = 0.5,
    iconObj = nil,
    specialID = 1
}


function End.init(self,host)
    --self.iconObj = 
    self.iconObj =  cppCreateIcon(host,self.asset,64,64,self.name,self.description,self.turnCost, self.specialID)

end

function End.getObject(self)
    return self.iconObj
end
