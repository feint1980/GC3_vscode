


bc =  require("./Assets/Luafiles/common/boss_common")
--dofile("./common/boss_common.lua")


-- Object struct table : 
--	m_pos | vec2 -> 2 float for x and y | posX , posY
--  t_animationPath -> string | animationPath ;
--	m_scale | vec2 -> 2 float for x and y | scaleX , scaleY;
--	m_depth | float | depth  ;
--	m_angle | float | angle;

local dynamics = {}


movingObject = nil
--isMovesetSelected = false

function  DynamicBehavior1( host, dynob )
	while true do 
	cppMoveObject(host,dynob,10,300,50)
	coroutine.yield()
	--bc.patern_PE_Rose_sin(host,dynob, asset, speed, lifeTime, startRange, rangeCover, angleStep,startAngle,petalCount,interval,rotation,count, eventTime)
	bc.patern_PE_Rose_cos(host,dynob, "projectile/bullet_shard_blue.png", 1.5, 5.0, 1, 4, 0.1,1,2,10, 0,200, 0)
	coroutine.yield()
	bc.patern_PE_Rose_sin(host,dynob, "projectile/bullet_shard_blue.png", 1.5, 5.0, 1, 4, 0.1,2,2,0, 30,200, 50)
	coroutine.yield()
	bc.patern_PE_Rose_cos(host,dynob, "projectile/bullet_shard_blue.png", 1.5, 5.0, 1, 4, 0.1,3,2,0, 60,200, 100)
	coroutine.yield()
	cppHoldPosition(host,dynob,10,"cast")
	coroutine.yield()
	cppMoveObject(host,dynob,300,100,50)
	coroutine.yield()
	--bc.patern_MA_hypocycloid(host, dynob, asset, speed, lifeTime,arcType, a, b, r,angleStep,startAngle, rotation,interval,count, eventTime )
	bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",0.5,5.0,13,14,45,0.5,0,0,1,400,1000)
	coroutine.yield()
	cppMoveObject(host,dynob,-300,100,50)
	coroutine.yield()
	--bc.patern_MA_hypocycloid(host, dynob, asset, speed, lifeTime,arcType, a, b, r,angleStep,startAngle, rotation,interval,count, eventTime )
	bc.patern_MA_hypocycloid(  host,dynob,"projectile/bullet_shard_blue.png",0.5,5.0,7,5,30,0.25,0,0,0,250,1000)
	coroutine.yield()
	bc.patern_MA_hypocycloid(  host,dynob,"projectile/bullet_shard_blue.png",0.5,5.0,7,5,30,0.25,0,30,0,250,1100)
	coroutine.yield()
	bc.patern_MA_hypocycloid(  host,dynob,"projectile/bullet_shard_blue.png",0.5,5.0,7,5,30,0.25,0,60,0,250,1200)
	coroutine.yield()
	bc.patern_MA_hypocycloid(  host,dynob,"projectile/bullet_shard_blue.png",0.5,5.0,7,5,30,0.25,0,90,0,250,1300)
	coroutine.yield()
	cppHoldPosition(host,dynob,150,"idle")
	coroutine.yield()
	--bc.patern_MA_hypotrochoid(host, dynob, asset, speed, lifeTime, a, b,c, r,angleStep,startAngle, rotation,interval,count, eventTime )
	bc.patern_MA_hypotrochoid(  host,dynob,"projectile/bullet_shard_blue.png",0.5,5.0,7,5,8,45,0.25,0,0,0,250,1000)
	coroutine.yield()
	cppMoveObject(host,dynob,100,200,50)
	coroutine.yield()
	bc.patern_MA_hypotrochoid(  host,dynob,"projectile/bullet_shard_blue.png",0.5,5.0,12,7,11,45,0.25,0,0,0,250,1000)
	coroutine.yield()
	cppMoveObject(host,dynob,0,0,50)
	coroutine.yield()
	-- bc.patern_MA_hypotrochoid(  host,dynob,"projectile/bullet_shard_blue.png",0.5,5.0,11,15,12,45,0.25,0,0,20,250,1000)
	-- coroutine.yield()
	-- bc.patern_MA_hypotrochoid(  host,dynob,"projectile/bullet_shard_yellow.png",0.5,5.0,11,15,12,45,0.25,0,30,20,250,1100)
	-- coroutine.yield()
	-- bc.patern_MA_hypotrochoid(  host,dynob,"projectile/bullet_shard_blue.png",0.5,5.0,11,15,12,45,0.25,0,60,20,250,1200)
	-- coroutine.yield()
	-- bc.patern_MA_hypotrochoid(  host,dynob,"projectile/bullet_shard_yellow.png",0.5,5.0,11,15,12,45,0.25,0,90,20,250,1300)
	-- coroutine.yield()
	--bc.cppSetFire_MA_custom_aff(host,dynob, asset, speed, lifeTime,k ,n,n2,l1,l2,posneg,startAngle, angleStep,rotation,interval, eventTime)
	bc.cppSetFire_MA_custom_aff(host,dynob, "projectile/bullet_shard_blue.png", 1.5, 5.0, 1, 9,9,2,3,-1, 90,3400, 0,60,10)
	coroutine.yield()
	cppHoldPosition(host,dynob,150,"cast")
	coroutine.yield()

	end
