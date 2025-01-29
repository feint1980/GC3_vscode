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
---@Description fire in the hypocycloid pattern total 14(16) parameters
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (4)
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param a number The a factor (6)
---@param b number The b factor (7)
---@param r number The radius factor (8)
---@param angleStep number The increament value for each bullet fires (9)
---@param startAngle number The first angle will start the fire (10)
---@param rotation number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time) (11)
---@param interval number the interval between each bullet (12)
---@param count number number of the bullets (13)
---@param eventTime number The time to trigger the event  (14)
---@param id? number (optional) The id of the bullets which are needed for "bullet manipulator" (15)
---@param eventName? string (optional) The name of event which will trigger (this is not "bullet manipulator") (16)
M.patern_MA_hypocycloid =  function (host, dynob, asset, speed, lifeTime, 
	a, b, r,angleStep,startAngle,
	rotation,interval,count,
	eventTime,id,eventName )
	id = id or 0
	eventName = eventName or ""
	-- cppSetFire_Type1(host, -- host 
	-- dynob,                 -- dynob
	-- asset,				   -- asset ( animated object / sprite) 
	-- speed,                 -- speed
	-- lifeTime,              -- lifeTime
	-- 1,                     -- arcType (hypocycloid) 
	-- a,                     -- a
	-- b,                     -- b
	-- 0,                     -- c ( unused )
	-- 0,                     -- d ( unused )
	-- r,                     -- r radius
	-- angleStep,             -- angleStep
	-- startAngle,            -- startAngle
	-- rotation,              -- rotation
	-- interval,              -- interval
	-- count,                 -- count
	-- eventTime,             -- eventTime
	-- id,eventName)

	W_F_fireType1(host, -- host 
	dynob,                 	-- dynob
	asset,				   	-- asset ( animated object / sprite) 
	speed,                 	-- speed
	lifeTime,            	-- lifeTime
	1,                     -- arcType (hypocycloid) 
	a,                     		-- a
	b,                     		-- b
	0,                     		-- c ( unused )
	0,                     		-- d ( unused )
	r,                     		-- r radius
	angleStep,           -- angleStep
	startAngle,         -- startAngle
	rotation,             -- rotation
	interval,             -- interval
	count,                 	-- count
	eventTime,           -- eventTime
	id,
	eventName)

end 
-- still keep this for old format to work

-- MARK: Patern_MA_hypocycloid

---@function fire in the hypocycloid pattern
---@Description fire in the hypocycloid pattern total 14(16) parameters
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (4)
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param a number The a factor (6)
---@param b number The b factor (7)
---@param r number The radius factor (8)
---@param angleStep number The increament value for each bullet fires (9)
---@param startAngle number The first angle will start the fire (10)
---@param rotation number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time) (11)
---@param interval number the interval between each bullet (12)
---@param count number number of the bullets (13)
---@param eventTime number The time to trigger the event  (14)
---@param id? number (optional) The id of the bullets which are needed for "bullet manipulator" (15)
---@param eventName? string (optional) The name of event which will trigger (this is not "bullet manipulator") (16)
function Patern_MA_hypocycloid(host, dynob, asset, speed, lifeTime, a, b, r,angleStep,startAngle, rotation,interval,count, eventTime,id,eventName )
	id = id or 0
	eventName = eventName or ""
	W_F_fireType1(host, -- host 
	dynob,                 	-- dynob
	asset,				   	-- asset ( animated object / sprite) 
	speed,                 	-- speed
	lifeTime,            	-- lifeTime
	1,                     -- arcType (hypocycloid) 
	a,                     		-- a
	b,                     		-- b
	0,                     		-- c ( unused )
	0,                     		-- d ( unused )
	r,                     		-- r radius
	angleStep,           -- angleStep
	startAngle,         -- startAngle
	rotation,             -- rotation
	interval,             -- interval
	count,                 	-- count
	eventTime,           -- eventTime
	id,
	eventName)
end

-- function fire in the hypotrochoid pattern
---@Description fire in the hypotrochoid pattern total 15(17) parameters
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (4)patern_MA_hypotrochoid
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param a number The a factor (6)
---@param b number The b factor (7)
---@param c number The c factor (8)
---@param r number The r factor (radius) (9)
---@param angleStep number The increament value for each bullet fires (10)
---@param startAngle number The first angle will start the fire (11)
---@param rotation number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time) (12)
---@param interval number the interval between each bullet (13)
---@param count number number of the bullets (14)
---@param eventTime number The time to trigger the event  (15)
---@param id? number (optional) The id of the bullets which are needed for "bullet manipulator" (16)
---@param eventName? string (optional) The name of event which will trigger (this is not "bullet manipulator") (17) 
function Patern_MA_hypotrochoid(host, dynob, asset, speed, lifeTime,
	a, b,c, r,angleStep,
	startAngle, rotation,interval,count,
	eventTime,id,eventName)
	id = id or 0
	eventName = eventName or ""

	W_F_fireType1(host, 	-- host
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
	id,
	eventName)

end



