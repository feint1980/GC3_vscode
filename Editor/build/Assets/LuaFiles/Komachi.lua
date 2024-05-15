bc =  require("./Assets/Luafiles/common/boss_common")

-- coroutine table
dynamics = {}

souls = {}
soulsCount = 0

komachi = nil
soul_1 = nil
t_soul = nil

-- init random seed
math.randomseed(os.time())

-- generic functions ( consider put them in a separate file )
function randomFloat(lower, greater)
    return lower + math.random()  * (greater - lower);
end


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

-- Komachi param
object = {posX = 0.0, posY = 0.0,
 animationPath = "./Assets/F_AObjects/boss_komachi.xml",
 scale = 0.6, depth = 15, angle = 0 }

-- soul param
soulData = {posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/komachi_effects.xml", scale = 1.0, depth = 15.0, angle = 0.0 }

-- init ( double click on the object in the editor ) note, path is unused for now
function CreateFromLua(host,path)
	print("[LUA] create from LUA called \n")

	komachi = cppCreateFromLua(host,object.animationPath,object.posX,object.posY,object.scale,object.depth,object.angle)

end

-- move set : normal 1 ( pre spell 1 )
function moveset_normal_1( host )

	dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior1,host,komachi)}
	IssueNextTask(host,komachi)
	isMovesetSelected = true

end
-- Belong to moveset_normal_1
function  DynamicBehavior1( host, dynob )
    direct = {1,-1}
    i = 1
	while true do 
        for i = 1, 2 do
            DynamicBehavior1_base( host, dynob, direct[i])
        end
        cppMoveObject(host,dynob,0,50,50)
        coroutine.yield()
        bc.patern_MA_hypotrochoid(host,dynob,"projectile/bullet_shard_white.png",
        0.5, -- speed
        10.0, -- lifeTime 
        7,   -- a
        9,   -- b 
        4,    -- c
        50,   -- r
        0.3,  -- angleStep
        0,    -- startAngle
        0,    -- rotation
        1,   -- interval
        900,  -- count
        100)  -- eventTime
        coroutine.yield()
        total_line = 12
        for i = 1, total_line do
            bc.patern_Feint_custom1(host,dynob,"projectile/bullet_shard_blue.png",
            2.5, -- speed
            10.0, -- lifeTime
            4,   -- a
            6,   -- b
            7,   -- c
            100,   -- r
            1.2,   -- angleStep
            0,  -- startAngle
            0 + (360/total_line * i),  -- rotation
            0,   -- interval
            50,  -- count
            100)   -- eventTime
            coroutine.yield()
        end
        cppHoldPosition(host,dynob,200,"cast")
        coroutine.yield()
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
function moveset_spell_1(host)
    dynamics[komachi] = {behavior = coroutine.create(spell_1_boss_movement,host,komachi)}
    IssueNextTask(host,komachi)
 end
 
 -- handle fire rate of the souls
function souls_fire(host, dynob)

    angle = cppGetObjectAngle(dynob)
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
        speed = randomFloat(0.5,1.7)
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
    while true do
        xMultiply = math.random(-4,4)
        yMultiply = math.random(0,3)    
        cppMoveObject(host,dynob,xMultiply * thresholdValue ,yMultiply * thresholdValue,50)
        coroutine.yield()
        cppHoldPosition(host,dynob,70,"idle",false)
        spawn_souls(host)
        coroutine.yield()
        handle_souls(host)
    end

end

