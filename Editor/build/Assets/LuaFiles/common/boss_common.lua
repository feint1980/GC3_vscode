
M = {}



-- cppSetFire_Type1 arcType belike   
-- 1 hypocycloid 
-- 2 hypotrochoid 
-- 3 feint_custom1 

M.patern_MA_hypocycloid =  function (host, dynob, asset, speed, lifeTime, a, b, r,angleStep,startAngle, rotation,interval,count, eventTime,id,eventName )
	id = id or 0
	eventName = eventName or ""
	cppSetFire_Type1(host, -- host 
	dynob,                 -- dynob
	asset,				   -- asset ( animated object / sprite) 
	speed,                 -- speed
	lifeTime,              -- lifeTime
	1,                     -- arcType 
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
	cppSetFire_Type1(host,dynob,asset,speed,lifeTime,2,a,b,c,0,r,angleStep,startAngle,rotation,interval,count,eventTime,id,eventName)

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