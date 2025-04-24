---@diagnostic disable: redundant-parameter
package.path = package.path .. ';./Assets/LuaFiles/Common/?.lua' .. ';./Assets/LuaFiles/Komachi/?.lua' ..';./Komachi/?.lua'

bc =  require("./Assets/Luafiles/common/boss_common")

require "wrapper"
require("./Assets/Luafiles/common/boss_common")
-- coroutine table
dynamics = {}

Souls = {}
SoulsCount = 0

KomachiObj = nil



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
KOMACHI_COINS = {"komachi/komachi_12.png","komachi/komachi_11.png","komachi/komachi_13.png"}

-- charge table

Komachi_charge_table = {"projectile/fire_1.png","projectile/fire_2.png","projectile/fire_3.png","projectile/fire_4.png"}

Komachi_factor_table = {2,7,12,6}


-- Komachi param -- "./Assets/F_AObjects/boss_komachi.xml", komachi_boss_t
Komachi_object = {posX = 0.0, posY = 0.0,
 animationPath = "./Assets/F_AObjects/boss_komachi.xml",
 scale = 0.6, depth = 15, angle = 0 }

-- soul param
Komachi_soulData = {posX = 0.0, posY = 0.0, animationPath = "./Assets/F_AObjects/komachi_effects.xml", scale = 1.0, depth = 15.0, angle = 0.0 }

-- init ( double click on the object in the editor ) note, path is unused for now
function CreateFromLua(host,path)
	print("[LUA] create from LUA called \n")

	--komachi = cppCreateFromLua(host,object.animationPath,object.posX,object.posY,object.scale,object.depth,object.angle)
    KomachiObj = W_createObject(host,Komachi_object.animationPath,Komachi_object.posX,Komachi_object.posY,Komachi_object.scale,Komachi_object.depth,Komachi_object.angle)
    -- forceReinit()

end
-- move set : normal 1 ( pre spell 1 )
function moveset_normal_1( host )

	dynamics[KomachiObj] = {behavior = coroutine.create(DynamicBehavior1,host,KomachiObj)}
	IssueNextTask(host,KomachiObj)
end

-- move set : spell 1
function moveset_spell_1(host)
    dynamics[KomachiObj] = {behavior = coroutine.create(Komachi_spell_1_boss_movement,host,KomachiObj)}
    IssueNextTask(host,KomachiObj)
end

-- move set : normal 2
function moveset_normal_2(host)
    dynamics[KomachiObj] = {behavior = coroutine.create(DynamicBehavior2,host,KomachiObj)}
    IssueNextTask(host,KomachiObj)
end

-- move set : spell 2
function moveset_spell_2(host)
    dynamics[KomachiObj] = {behavior = coroutine.create(Komaci_spell_2_behavior,host,KomachiObj)}
    IssueNextTask(host,KomachiObj)
end

function moveset_normal_3(host)
    dynamics[KomachiObj] = {behavior = coroutine.create(DynamicBehavior3_normal,host,KomachiObj)}
    IssueNextTask(host,KomachiObj)
end

function moveset_spell_3(host)
    dynamics[KomachiObj] = {behavior = coroutine.create(DynamicBehavior3,host,KomachiObj)}
    IssueNextTask(host,KomachiObj)
end

function moveset_spell_4(host)
    dynamics[KomachiObj] = {behavior = coroutine.create(DynamicBehavior4,host,KomachiObj)}
    IssueNextTask(host,KomachiObj)
end