end


function  DynamicBehavior3( host, dynob )
	while true do 
	cppMoveObject(host,dynob,10,300,50)
	coroutine.yield()
	--function bc.patern_MA_hypocycloid(host, dynob, asset, speed, lifeTime, a, b, r,angleStep,startAngle, rotation,interval,count, eventTime )
	bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",0.25,10.0,17,22,45,2.1,0,0,10,300,100)
	coroutine.yield()
	bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",0.25,10.0,17,22,45,2.1,90,90,10,300,100)
	coroutine.yield()
	bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",0.25,10.0,17,22,45,2.1,180,180,10,300,100)
	coroutine.yield()
	bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_blue.png",0.25,10.0,17,22,45,2.1,270,270,10,300,100)
	coroutine.yield()
	bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_yellow.png",0.25,10.0,17,22,45,-2.1,0,0,10,300,100)
	coroutine.yield()
	bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_yellow.png",0.25,10.0,17,22,45,-2.1,90,90,10,300,100)
	coroutine.yield()
	bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_yellow.png",0.25,10.0,17,22,45,-2.1,180,180,10,300,100)
	coroutine.yield()
	bc.patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_yellow.png",0.25,10.0,17,22,45,-2.1,270,270,10,300,100)
	coroutine.yield()
	cppHoldPosition(host,dynob,300,"cast")
	coroutine.yield()
	cppMoveObject(host,dynob,0,0,50)
	coroutine.yield()

	bc.cppSetFire_MA_custom_aff(host,dynob, "projectile/bullet_shard_blue.png", 1.5, 5.0, 1, 6,9,2,3,-1, 90,3400, 0,120,100)
	coroutine.yield()
	bc.cppSetFire_MA_custom_aff(host,dynob, "projectile/bullet_shard_yellow.png", 1.5, 5.0, 1, 6,9,2,3,1, 90,3400, 0,12,1100)
	coroutine.yield()

	bc.cppSetFire_MA_custom_aff(host,dynob, "projectile/bullet_shard_blue.png", 1.5, 5.0, 1, 6,9,2,3,-1, 90,3400, 90,120,100)
	coroutine.yield()
	bc.cppSetFire_MA_custom_aff(host,dynob, "projectile/bullet_shard_yellow.png", 1.5, 5.0, 1, 6,9,2,3,1, 90,3400, 90,120,1100)
	coroutine.yield()
	cppHoldPosition(host,dynob,100,"cast")
	coroutine.yield()
	end
end

function  DynamicBehavior4( host, dynob )
	while true do 
	
	cppMoveObject(host,dynob,10,300,50)
	coroutine.yield()
