
-- Manual wrapper because I want to mark all the function expose by C++
-- OCD warning : this file will contain alot of warning 



--- dict define



-- 
--  ||| Wrapper of HHP (BNML) |||
--

--  MARK: Object

--- Wrapper of cppCreateFromLua
---@Description: Creates a new object (F_Lua_GenericObject)
---@param host pointer instance of F_Lua_Boss_Manager
---@param animationPath string The path to the animation file
---@param posX number The x position of the object
---@param posY number The y position of the object
---@param scale number The scale of the object
---@param depth number The depth of the object
---@param angle number The angle of the object
---@return pointer instance of created F_Lua_GenericObject
function W_createObject(host ,animationPath , posX, posY,scale,depth,angle)
    return cppCreateFromLua(host,animationPath,posX,posY,scale,depth,angle)
end

-- --- Wrapper of cppRemoveFromLua
-- --- @Description: Remove object
-- --- @param host pointer instance of F_Lua_Boss_Manager
-- --- @param dynob pointer instance of F_Lua_GenericObject to remove
-- function W_removeObject(host,dynob)
--     cppRemoveFromLua(host,dynob)
-- end

--- wrapper of cppRemoveObject
--- @Description: Remove object
--- @param host pointer instance of F_Lua_Boss_Manager
--- @param dynob pointer instance of F_Lua_GenericObject to remove
function W_removeObject(host,dynob)
    cppRemoveFromLua(host,dynob)
end

--- wrapper of cppMoveObject
---@Description: Move object to specific position
---@param host pointer instance of F_Lua_Boss_Manager
---@param dynob pointer instance of F_Lua_GenericObject to move
---@param posX number The x position of the object
---@param posY number The y position of the object
---@param time number the time to complete the move
---@param isWait? boolean (optional) If the move should wait for completion (default true)
function W_moveObject(host,dynob,posX,posY,time,isWait)
    isWait = isWait or true
    cppMoveObject(host,dynob,posX,posY,time,isWait)
end

--- wrapper of cppHoldPosition
--- @Description: Hold object at specific position
--- @param host pointer instance of F_Lua_Boss_Manager
--- @param dynob pointer instance of F_Lua_GenericObject to hold
--- @param time number the time to complete the hold
--- @param animationName string The name of the animation to play
--- @param isWait? boolean(optional) If the hold should wait for completion (default true)
function W_holdPosition(host,dynob,time,animationName,isWait)
    isWait = isWait or true
    cppHoldPosition(host,dynob,time,animationName,isWait)
end

--- Wrapper of coroutine.yield
function W_yield()
    coroutine.yield()
end

--- wrapper of cppSetAfterImage
--- @Description: Set the object to get the "after image" effect
--- @param dynob pointer instance of F_Lua_GenericObject 
--- @param interval number The time between each after image
--- @param lifetime number The lifetime of the after image
--- @param maxNum number The maximum number of after image (default 10)
--- @param scaleRate number The scale rate of the after image (default 0.0)
--- @param alphaRate number The alpha rate of the after image (default 0.5)
--- @param traceLifeTime number The lifetime of the trace (default 2.0)
function W_setObjectAfterImage(dynob,interval,lifetime,maxNum,scaleRate,alphaRate,traceLifeTime)
    maxNum = maxNum or 10
    scaleRate = scaleRate or 0.0
    alphaRate = alphaRate or 0.5
    traceLifeTime = traceLifeTime or 2.0
    cppSetAfterImage(dynob,interval,lifetime,maxNum,scaleRate,alphaRate,traceLifeTime)
end

--- wrapper of cppGetObjectPos
--- @Description: Get the position of the object
--- @param dynob pointer instance of F_Lua_GenericObject
--- @return table The position of the object
function W_getObjectPos(dynob)
    return cppGetObjectPos(dynob)
end



--- wrapper of cppSetObjectVel
--- @Description: Set the velocity of the object
--- @param dynob pointer instance of F_Lua_GenericObject
--- @param xVel number The x velocity of the object
--- @param yVel number The y velocity of the object
function W_setObjectVel(dynob,xVel,yVel)
    cppSetObjectVel(dynob,xVel,yVel)
end

--- wrapper of cppGetObjectAngle
--- @Description: Get the angle of the object
--- @param dynob pointer instance of F_Lua_GenericObject
--- @return number The angle of the object
function W_getObjectAngle(dynob)
    return cppGetObjectAngle(dynob)
end

--- wrapper of cppWaitFor
--- @Description: Wait for a specific time
--- @param host pointer instance of F_Lua_Boss_Manager
--- @param dynob pointer instance of F_Lua_GenericObject
--- @param time number The time to wait
function W_wait(host,dynob,time)
    cppWaitFor(host,dynob,time)
