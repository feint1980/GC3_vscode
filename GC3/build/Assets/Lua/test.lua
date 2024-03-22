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

local dynamics = {}

komachi = nils

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


komachi = nil



function test_ttt(host,dynob)
  while true do 
    print("test")
    main.setTargetPos(boss_komachi["id"], -250,-200)
    coroutine.yield()
    main.setTargetPos(boss_komachi["id"], -250,200)
    coroutine.yield()
  end
end


function createBoss(host, name)
  komachi = main.createObject(name)
end
function test(host)
 
  dynamics[komachi] = {behavior = coroutine.create(test_ttt,host,komachi)}
  IssueNextTask(host,komachi)
end


function IssueNextTask(host,dynob)
  if coroutine.status(dynamics[komachi].behavior) ~= 'dead' then
      coroutine.resume(dynamics[komachi].behavior, host,dynob)
  else
      print(coroutine.status(dynamics[komachi].behavior))
  end
end

komachi = main.createObject("boss_komachi")

co = coroutine.create(function() 
  print("!!!!!!!!!!!!!!!!!test corona")
end)

coroutine.resume(co)


function test_coroutine2(name)
  while true do
    print("cung manh")
    main.sleep(1000)
    coroutine.yield()
    print("cung dc")
    main.sleep(1000)
    coroutine.yield()
    print("cung dep")
    main.sleep(1000)
    coroutine.yield()
  end

end

co2  = coroutine.create(test_coroutine2,"test name")


function issueTask()
  print("issue task")
  if coroutine.status(co2) ~= 'dead' then
    coroutine.resume(co2,"test")
  else
    print(coroutine.status(co2))
  end
end

function helloTest()
  print("hello test")
end

helloTest()

function mainTask()
  while true do
    issueTask()
  end

end


mainTask()


-- coroutine.yield()
-- main.setTargetPos(boss_komachi["id"], -250,-200)
-- print("end ")