--behavior = coroutine.create(DynamicBehavior4,host,movingObject)
	--bc.ftest_ma_custom_aff(host,dynob,asset,speed,lifeTime,k,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time)
	bc.ftest_ma_custom_aff(host,dynob,"projectile/bullet_shard_yellow.png",0.95,7.0,1,2,2,4,6,1,90,10,90,10,0)
	bc.ftest_ma_custom_aff(host,dynob,"projectile/bullet_shard_blue.png",0.95,7.0,1,2,2,4,6,-1,90,10,90,10,100)
	cppHoldPosition(host,dynob,500,"cast")
	coroutine.yield()
	cppMoveObject(host,dynob,0,0,50)
	coroutine.yield()
	bc.ftest_ma_custom_aff(host,dynob,"projectile/bullet_shard_blue.png",0.95,7.0,1,2,2,2,3,-1,90,10,90,1,100)
	cppHoldPosition(host,dynob,50,"cast")
	coroutine.yield()
	end
end

function  DynamicBehavior5( host, dynob )
	local des_x = 200
	local des_y = 200
	local circleCount = 0
	while true do 

		des_x, des_y = getStarPosition( circleCount,1.5)
		cppMoveObject(host,dynob,des_x,des_y,10 )
		coroutine.yield()
		if( circleCount == 0) 
		then
			cppHoldPosition(host,dynob,100,"idle")
			coroutine.yield()
		end
	--behavior = coroutine.create(DynamicBehavior4,host,movingObject)
		--bc.ftest_ma_custom_aff(host,dynob,asset,speed,lifeTime,k,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time)
		--bc.ftest_ma_custom_aff2(host,dynob,asset             ,speed,lifeTime,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time)
		bc.ftest_ma_custom_aff2(host,dynob,"projectile/bullet_shard_blue.png",0.15,1.0,6,5,2,10,1,90,10,90,1,0)
		--bc.ftest_ma_custom_aff2(host,dynob,"projectile/bullet_shard_yellow.png",0.15,7.0,6,2,2,10,-1,90,10,0,1,100)
		--bc.ftest_ma_custom_aff2(host,dynob,"projectile/bullet_shard_blue.png",1.95,7.0,6,10,2,2,1,45,10,1,15,200)
		--bc.ftest_ma_custom_aff(host,dynob,"projectile/bullet_shard_blue.png",0.95,7.0,1,2,2,4,6,-1,90,10,90,10,100)
		--cppHoldPosition(host,dynob,100,"cast")
		--coroutine.yield()

		--bc.ftest_ma_custom_aff(host,dynob,"projectile/bullet_shard_blue.png",0.95,7.0,1,2,2,2,3,-1,90,10,90,1,100)
		--cppHoldPosition(host,dynob,50,"cast")
		--coroutine.yield()
		circleCount = circleCount + 1
		if (circleCount > 4)
		then	 
			circleCount = 0
			
		end
		
	end
end








function rotatePoint(x,y,angle)
	local  retX, retY
	retX = x * math.cos(angle) - y * math.sin(angle)
	retY = x * math.sin(angle) + y * math.cos(angle) 
	return retX, retY
end

function getStarPosition(index,scale)
	local defaultMax = 200 * scale
	local retX, retY
	if(index == 0)     then 
		retX = 0
		retY = defaultMax
	elseif(index == 1) then
		retX = defaultMax * 0.7
		retY = -defaultMax
	elseif(index == 2) then
		retX = -defaultMax
		retY = defaultMax * 0.5
	elseif(index == 3) then
		retX = defaultMax
		retY = defaultMax * 0.5
	elseif(index == 4) then
		retX = -defaultMax * 0.7
		retY = -defaultMax
	end
	return retX, retY
end

function moveset_test( host )
	dynamics[movingObject] = {behavior = coroutine.create(DynamicBehavior5,host,movingObject)}
	IssueNextTask(host,movingObject)
	isMovesetSelected = true
