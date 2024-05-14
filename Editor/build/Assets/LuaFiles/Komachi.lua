    
bc =  require("./Assets/Luafiles/common/boss_common")

dynamics = {}

souls = {}
soulsCount = 0

komachi = nil
soul_1 = nil
t_soul = nil

math.randomseed(os.time())


komachi_coins = {"komachi/komachi_12.png","komachi/komachi_11.png","komachi/komachi_13.png"}

object = {posX = 0.0, posY = 0.0,
 animationPath = "./Assets/F_AObjects/boss_komachi.xml",
 scale = 0.6, depth = 15, angle = 0 }


soulData = {posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/komachi_effects.xml", scale = 1.0, depth = 15.0, angle = 0.0 }
-- init
function CreateFromLua(host,path)
	print("[LUA] create from LUA called \n")

	--komachi = {posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/boss_eiki.xml", scaleX = 1.0, scaleY = 1.0, depth = 15.0, angle = 0.0 }
	--cppCreateFromLua(host)
	komachi = cppCreateFromLua(host,object.animationPath,object.posX,object.posY,object.scale,object.depth,object.angle)
	--dynamics[komachi].behavior  = nil
	--dynamics[komachi] = {}
	--dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior5,host,komachi)}
	--IssueNextTask(host,komachi)

end

function moveset_summon(host)
    soul_1  = cppCreateFromLua(host,soul.animationPath,soul.posX,soul.posY,soul.scale,soul.depth,soul.angle)
    dynamics[soul_1] = {behavior = coroutine.create(DynamicBehavior1_invert,host,soul_1)}
    IssueNextTask(host,soul_1)
    dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior1,host,komachi)}
    IssueNextTask(host,komachi)
    cppSetAfterImage(komachi,0.2,10.0)
    
    isMovesetSelected = true
    

end

function moveset_normal_1( host )
    print("create")
	dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior1,host,komachi)}
    print("half")
	IssueNextTask(host,komachi)
	isMovesetSelected = true
    print("end")
end

-- function DynamicBehavior_boat_move(host, dynob, targetX, targetY)

--     cppSetObjectVel(host, dynob, targetX, targetY)
   
-- end


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
    --while true do 
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
        --coroutine.yield()
    end

end

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

function randomFloat(lower, greater)
    return lower + math.random()  * (greater - lower);
end

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

function moveset_spell_1(host)
   dynamics[komachi] = {behavior = coroutine.create(spell_1_boss_movement,host,komachi)}
   IssueNextTask(host,komachi)
end



function moveset_normal_2(host)
    dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior2,host,komachi)}
    IssueNextTask(host,komachi)
    isMovesetSelected = true
end

function moveset_normal_3(host)
    dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior3,host,komachi)}
    IssueNextTask(host,komachi)
    isMovesetSelected = true
end

-- function movset_spellcard_1(host)
--     dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior3,host,komachi)}
--     IssueNextTask(host,komachi)
--     isMovesetSelected = true
-- end


function DynamicBehavior3(host, dynob)
    while true do
        cppMoveObject(host,dynob,0,300,50)
        coroutine.yield()
        cppHoldPosition(host,dynob,10,"cast")
        coroutine.yield()
        --create helper param (F_Lua_Boss dynamicObject,string  objectName,
	    --string  asset, float x, float y, float scaleX, float scaleY, float depth,
        --float velX, float velY,int afterImageCount, float afterImageRate, float scaleRate,double time)
        -- souls[soulsCount + 1] = cppCreateFLObject(host,dynob,1,"Assets/F_AObjects/komachi_souls.xml" ,
        -- 100 , 200, 1,1,14,-10,0)
        -- soulsCount = soulsCount + 1
        -- print("print from lua ")
        --manipulateSouls()
        cppMoveObject(host,dynob,0,0,50)

        coroutine.yield()
    end
end