--- function: Patern_Feint_custom1 fire in the feint custom pattern
---@Description fire in the feint custom pattern total 17(19) parameters
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (3)
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param a number The a factor (6)
---@param b number The b factor (7)
---@param c number The c factor (8)
---@param r number The radius factor (9)
---@param angleStep number The increament value for each bullet fires (10)
---@param startAngle number The first angle will start the fire (11)
---@param rotation number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time) (12)
---@param interval number the interval between each bullet (13)
---@param count number number of the bullets (14)
---@param eventTime number The time to trigger the event (15)
---@param id? number (optional) The id of the bullets which are needed for "bullet manipulator" (16)
---@param eventName? string (optional) The name of event which will trigger (this is not "bullet manipulator") (17)
function Patern_Feint_custom1(host, dynob, asset, speed, lifeTime, a, b,c, r,angleStep,startAngle, rotation,interval,count, eventTime,id,eventName)
	id = id or 0
	eventName = eventName or ""

	W_F_fireType1(host		-- host (1)
	, dynob 				-- dynob (2)
	, asset 				-- asset (3)
	, speed 				-- speed (4)
	, lifeTime 				-- lifeTime (5)
	, 3 					-- arcType (predetermined) (6)
	, a 					-- a factor (7)
	, b 					-- b factor (8)
	, c 					-- c factor (9)
	, 0 					-- d factor (unused) (10)
	, r 					-- r radius (11)
	, angleStep 			-- angleStep (12)
	, startAngle 			-- startAngle (13)
	, rotation 				-- rotation (14)
	, interval 				-- interval (15)
	, count 				-- count (16)
	, eventTime 			-- eventTime (17)
	, id ,eventName) 		-- id and eventName (optional) (18 and 19)

end


--- function: patern_Feint_custom2 fire in the feint custom pattern (2)
---@Description: fire in the feint custom pattern total 16(18) parameters
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (4)
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param a number The a factor (6)
---@param b number The b factor (7)
---@param c number The c factor (8)
---@param d number The d factor (9)
---@param r number The radius factor (10)
---@param angleStep number The increament value for each bullet fires (11)
---@param startAngle number The first angle will start the fire (12)
---@param rotation number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time) (13)
---@param interval number the interval between each bullet (14)
---@param count number number of the bullets (15)
---@param eventTime number The time to trigger the event (16)
---@param id? number (optional) The id of the bullets which are needed for "bullet manipulator" (17)
---@param eventName? string (optional) The name of event which will trigger (this is not "bullet manipulator") (18)
Patern_Feint_custom2 = function (host, dynob, asset, speed,
	lifeTime, a, b,c,d,
	r,angleStep,startAngle, rotation,interval,
	count, eventTime, id,eventName )
	id = id or 0
	eventName = eventName or ""
	W_F_fireType1(host,dynob,asset,speed,lifeTime
	,4,a,b,c,d,r,angleStep
	,startAngle,rotation,interval
	,count,eventTime,id,eventName)

end


--- function: patern_MA_epicycloid fire in the epicycloid pattern (2)
---@Description: fire in the epicycloid pattern total 16(18) parameters
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (4)
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param a number The a factor (6)
---@param b number The b factor (7)
---@param r number The radius factor (8)
---@param angleStep number The increament value for each bullet fires (9)
---@param startAngle number The first angle will start the fire (10)
---@param rotation number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time) (11)
---@param interval number the interval between each bullet (12)
---@param count number number of the bullets (13)
---@param eventTime number The time to trigger the event (14)
---@param id? number (optional) The id of the bullets which are needed for "bullet manipulator" (15)
---@param eventName? string (optional) The name of event which will trigger (this is not "bullet manipulator") (16)
Patern_MA_epicycloid =  function (host, dynob, asset, speed, lifeTime,
	a, b, r,angleStep,startAngle,
	rotation,interval,count,
	eventTime,id,eventName) 
	id = id or 0
	eventName = eventName or ""
	W_F_fireType1(host, -- host 
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

--- function: Patern_PE_Rose_sin fire in the Rose (sin) pattern (2)
---@Description: fire in the Rose (sin) pattern 
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (4)
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param startRange number The start range (6)
---@param rangeCover number The range cover (7)
---@param angleStep number The increament value for each bullet fires (8)
---@param startAngle number The first angle will start the fire (9)
---@param petalCount number The number of petal (10)
---@param rotation number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time) (11)
---@param interval number the interval between each bullet (12)
---@param count number number of the bullets (13)
---@param eventTime number The time to trigger the event (14)
M.patern_PE_Rose_sin = function (host,dynob, asset,
	speed, lifeTime, startRange, rangeCover, angleStep,
	startAngle,petalCount,rotation,
	interval,count, eventTime)
	W_F_fireTypePE(host,dynob,asset, speed, lifeTime
	, 1, startRange, rangeCover, angleStep
	, startAngle,petalCount,rotation
	,interval,count,eventTime)

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
						local x = math.cos(f_angle * posneg)
						local y = math.sin(f_angle * posneg)
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