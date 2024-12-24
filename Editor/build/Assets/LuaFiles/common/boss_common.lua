package.path = package.path .. ';./Assets/LuaFiles/Common/?.lua' 

require "wrapper"


M = {}


-- cppSetFire_Type1 arcType belike   
-- 1 hypocycloid 
-- 2 hypotrochoid 
-- 3 feint_custom1 
-- 4 feint_custom2
-- 5 epicycloid



---@function fire in the hypocycloid pattern
---@Description fire in the hypocycloid pattern
---@param host (1) pointer instance of F_Lua_Boss_Manager
---@param dynob (2) pointer instance of F_Lua_GenericObject
---@param asset (3) string asset (sprite/animation) of the fire
---@param speed (4) number speed of the bullet
---@param lifeTime (5) number lifetime of the bullet (to clean up)
---@param a (6) number The a factor
---@param b (7) number The b factor
---@param r (8) number The r factor (radius)
---@param angleStep (9) number The increament value for each bullet fires
---@param startAngle (10) number The first angle will start the fire
---@param rotation (11) number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time)
---@param interval (12) number the interval between each bullet
---@param count (13) number number of the bullets
---@param eventTime (14) number The time to trigger the event 
---@param id (15) (optional) number The id of the bullets which are needed for "bullet manipulator"
---@param eventName (16) (optional) string The name of event which will trigger (this is not "bullet manipulator")
M.patern_MA_hypocycloid =  function (host, dynob, asset, speed, lifeTime, a, b, r,angleStep,startAngle, rotation,interval,count, eventTime,id,eventName )
	id = id or 0
	eventName = eventName or ""
	cppSetFire_Type1(host, -- host 
	dynob,                 -- dynob
	asset,				   -- asset ( animated object / sprite) 
	speed,                 -- speed
	lifeTime,              -- lifeTime
	1,                     -- arcType (hypocycloid) 
	a,                     -- a
	b,                     -- b
	0,                     -- c ( unused )
	0,                     -- d ( unused )
	r,                     -- r radius
	angleStep,             -- angleStep
	startAngle,            -- startAngle
	rotation,              -- rotation
	interval,              -- interval
	count,                 -- count
	eventTime,             -- eventTime
	id,eventName)
end

M.patern_MA_hypotrochoid= function (host, dynob, asset, speed, lifeTime, a, b,c, r,angleStep,startAngle, rotation,interval,count, eventTime,id,eventName) 
	id = id or 0
	eventName = eventName or ""
	cppSetFire_Type1(host, 	-- host
	dynob, 					-- dynob
	asset, 					-- asset
	speed, 					-- speed
	lifeTime, 				-- lifeTime
	2, 						-- 2 hypotrochoid
	a, 						-- a factor
	b, 						-- b factor
	c, 						-- c factor
	0, 						-- d factor (unused)
	r, 						-- r radius
	angleStep, 				-- angleStep
	startAngle, 			-- startAngle
	rotation, 				-- rotation (stupid, fix later)
	interval, 				-- interval
	count, 					-- count
	eventTime, 				-- eventTime (the time to trigger event)
	id,eventName)

end

M.patern_Feint_custom1 = function (host, dynob, asset, speed, lifeTime, a, b,c, r,angleStep,startAngle, rotation,interval,count, eventTime,id,eventName)
	id = id or 0
	eventName = eventName or ""
	cppSetFire_Type1(host,dynob,asset,speed,lifeTime,3,a,b,c,0,r,angleStep,startAngle,rotation,interval,count,eventTime,id,eventName)

end

M.patern_Feint_custom2 = function (host, dynob, asset, speed, lifeTime, a, b,c,d,r,angleStep,startAngle, rotation,interval,count, eventTime, id,eventName )
	id = id or 0
	eventName = eventName or ""
	cppSetFire_Type1(host,dynob,asset,speed,lifeTime,4,a,b,c,d,r,angleStep,startAngle,rotation,interval,count,eventTime,id,eventName)

end

M.patern_MA_epicycloid =  function (host, dynob, asset, speed, lifeTime, a, b, r,angleStep,startAngle, rotation,interval,count, eventTime,id,eventName) 
	id = id or 0
	eventName = eventName or ""
	cppSetFire_Type1(host, -- host 
	dynob,                 -- dynob
	asset,				   -- asset ( animated object / sprite) 
	speed,                 -- speed
	lifeTime,              -- lifeTime
	5,                     -- arcType 
	a,                     -- a
	b,                     -- b
	0,                     -- c ( unused )
	0,                     -- d ( unused )
	r,                     -- r radius
	angleStep,             -- angleStep
	startAngle,            -- startAngle
	rotation,              -- rotation
	interval,              -- interval
	count,                 -- count
	eventTime,             -- eventTime
	id,eventName)
