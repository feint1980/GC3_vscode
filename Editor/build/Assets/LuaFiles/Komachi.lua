    
bc =  require("./Assets/Luafiles/common/boss_common")

local dynamics = {}

local souls = {}
local soulsCount = 0

komachi = nil
soul_1 = nil


object = {posX = 0.0, posY = 0.0,
 animationPath = "./Assets/F_AObjects/boss_komachi.xml",
 scale = 0.6, depth = 15, angle = 0 }


soul = {posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/komachi_souls.xml", scale = 1.0, depth = 15.0, angle = 0.0 }
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
    cppSetAfterImage(host,komachi,0.2,10.0)
    
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
        souls[soulsCount + 1] = cppCreateFLObject(host,dynob,1,"Assets/F_AObjects/komachi_souls.xml" ,
        100 , 200, 1,1,14,-10,0)
        soulsCount = soulsCount + 1
        print("print from lua ")
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
    while true do 
        cppMoveObject(host,dynob,200,300,50)
        coroutine.yield()
       
        -- ftest_ma_custom_aff (host,dynob,asset,speed,lifeTime,k,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time)
        -- example bc.ftest_ma_custom_aff(host,dynob,"projectile/bullet_shard_yellow.png",0.95,7.0,1,2,2,4,6,1,90,10,90,10,0)
        cppHoldPosition(host,dynob,10,"idle")
        coroutine.yield()
        cppHoldPosition(host,dynob,50,"cast")
        
        bc.ftest_ma_custom_aff(host,dynob,"projectile/bullet_shard_white.png",0.925,10.0,4,2,2,2,3,1,90,10,45,1,0)
        --coroutine.yield()
        --bc.ftest_ma_custom_aff(host,dynob,"projectile/bullet_shard_white.png",0.925,10.0,4,2,2,2,3,-1,90,10,45,2,100)
        coroutine.yield()
        cppHoldPosition(host,dynob,70,"idle")
        coroutine.yield()

        cppMoveObject(host,dynob,-200,300,50)
        coroutine.yield()

        cppHoldPosition(host,dynob,10,"idle")
        coroutine.yield()
        cppHoldPosition(host,dynob,50,"cast")
        
        bc.ftest_ma_custom_aff(host,dynob,"projectile/bullet_shard_white.png",0.925,10.0,4,2,2,2,3,1,90,10,45,1,0)
        --coroutine.yield()
        --bc.ftest_ma_custom_aff(host,dynob,"projectile/bullet_shard_white.png",0.925,10.0,4,2,2,2,3,-1,90,10,45,2,100)
        coroutine.yield()
        cppHoldPosition(host,dynob,70,"idle")
        coroutine.yield()

        cppMoveObject(host,dynob,0,200,50)
        coroutine.yield()
        --coroutine.yield()
        --bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",0.25,10.0,17,22,45,1.3,0,0,5,900,0)
        bc.patern_Feint_custom1(host,dynob,"projectile/bullet_shard_blue.png",5.25,10.0,4,12,7,45,1.3,0,0,5,450,0)
        coroutine.yield()
        bc.patern_Feint_custom1(host,dynob,"projectile/bullet_shard_blue.png",5.25,10.0,4,12,7,45,-1.3,0,30,5,450,0)
        coroutine.yield()
        bc.patern_Feint_custom1(host,dynob,"projectile/bullet_shard_blue.png",5.25,10.0,4,12,7,45,1.8,0,70,5,450,0)
        coroutine.yield()
        bc.patern_Feint_custom1(host,dynob,"projectile/bullet_shard_blue.png",5.25,10.0,4,12,7,45,-1.8,0,-70,5,450,0)
        coroutine.yield()
        cppHoldPosition(host,dynob,220,"cast")
        coroutine.yield()

        cppMoveObject(host,dynob,-200,0,50)
        coroutine.yield()
        --coroutine.yield()
        --bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",0.25,10.0,17,22,45,1.3,0,0,5,900,0)
        bc.patern_MA_hypotrochoid(host,dynob,"projectile/bullet_shard_blue.png",1.25,10.0,3,7,2,45,5,0,0,5,450,0)
        coroutine.yield()
        bc.patern_MA_hypotrochoid(host,dynob,"projectile/bullet_shard_blue.png",1.25,10.0,3,7,2,45,-5,0,90,5,450,0)
        coroutine.yield()
        bc.patern_MA_hypotrochoid(host,dynob,"projectile/bullet_shard_white.png",1.25,10.0,3,7,2,45,3.3,0,180,3,900,0)
        coroutine.yield()
        bc.patern_MA_hypotrochoid(host,dynob,"projectile/bullet_shard_white.png",1.25,10.0,3,7,2,45,3.3,0,0,3,900,0)
        coroutine.yield()
        cppHoldPosition(host,dynob,270,"cast")
        coroutine.yield()
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
            1.2,   -- angleStep
            0,  -- startAngle
            180 + (180 * direction),  -- rotation
            0,   -- interval
            100,  -- count
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
        100,   -- r
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
            4.5, -- speed
            10.0, -- lifeTime
            4,   -- a
            6,   -- b
            7,   -- c
            100,   -- r
            1.2,   -- angleStep
            0,  -- startAngle
            0 + (360/total_line * i),  -- rotation
            0,   -- interval
            100,  -- count
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
    cppSetAfterImage(host,dynob,0.01,10.0,25,0.05)
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
    cppSetAfterImage(host,dynob,0.01,10.0,25,0.05)
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