-- handle delete souls when out of bound
function handle_souls(host)
    x_border = 350
    for i = 1 , soulsCount 
    do 
        x,y = cppGetObjectPos(souls[i])
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
    spawn_number = math.random(1,3)
    pos_x_dif = 50
    pos_y_dif = 400
    x_vel_max = 2.2
    x_vel_min = 0.5
    for i = 1, spawn_number do
        x_multiplier = math.random(-7,7)
        x_location = x_multiplier * pos_x_dif

        local t_soul = cppCreateFromLua (host,soulData.animationPath,x_location  ,pos_y_dif,soulData.scale,soulData.depth,soulData.angle)
        x_vel = randomFloat(x_vel_min,x_vel_max)
        y_vel = randomFloat(-4.5,-3.0)
        if(x_location > 0) then
            x_vel = x_vel * -1
        end
        cppSetObjectVel(t_soul,x_vel,y_vel)
        cppSetAfterImage(t_soul,0.1,100.0,20,0.0125,0.125,4.2)
        cppPlayAnimation(t_soul,"idle",-1,true)

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
    xthresHold = 125
    while true do 
        if (count > 1) then
            count = -1
            cppMoveObject(host,dynob,0,170,25)
            coroutine.yield()
            cppHoldPosition(host,dynob,200,"cast")

            bc.ftest_ma_custom_aff(host,dynob,"komachi/komachi_13.png",
            3.425, -- speed 
            10.0,  -- lifeTime
            2,     -- k
            4,     -- n
            4,     -- n2
            2,     -- l1
            1,     -- l2
            -1,     -- posneg
            0,    -- startAngle
            2.5,    -- angleStep
            45,    -- rotation
            3,     -- interval
            100)     -- time
            coroutine.yield()

            cppHoldPosition(host,dynob,1,"idle",false)
            coroutine.yield()
        end
        cppMoveObject(host,dynob,count * xthresHold,150,30)
        coroutine.yield()
        cppHoldPosition(host,dynob,85,"cast")
        
        bc.ftest_ma_custom_coin(host,dynob,"komachi_coins",komachi_coins,
        1, -- tier
        2.9, -- speed 
        10.0,  -- lifeTime
        2,     -- k
        1,     -- n
        2,     -- n2
        2,     -- l1
        1,     -- l2
        1,     -- posneg
        0,    -- startAngle
        1.2,    -- angleStep
        45,    -- rotation
        4,     -- interval
        100)     -- time

        coroutine.yield()
        cppHoldPosition(host,dynob,1,"cast",false)
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
    
    x_index = -2
    y_index = 2
    x_pos_threshold = 100
    y_pos_threshold = 100
    increament = 1
    reset = false

    start = false
    reach_right = false
    reset_time = 60

    while true do            
        cppMoveObject(host,dynob,x_index * x_pos_threshold,y_pos_threshold * y_index,10 + reset_time )
        coroutine.yield()
        if (start) then
            cppPlayAnimation(dynob,"cast",1,true)
        end
        cppHoldPosition(host,dynob,10,"cast",false)
        coroutine.yield()
        spell_2_side_coin(host,dynob,
        increament,         -- direction
        0,                  -- tier
        "komachi_coins",    -- tableName
        komachi_coins,      -- tableAssets
        2.9,                -- speed
        10.0,               -- lifeTime
        -125 * 0.0174533,   -- current_angle
        -12 * 0.01745336 ,  -- angle_step
        4,                  -- interval
        0,                  -- time
        (180 - 55) * 0.0174533, -- addon_angle
        4,                  -- coin_line
        3)                  -- spread_time
        cppHoldPosition(host,dynob,20,"cast",true)
        coroutine.yield()

        x_index = x_index + increament
        start = true
        reset_time = 0
        if(reach_right) then
            if (x_index == 0) then
                for i = 1, 3 do
                    cppMoveObject(host,dynob,0 * x_pos_threshold,y_pos_threshold * y_index,10)
                    coroutine.yield()
                    spell_2_side_coin(host,dynob,
                    increament,         -- direction
                    1,                  -- tier
                    "komachi_coins",    -- tableName
                    komachi_coins,      -- tableAssets
                    2.9,                -- speed
                    10.0,               -- lifeTime
                    9 * 0.01745336,    -- current_angle
                    -9 * 0.01745336 ,  -- angle_step
                    4,                  -- interval
                    0,                 -- time
                    (180 - 60) * 0.0174533, -- addon_angle
                    5,                  -- coin_line
                    7)                  -- spread_time
                    cppHoldPosition(host,dynob,30,"cast",true)
                    coroutine.yield()
                    y_index = y_index - 1
                end
                cppHoldPosition(host,dynob,350,"cast")
        
                bc.ftest_ma_custom_coin(host,dynob,"komachi_coins",komachi_coins,
                1, -- tier
                1.7, -- speed 
                10.0,  -- lifeTime
                1,     -- k
                3,     -- n
                2,     -- n2
                2,     -- l1
                1,     -- l2
                -1,     -- posneg
                0,    -- startAngle
                4.8 * 0.1,    -- angleStep
                45,    -- rotation
                10,     -- interval
                1)     -- time

                bc.ftest_ma_custom_coin(host,dynob,"komachi_coins",komachi_coins,
                0, -- tier
                1.8, -- speed 
                10.0,  -- lifeTime
                1,     -- k
                3,     -- n
                1,     -- n2
                2,     -- l1
                1,     -- l2
                -1,     -- posneg
                0,    -- startAngle
                9.8 * 0.1,    -- angleStep
                45,    -- rotation
                10,     -- interval
                1)     -- time

                --cppHoldPosition(host,dynob,400,"cast")
                coroutine.yield()
                y_index = 2
                x_index = -2
                reach_right = false
                reset_time = 60
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

    for f = 1, coin_line do
        for i = 1, spread_time do
            x = math.cos((t_current_angle + i * (angle_step) ))
            y = math.sin((t_current_angle + i * (angle_step) ))
            cppSetFire_KomachiCoin(host,dynob,tableName,tableAssets,tier,
                            speed,lifeTime,x,y,f_angle,time + (interval  * (f * 25) ))
        end
    end
end





