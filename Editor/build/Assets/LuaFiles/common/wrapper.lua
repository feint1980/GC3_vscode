
-- Manual wrapper because I want to mark all the function expose by C++
-- OCD warning : this file will contain alot of warning 

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

--- wrapper of cppRemoveObject
--- @Description: Remove object
--- @  param host pointer instance of F_Lua_Boss_Manager
--- @  param dynamicObject pointer instance of F_Lua_GenericObject to remove
function W_removeObject(host,dynob)
    cppRemoveObject(host,dynob)
end

--- wrapper of cppMoveObject
---@Description: Move object to specific position
---@param host pointer instance of F_Lua_Boss_Manager
---@param dynamicObject pointer instance of F_Lua_GenericObject to move
---@param posX number The x position of the object
---@param posY number The y position of the object
---@param time number the time to complete the move
---@param isWait boolean If the move should wait for completion (default true)
function W_moveObject(host,dynob,posX,posY,time,isWait)
    isWait = isWait or true
    cppMoveObject(host,dynob,posX,posY,time,isWait)
end

--- wrapper of cppHoldPosition
--- @Description: Hold object at specific position
--- @param host pointer instance of F_Lua_Boss_Manager
--- @param dynamicObject pointer instance of F_Lua_GenericObject to hold
--- @param time number the time to complete the hold
--- @param animationName string The name of the animation to play
--- @param isWait boolean If the hold should wait for completion (default true)
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
--- @param isWait boolean If the animation should wait for completion (default true)
--- @param isOverride boolean If the animation should override the current animation (default false)
--- @param playSpeed number The speed of the animation (default 1.0)
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

--- wrapper of cppSetFire_Type1
---@Description: Set the fire of the object
---@param host (1) pointer instance of F_Lua_Boss_Manager
---@param dynob (2) pointer instance of F_Lua_GenericObject
---@param asset (3) string asset (sprite/animation) of the fire
---@param speed (4) number speed of the bullet
---@param lifeTime (5) number lifetime of the bullet (to clean up)
---@param arcType (6) number Arc type : 1(hypocycloid) | 2(hypotrochoid) | 3(custom1) | 4(custom2) | 5(epicycloid) 
---@param a (7) number The a factor
---@param b (8) number The b factor
---@param c (9) number The c factor
---@param d (10) number The d factor
---@param r (11) number The r factor (radius)
---@param angleStep (12) number The increament value for each bullet fires
---@param startAngle (13) number The first angle will start the fire
---@param rotation (14) number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time)
---@param interval (15) number the interval between each bullet
---@param count (16) number number of the bullets
---@param evenTime (17) number The time to trigger the event 
---@param id (18) (optional) number The id of the bullets which are needed for "bullet manipulator" 
---@param eventName (19) (optional) string The name of event which will trigger (this is not "bullet manipulator")
---@param isWait (20) (optional) boolean If the fire should wait for completion (default true)
function W_F_fireType1(host,dynob,asset,speed,lifeTime,a,b,c,r,angleStep,startAngle,rotation,interval,count,eventTime,id,eventName,isWait)

    id = id or 0
    eventName = eventName or ""
    isWait = isWait or true
    cppSetFire_Type1(host,dynob,asset,speed,lifeTime,1,a,b,c,r,angleStep,startAngle,rotation,interval,count,eventTime,id,eventName,isWait)
end

--- wrapper of cppSetFire_TypePE
---@Description: Set the fire of the object using polar equation
---@param host (1) pointer instance of F_Lua_Boss_Manager
---@param dynob (2) pointer instance of F_Lua_GenericObject
---@param asset (3) string asset (sprite/animation) of the fire
---@param speed (4) number speed of the bullet
---@param lifeTime (5) number lifetime of the bullet (to clean up)
---@param peType (6) number Arc type : 1(sin) | 2(cos) 
---@param startRange (7) number The start range of the object
---@param rangeCover (8) number The end range of the fire
---@param angleStep (9) number The increament value for each bullet fires
---@param startAngle (10) number The first angle will start the fire
---@param petalCount (11) number The number of petal
---@param interval (12) number the interval between each bullet
---@param rotatePoint (13) number The point to rotate
---@param count (14) number number of the bullets
---@param time (15) number The time to trigger the event 
---@param isWait (16) (optional) boolean If the fire should wait for completion (default true)
function W_F_fireTypePE(host,dynob,asset,speed,lifeTime,peType,startRange,rangeCover,angleStep,startAngle,petalCount,interval,rotatePoint,count,time,isWait)
    
    isWait = isWait or true
    cppSetFire_TypePE(host,dynob,asset,speed,lifeTime,peType,startRange,rangeCover,angleStep,startAngle,petalCount,interval,rotatePoint,count,time,isWait)
