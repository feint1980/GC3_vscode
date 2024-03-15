print("Helloooooo ")



-- boss_komachi = {
--     4, -- 1: ID 
--     "Komachi", -- 2: Name  
--     "./Assets/F_AObjects/boss_komachi.xml", -- 3: Animation Path
--     {50,50}, -- 4: Position
--     {1.0, 1.0}, -- 5: Scale
--     15.0, -- 6: Depth
--     0.0, -- 7: Angle
--     {0,0}, -- 8: Velocity
--     {4,1500}, -- 9: HP bars
--     "dialogue_path.xml" -- 10: Dialogue
-- }

function table.shallow_copy(t)
    local t2 = {}
    for k,v in pairs(t) do
      t2[k] = v
    end
    return t2
  end

boss_komachi = {
    id = 4, -- 1: ID 
    name = "Komachi", -- 2: Name  
    assetPath = "./Assets/F_AObjects/boss_eiki.xml", -- 3: Animation Path
    pos = {0.0,0.0}, -- 4: Position
    scale = {1.0, 1.0}, -- 5: Scale
    depth = 15.0, -- 6: Depth
    angle =  0.0, -- 7: Angle
    vel = {0,0}, -- 8: Velocity
    hpBars = {4,1500}, -- 9: HP bars
    dialoge_path = "dialogue_path.xml" -- 10: Dialogue
}




print(boss_komachi["name"])

boss_eiki = table.shallow_copy(boss_komachi)

boss_eiki.id = 7
boss_eiki.name = "Eiki"

print(boss_eiki["name"])

main.createObject("boss_komachi")


coroutine.yield(main.setTargetPos(boss_komachi["id"], 50,200))

coroutine.yield(main.setTargetPos(boss_komachi["id"], 0,0))

-- coroutine.yield()
-- main.setTargetPos(boss_komachi["id"], -250,-200)
-- print("end ")