end

--- wrapper of cppObjectPlayAnimation
--- @Description: Play an animation on the object
--- @param dynob pointer instance of F_Lua_GenericObject
--- @param animationName string The name of the animation to play
--- @param time number The time to play the animation
--- @param isWait? boolean (optional) If the animation should wait for completion (default true)
--- @param isOverride? boolean (optional) If the animation should override the current animation (default false)
--- @param playSpeed? number (optional) The speed of the animation (default 1.0)
function W_playAnimation(dynob,animationName,time,isWait,isOverride,playSpeed)
    isWait = isWait or true
    isOverride = isOverride or false
    playSpeed = playSpeed or 1
    cppObjectPlayAnimation(dynob,animationName,time,isWait)
end

--- wrapper of cppObjectSetChargingEffect
--- @Description: Set the charging effect of the object
--- @param dynob pointer instance of F_Lua_GenericObject
--- @param tableName string The name of the table to use
--- @param table table The table to use
--- @param time number The time to play the effect
--- @param radius number The radius of the effect
--- @param maxCount number The maximum charging particles of effect
--- @param minSpeed number The minimum speed of the effect
--- @param maxSpeed number The maximum speed of the effect
function W_setObjectCharging(dynob,tableName,table,time,radius,maxCount,minSpeed,maxSpeed)
    cppObjectSetChargingEffect(dynob,tableName,table,time,radius,maxCount,minSpeed,maxSpeed)
end

-- MARK: Fire

--- wrapper of cppSetFire_Type1 (total parameters : 20)
---@Description: Set the fire of the object
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (4)
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param arcType number Arc type : |1(hypocycloid) | 2(hypotrochoid) | 3(custom1) | 4(custom2) | 5(epicycloid)| (6)
---@param a number The a factor (7)
---@param b number The b factor (8)
---@param c number The c factor (9)
---@param d number The d factor (10)
---@param r number The radius factor (11)
---@param angleStep number The increament value for each bullet fires (12)
---@param startAngle number The first angle will start the fire (13)
---@param rotation number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time) (14)
---@param interval number the interval between each bullet (15)
---@param count number number of the bullets (16)
---@param eventTime number The time to trigger the event  (17)
---@param id? number (optional) The id of the bullets which are needed for "bullet manipulator"  (18)
---@param eventName? string (optional) The name of event which will trigger (this is not "bullet manipulator") (19)
---@param isWait? boolean (optional) If the fire should wait for completion (default true) (20)
function W_F_fireType1(host,dynob,asset,speed,lifeTime,
    arcType,a,b,
    c,d ,r,
    angleStep,startAngle,rotation,
    interval,count,eventTime,
    id,eventName,isWait)

    id = id or 0
    eventName = eventName or ""
    isWait = isWait or true

    cppSetFire_Type1(host   -- 1
    ,dynob                  -- 2
    ,asset                  -- 3 
    ,speed                  -- 4
    ,lifeTime               -- 5
    ,arcType                -- 6 
    ,a                      -- 7
    ,b                      -- 8
    ,c                      -- 9
    ,d                      -- 10
    ,r                      -- 11
    ,angleStep              -- 12 
    ,startAngle             -- 13
    ,rotation               -- 14
    ,interval               -- 15
    ,count                  -- 16
    ,eventTime              -- 17
    ,id                     -- 18
    ,eventName              -- 19
    ,isWait                 -- 20
    )
end

--- wrapper of cppSetFire_TypePE
---@Description: Set the fire of the object using polar equation
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (4)
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param peType number Arc type : |1(sin)|2(cos)| (6)
---@param startRange number The start range of the object (7)
---@param rangeCover number The end range of the fire (8)
---@param angleStep number The increament value for each bullet fires (9)
---@param startAngle number The first angle will start the fire (10)
---@param petalCount number The number of petal (11)
---@param interval number the interval between each bullet (12)
---@param rotatePoint number The point to rotate (13)
---@param count number number of the bullets (14)
---@param time number The time to trigger the event  (15)
---@param isWait? boolean (optional) If the fire should wait for completion (default true) (16)
function W_F_fireTypePE(host,dynob,asset,speed,
    lifeTime,peType,startRange,rangeCover,angleStep,
    startAngle,petalCount,interval,rotatePoint,
    count,time,isWait)
    isWait = isWait or true
    cppSetFire_TypePE(host  -- host
    ,dynob                  -- dynob
    ,asset                  -- asset
    ,speed                  -- speed
    ,lifeTime               -- lifeTime
    ,peType                 -- peType
    ,startRange             -- startRange
    ,rangeCover             -- rangeCover
    ,angleStep              -- angleStep
    ,startAngle             -- startAngle
    ,petalCount             -- petalCount
    ,interval               -- interval
    ,rotatePoint            -- rotatePoint
    ,count                  -- count
    ,time                   -- time
    ,isWait)                -- isWait
