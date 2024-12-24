package.path = package.path .. ';./Assets/LuaFiles/Common/?.lua' .. ';./Assets/LuaFiles/Komachi/?.lua'

bc =  require("./Assets/Luafiles/common/boss_common")

require "general"
require "wrapper"
-- coroutine table
dynamics = {}

souls = {}
soulsCount = 0

komachi = nil
soul_1 = nil
t_soul = nil

function IssueNextTask(host, dynob)
    if coroutine.status(dynamics[dynob].behavior) ~= 'dead' then
		coroutine.resume(dynamics[dynob].behavior, host, dynob)
	else
		print(coroutine.status(dynamics[dynob].behavior))
	end
end

------------------------------------------------------------------

-- coin table
komachi_coins = {"komachi/komachi_12.png","komachi/komachi_11.png","komachi/komachi_13.png"}

-- charge table

charge_table = {"projectile/fire_1.png","projectile/fire_2.png","projectile/fire_3.png","projectile/fire_4.png"}

factor_table = {2,7,12,6}

-- Komachi param -- "./Assets/F_AObjects/boss_komachi.xml",
object = {posX = 0.0, posY = 0.0,
 animationPath = "./Assets/F_AObjects/komachi_boss_t.xml",
 scale = 0.6, depth = 15, angle = 0 }

-- soul param
soulData = {posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/komachi_effects.xml", scale = 1.0, depth = 15.0, angle = 0.0 }

-- init ( double click on the object in the editor ) note, path is unused for now
function CreateFromLua(host,path)
	print("[LUA] create from LUA called \n")

	komachi = W_createObject(host,object.animationPath,object.posX,object.posY,object.scale,object.depth,object.angle)
end

-- move set : normal 1 ( pre spell 1 )
function moveset_normal_1( host )

	dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior1,host,komachi)}
	IssueNextTask(host,komachi)
	isMovesetSelected = true

end
-- Belong to moveset_normal_1
function  DynamicBehavior1( host, dynob )
    local direct = {1,-1}
    local angle_count = 0
    local t_angle = 12 * 0.0174532925
	while true do
        for i = 1, 2 do
            DynamicBehavior1_base( host, dynob, direct[i])
        end
        W_moveObject(host,dynob,0,150,50)
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

    W_moveObject(host,dynob,150 * direction,150,25)
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
function moveset_spell_1(host)
    dynamics[komachi] = {behavior = coroutine.create(spell_1_boss_movement,host,komachi)}
    IssueNextTask(host,komachi)
 end

 -- handle fire rate of the souls
function souls_fire(host, dynob)

    
    angle = W_getObjectAngle(dynob)
    addon_angle = 190 * 0.0174532925
    fire_angle = angle - addon_angle
    invert_fire_angle = angle - 10 * 0.0174532925

    x = math.cos(fire_angle)
    y = math.sin(fire_angle)
    mX = math.cos(invert_fire_angle)
    mY = math.sin(invert_fire_angle)
    interval = 85 --*  math.abs( x + y)
    time = 300

    bullet_count = math.random(30,50)
    for t = 0, bullet_count do
        speed = G_randomFloat(0.5,1.7)
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

    thresholdValue = 50
    oldXMultiplyValue = 0
    while true do
        xMultiply = math.random(-4,4)
        yMultiply = math.random(0,3)
        oldXMultiplyValue = xMultiply
        while oldXMultiplyValue == xMultiply do
            xMultiply = math.random(-5,5)

        end
        oldXMultiplyValue = xMultiply
        W_moveObject(host,dynob,xMultiply * thresholdValue ,yMultiply * thresholdValue,100)
        coroutine.yield()
        --W_playAnimation(dynob,"charging",-1,true)
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
    x_border = 350
    for i = 1 , soulsCount
    do
        x,y = W_getObjectPos(souls[i])
        if (x > x_border or x < -x_border) then
            W_removeObject(host,souls[i])
        end
        if ( y < -600) then
            W_removeObject(host,souls[i])
        end
    end
end