end

--- wrapper of cppSetFire_MA_custom_aff
---@Description: Set the fire of the object using custom affine equation
---@param host (1) pointer instance of F_Lua_Boss_Manager
---@param dynob (2) pointer instance of F_Lua_GenericObject
---@param asset (3) string asset (sprite/animation) of the fire
---@param speed (4) number speed of the bullet
---@param lifeTime (5) number lifetime of the bullet (to clean up)
---@param k (6) number The k factor
---@param n (7) number The n factor
---@param n2 (8) number The n2 factor
---@param l1 (9) number The l1 factor
---@param l2 (10) number The l2 factor
---@param posneg (11) number The posneg factor
---@param startAngle (12) number The first angle will start the fire
---@param angleStep (13) number The increament value for each bullet fires
---@param rotation (14) number rotation start from angle (IDK why this still exist, stupid tho, but I will change once I got time)
---@param interval (15) number the interval between each bullet
---@param time (16) number The time to trigger the event
---@param isWait (17) (optional) boolean If the fire should wait for completion (default true)
function W_F_fireTypeMACustom(host,dynob,asset,speed,lifeTime,k,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time,isWait)

    isWait = isWait or true
    cppSetFire_MA_custom_aff(host,dynob,asset,speed,lifeTime,k,n,n2,l1,l2,posneg,startAngle,angleStep,rotation,interval,time,isWait)
end


--- wrapper of cppSetFire_Base
---@Description: Set the base fire
---@param host (1) pointer instance of F_Lua_Boss_Manager
---@param dynob (2) pointer instance of F_Lua_GenericObject
---@param asset (3) string asset (sprite/animation) of the fire
---@param speed (4) number speed of the bullet
---@param lifeTime (5) number lifetime of the bullet (to clean up)
---@param x (6) number The x position of the object
---@param y (7) number The y position of the object
---@param currentAngle (8) number The current angle of the object
---@param time (9) number The time to trigger the event
---@param id (10) (optional) number The id of the bullets which are needed for "bullet manipulator"
---@param eventName (11) (optional) string The name of event which will trigger (this is not "bullet manipulator")
function W_F_fireBase(host,dynob,asset,speed,lifeTime,x,y,currentAngle,time,id,eventName)
    id = id or 0
    eventName = eventName or ""
    cppSetFire_Base(host,dynob,asset,speed,lifeTime,x,y,currentAngle,time,id,eventName)
end

--- wrapper of cppSetBulletEvent
---@Description: Set the bullets that has certain ID to act to an event by name
---@param host (1) pointer instance of F_Lua_Boss_Manager
---@param id (2) number The id of the bullet
---@param eventName (3) string The name of event
function W_setBulletEvent(host,id,eventName)
    cppSetBulletEvent(host,id,eventName)
end

--- wrapper of cppAddBulletManipulatorPatern
---@Description: set bullets with certain ID to be manipulated
---@param host (1) pointer instance of F_Lua_Boss_Manager
---@param xNode (2) number The x position of the object
---@param yNode (3) number The y position of the object
---@param radius (4) number The radius of the object
---@param tableName (5) string table name of the fire
---@param type (6) number type of the fire
---@param id (7) number The id of the bullets which are needed for "bullet manipulator"
function W_manipulate(host,xNode,yNode,radius,tableName,type,id)

    cppAddBulletManipulatorPatern(host,xNode,yNode,radius,tableName,type,id)
end

-- MARK: Komachi

--- wrapper of cppSetFire_KomachiCoin
---@Description: Set the fire of the object
---@param host (1) pointer instance of F_Lua_Boss_Manager
---@param dynob (2) pointer instance of F_Lua_GenericObject
---@param tableName (3) string table name of the fire
---@param table (4) string table name of the fire
---@param tier (5) number tier of the fire
---@param speed (6) number speed of the bullet
---@param lifeTime (7) number lifetime of the bullet (to clean up)
---@param x (8) number The x position of the object
---@param y (9) number The y position of the object
---@param currentAngle (10) number The current angle of the object
---@param time (11) number The time to trigger the event
function W_Komachi_fireCoin(host,dynob,tableName,table,tier,speed,lifeTime,x,y,currentAngle,time)
    cppSetFire_KomachiCoin(host,dynob,tableName,table,tier,speed,lifeTime,x,y,currentAngle,time)
end

