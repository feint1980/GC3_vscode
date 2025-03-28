package.path = package.path .. ';./Assets/LuaFiles/Common/?.lua' .. ';./Assets/LuaFiles/Komachi/?.lua'


bc =  require("./Assets/Luafiles/common/boss_common")

Komachi_fire_pilar = nil

Komachi_fire_pillar_up = nil

Komachi_fire_pillar_up_2 = nil

--@cppKomachi_pillar_setLightColor(pillar, r, g, b, a,transitionTime)

-- Belong to moveset_normal_4
function DynamicBehavior4(host,dynob)
    local count = 2
    local xthresHold = 175
    while true do
        --if (count > 1) then
            --count = -1
            W_moveObject(host,dynob,0,170,25)
            coroutine.yield()
            W_playAnimation(dynob,"charging",1,false)
            W_setObjectCharging(dynob,"Komachi_charge_table",
            Komachi_charge_table,100,250,
            120,9.5,15.5)
            W_holdPosition(host,dynob,80,"charging")
            coroutine.yield()
            W_holdPosition(host,dynob,80,"cast")
            W_StartShakeCamera(host,1.5,6,3)

            -- init, create pillar
            Komachi_fire_pilar = W_Komachi_summonPillar(host,dynob,"Textures/pillar_1.png","Textures/pillar_2.png",0,1024,
            2,0,255,255,255,255)

            Komachi_fire_pillar_up = W_Komachi_summonPillar(host,dynob,"Textures/pillar_1.png","Textures/pillar_2.png",0,1024,
            2,0,255,255,255,0)
            Komachi_fire_pillar_up_2 = W_Komachi_summonPillar(host,dynob,"Textures/pillar_1.png","Textures/pillar_2.png",0,1024,
            2,0,255,255,255,0)

            W_Komachi_pillar_setFrameIndex(Komachi_fire_pillar_up,1)
            W_Komachi_pillar_setFrameIndex(Komachi_fire_pillar_up_2,1)

            -- summon pillar into place
            W_Komachi_pillarMove(Komachi_fire_pilar,0,0,2)
            W_Komachi_pillarMove(Komachi_fire_pillar_up,0,0,2)
            W_Komachi_pillarMove(Komachi_fire_pillar_up_2,0,0,2)

            -- update 1, expand pillar
            W_Komachi_pillarExpand(Komachi_fire_pilar,11,1024,5)
            W_Komachi_pillarExpand(Komachi_fire_pillar_up,2,1024,5)
            W_Komachi_pillarExpand(Komachi_fire_pillar_up_2,2,1024,5)

            W_Komachi_pillar_setFlash(Komachi_fire_pilar,120,2)

            W_wait(host,dynob,60)
            coroutine.yield()
            W_Komachi_pillar_setLight(Komachi_fire_pilar,0.0,0.0,0,0,12,13,16.5,5500)



            -- update 2, pillar transform to full
            W_Komachi_pillar_setLightColor(Komachi_fire_pilar,0.65,0.08,1.0,1.0,4.5)
            W_Komachi_pillar_setLightAttenuation(Komachi_fire_pilar,12,13,16.5,4.5)
            

            W_wait(host,dynob,30)
            coroutine.yield()
            W_StartShakeCamera(host,6.5,4,6)
            
            W_Komachi_pillar_setLightAttenuation(Komachi_fire_pilar,44,26,75.5,4.5)
            -- W_Komachi_set_pillar_light(Komachi_fire_pilar,0.65,0.08,1.0,1.0,12,23,88.5,2000)
            W_Komachi_pillarExpand(Komachi_fire_pilar,500,1024,20)
            W_Komachi_pillar_setColor(Komachi_fire_pilar,255,255,255,122,20)
            W_wait(host,dynob,30)
            coroutine.yield()
            -- camera shake
            
            -- distortion
            --W_AddScreenDistortion(host,10,-512,1.2, 12.5, -200.0, 0.0005, 0.00012)

            -- W_AddScreenDistortion(host,10,-200,.7, 9.5, -125.0, 0.001, 0.0007)

            -- W_AddScreenDistortion(host,10,-100,.7, 10.5, -105.0, 0.001, 0.0007)

            W_Komachi_pillar_setLightColor(Komachi_fire_pilar,0.7,0.1,1.0,1.0,4.5)

            W_Komachi_pillar_setFlash(Komachi_fire_pilar,300,1)

            --- update 3, show souls follow
            W_Komachi_pillar_setUVUpdate(Komachi_fire_pillar_up,-0.00125,5000)
            W_wait(host,dynob,50)
            coroutine.yield()
            W_Komachi_pillar_setLightAttenuation(Komachi_fire_pilar,24,26,32.5,4.5)
            W_Komachi_pillar_setUVUpdate(Komachi_fire_pillar_up_2,-0.0025,5000)
            W_wait(host,dynob,100)
            coroutine.yield()
            W_StartShakeCamera(host,30,2,2)
            -- W_AddScreenDistortion(host,0,-512, .7, 6.5,500,
            -- -135.0, 0.001)

            W_Komachi_pillarExpand(Komachi_fire_pillar_up,500,1024,10)
            W_Komachi_pillarExpand(Komachi_fire_pillar_up_2,500,1024,10)
            W_wait(host,dynob,20)
            coroutine.yield()
            W_Komachi_pillar_setColor(Komachi_fire_pillar_up,255,255,255,75,40)
            W_Komachi_pillar_setColor(Komachi_fire_pillar_up_2,255,255,255,50,20)
            W_wait(host,dynob,20)
            coroutine.yield()

            W_Komachi_pillar_setLightAttenuation(Komachi_fire_pilar,44,26,75.5,45.5)


            -- W_Komachi_pillar_setFrameIndex(Komachi_fire_pilar,1)
            --cppKomachi_pillar_setFlashEffect(Komachi_fire_pilar,500,3)

            W_wait(host,dynob,500)
            coroutine.yield()

            coroutine.yield() -- this is for block the loop (to test)
            W_yield()
            print("hereeee !!!")
            -- W_playAnimation(dynob,"charge_end",1,true)
            -- cppHoldPosition(host,dynob,100,"charge_end",false)
            -- coroutine.yield()
        --end
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
            cppMoveObject(host,dynob,x_index * x_pos_threshold,y_pos_threshold * y_index,10 + reset_time )
            coroutine.yield()
        end

        if (start) then
            W_playAnimation(dynob,"cast",1,true)
        end
        x_index = x_index + increament
        start = true
        reset_time = 0

        cppHoldPosition(host,dynob,20,"charging",true)
        coroutine.yield()

        cppHoldPosition(host,dynob,1,"charge_end",true)
        spell_2_side_coin(host,dynob,
        increament,         -- direction
        0,                  -- tier
        "KOMACHI_COINS",    -- tableName
        KOMACHI_COINS,      -- tableAssets
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
        cppMoveObject(host,dynob,x_index * x_pos_threshold,y_pos_threshold * y_index,7  )
        coroutine.yield()
        cppHoldPosition(host,dynob,15,"charge_end",true)
        coroutine.yield()
        --cppHoldPosition(host,dynob,20,"charge_end",true)

        if(reach_right) then
            if (x_index == 0) then
                for i = 1, 3 do
                    cppHoldPosition(host,dynob,20,"charging",true)
                    coroutine.yield()
                    cppHoldPosition(host,dynob,1,"charge_end",true)
                    spell_2_side_coin(host,dynob,
                    increament,         -- direction
                    1,                  -- tier
                    "KOMACHI_COINS",    -- tableName
                    KOMACHI_COINS,      -- tableAssets
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
                    cppMoveObject(host,dynob,0 * x_pos_threshold,y_pos_threshold * y_index,10)
                    coroutine.yield()

                end

                W_playAnimation(dynob,"charging",1,false)
                cppObjectSetChargingEffect(dynob,"Komachi_charge_table",Komachi_charge_table,100,250,120,9.2,15.5)
                cppHoldPosition(host,dynob,80,"charging")
                coroutine.yield()

                Ftest_ma_custom_coin(host,dynob,"KOMACHI_COINS",KOMACHI_COINS,
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

                Ftest_ma_custom_coin(host,dynob,"KOMACHI_COINS",KOMACHI_COINS,
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
                cppHoldPosition(host,dynob,370,"cast")
                increament_count = increament_count + 1
                --cppHoldPosition(host,dynob,400,"cast")
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