-- spawn souls
function spawn_souls(host)
    spawn_number = math.random(1,3)
    pos_x_dif = 50
    pos_y_dif = 400
    x_vel_max = 2.2
    x_vel_min = 0.5
    for i = 1, spawn_number do
        x_multiplier = math.random(-7,7)
        x_location = x_multiplier * pos_x_dif

        local t_soul = W_createObject (host,soulData.animationPath,x_location  ,pos_y_dif,soulData.scale,soulData.depth,soulData.angle)
        x_vel = G_randomFloat(x_vel_min,x_vel_max)
        y_vel = G_randomFloat(-4.5,-3.0)
        if(x_location > 0) then
            x_vel = x_vel * -1
        end
        W_setObjectVel(t_soul,x_vel,y_vel)
        W_setObjectAfterImage(t_soul,0.1,100.0,20,0.0125,0.125,4.2)
        W_playAnimation(t_soul,"idle",-1,true)

        dynamics[t_soul] = {behavior = coroutine.create(souls_fire,host,t_soul)}
        IssueNextTask(host,t_soul)
        souls[soulsCount + 1] = t_soul
        soulsCount = soulsCount + 1

    end
end

-- end of move set : spell 1


-- move set : normal 2
function moveset_normal_2(host)
    dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior2,host,komachi)}
    IssueNextTask(host,komachi)
    isMovesetSelected = true
end

function DynamicBehavior2(host,dynob)

    count = 2
    xthresHold = 175
    while true do
        if (count > 1) then
            count = -1
            W_moveObject(host,dynob,0,170,25)
            coroutine.yield()
            W_playAnimation(dynob,"charging",1,false)
            cppObjectSetChargingEffect(dynob,"charge_table",charge_table,100,250,120,9.5,15.5)
            cppHoldPosition(host,dynob,80,"charging")
            coroutine.yield()
            W_playAnimation(dynob,"charge_end",1,true)
            bc.ftest_ma_custom_aff(host,dynob,"komachi/komachi_13.png",
            3.425, -- speed
            10.0,  -- lifeTime
            3,     -- k
            2,     -- n
            4,     -- n2
            2,     -- l1
            3,     -- l2
            -1,     -- posneg
            0,    -- startAngle
            1.3777,    -- angleStep
            45,    -- rotation
            3,     -- interval
            0)     -- time

            cppHoldPosition(host,dynob,200,"charge_end",false)
            coroutine.yield()
        end
        W_moveObject(host,dynob,count * xthresHold,150,30)
        coroutine.yield()
        cppHoldPosition(host,dynob,10,"charging")
        coroutine.yield()
        cppHoldPosition(host,dynob,200,"charge_end")
        bc.ftest_ma_custom_coin(host,dynob,"komachi_coins",komachi_coins,
        1, -- tier
        1.7, -- speed
        10.0,  -- lifeTime
        2,     -- k
        2,     -- n
        1,     -- n2
        2,     -- l1
        3,     -- l2
        1,     -- posneg
        0,    -- startAngle
        15.11,    -- angleStep
        0,    -- rotation
        5,     -- interval
        10)     -- time
        coroutine.yield()
        cppHoldPosition(host,dynob,1,"charge_end",false)
        coroutine.yield()
        count = count + 1
    end
end

-- end of move set : normal 2

-- move set : spell 2

function moveset_spell_2(host)
    dynamics[komachi] = {behavior = coroutine.create(spell_2_behavior,host,komachi)}
    IssueNextTask(host,komachi)
end