end

function moveset_normal_1( host )
	dynamics[movingObject] = {behavior = coroutine.create(DynamicBehavior1,host,movingObject)}
	IssueNextTask(host,movingObject)
	isMovesetSelected = true
end
function moveset_normal_2( host )
	dynamics[movingObject] = {behavior = coroutine.create(DynamicBehavior2,host,movingObject)}
	IssueNextTask(host,movingObject)
	isMovesetSelected = true
end
function moveset_normal_3( host )
	dynamics[movingObject] = {behavior = coroutine.create(DynamicBehavior3,host,movingObject)}
	IssueNextTask(host,movingObject)
	isMovesetSelected = true
end
function moveset_normal_4( host )
	dynamics[movingObject] = {behavior = coroutine.create(DynamicBehavior4,host,movingObject)}
	IssueNextTask(host,movingObject)
	isMovesetSelected = true
end


function DynamicBehavior2(host, dynob )
	
	--print("co",1)
	cppMoveObject(host,dynob,100,200,50)
	--print(coroutine.status(dynamics[dynob].dynob))
	coroutine.yield()

	--print("co",2)
	cppMoveObject(host,dynob,-100,200,50)
	--print(coroutine.status(dynamics[dynob].behavior))
	coroutine.yield()
end

function resetFunction(host)
	-- if(dynamics[movingObject].behavior ~= nil) 
	-- then
		--coroutine.yield()
	-- if (coroutine.status(dynamics[movingObject].behavior) ~= 'dead') then 
	-- 	coroutine.kill(dynamics[movingObject].behavior)
 -- 	end
	-- end
	--isMovesetSelected = false
end

function IssueNextTask(host, dynob)
	--print("Issue next task lua called \n")
	--cppMoveObject(host,dynob,100,10,10)
	if coroutine.status(dynamics[movingObject].behavior) ~= 'dead' then
		--print("coroutine not dead status ")
		--print(coroutine.status(dynamics[movingObject].behavior))
		coroutine.resume(dynamics[movingObject].behavior, host, dynob)
	else
		print(coroutine.status(dynamics[movingObject].behavior))
		--coroutine.resume(dynamics[dynob].behavior, host, dynob)
	end

end


function TestFunc(t,f)
	print("[LUA] TestFunc called " ..t.. "," ..f.." \n")
	return t * f 
end

function callCPPFunc(q,r)
	print("[LUA] call from Lua call callCPPFunc " ..q.. "," ..r.." \n")
	c = HostFunction(q,r)
	return c
end

--objects = {} -- declare object array
object = { posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/boss_eiki.xml", scaleX = 2.0, scaleY = 2.0, depth = 15.0, angle = 0.0 }


function IssueNextTask2( host, dynob)
	--print("host is ", host)
	--print("dynob is ", dynob)
	--print("IssueNextTask2 ")
	if coroutine.status(dynamics[movingObject]) ~= 'dead' then
		--print("coroutine not dead status ")
		--print(coroutine.status(dynamics[movingObject]))
		coroutine.resume(dynamics[movingObject],host,dynob)
	else
		--print(coroutine.status(dynamics[movingObject]))
		--coroutine.resume(dynamics[dynob].behavior, host, dynob)
	end
end


function CreateFromLua(host)
	print("[LUA] create from LUA called \n")

	--movingObject = {posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/boss_eiki.xml", scaleX = 1.0, scaleY = 1.0, depth = 15.0, angle = 0.0 }
	--cppCreateFromLua(host)
	movingObject = cppCreateFromLua(host,"./Assets/F_AObjects/boss_eiki.xml",0,0,1.0,15.0,0.0)
	--dynamics[movingObject].behavior  = nil
	--dynamics[movingObject] = {}
	--dynamics[movingObject] = {behavior = coroutine.create(DynamicBehavior5,host,movingObject)}
	--IssueNextTask(host,movingObject)

end



--CreateFromLua()


