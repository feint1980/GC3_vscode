-- patchouli_orbs.lua
-- Minimal interactive test rig for Patchouli's 5-orb combination rule.
-- Run with: lua patchouli_orbs.lua
--
-- Controls (type the key then press Enter):
--   1 = Metal   2 = Wood   3 = Water   4 = Fire   5 = Earth
--   r = reset all slots to Free
--   q = quit
--
-- Rule:
--   Each element has exactly one killer:
--     Metal kills Wood
--     Wood  kills Earth
--     Earth kills Water
--     Water kills Fire
--     Fire  kills Metal
--   What happens depends on which orb you just placed:
--     - Place the VICTIM while its killer is stacked >= 2 -> that's a
--       rescue: the killer trims down to exactly 1, and the victim enters.
--     - Place the KILLER, bringing it to >= 2, while its victim already
--       exists -> that's an attack: ALL copies of the victim are removed.
--   Slots always stay compacted left-to-right -- no gaps in the middle,
--   Free slots only ever trail at the end.

local KEY_TO_ELEMENT = {
    ["1"] = "Metal",
    ["2"] = "Wood",
    ["3"] = "Water",
    ["4"] = "Fire",
    ["5"] = "Earth",
}

-- destroyerOf[X] = the element that destroys X
local destroyerOf = {
    Wood  = "Metal",
    Earth = "Wood",
    Water = "Earth",
    Fire  = "Water",
    Metal = "Fire",
}

-- victimOf[X] = the element that X destroys (reverse of destroyerOf)
local victimOf = {}
for victim, killer in pairs(destroyerOf) do
    victimOf[killer] = victim
end

local slots = { "Free", "Free", "Free", "Free", "Free" }

local function countElement(elem)
    local c = 0
    for i = 1, 5 do
        if slots[i] == elem then c = c + 1 end
    end
    return c
end

local function removeAll(elem)
    for i = 1, 5 do
        if slots[i] == elem then
            slots[i] = "Free"
        end
    end
end

local function trimToOne(elem)
    local kept = false
    for i = 1, 5 do
        if slots[i] == elem then
            if kept then
                slots[i] = "Free"
            else
                kept = true
            end
        end
    end
end

-- Left-packs all non-Free orbs so Free slots only ever trail at the end.
local function compact()
    local filled = {}
    for i = 1, 5 do
        if slots[i] ~= "Free" then
            filled[#filled + 1] = slots[i]
        end
    end
    for i = 1, 5 do
        slots[i] = filled[i] or "Free"
    end
end

local function nextFreeSlot()
    for i = 1, 5 do
        if slots[i] == "Free" then return i end
    end
    return nil
end

local function render()
    local parts = {}
    for i = 1, 5 do
        parts[i] = slots[i]
    end
    print("[ " .. table.concat(parts, " | ") .. " ]")
end

local function placeOrb(elem)
    if nextFreeSlot() == nil then
        print("-> All 5 slots full. Press 'r' to reset.")
        return
    end

    -- RESCUE: elem is a victim, and its killer is currently stacked >= 2.
    -- The over-stacked killer trims to exactly 1, freeing room, then elem enters.
    local killer = destroyerOf[elem]
    if killer and countElement(killer) >= 2 then
        trimToOne(killer)
        print(("-> %s was stacked >=2 -> trimmed to 1 so %s could enter")
            :format(killer, elem))
    end

    slots[nextFreeSlot()] = elem

    -- ATTACK: elem is a killer, and placing it just brought it to >= 2
    -- while its victim already exists. Wipe every copy of the victim.
    local victim = victimOf[elem]
    if victim and countElement(elem) >= 2 and countElement(victim) >= 1 then
        removeAll(victim)
        print(("-> %s reached >=2 -> %s cannot exist, all %s removed")
            :format(elem, victim, victim))
    end

    compact()
end

local function reset()
    for i = 1, 5 do slots[i] = "Free" end
    print("-> Reset.")
end

print("Patchouli Orb Combination Tester")
print("1=Metal 2=Wood 3=Water 4=Fire 5=Earth | r=reset q=quit")
render()

while true do
    io.write("> ")
    local input = io.read("*l")
    if not input then break end
    input = input:gsub("%s+", "")

    if input == "q" then
        break
    elseif input == "r" then
        reset()
        render()
    elseif KEY_TO_ELEMENT[input] then
        placeOrb(KEY_TO_ELEMENT[input])
        render()
    else
        print("-> Unrecognized input. Use 1-5, r, or q.")
    end
end

print("Done.")