end

--- wrapper of cppSetFire_MA_custom_aff
---@Description: Set the fire of the object using custom affine equation, total 17(18)parameters 
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (4)
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param k number The k factor (6)
---@param n number The n factor (7)
---@param n2 number The n2 factor (8)
---@param l1 number The l1 factor (9)
---@param l2 number The l2 factor (10)
---@param posneg number The posneg factor (11)
---@param startAngle number The first angle will start the fire (12)
---@param angleStep number The increament value for each bullet fires (13)
---@param rotation number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time) (14)
---@param interval number the interval between each bullet (15)
---@param time number The time to trigger the event (16)
---@param isWait? boolean (optional) If the fire should wait for completion (default true) (17)
function W_F_fireTypeMACustom(host,dynob,asset,speed,
    lifeTime,k,n,n2,l1,l2
    ,posneg,startAngle,angleStep,rotation,interval
    ,time,isWait)

    isWait = isWait or true
    cppSetFire_MA_custom_aff(host,dynob,asset,speed,lifeTime,k,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time,isWait)
end

--- wrapper of cppSetFire_Base
---@Description: Set the base fire
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset string asset (sprite/animation) of the fire (3)
---@param speed number speed of the bullet (4)
---@param lifeTime number lifetime of the bullet (to clean up) (5)
---@param x number The x position of the object (6)
---@param y number The y position of the object (7)
---@param currentAngle number The current angle of the object (8)
---@param time number The time to trigger the event (9)
---@param id? number (optional) The id of the bullets which are needed for "bullet manipulator" (10)
---@param eventName? string (optional) The name of event which will trigger (this is not "bullet manipulator") (11)
function W_F_fireBase(host,dynob,asset,speed,lifeTime,x,y,currentAngle,time,id,eventName)
    id = id or 0
    eventName = eventName or ""
    cppSetFire_Base(host,dynob,asset,speed,lifeTime,x,y,currentAngle,time,id,eventName)
end

--- wrapper of cppSetBulletEvent
---@Description: Set the bullets that has certain ID to act to an event by name
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param id number The id of the bullet (2)
---@param eventName string The name of event (3)
function W_setBulletEvent(host,id,eventName)
    cppSetBulletEvent(host,id,eventName)
end

--- wrapper of cppAddBulletManipulatorPatern
---@Description: set bullets with certain ID to be manipulated
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param xNode number The x position of the object (2)
---@param yNode number The y position of the object (3)
---@param radius number The radius of the object (4)
---@param tableName string table name of the fire (5)
---@param type number type of the fire (6)
---@param id number The id of the bullets which are needed for "bullet manipulator" (7)
function W_manipulate(host,xNode,yNode,radius,tableName,type,id)
    cppAddBulletManipulatorPatern(host,xNode,yNode,radius,tableName,type,id)
end

-- MARK: Komachi

--- wrapper of cppSetFire_KomachiCoin
---@Description: Set the fire of the object
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param tableName string table name of the fire (3)
---@param table table table name of the fire (4)
---@param tier number tier of the fire (5)
---@param speed number speed of the bullet (6)
---@param lifeTime number lifetime of the bullet (to clean up) (7)
---@param x number The x position of the object (8)
---@param y number The y position of the object (9)
---@param currentAngle number The current angle of the object (10)
---@param time number The time to trigger the event (11)
function W_Komachi_fireCoin(host,dynob,tableName,table,
    tier,speed,lifeTime,x,
    y,currentAngle,time)
    cppSetFire_KomachiCoin(host,dynob,tableName,table,tier,speed,lifeTime,x,y,currentAngle,time)
end

--- wrapper of cppKomachi_summon_pillar
---@Description: Summon the flame pillar
---@param host pointer instance of F_Lua_Boss_Manager (1)
---@param dynob pointer instance of F_Lua_GenericObject (2)
---@param asset1 string asset (sprite/animation) of the fire 1 (3)
---@param asset2 string asset (sprite/animation) of the fire 2 (4)
---@param x number The x position of the object (5)
---@param y number The y position of the object (6)
---@param dimX number The x dimension of the object (7)
---@param dimY number The y dimension of the object (8)
---@param r number The color red of the object (9)
---@param g number The color green of the object (10)
---@param b number The color blue of the object (11)
---@param a number The color alpha of the object (12)
---@return pointer instance of created F_Komachi_pillar
function W_Komachi_summonPillar(host,dynob,asset1,asset2,
    x,y,dimX,dimY,
    r,g,b,a)
    return cppKomachi_summon_pillar(host,dynob,asset1,asset2,x,y,dimX,dimY,r,g,b,a)