end


M.patern_PE_Rose_sin = function (host,dynob, asset, speed, lifeTime, startRange, rangeCover, angleStep,startAngle,petalCount,rotation, interval,count, eventTime)
	cppSetFire_TypePE(host,dynob,asset, speed, lifeTime, 1, startRange, rangeCover, angleStep, startAngle,petalCount,rotation,interval,count,eventTime)

end


M.patern_PE_Rose_cos = function (host,dynob, asset, speed, lifeTime, startRange, rangeCover, angleStep,startAngle,petalCount,rotation, interval,count, eventTime)
	cppSetFire_TypePE(host,dynob,asset, speed, lifeTime, 2, startRange, rangeCover, angleStep, startAngle,petalCount,rotation,interval,count,eventTime)

end


M.patern_PE_circle = function (host,dynob, asset, speed, lifeTime, startRange, rangeCover, angleStep,startAngle,petalCount,rotation, interval,count, eventTime)
	cppSetFire_TypePE(host,dynob,asset, speed, lifeTime, 3, startRange, rangeCover, angleStep, startAngle,petalCount,rotation,interval,count,eventTime)

end


M.ftest_ma_custom_aff = function (host,dynob,asset,speed,lifeTime,k,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time,id,eventName)
	local f_angle = startAngle 
	local f_count = 0;
	id = id or 0
	eventName = eventName or ""
	for t_k = 0,k
	do
	f_angle = f_angle +angleStep
		for t_l1 = 0,l1
		do
			f_angle = f_angle +angleStep
			for t_l2 = 0,l2
			do
				f_angle = f_angle +angleStep
				for t_n2 = 0,n2
				do
					f_angle = f_angle +angleStep
					for t_n = 0,n
					do 
						x = math.cos(f_angle * posneg)
						y = math.sin(f_angle * posneg)
						f_angle = f_angle + math.rad(360/n)

						--coroutine.create(cppSetFire_Base,host,dynob,asset,speed,lifeTime,x,y,f_angle,time)
						cppSetFire_Base(host,dynob,asset,speed,lifeTime,x,y,f_angle,time + (interval  * f_count),id,eventName)
						f_count = f_count + 1
					end -- n
				end -- n2
			end -- l2
		end -- l1
	end -- k
end

M.ftest_ma_custom_coin = function (host,dynob,tableName,tableAssets,tier,speed,lifeTime,k,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time)
	local f_angle = startAngle 
	local f_count = 0;
	for t_k = 0,k
	do
	f_angle = f_angle +angleStep
		for t_l1 = 0,l1
		do
			f_angle = f_angle +angleStep
			for t_l2 = 0,l2
			do
				f_angle = f_angle +angleStep
				for t_n2 = 0,n2
				do
					f_angle = f_angle +angleStep
					for t_n = 0,n
					do 
						x = math.cos(f_angle * posneg)
						y = math.sin(f_angle * posneg)
						f_angle = f_angle + math.rad(360/n)

						cppSetFire_KomachiCoin(host,dynob,tableName,tableAssets,tier,
						speed,lifeTime,x,y,f_angle,time + (interval  * f_count))

						f_count = f_count + 1
					end -- n
				end -- n2
			end -- l2
		end -- l1
	end -- k
end



M.ftest_ma_custom_aff2 =function(host,dynob,asset,speed,lifeTime,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time,id,eventName)

	local f_angle =  startAngle
	local f_count = 0;
	id = id or 0
	eventName = eventName or ""
	for t_l1 = 0,l1
	do
		f_angle = f_angle + angleStep + math.random(0,360)
		for t_l2 = 0,l2
		do
			f_angle = f_angle +angleStep
			for t_n2 = 0,n2
			do
				f_angle = f_angle +angleStep
				for t_n = 0,n
				do 
					x = math.cos(f_angle * posneg)
					y = math.sin(f_angle * posneg)
					f_angle = f_angle + math.rad(360/n)

					--coroutine.create(cppSetFire_Base,host,dynob,asset,speed,lifeTime,x,y,f_angle,time)
					cppSetFire_Base(host,dynob,asset,speed,lifeTime,x,y,f_angle,time + (interval  * f_count),id,eventName) 
					f_count = f_count + 1
				end -- n
			
			end -- n2
		end -- l2
	end -- l1
end


M.arc_hypocycloid =  function (a,b,r,t)
	local retX, retY
	retX = ((a - b) * math.cos(t) +( b * math.cos((a - b) / b) * t)) * r
	retY = ((a - b) * math.sin(t) + (b * math.sin((a - b) / b) * t)) * r
	return retX, retY
end

-- M.add_bullet_event = function(host,id,eventName)
-- 	cppSetBulletEvent(host,id,eventName)
-- end


return M