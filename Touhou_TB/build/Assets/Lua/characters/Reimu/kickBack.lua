package.path = package.path .. ';./Assets/lua/Icons/?.lua;' .. ';./Assets/Lua/system/?.lua'

require "Icon"
require "system"

KickBack = Icon:new({
    asset = "./Assets/TB_GUI/spell_1.png",
    name = "Hakurei's Kick",--"Bác Lệ Thần Cước",--"Hakurei's Kick",
    description = "",
    turnCost = 0.75,
    manaCost = 0,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    selectedFunct = function() KickBack:selected() end,
    funct = function()  end,
    host = nil,
    selectionSide = 2,
    index = 1,
    requiredSlotCount = 1,
    slotFlag = 2, --  0 = none, 1 = empty only,2 = has character in slot
    character = nil
})

kickCount = 0


function KickBack:init(host,dyobj,character)

    self.host = host
    self.dyobj = dyobj
    self.character = tCharacter
    local retStr = ""
    retStr = "Đá 1 đối tượng, gây <i><color=#ff1200>" --"Kick back a target, deals <i><color=#ff1200>"
    retStr = retStr .. tostring(character:getPhysicDmg() * 0.5 )
    retStr = retStr .. "</color></i><i><color=#FF5D00> Damage mod (50%)</color></i> sát thương vật lý "--"</color></i> damage"
    retStr = retStr .. "\nĐẩy đối tượng lui <i><color=#00ff1d>1</color></i> bước" --"\nSend the target back <i><color=#00ff1d>1</color></i> distance"

    self.iconObj =  cppCreateIcon(host,self.asset,64,64,self.name,retStr,self.turnCost,self.manaCost,self.turnCostStr,self.manaCostStr, self.specialID)

end



function kickBackSelected(host,dyobj)

    cppEntityPlayAnimation(host,dyobj,"hakurei_kick_ready",false,-1)
    coroutine.yield()
end

function KickBack:selected(host,character)
    print("move selected called")
    setPhase(host,2,2)
    t_slotHandler:onSignal(host,2,self.selectionSide,self.slotFlag)
    

    --cppEntityPlayAnimation(host,character.dyobj,"hakurei_kick_ready",false,-1)

    tasks[character.dyobj] = {behavior = coroutine.create(kickBackSelected,host,character.dyobj)}
    if coroutine.status(tasks[character.dyobj].behavior) ~= 'dead' then
        coroutine.resume(tasks[character.dyobj].behavior,host,character.dyobj)
    end
    --HandleSkillTasks(host,character.dyobj)
   -- cppEntityPlayAnimation(host,character.dyobj,"hakurei_kick_ready",-1)
    --coroutine.yield()
   
    -- todo, make the host now able to select the slot to move
end

function kickBackBehavior(host, dyobj)


    --cppClearEntityTasks(host,dyobj)

    print("kickBackBehavior called")
    local slots = t_slotHandler:getSelectedSlots()

    local count =  tablelength(slots)
    print("slot count " .. count)
    print("testttt ")
    if count ~= 1 then
        print("wrong number of slots selected")
        return
    end

    local slot = slots[1]
    local slot_posx, slot_posy = cppGetSlotPos(slot)
    local offset_x = -50
    local offset_y = 40

    local character = t_turnHandler:getCurrentCharacter()

    if character.side == 2 then
        offset_x = -offset_x
    end

    cppCameraTargetZoom(host,dyobj,false,slot_posx,slot_posy,3.7,5)
    cppEntityPlayAnimation(host,dyobj,"hakurei_kick_hit",false,-1)
    cppMoveEntity(host,dyobj,true,slot_posx + offset_x,slot_posy + offset_y ,5)
    
    -- offset_x = 50
    -- if character.side == 2 then
    --     offset_x = -offset_x
    -- end
    
    --cppWaitTime(host,dyobj,200)
   
    coroutine.yield()
    --coroutine.yield() -- wtf ? 
    local targetSlot = t_slotHandler:getSelectedSlots()[1]
    kickbackTarget = cppGetSlotEntity(host,targetSlot)
    if(kickbackTarget ~= nil) then
        cppEntityPlayAnimation(host,kickbackTarget,"hit_upper",false,-1)
    else
        print("kickbackTarget is nil")
    end

    -- for i = 1, kickCount do
    --     coroutine.yield()
    -- end
    --print("cppWaitTime @@@@@@@@")
    cppWaitTime(host,dyobj,40)
    --cppMoveEntity(host,dyobj,true,slot_posx + offset_x,slot_posy + offset_y,100)
    --os.execute("sleep " .. tonumber(200000))

    coroutine.yield()
   


    if(kickbackTarget ~= nil) then
        print("check evade roll !!!!!!!!!!!!!!!!!!")
        if kickbackTarget:determineEvade( character, dyobj) then 
            cppEntityPlayAnimation(host,kickbackTarget,"hit_upper_end",true,25)
            local currentSlotRow = cppGetSlotRow(targetSlot)
            local currentSlotCol = cppGetSlotCol(targetSlot)
            local targetSide = getInvertSide(character.side)
            if( currentSlotCol < 3) then
                currentSlotCol = currentSlotCol + 1
                local moveSlot = t_slotHandler:getSlot(currentSlotCol,currentSlotRow,targetSide)
                --local checkEmpty= 
                if cppIsSlotEmpty(host,moveSlot) ~= false then
                    cppEntityMoveToslot(host,kickbackTarget,moveSlot,25,false)
                end
                --coroutine.yield()
            end
        else 
            print("evaded")
            --cppEntityPlayAnimation(host,kickbackTarget,"evade",true,25)
        end
    else
        print("kickbackTarget is nil")
    end
    
    
    

    cppResetCamera(host,dyobj,false,20)

   

    local currentSlot = t_turnHandler:getCurrentCharacter().currentSlot
    cppEntityPlayAnimation(host,dyobj,"hakurei_kick_recover",false,1)
    cppEntityMoveToslot(host,dyobj,currentSlot,20)
    coroutine.yield()
  
    if(kickbackTarget ~= nil) then
        cppEntityPlayAnimation(host,kickbackTarget,"idle",false,-1)
    else
        print("kickbackTarget is nil")
    end
    
    cppEntityPlayAnimation(host,dyobj,"idle",false,-1)
    coroutine.yield()

    --coroutine.yield()
   

    cppClearEntityTasks(host,dyobj)
   
end


function KickBack:useFunction(host, character)
    print("KickBack use function called")

    kickCount = kickCount + 1
    
    -- if(tasks[character.dyobj] ~= nil) then
    --     print("task is not nil")
    --     tasks[character.dyobj].behavior = nil
    -- end
    tasks[character.dyobj] = {behavior = coroutine.create(kickBackBehavior,host,character.dyobj)}
    --coroutine.resume(tasks[character.dyobj].behavior,host,character.dyobj)
   HandleSkillTasks(host,character.dyobj)
    -- local x,y = cppGetEntityPos(character.dyobj)
    -- cppCameraTargetZoom(host,x,y,3.7,8)
    setPhase(host,1,3)
end

function cancelAnimation(host,dyobj)
    cppEntityPlayAnimation(host,dyobj,"hakurei_kick_cancel",true,1)
    coroutine.yield()
    cppEntityPlayAnimation(host,dyobj,"idle",false,-1)
    coroutine.yield()
end

function KickBack:onCancel(host,character)
    tasks[character.dyobj] = {behavior = coroutine.create(cancelAnimation,host,character.dyobj)}
    HandleSkillTasks(host,character.dyobj)
end
