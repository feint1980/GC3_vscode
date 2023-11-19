
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
    -- bc.cppSetFire_MA_custom_aff(host,dynob, "projectile/bullet_shard_blue.png", 1.5, 5.0, 1, 6,9,2,3,-1, 90,3400, 0,120,100)
    -- coroutine.yield()
    -- bc.cppSetFire_MA_custom_aff(host,dynob, "projectile/bullet_shard_yellow.png", 1.5, 5.0, 1, 6,9,2,3,1, 90,3400, 0,12,1100)
    -- coroutine.yield()

    -- bc.cppSetFire_MA_custom_aff(host,dynob, "projectile/bullet_shard_blue.png", 1.5, 5.0, 1, 6,9,2,3,-1, 90,3400, 90,120,100)
    -- coroutine.yield()
    -- bc.cppSetFire_MA_custom_aff(host,dynob, "projectile/bullet_shard_yellow.png", 1.5, 5.0, 1, 6,9,2,3,1, 90,3400, 90,120,1100)
    -- coroutine.yield()
    -- cppHoldPosition(host,dynob,100,"cast")
    -- coroutine.yield()
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