function spell_2_behavior(host,dynob)

    local x_index = -2
    local y_index = 5
    local x_pos_threshold = 100
    local y_pos_threshold = 40
    local increament = 1
    local reset = false

    local start = false
    local reach_right = false
    local reset_time = 60
    local increament_count = 1

    while true do
        if( start == false ) then
            W_moveObject(host,dynob,x_index * x_pos_threshold,y_pos_threshold * y_index,10 + reset_time )
            coroutine.yield()
        end

        if (start) then
            W_playAnimation(dynob,"cast",1,true)
        end
        x_index = x_index + increament
        start = true
        reset_time = 0

        cppHoldPosition(host,dynob,20,"charging",true)
        coroutine.yield()

        cppHoldPosition(host,dynob,1,"charge_end",true)
        spell_2_side_coin(host,dynob,
        increament,         -- direction
        0,                  -- tier
        "komachi_coins",    -- tableName
        komachi_coins,      -- tableAssets
        4.8,                -- speed
        9.0,               -- lifeTime
        -125 * 0.0174533,   -- current_angle
        -12 * 0.01745336 ,  -- angle_step
        0,                  -- interval
        0,                  -- time
        (180 - 55) * 0.0174533, -- addon_angle
        4,                  -- coin_line
        3)                  -- spread_time
        coroutine.yield()
        W_moveObject(host,dynob,x_index * x_pos_threshold,y_pos_threshold * y_index,7  )
        coroutine.yield()
        cppHoldPosition(host,dynob,15,"charge_end",true)
        coroutine.yield()
        --cppHoldPosition(host,dynob,20,"charge_end",true)

        if(reach_right) then
            if (x_index == 0) then
                for i = 1, 3 do
                    cppHoldPosition(host,dynob,20,"charging",true)
                    coroutine.yield()
                    cppHoldPosition(host,dynob,1,"charge_end",true)
                    spell_2_side_coin(host,dynob,
                    increament,         -- direction
                    1,                  -- tier
                    "komachi_coins",    -- tableName
                    komachi_coins,      -- tableAssets
                    2.6,                -- speed
                    10.0,               -- lifeTime
                    9 * 0.01745336,    -- current_angle
                    -9 * 0.01745336 ,  -- angle_step
                    0,                  -- interval
                    0,                 -- time
                    (180 - 60) * 0.0174533, -- addon_angle
                    5,                  -- coin_line
                    7)                  -- spread_time
                    y_index = y_index - 1
                    coroutine.yield()
                    W_moveObject(host,dynob,0 * x_pos_threshold,y_pos_threshold * y_index,10)
                    coroutine.yield()

                end

                W_playAnimation(dynob,"charging",1,false)
                cppObjectSetChargingEffect(dynob,"charge_table",charge_table,100,250,120,9.2,15.5)
                cppHoldPosition(host,dynob,80,"charging")
                coroutine.yield()

                bc.ftest_ma_custom_coin(host,dynob,"komachi_coins",komachi_coins,
                1, -- tier
                1.4, -- speed
                10.0,  -- lifeTime
                3,     -- k
                3,     -- n
                1,     -- n2
                2,     -- l1
                1,     -- l2
                -1,    -- posneg
                0,    -- startAngle
                1.1,    -- angleStep
                45 * increament_count,    -- rotation
                12,     -- interval
                1)     -- time

                bc.ftest_ma_custom_coin(host,dynob,"komachi_coins",komachi_coins,
                0, -- tier
                1.6, -- speed
                10.0,  -- lifeTime
                2,     -- k
                1,     -- n
                3,     -- n2
                1,     -- l1
                1,     -- l2
                -1,     -- posneg
                0,    -- startAngle
                2.25,    -- angleStep
                60 * increament_count,    -- rotation
                18,     -- interval
                1)     -- time
                cppHoldPosition(host,dynob,370,"cast")
                increament_count = increament_count + 1
                --cppHoldPosition(host,dynob,400,"cast")
                coroutine.yield()
                y_index = 5
                x_index = -2
                reach_right = false
                reset_time = 60
                start = false
            end
        end
        if (x_index >= 2) then
            increament = -1
            reach_right = true
        end
        if(x_index <= -2) then
            increament = 1
        end

    end
end

function spell_2_side_coin(host,dynob,direction,tier,tableName,tableAssets,speed,lifeTime,current_angle,angle_step,interval,time, addon_angle , coin_line, spread_time)

    addon_value = 0

    if (direction == -1) then
        addon_value = addon_angle --=  addon_value
    end
    t_current_angle = current_angle + addon_value

    additional_speed = 0.7

    for f = 1, coin_line do
        for i = 1, spread_time do
            x = math.cos((t_current_angle + i * (angle_step) ))
            y = math.sin((t_current_angle + i * (angle_step) ))
            cppSetFire_KomachiCoin(host,dynob,tableName,tableAssets,tier,
                            speed + additional_speed * f,lifeTime,x,y,f_angle,time + (interval  * (f * 25) ))
        end
    end
end


function moveset_normal_3(host)
    dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior3_normal,host,komachi)}
    IssueNextTask(host,komachi)
    isMovesetSelected = true
end