function manipulateSouls()
    for i = 1, soulsCount do
        print(i)
        --souls[i].
       --cppMoveObject(host,souls[i],0,0,50)
    end
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
        --cppPlayAnimation(dynob,"cast",1)
        
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

        --ftest_ma_custom_coin = function (host,dynob,tableName,tableAssets,tier,speed,lifeTime,k,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time)
        coroutine.yield()
        cppHoldPosition(host,dynob,1,"cast",false)
        coroutine.yield()
        count = count + 1
       

        --cppPlayAnimation(dynob,"idle",0)
       
    end
end


function DynamicBehavior1_base( host, dynob, direction)
   

    cppMoveObject(host,dynob,150 * direction,150,25)
    coroutine.yield()
    --function bc.patern_MA_hypocycloid(host, dynob, asset, speed, lifeTime, a, b, r,angleStep,startAngle, rotation,interval,count, eventTime )

    -- bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",
    --     0.5, -- speed
    --     10.0, -- lifeTime
    --     7,   -- a
    --     8,   -- b
    --     45,   -- r
    --     2.1,  -- angleStep
    --     90,   -- startAngle
    --     90,   -- rotation
    --     10,   -- interval
    --     300,  -- count
    --     100)  -- eventTime
    -- coroutine.yield()
    -- bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",
    --     0.5, -- speed
    --     10.0, -- lifeTime
    --     7,   -- a
    --     8,   -- b
    --     45,   -- r
    --     2.1,  -- angleStep
    --     180,  -- startAngle
    --     180,  -- rotation
    --     10,   -- interval
    --     300,  -- count
    --     100)  -- eventTime
    -- coroutine.yield()
    --total_line = 12
   -- for i = 1, total_line do
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
  --  end
   
    cppHoldPosition(host,dynob,30,"cast")
    coroutine.yield()

    cppHoldPosition(host,dynob,10,"idle",false )
    coroutine.yield()
end


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


function  DynamicBehavior1_invert( host, dynob )
	while true do 
    cppMoveObject(host,dynob,-200,300,50)
    cppSetAfterImage(dynob,0.01,10.0,25,0.05)
    coroutine.yield()
    --function bc.patern_MA_hypocycloid(host, dynob, asset, speed, lifeTime, a, b, r,angleStep,startAngle, rotation,interval,count, eventTime )
   bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_white.png",
        0.55, -- speed
        10.0, -- lifeTime 
        15,   -- a
        16,   -- b 
        45,   -- r
        2.1,  -- angleStep
        0,    -- startAngle
        0,    -- rotation
        10,   -- interval
        300,  -- count
        100)  -- eventTime
    coroutine.yield()
    bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",
        0.55, -- speed
        10.0, -- lifeTime
        15,   -- a
        16,   -- b
        45,   -- r
        2.1,  -- angleStep
        90,   -- startAngle
        0,   -- rotation
        10,   -- interval
        300,  -- count
        100)  -- eventTime
    coroutine.yield()
    bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",
        0.25, -- speed
        10.0, -- lifeTime
        17,   -- a
        22,   -- b
        45,   -- r
        2.1,  -- angleStep
        180,  -- startAngle
        0,  -- rotation
        10,   -- interval
        300,  -- count
        100)  -- eventTime
    coroutine.yield()
    bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",
        0.25, -- speed
        10.0, -- lifeTime
        17,   -- a
        22,   -- b
        45,   -- r
        2.1,  -- angleStep
        270,  -- startAngle
        0,    -- rotation
        10,   -- interval
        300,  -- count
        100)  -- eventTime
    coroutine.yield()
  
    cppHoldPosition(host,dynob,250,"cast")
    coroutine.yield()

    cppMoveObject(host,dynob,0,0,50)
    cppSetAfterImage(dynob,0.01,10.0,25,0.05)
    coroutine.yield()

    cppHoldPosition(host,dynob,100,"idle")
    coroutine.yield()
    cppRemoveFromLua(host,dynob)
    end
end


function IssueNextTask(host, dynob)
    if coroutine.status(dynamics[dynob].behavior) ~= 'dead' then
		coroutine.resume(dynamics[dynob].behavior, host, dynob)
	else
		print(coroutine.status(dynamics[dynob].behavior))
	end
end