--- wrapper of cppKomachi_summon_pillar
---@Description: Summon the flame pillar
---@param host (1) pointer instance of F_Lua_Boss_Manager
---@param dynob (2) pointer instance of F_Lua_GenericObject
---@param asset1 (3) string asset (sprite/animation) of the fire 1
---@param asset2 (4) string asset (sprite/animation) of the fire 2
---@param x (5) number The x position of the object
---@param y (6) number The y position of the object
---@param dimX (7) number The x dimension of the object
---@param dimY (8) number The y dimension of the object
---@param r (9) number The color red of the object
---@param g (10) number The color green of the object
---@param b (11) number The color blue of the object
---@param a (12) number The color alpha of the object
---@return pointer instance of created F_Komachi_pillar
function W_Komachi_summonPillar(host,dynob,asset1,asset2,x,y,dimX,dimY,r,g,b,a)
    return cppKomachi_summon_pillar(host,dynob,asset1,asset2,x,y,dimX,dimY,r,g,b,a)
end

--- wrapper of cppKomachi_pillar_expand
---@Description: Expand the flame pillar
---@param pillar (1) pointer instance of F_Komachi_pillar
---@param dimX (2) number The x dimension of the object
---@param dimY (3) number The y dimension of the object
---@param time (4) number The the total time to expand or shrink from original dimension to new dimension
function W_Komachi_pillarExpand(pillar,dimX,dimY,time)
    cppKomachi_pillar_expand(pillar,dimX,dimY,time)
end

--- wrapper of cppKomachi_pillar_move
---@Description: Move the flame pillar
---@param pillar (1) pointer instance of F_Komachi_pillar
---@param x (2) number The x position of the object
---@param y (3) number The y position of the object
---@param time (4) number The the total time to move from original position to new position
function W_Komachi_pillarMove(pillar,x,y,time)
    cppKomachi_pillar_move(pillar,x,y,time)
end

--- wrapper of cppKomachi_pillar_setColor
---@Description: Set the color of the flame pillar
---@param pillar (1) pointer instance of F_Komachi_pillar
---@param r (2) number The color red of the object
---@param g (3) number The color green of the object
---@param b (4) number The color blue of the object
---@param a (5) number The color alpha of the object
---@param time (6) number The the total time to change from original color to new color
function W_Komachi_pillar_setColor(pillar,r,g,b,a,time)
    cppKomachi_pillar_setColor(pillar,r,g,b,a,time)
end


--- wrapper of cppKomachi_pillar_setFlashEffect 
---@Description: Set the flash effect of the flame pillar
---@param pillar (1) pointer instance of F_Komachi_pillar
---@param time (2) number The the total time to flash the pillar
---@param freq (3) number The frequency of the flash
function W_Komachi_set_pillar_flash(pillar,time,freq)

    cppKomachi_pillar_setFlashEffect(pillar,time,freq)
end

-- wrapper of cppKomachi_pillar_setLightEffect
---@Description: Set the light effect of the flame pillar
---@param pillar (1) pointer instance of F_Komachi_pillar
---@param r (2) number The color red of the object
---@param g (3) number The color green of the object
---@param b (4) number The color blue of the object
---@param a (5) number The color alpha of the object
---@param x (6) number The x attenuation of the light
---@param y (7) number The y attenuation of the light
---@param z (8) number The z attenuation of the light
---@param time (9) number The the total time to change from original color to new color
function W_Komachi_set_pillar_light(pillar,r,g,b,a,x,y,z,time)
    cppKomachi_pillar_setLightEffect(pillar,r,g,b,a,x,y,z,time)
end

--- wrapper of cppKomachi_pillar_setLightAttenuation
---@Description: Set the light attenuation of the flame pillar
---@param pillar (1) pointer instance of F_Komachi_pillar
---@param x (2) number The x position of the object
---@param y (3) number The y position of the object
---@param z (4) number The z position of the object
---@param time (5) number The the total time to change from original color to new color
function  W_Komachi_set_pillar_light_attenuation(pillar,x,y,z,time)
    cppKomachi_pillar_setLightAttenuation(pillar,x,y,z,time)
end

--- wrapper of cppKomachi_pillar_setLightColor
---@Description: Set the light color of the flame pillar
---@param pillar (1) pointer instance of F_Komachi_pillar
---@param r (2) number The color red of the object
---@param g (3) number The color green of the object
---@param b (4) number The color blue of the object
---@param a (5) number The color alpha of the object
---@param time (6) number The the total time to change from original color to new color
function W_Komachi_set_pillar_color(pillar,r,g,b,a,time)
    cppKomachi_pillar_setLightColor(pillar,r,g,b,a,time)
end