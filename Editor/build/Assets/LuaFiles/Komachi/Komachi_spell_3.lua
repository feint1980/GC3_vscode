package.path = package.path .. ';./Assets/LuaFiles/Common/?.lua' .. ';./Assets/LuaFiles/Komachi/?.lua'

bc =  require("./Assets/Luafiles/common/boss_common")


function DynamicBehavior3_normal(host,dynob)

    local x_index = 0
    local y_index = 2
    local x_pos_threshold = 75
    local y_pos_threshold = 100
    local t_angle = 30 * 0.0174532925
    local t_xPos = 1
    while true do

        W_moveObject(host,dynob,t_xPos,150,20)
        t_xPos = t_xPos * -1
        coroutine.yield()
        W_holdPosition(host,dynob,10,"charging")
        coroutine.yield()
        W_holdPosition(host,dynob,80,"charge_end")
        for angle_count = 1, 5 do
            Patern_MA_hypocycloid(host,dynob,"projectile/bullet_shard_white.png",
            0.65, -- speed
            10.0, -- lifeTime
            5,   -- a
            4,   -- b
            50,   -- r
            2.5,  -- angleStep
            0,    -- startAngle
            angle_count * 360/5 * 0.0174532925,    -- rotation
            2,   -- interval
            120,  -- count
            100)  -- eventTime
            coroutine.yield()
        end
        coroutine.yield()
        -- cppAddBulletManipulatorPatern(host,"((a - b) * cos(t) + (c * cos((a / b - 1)*t))) *r","((a - b) * sin(t) - (c * sin((a / b - 1)*t))) *r",450,"factor_table",factor_table,0)
        --cppAddBulletManipulatorPatern(host,"a * 50","a - b * sin(t)",45,"factor_table",factor_table,0)
        for i = 1, 3 do
            x_index = math.random( -2,2 )
            y_index = math.random( 1,2 )
            W_moveObject(host,dynob,x_index * x_pos_threshold,y_pos_threshold * y_index,40)
            coroutine.yield()
            W_holdPosition(host,dynob,10,"charging")
            coroutine.yield()
            W_holdPosition(host,dynob,300,"charge_end")
            for angle_count = 1, 4 do
                Patern_MA_hypotrochoid(host,dynob
                ,"projectile/bullet_shard_blue.png",
                0.65, -- speed
                7.0, -- lifeTime
                9,   -- a
                7,   -- b
                3,    -- c
                50,   -- r
                0.5,  -- angleStep
                0,    -- startAngle
                angle_count * 90 * 0.0174532925,    -- rotation
                10,   -- interval
                125,  -- count
                100)  -- eventTime
                coroutine.yield()
            end
            for angle_count = 1, 3 do
                Patern_MA_hypotrochoid(host,dynob,"projectile/bullet_medium_red.png",
                0.5, -- speed
                10.0, -- lifeTime
                2,   -- a
                3,   -- b
                5,    -- c
                50,   -- r
                0.33,  -- angleStep
                0,    -- startAngle
                angle_count * 120 * 0.0174532925,    -- rotation
                0,   -- interval
                100,  -- count
                100)  -- eventTime
                coroutine.yield()
            end
            coroutine.yield()
            W_holdPosition(host,dynob,1,"charge_end",false)
            coroutine.yield()
        end
    end
end

function DynamicBehavior3(host,dynob)
    while true do
        W_moveObject(host,dynob,0,150,20)
        coroutine.yield()
        W_holdPosition(host,dynob,100,"charging")
        W_setObjectCharging(dynob,"Komachi_charge_table",Komachi_charge_table
        ,100,250,120,
        9.5,15.5)
        coroutine.yield()
        W_holdPosition(host,dynob,750,"charge_end")
        bc.ftest_ma_custom_aff2(host,dynob,
        "projectile/knife_red.png",
        0.85,    -- speed
        10.0,   -- lifeTime
        4,      -- n
        6,      -- n2
        3,      -- l1
        6,      -- l2
        1,      -- posneg
        3,      -- startAngle
        200,     -- angleStep
        0,      -- rotation
        10,      -- interval
        0,      -- time
        0,      -- id
        "slowdownCustomF2")      -- event)

        bc.ftest_ma_custom_aff2(host,dynob,
        "projectile/knife_yellow.png",
        0.85,    -- speed
        10.0,   -- lifeTime
        4,      -- n
        6,      -- n2
        3,      -- l1
        6,      -- l2
        -1,      -- posneg
        3,      -- startAngle
        200,     -- angleStep
        0,      -- rotation
        10,      -- interval
        0,      -- time
        0,      -- id
        "slowdownCustomF2")      -- event)


        bc.ftest_ma_custom_aff2(host,dynob,
        "projectile/bullet_shard_blue.png",
        0.85,    -- speed
        10.0,   -- lifeTime
        4,      -- n
        6,      -- n2
        3,      -- l1
        6,      -- l2
        1,      -- posneg
        3,      -- startAngle
        200,     -- angleStep
        45,      -- rotation
        10,      -- interval
        0,      -- time
        0,      -- id
        "slowdownCustomF3")      -- event)

        bc.ftest_ma_custom_aff2(host,dynob,
        "projectile/bullet_shard_yellow.png",
        0.85,    -- speed
        10.0,   -- lifeTime
        4,      -- n
        6,      -- n2
        3,      -- l1
        6,      -- l2
        -1,      -- posneg
        3,      -- startAngle
        200,     -- angleStep
        45,      -- rotation
        10,      -- interval
        0,      -- time
        0,      -- id
        "slowdownCustomF3")      -- event)

        coroutine.yield()

        -- cppMoveObject(host,dynob,1,0,150)
        -- coroutine.yield()
    end
end