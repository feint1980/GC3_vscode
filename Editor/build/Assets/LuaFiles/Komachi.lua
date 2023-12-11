
bc =  require("./Assets/Luafiles/common/boss_common")

local dynamics = {}

movingObject = nil


object = {posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/boss_komachi.xml",scaleX = 1.0, scaleY = 1.0, depth = 15, angle = 30 }


-- init
function CreateFromLua(host,path)
	print("[LUA] create from LUA called \n")

	--movingObject = {posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/boss_eiki.xml", scaleX = 1.0, scaleY = 1.0, depth = 15.0, angle = 0.0 }
	--cppCreateFromLua(host)
	movingObject = cppCreateFromLua(host,"./Assets/F_AObjects/boss_komachi.xml",0,0,0.72,15.0,0.0)
	--dynamics[movingObject].behavior  = nil
	--dynamics[movingObject] = {}
	--dynamics[movingObject] = {behavior = coroutine.create(DynamicBehavior5,host,movingObject)}
	--IssueNextTask(host,movingObject)

end

function moveset_normal_1( host )
	dynamics[movingObject] = {behavior = coroutine.create(DynamicBehavior1,host,movingObject)}
	IssueNextTask(host,movingObject)
	isMovesetSelected = true
end

function moveset_normal_2(host)
    dynamics[movingObject] = {behavior = coroutine.create(DynamicBehavior2,host,movingObject)}
    IssueNextTask(host,movingObject)
    isMovesetSelected = true
end

-- function movset_spellcard_1(host)
--     dynamics[movingObject] = {behavior = coroutine.create(DynamicBehavior3,host,movingObject)}
--     IssueNextTask(host,movingObject)
--     isMovesetSelected = true
-- end



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

function  DynamicBehavior1( host, dynob )
	while true do 
    cppMoveObject(host,dynob,10,300,50)
    coroutine.yield()
    --function bc.patern_MA_hypocycloid(host, dynob, asset, speed, lifeTime, a, b, r,angleStep,startAngle, rotation,interval,count, eventTime )
    bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_white.png",0.25,10.0,17,22,45,2.1,0,0,10,300,100)
    coroutine.yield()
    bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",0.25,10.0,17,22,45,2.1,90,90,10,300,100)
    coroutine.yield()
    bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",0.25,10.0,17,22,45,2.1,180,180,10,300,100)
    coroutine.yield()
    bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",0.25,10.0,17,22,45,2.1,270,270,10,300,100)
    coroutine.yield()
  
    cppHoldPosition(host,dynob,250,"cast")
    coroutine.yield()

    cppMoveObject(host,dynob,0,0,50)
    coroutine.yield()

    cppHoldPosition(host,dynob,100,"idle")
    coroutine.yield()
    end
end


-- main update of the boss
function IssueNextTask(host, dynob)
	if coroutine.status(dynamics[movingObject].behavior) ~= 'dead' then
		coroutine.resume(dynamics[movingObject].behavior, host, dynob)
	else
		print(coroutine.status(dynamics[movingObject].behavior))
	end

end