package.path = package.path .. ';./Assets/LuaFiles/Common/?.lua' .. ';./Assets/LuaFiles/Komachi/?.lua'

bc =  require("./Assets/Luafiles/common/boss_common")


require "general"

-- Belong to moveset_normal_1
function  DynamicBehavior1( host, dynob )
    local direct = {1,-1}
    local angle_count = 0
    local t_angle = 12 * 0.0174532925
	while true do
        for i = 1, 2 do
            DynamicBehavior1_base( host, dynob, direct[i])
        end
        cppMoveObject(host,dynob,0,150,50)
        coroutine.yield()

        bc.patern_MA_hypotrochoid(host,dynob,"projectile/bullet_shard_white.png",
        0.5, -- speed
        10.0, -- lifeTime
        3,   -- a
        7,   -- b
        12,    -- c
        25,   -- r
        0.75,  -- angleStep
        0 ,    -- startAngle
        0,    -- rotation
        0,   -- interval
        155,  -- count
        100,4)  -- eventTime
        coroutine.yield()


        local total_line = 12
        for i = 0, total_line do
            bc.patern_Feint_custom1(host,dynob,"projectile/bullet_shard_blue.png",
            2.5, -- speed
            10.0, -- lifeTime
            4,   -- a
            6,   -- b
            7,   -- c
            100,   -- r
            .2,   -- angleStep
            0 ,  -- startAngle
            (360/total_line * i) * 0.0174532925,  -- rotation
            1,   -- interval
            25,  -- count
            100,4)   -- eventTime
            coroutine.yield()
        end
        cppHoldPosition(host,dynob,200,"cast")
        coroutine.yield()
        cppSetBulletEvent(host,4,"max_1_5")
        angle_count = angle_count + 1
    end
end


function DynamicBehavior1_base( host, dynob, direction)

    cppMoveObject(host,dynob,150 * direction,150,25)
    coroutine.yield()

    bc.patern_Feint_custom1(host,dynob,"projectile/bullet_shard_blue.png",
        4.5 + (-1.0 * direction), -- speed
        10.0, -- lifeTime
        4,   -- a
        6,   -- b
        7,   -- c
        100,   -- r
        1.6,   -- angleStep
        0,  -- startAngle
        180 + (180 * direction),  -- rotation
        0,   -- interval
        50,  -- count
        100)   -- eventTime
    coroutine.yield()
    cppHoldPosition(host,dynob,30,"cast")
    coroutine.yield()
    cppHoldPosition(host,dynob,10,"idle",false )
    coroutine.yield()
end

-- moveset_normal_1 end

-- move set : spell 1


 -- handle fire rate of the souls
function souls_fire(host, dynob)

    local angle = cppGetObjectAngle(dynob)
    local addon_angle = 190 * 0.0174532925
    local fire_angle = angle - addon_angle
    local invert_fire_angle = angle - 10 * 0.0174532925

    local x = math.cos(fire_angle)
    local y = math.sin(fire_angle)
    local mX = math.cos(invert_fire_angle)
    local mY = math.sin(invert_fire_angle)
    local interval = 85 --*  math.abs( x + y)
    local time = 300

    local bullet_count = math.random(30,50)
    for t = 0, bullet_count do
        local speed = G_randomFloat(0.5,1.7)
        cppSetFire_Base(host,dynob,"projectile/bullet_shard_blue.png",
        speed, -- speed
        5.0, -- lifeTime
        x, -- x
        y, -- y
        angle, -- angle
        time + (t  * interval) )
        cppSetFire_Base(host,dynob,"projectile/bullet_shard_blue.png",
        speed, -- speed
        5.0, -- lifeTime
        mX, -- x
        mY, -- y
        0, -- angle
        time + (t  * interval) )
    end
    coroutine.yield()

end

-- handle boss's movement
function spell_1_boss_movement(host, dynob)

    local thresholdValue = 50
    local oldXMultiplyValue = 0
    while true do
        local xMultiply = math.random(-4,4)
        local yMultiply = math.random(0,3)
        oldXMultiplyValue = xMultiply
        while oldXMultiplyValue == xMultiply do
            xMultiply = math.random(-5,5)

        end
        oldXMultiplyValue = xMultiply
        cppMoveObject(host,dynob,xMultiply * thresholdValue ,yMultiply * thresholdValue,100)
        coroutine.yield()
        --cppOjbectPlayAnimation(dynob,"charging",-1,true)
        cppHoldPosition(host,dynob,70,"charging",true)
        cppObjectSetChargingEffect(dynob,"charge_table",charge_table,250,200,60,9.5,15.5)
        spawn_souls(host)
        coroutine.yield()
        cppHoldPosition(host,dynob,1,"charging",false)
        coroutine.yield()
        handle_souls(host)
    end

end

-- handle delete souls when out of bound
function handle_souls(host)
    local x_border = 350
    for i = 1 , soulsCount
    do
        local x,y = cppGetObjectPos(souls[i])
        if (x > x_border or x < -x_border) then
            cppRemoveFromLua(host,souls[i])
        end
        if ( y < -600) then
            cppRemoveFromLua(host,souls[i])
        end
    end
end

-- spawn souls
function spawn_souls(host)
    local spawn_number = math.random(1,3)
    local pos_x_dif = 50
    local pos_y_dif = 400
    local x_vel_max = 2.2
    local x_vel_min = 0.5
    for i = 1, spawn_number do
        local x_multiplier = math.random(-7,7)
        local x_location = x_multiplier * pos_x_dif

        local t_soul = cppCreateFromLua (host,soulData.animationPath,x_location  ,pos_y_dif,soulData.scale,soulData.depth,soulData.angle)
        local x_vel = G_randomFloat(x_vel_min,x_vel_max)
        local y_vel = G_randomFloat(-4.5,-3.0)
        if(x_location > 0) then
            x_vel = x_vel * -1
        end
        cppSetObjectVel(t_soul,x_vel,y_vel)
        cppSetAfterImage(t_soul,0.1,100.0,20,0.0125,0.125,4.2)
        cppOjbectPlayAnimation(t_soul,"idle",-1,true)

        dynamics[t_soul] = {behavior = coroutine.create(souls_fire,host,t_soul)}
        IssueNextTask(host,t_soul)
        souls[soulsCount + 1] = t_soul
        soulsCount = soulsCount + 1

    end
end

-- end of move set : spell 1
