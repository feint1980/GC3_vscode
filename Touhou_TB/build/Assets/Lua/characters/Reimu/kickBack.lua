package.path = package.path .. ';./Assets/Lua/Icons/?.lua;' .. ';./Assets/Lua/system/?.lua' .. './Assets/Lua/system/event/?.lua'

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
    selectedFunct = function() KickBack:selected(KickBack.host, KickBack.dyobj) end,
    funct = function()  end,
    host = nil,
    selectionSide = 2, -- 1 = self, 2 = other
    index = 2,
    requiredSlotCount = 1,
    slotFlag = 2, --  0 = none, 1 = empty only,2 = has character in slot
    character = nil
})

KickCount = 0 -- try remove this, may be this is unused

function KickBack:init(host,dyobj,character)

    self.host = host
    self.dyobj = dyobj
    self.character = character
    local retStr = ""
    retStr = "Đá 1 mục tiêu, gây <i><color=#ff1200>" --"Kick back a target, deals <i><color=#ff1200>"
    retStr = retStr .. tostring(character:getPhysicDmg() * 0.5 )
    retStr = retStr .. "</color></i><i><color=#FF5D00> Damage mod (50%)</color></i> sát thương vật lý "--"</color></i> damage"
    retStr = retStr .. "\nĐẩy đối tượng lui <i><color=#00ff1d>1</color></i> bước" --"\nSend the target back <i><color=#00ff1d>1</color></i> distance"

    self.iconObj =  TB_CreateIcon(host,self.asset,64,64,
    self.name,retStr,self.turnCost,self.manaCost,
    self.turnCostStr,self.manaCostStr, self.specialID)

end


---@Description Kick back coroutine
---@param host pointer instance of BattleScene
---@param dyobj pointer instance of F_Lua_BaseEntity
function KickBackSelected(host,dyobj)

    print("KickBackSelected !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
    cppEntityPlayAnimation(host,dyobj,"hakurei_kick_ready",false,-1)
    coroutine.yield()
end

function KickBack:selected(host,character)
    print("move selected called")


    -- work around 
    if T_CurrentInputType == INPUT_type.Keyboard then
        T_slotHandler:onSignal(host,2,self.selectionSide,self.slotFlag)
    else
        if T_slotHandler.currentSlot ~= nil then
            T_slotHandler.currentSlot = nil
        end
    end

    SetPhase(host,2,2)
    --cppEntityPlayAnimation(host,character.dyobj,"hakurei_kick_ready",false,-1)
    tasks[character] = {behavior = coroutine.create(KickBackSelected,host,character)}
    if coroutine.status(tasks[character].behavior) ~= 'dead' then
        coroutine.resume(tasks[character].behavior,host,character)
    end
    --HandleSkillTasks(host,character.dyobj)
    -- cppEntityPlayAnimation(host,character.dyobj,"hakurei_kick_ready",-1)
    --coroutine.yield()

end

function kickBackBehavior(host, dyobj)

    --cppClearEntityTasks(host,dyobj)

    print("kickBackBehavior called")
    local slots = T_slotHandler:getSelectedSlots()

    local count = tablelength(slots)
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

    local character = T_turnHandler:getCurrentCharacter()

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
    local targetSlot = T_slotHandler:getSelectedSlots()[1]
    local kickbackTarget = cppGetSlotEntity(host,targetSlot)
    local kickBackTargetCharWrap = T_turnHandler:getCharacterFromDyobj(kickbackTarget)
    local rollHit = true
    if(kickbackTarget ~= nil) then
        if (kickBackTargetCharWrap ~= nil) then
            if kickBackTargetCharWrap:determineEvade( T_turnHandler:getCharacterFromDyobj(dyobj)) then
                rollHit = false
            end
        else
            print("kickbackTargetCharWrap is nil")
        end
    else
        print("kickbackTarget is nil")
    end

    if rollHit then
        print("roll hit")
        cppEntityPlayAnimation(host,kickbackTarget,"hit_under",false,1)
    else
        print("roll miss")
        cppEntityPlayAnimation(host,kickbackTarget,"evade",false,1)
    end


    -- for i = 1, KickCount do
    --     coroutine.yield()
    -- end
    --print("cppWaitTime @@@@@@@@")
    cppWaitTime(host,dyobj,40)
    --cppMoveEntity(host,dyobj,true,slot_posx + offset_x,slot_posy + offset_y,100)
    --os.execute("sleep " .. tonumber(200000))

    coroutine.yield()

    if rollHit then
        cppEntityPlayAnimation(host,kickbackTarget,"hit_under_end",true,25)
        local currentSlotRow = cppGetSlotRow(targetSlot)
        local currentSlotCol = cppGetSlotCol(targetSlot)
        local targetSide = getInvertSide(character.side)
        if( currentSlotCol < 3) then
            currentSlotCol = currentSlotCol + 1
            local moveSlot = T_slotHandler:getSlot(currentSlotCol,currentSlotRow,targetSide)
            --local checkEmpty=
            if cppIsSlotEmpty(host,moveSlot) ~= false then
                cppEntityMoveToslot(host,kickbackTarget,moveSlot,25,false)
            end
            --coroutine.yield()
        end
    end



    cppResetCamera(host,dyobj,false,20)



    local currentSlot = T_turnHandler:getCurrentCharacter().currentSlot
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

    KickCount = KickCount + 1

    -- if(tasks[character.dyobj] ~= nil) then
    --     print("task is not nil")
    --     tasks[character.dyobj].behavior = nil
    -- end
    tasks[character.dyobj] = {behavior = coroutine.create(kickBackBehavior,host,character.dyobj)}
    --coroutine.resume(tasks[character.dyobj].behavior,host,character.dyobj)
    HandleSkillTasks(host,character.dyobj)
    -- local x,y = cppGetEntityPos(character.dyobj)
    -- cppCameraTargetZoom(host,x,y,3.7,8)
    SetPhase(host,1,3)
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
