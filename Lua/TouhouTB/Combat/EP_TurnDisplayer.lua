
-- =============================================================================
--  EP_TurnDisplayer_Example.lua
--  Usage example: wiring the turn displayer animation sequence to EventPipeline.
--
--  LOAD ORDER (in your scene init):
--    1. TaskManager.lua       (loaded by LuaTaskManager::init)
--    2. BS_EventPipeline.lua  (loaded by LuaEventPipeline::init)
--    3. This file             (loaded by luaL_dofile in your scene script)
--
--  C++ UPDATE LOOP (call both every frame):
--    m_taskManager.update(dt);
--    m_eventPipeline.update(dt);
-- =============================================================================


-- ─── One-time setup ───────────────────────────────────────────────────────────
-- Delegate timed steps to your existing TaskManager timer.
-- This is the only connection between the two modules.

EventPipeline.setTimerFn(function(sec, cb)
    TM_addTask(cb, sec)
end)


-- =============================================================================
--  HANDLER REGISTRATION
--  Do this once when the match scene loads.
--  These stay registered for the whole match — no need to re-register per round.
-- =============================================================================

-- ── MATCH_START ───────────────────────────────────────────────────────────────
-- Server sends: { characters = { {id, icon, baseSpeed}, ... } }
-- Spreads character icon cards from center to the top bar.

EventPipeline.on("MATCH_START", {
    {
        type = "async",
        fn   = function(data, done)
            TurnDisplayer.spreadCards(data.characters, done)
            -- TurnDisplayer.spreadCards plays the fan-out tween,
            -- calls done() when all cards have reached their positions.
        end,
    },
})


-- ── ROLL_RESULTS ──────────────────────────────────────────────────────────────
-- Server sends: { changes = { {id, delta, finalSpeed}, ... } }
-- Four sequential steps — each waits for the previous to fully finish.

EventPipeline.on("ROLL_RESULTS", {
    {
        -- Step 1: floating +/- delta text animates out from each icon
        -- Green for positive rolls, red for negative (handled inside showSpeedDeltas)
        type = "async",
        fn   = function(data, done)
            TurnDisplayer.showSpeedDeltas(data.changes, done)
        end,
    },
    {
        -- Step 2: update the speed number shown on each icon (instant, no anim)
        type = "instant",
        fn   = function(data)
            TurnDisplayer.updateSpeeds(data.changes)
        end,
    },
    {
        -- Step 3: slide cards into sorted order (highest speed → top)
        type = "async",
        fn   = function(data, done)
            TurnDisplayer.sortCards(data.changes, done)
        end,
    },
    -- Note: no selectCard step here.
    -- CHARACTER_TURN packet handles selection and is queued AFTER these steps.
    -- The race condition is structurally impossible — it sits behind sortCards.
})


-- ── CHARACTER_TURN ────────────────────────────────────────────────────────────
-- Server sends: { characterId, ownerId }
-- Moves the selection border to the active character's card.
--
-- This packet often arrives BEFORE sortCards is done animating.
-- Because it's queued, it will always execute after sort finishes. No guard needed.

EventPipeline.on("CHARACTER_TURN", {
    {
        type = "instant",
        fn   = function(data)
            TurnDisplayer.selectCard(data.characterId)
        end,
    },
})


-- ── NEW_ROUND ─────────────────────────────────────────────────────────────────
-- Server sends: { round, changes = { {id, delta, finalSpeed}, ... } }
-- Same as ROLL_RESULTS but with a round banner shown first.

EventPipeline.on("NEW_ROUND", {
    {
        -- Show "Round X" banner for 1 second, then auto-continue
        type     = "timed",
        duration = 1.0,
        fn       = function(data)
            TurnDisplayer.showRoundBanner(data.round)
        end,
    },
    {
        type = "async",
        fn   = function(data, done)
            TurnDisplayer.showSpeedDeltas(data.changes, done)
        end,
    },
    {
        type = "instant",
        fn   = function(data)
            TurnDisplayer.updateSpeeds(data.changes)
        end,
    },
    {
        type = "async",
        fn   = function(data, done)
            TurnDisplayer.sortCards(data.changes, done)
        end,
    },
})


-- ── BATTLE_END ────────────────────────────────────────────────────────────────
-- Server sends: { winnerId, loserId, rounds }
-- Clears the queue first (abort any in-progress animations), then show result.

EventPipeline.on("BATTLE_END", {
    {
        type = "instant",
        fn   = function(data)
            -- Wipe any pending animation steps (e.g. match ended mid-sort)
            EventPipeline.clearQueue()
            TurnDisplayer.hide()
            ResultScreen.show(data.winnerId, data.loserId, data.rounds)
        end,
    },
})


-- =============================================================================
--  OPTIONAL: Guards
--  Drop incoming events during specific game states.
-- =============================================================================

-- Ignore CHARACTER_TURN events while the result screen is visible
EventPipeline.guard("CHARACTER_TURN", function(data)
    return not ResultScreen.isVisible()
end)


-- =============================================================================
--  PACKET RECEIVE HANDLER
--  Wire this to your RakNet receive callback.
--  This is ALL the packet handler needs to do — one line per event.
-- =============================================================================

function OnBattlePacketReceived(eventName, data)
    EventPipeline.emit(eventName, data)
end


-- =============================================================================
--  EXAMPLE: Manual emit for testing without a server
--  Call these from your debug console or test script.
-- =============================================================================

function DEBUG_simulateMatchStart()
    EventPipeline.emit("MATCH_START", {
        characters = {
            { id = "reimu",   icon = "reimu_icon",   baseSpeed = 14 },
            { id = "yukari",  icon = "yukari_icon",  baseSpeed = 11 },
            { id = "meiling", icon = "meiling_icon", baseSpeed = 16 },
            { id = "remilia", icon = "remilia_icon", baseSpeed = 13 },
        }
    })
end

function DEBUG_simulateRollResults()
    EventPipeline.emit("ROLL_RESULTS", {
        changes = {
            { id = "reimu",   delta =  3, finalSpeed = 17 },
            { id = "yukari",  delta =  5, finalSpeed = 16 },
            { id = "meiling", delta = -2, finalSpeed = 14 },
            { id = "remilia", delta =  4, finalSpeed = 17 },
        }
    })
end

function DEBUG_simulateCharacterTurn()
    -- Call this immediately after simulateRollResults to test the race condition fix.
    -- selectCard should fire AFTER sortCards finishes, even though this emit
    -- happens at the same moment as ROLL_RESULTS.
    EventPipeline.emit("CHARACTER_TURN", {
        characterId = "reimu",
        ownerId     = "player1",
    })
end
