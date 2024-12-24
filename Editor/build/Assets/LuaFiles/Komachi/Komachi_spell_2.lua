package.path = package.path .. ';./Assets/LuaFiles/Common/?.lua' .. ';./Assets/LuaFiles/Komachi/?.lua'

bc =  require("./Assets/Luafiles/common/boss_common")

-- Belong to moveset_normal_4
function DynamicBehavior4(host,dynob)
    local count = 2
    local xthresHold = 175
    while true do
        if (count > 1) then
            count = -1
            W_moveObject(host,dynob,0,170,25)
            coroutine.yield()
            W_playAnimation(dynob,"charging",1,false)
            cppObjectSetChargingEffect(dynob,"charge_table",charge_table,100,250,120,9.5,15.5)
            W_holdPosition(host,dynob,80,"charging")
            coroutine.yield()
            W_playAnimation(dynob,"charge_end",1,true)
            bc.ftest_ma_custom_aff(host,dynob,"komachi/komachi_13.png",
            3.425, -- speed
            10.0,  -- lifeTime
            3,     -- k
            2,     -- n
            4,     -- n2
            2,     -- l1
            3,     -- l2
            -1,     -- posneg
            0,    -- startAngle
            1.3777,    -- angleStep
            45,    -- rotation
            3,     -- interval
            0)     -- time

            W_holdPosition(host,dynob,200,"charge_end",false)
            coroutine.yield()
        end
        W_moveObject(host,dynob,count * xthresHold,150,30)
        coroutine.yield()
        W_holdPosition(host,dynob,10,"charging")
        coroutine.yield()
        W_holdPosition(host,dynob,200,"charge_end")
        bc.ftest_ma_custom_coin(host,dynob,"komachi_coins",komachi_coins,
        1, -- tier
        1.7, -- speed
        10.0,  -- lifeTime
        2,     -- k
        2,     -- n
        1,     -- n2
        2,     -- l1
        3,     -- l2
        1,     -- posneg
        0,    -- startAngle
        15.11,    -- angleStep
        0,    -- rotation
        5,     -- interval
        10)     -- time
        coroutine.yield()
        W_holdPosition(host,dynob,1,"charge_end",false)
        coroutine.yield()
        count = count + 1
    end
end

-- end of move set : normal 4


function spell_4_behavior(host,dynob)

    local x_index = -2
    local y_index = 5
    local x_pos_threshold = 100
    local y_pos_threshold = 40
    local increament = 1
    local reset = false

    local start = false
    local reach_right = false
    local reset_time = 60
    local increament_count = 1

    while true do
        if( start == false ) then
            W_moveObject(host,dynob,x_index * x_pos_threshold,y_pos_threshold * y_index,10 + reset_time )
            coroutine.yield()
        end

        if (start) then
            W_playAnimation(dynob,"cast",1,true)
        end
        x_index = x_index + increament
        start = true
        reset_time = 0

        W_holdPosition(host,dynob,20,"charging",true)
        coroutine.yield()

        W_holdPosition(host,dynob,1,"charge_end",true)
        spell_2_side_coin(host,dynob,
        increament,         -- direction
        0,                  -- tier
        "komachi_coins",    -- tableName
        komachi_coins,      -- tableAssets
        4.8,                -- speed
        9.0,               -- lifeTime
        -125 * 0.0174533,   -- current_angle
        -12 * 0.01745336 ,  -- angle_step
        0,                  -- interval
        0,                  -- time
        (180 - 55) * 0.0174533, -- addon_angle
        4,                  -- coin_line
        3)                  -- spread_time
        coroutine.yield()
        W_moveObject(host,dynob,x_index * x_pos_threshold,y_pos_threshold * y_index,7  )
        coroutine.yield()
        W_holdPosition(host,dynob,15,"charge_end",true)
        coroutine.yield()
        --W_holdPosition(host,dynob,20,"charge_end",true)

        if(reach_right) then
            if (x_index == 0) then
                for i = 1, 3 do
                    W_holdPosition(host,dynob,20,"charging",true)
                    coroutine.yield()
                    W_holdPosition(host,dynob,1,"charge_end",true)
                    spell_2_side_coin(host,dynob,
                    increament,         -- direction
                    1,                  -- tier
                    "komachi_coins",    -- tableName
                    komachi_coins,      -- tableAssets
                    2.6,                -- speed
                    10.0,               -- lifeTime
                    9 * 0.01745336,    -- current_angle
                    -9 * 0.01745336 ,  -- angle_step
                    0,                  -- interval
                    0,                 -- time
                    (180 - 60) * 0.0174533, -- addon_angle
                    5,                  -- coin_line
                    7)                  -- spread_time
                    y_index = y_index - 1
                    coroutine.yield()
                    W_moveObject(host,dynob,0 * x_pos_threshold,y_pos_threshold * y_index,10)
                    coroutine.yield()

                end

                W_playAnimation(dynob,"charging",1,false)
                cppObjectSetChargingEffect(dynob,"charge_table",charge_table,100,250,120,9.2,15.5)
                W_holdPosition(host,dynob,80,"charging")
                coroutine.yield()

                bc.ftest_ma_custom_coin(host,dynob,"komachi_coins",komachi_coins,
                1, -- tier
                1.4, -- speed
                10.0,  -- lifeTime
                3,     -- k
                3,     -- n
                1,     -- n2
                2,     -- l1
                1,     -- l2
                -1,    -- posneg
                0,    -- startAngle
                1.1,    -- angleStep
                45 * increament_count,    -- rotation
                12,     -- interval
                1)     -- time

                bc.ftest_ma_custom_coin(host,dynob,"komachi_coins",komachi_coins,
                0, -- tier
                1.6, -- speed
                10.0,  -- lifeTime
                2,     -- k
                1,     -- n
                3,     -- n2
                1,     -- l1
                1,     -- l2
                -1,     -- posneg
                0,    -- startAngle
                2.25,    -- angleStep
                60 * increament_count,    -- rotation
                18,     -- interval
                1)     -- time
                W_holdPosition(host,dynob,370,"cast")
                increament_count = increament_count + 1
                --W_holdPosition(host,dynob,400,"cast")
                coroutine.yield()
                y_index = 5
                x_index = -2
                reach_right = false
                reset_time = 60
                start = false
            end
        end
        if (x_index >= 2) then
            increament = -1
            reach_right = true
        end
        if(x_index <= -2) then
            increament = 1
        end

    end
end