end

--- wrapper of cppKomachi_pillar_expand
---@Description: Expand the flame pillar
---@param pillar pointer instance of F_Komachi_pillar (1)
---@param dimX number The x dimension of the object (2)
---@param dimY number The y dimension of the object (3)
---@param time number The the total time to expand or shrink from original dimension to new dimension (4)
function W_Komachi_pillarExpand(pillar,dimX,dimY,time)
    cppKomachi_pillar_expand(pillar,dimX,dimY,time)
end

--- wrapper of cppKomachi_pillar_move
---@Description: Move the flame pillar
---@param pillar pointer instance of F_Komachi_pillar (1)
---@param x number The x position of the object (2)
---@param y number The y position of the object (3)
---@param time number The the total time to move from original position to new position (4)
function W_Komachi_pillarMove(pillar,x,y,time)
    cppKomachi_pillar_move(pillar,x,y,time)
end

--- wrapper of cppKomachi_pillar_setColor
---@Description: Set the color of the flame pillar
---@param pillar pointer instance of F_Komachi_pillar (1)
---@param r number The color red of the object (2)
---@param g number The color green of the object (3)
---@param b number The color blue of the object (4)
---@param a number The color alpha of the object (5)
---@param time number The the total time to change from original color to new color (6)
function W_Komachi_pillar_setColor(pillar,r,g,
    b,a,time)
    cppKomachi_pillar_setColor(pillar,r,g,b,a,time)
end


--- wrapper of cppKomachi_pillar_setFlashEffect 
---@Description: Set the flash effect of the flame pillar
---@param pillar pointer instance of F_Komachi_pillar (1)
---@param time number The the total time to flash the pillar (2)
---@param freq number The frequency of the flash (3)
function W_Komachi_pillar_setFlash(pillar,time,freq)

    cppKomachi_pillar_setFlashEffect(pillar,time,freq)
end

-- wrapper of cppKomachi_pillar_setLightEffect
---@Description: Set the light effect of the flame pillar
---@param pillar pointer instance of F_Komachi_pillar (1)
---@param r number The color red of the object (2)
---@param g number The color green of the object (3)
---@param b number The color blue of the object (4)
---@param a number The color alpha of the object (5)
---@param x number The x attenuation of the light (6)
---@param y number The y attenuation of the light (7)
---@param z number The z attenuation of the light (8)
---@param time number The the total time to change from original color to new color (9)
function W_Komachi_pillar_setLight(pillar,r,g,b,a,x,y,z,time)
    cppKomachi_pillar_setLightEffect(pillar,r,g,b,a,x,y,z,time)
end

--- wrapper of cppKomachi_pillar_setLightAttenuation
---@Description: Set the light attenuation of the flame pillar
---@param pillar pointer instance of F_Komachi_pillar (1)
---@param x number The x position of the object (2)
---@param y number The y position of the object (3)
---@param z number The z position of the object (4)
---@param time number The the total time to change from original color to new color (5)
function  W_Komachi_pillar_setLightAttenuation(pillar,x,y,z,time)
    cppKomachi_pillar_setLightAttenuation(pillar,x,y,z,time)
end

--- wrapper of cppKomachi_pillar_setLightColor
---@Description: Set the light color of the flame pillar
---@param pillar pointer instance of F_Komachi_pillar (1)
---@param r number The color red of the object (2)
---@param g number The color green of the object (3)
---@param b number The color blue of the object (4)
---@param a number The color alpha of the object (5)
---@param time number The the total time to change from original color to new color (6)
function W_Komachi_pillar_setLightColor(pillar,r,g,b,a,time)
    cppKomachi_pillar_setLightColor(pillar,r,g,b,a,time)
end


--- wrapper of cppKomachi_pillar_setFrameIndex
---@Description: Set the frame index of the flame pillar
---@param pillar pointer instance of F_Komachi_pillar (1)
---@param index number The index of the frame    
function W_Komachi_pillar_setFrameIndex(pillar,index) 
    cppKomachi_pillar_setFrameIndex(pillar,index)
end


--- wrapper of cppKomachi_pillar_setUVUpdate
---@Description: Set the UV update of the flame pillar
---@param pillar pointer instance of F_Komachi_pillar (1)
---@param rate number The UV update rate
---@param time number the UV update time 
function W_Komachi_pillar_setUVUpdate(pillar,rate,time)
    cppKomachi_pillar_setUVUpdate(pillar,rate,time)
end