package.path = package.path .. ';./Assets/LuaFiles/Common/?.lua' .. ';./Assets/LuaFiles/Komachi/?.lua' ..';./Komachi/?.lua'

bc =  require("./Assets/Luafiles/common/boss_common")

require "wrapper"
-- coroutine table
dynamics = {}

souls = {}
soulsCount = 0

komachi = nil
soul_1 = nil
t_soul = nil


-- require "Komachi_spell_1"
-- require "Komachi_spell_2"
-- require "Komachi_spell_3"
-- require "Komachi_spell_4"

-- load all module in ./Assets/LuaFiles/Komachi
-- for filename in io.popen('dir /b/a-d "./Assets/LuaFiles/Komachi/"'):lines() do  --Windows
--     filename = filename:match"^(.*)%.lua$"
--     if filename then
--         print("reloading files ... " .. filename)
--         require("./Assets/LuaFiles/Komachi."..filename)
--     end
-- end

--- reload all lua files (at runtime)
local function forceReinit()
    for filename in io.popen('dir /b/a-d "./Assets/LuaFiles/Komachi/"'):lines() do  --Windows
        filename = filename:match"^(.*)%.lua$"
        if filename then
            print("reloading files ... " .. filename)
            dofile("./Assets/LuaFiles/Komachi/"..filename .. ".lua")
        end
    end
end


forceReinit()
-- init random seed
math.randomseed(os.time())

function IssueNextTask(host, dynob)
    if coroutine.status(dynamics[dynob].behavior) ~= 'dead' then
		coroutine.resume(dynamics[dynob].behavior, host, dynob)
	else
		print(coroutine.status(dynamics[dynob].behavior))
	end
end

------------------------------------------------------------------

-- coin table
komachi_coins = {"komachi/komachi_12.png","komachi/komachi_11.png","komachi/komachi_13.png"}

-- charge table

charge_table = {"projectile/fire_1.png","projectile/fire_2.png","projectile/fire_3.png","projectile/fire_4.png"}

factor_table = {2,7,12,6}

-- Komachi param -- "./Assets/F_AObjects/boss_komachi.xml", komachi_boss_t
object = {posX = 0.0, posY = 0.0,
 animationPath = "./Assets/F_AObjects/boss_komachi.xml",
 scale = 0.6, depth = 15, angle = 0 }

-- soul param
soulData = {posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/komachi_effects.xml", scale = 1.0, depth = 15.0, angle = 0.0 }

-- init ( double click on the object in the editor ) note, path is unused for now
function CreateFromLua(host,path)
	print("[LUA] create from LUA called \n")

	--komachi = cppCreateFromLua(host,object.animationPath,object.posX,object.posY,object.scale,object.depth,object.angle)
    komachi = W_createObject(host,object.animationPath,object.posX,object.posY,object.scale,object.depth,object.angle)
    -- forceReinit()

end
-- move set : normal 1 ( pre spell 1 )
function moveset_normal_1( host )

	dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior1,host,komachi)}
	IssueNextTask(host,komachi)
end

-- move set : spell 1
function moveset_spell_1(host)
    dynamics[komachi] = {behavior = coroutine.create(spell_1_boss_movement,host,komachi)}
    IssueNextTask(host,komachi)
 end

-- move set : normal 2
function moveset_normal_2(host)
    dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior2,host,komachi)}
    IssueNextTask(host,komachi)
end

-- move set : spell 2
function moveset_spell_2(host)
    dynamics[komachi] = {behavior = coroutine.create(spell_2_behavior,host,komachi)}
    IssueNextTask(host,komachi)
end

function moveset_normal_3(host)
    dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior3_normal,host,komachi)}
    IssueNextTask(host,komachi)
end

function moveset_spell_3(host)
    dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior3,host,komachi)}
    IssueNextTask(host,komachi)
end

function moveset_spell_4(host)
    dynamics[komachi] = {behavior = coroutine.create(DynamicBehavior4,host,komachi)}
    IssueNextTask(host,komachi)
end