function DynamicBehavior3_normal(host,dynob)

    x_index = 0
    y_index = 2
    x_pos_threshold = 75
    y_pos_threshold = 100
    t_angle = 30 * 0.0174532925



    while true do


        W_moveObject(host,dynob,0,100,20)
        coroutine.yield()
        cppHoldPosition(host,dynob,10,"charging")

        coroutine.yield()
        cppHoldPosition(host,dynob,100,"charge_end")
        for angle_count = 1, 5 do
            bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_white.png",
            0.65, -- speed
            10.0, -- lifeTime
            5,   -- a
            4,   -- b
            50,   -- r
            2.5,  -- angleStep
            0,    -- startAngle
            angle_count * 360/5 * 0.0174532925,    -- rotation
            2,   -- interval
            120,  -- count
            100)  -- eventTime
            coroutine.yield()
        end
        coroutine.yield()
        cppAddBulletManipulatorPatern(host,"((a - b) * cos(t) + (c * cos((a / b - 1)*t))) *r","((a - b) * sin(t) - (c * sin((a / b - 1)*t))) *r",450,"factor_table",factor_table,0)
        --cppAddBulletManipulatorPatern(host,"a * 50","a - b * sin(t)",45,"factor_table",factor_table,0)
        for i = 1, 3 do
            x_index = math.random( -2,2 )
            y_index = math.random( 1,2 )
            W_moveObject(host,dynob,x_index * x_pos_threshold,y_pos_threshold * y_index,40)
            coroutine.yield()
            cppHoldPosition(host,dynob,10,"charging")
            coroutine.yield()
            cppHoldPosition(host,dynob,300,"charge_end")
            for angle_count = 1, 4 do
                bc.patern_MA_hypotrochoid(host,dynob,"projectile/bullet_shard_blue.png",
                0.65, -- speed
                7.0, -- lifeTime
                9,   -- a
                7,   -- b
                3,    -- c
                50,   -- r
                0.5,  -- angleStep
                0,    -- startAngle
                angle_count * 90 * 0.0174532925,    -- rotation
                10,   -- interval
                125,  -- count
                100)  -- eventTime
                coroutine.yield()
            end
            for angle_count = 1, 3 do
                bc.patern_MA_hypotrochoid(host,dynob,"projectile/bullet_medium_red.png",
                0.5, -- speed
                10.0, -- lifeTime
                2,   -- a
                3,   -- b
                5,    -- c
                50,   -- r
                0.33,  -- angleStep
                0,    -- startAngle
                angle_count * 120 * 0.0174532925,    -- rotation
                0,   -- interval
                100,  -- count
                100)  -- eventTime
                coroutine.yield()
            end
            coroutine.yield()
            cppHoldPosition(host,dynob,1,"charge_end",false)
            coroutine.yield()
            
        end
    end
end

function moveset_spell_3(host)
    dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior3,host,komachi)}
    IssueNextTask(host,komachi)
    isMovesetSelected = true
end


function DynamicBehavior3(host,dynob)

    while true do
        W_moveObject(host,dynob,0,150,20)
        coroutine.yield()

        cppHoldPosition(host,dynob,100,"charging")
        cppObjectSetChargingEffect(dynob,"charge_table",charge_table,100,250,120,9.5,15.5)
        coroutine.yield()
        cppHoldPosition(host,dynob,750,"charge_end")
        bc.ftest_ma_custom_aff2(host,dynob,
        "projectile/knife_red.png",
        0.85,    -- speed
        10.0,   -- lifeTime
        4,      -- n
        6,      -- n2
        3,      -- l1
        6,      -- l2
        1,      -- posneg
        3,      -- startAngle
        200,     -- angleStep
        0,      -- rotation
        10,      -- interval
        0,      -- time
        0,      -- id
        "slowdownCustomF2")      -- event)

        bc.ftest_ma_custom_aff2(host,dynob,
        "projectile/knife_yellow.png",
        0.85,    -- speed
        10.0,   -- lifeTime
        4,      -- n
        6,      -- n2
        3,      -- l1
        6,      -- l2
        -1,      -- posneg
        3,      -- startAngle
        200,     -- angleStep
        0,      -- rotation
        10,      -- interval
        0,      -- time
        0,      -- id
        "slowdownCustomF2")      -- event)


        bc.ftest_ma_custom_aff2(host,dynob,
        "projectile/bullet_shard_blue.png",
        0.85,    -- speed
        10.0,   -- lifeTime
        4,      -- n
        6,      -- n2
        3,      -- l1
        6,      -- l2
        1,      -- posneg
        3,      -- startAngle
        200,     -- angleStep
        45,      -- rotation
        10,      -- interval
        0,      -- time
        0,      -- id
        "slowdownCustomF3")      -- event)

        bc.ftest_ma_custom_aff2(host,dynob,
        "projectile/bullet_shard_yellow.png",
        0.85,    -- speed
        10.0,   -- lifeTime
        4,      -- n
        6,      -- n2
        3,      -- l1
        6,      -- l2
        -1,      -- posneg
        3,      -- startAngle
        200,     -- angleStep
        45,      -- rotation
        10,      -- interval
        0,      -- time
        0,      -- id
        "slowdownCustomF3")      -- event)


        coroutine.yield()

        -- W_moveObject(host,dynob,1,0,150)
        -- coroutine.yield()
    end
end