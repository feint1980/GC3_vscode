package.path = package.path .. ';../../Lua/system/event/?.lua;'

require "TaskManager"
require "EventPipeline"

--- This is the pipeline event for home scene
--- Note, prefix must be "HOMESCENE_<EVENTNAME>"

EventPipeline.on("HOMESCENE_SYNCDATA", {

    -- instant: runs and continues immediately
    {
        type = "instant",
        -- duration = 10,
        fn   = function(data)
            print("HOMESCENE_SYNCDATA sync data after 50 tick" )
            Prompt_UI_Table["Home_Status"]:showMsg("Syncing data ...")
        end,
    },

{
        type = "async",
        fn = function(data,done)
            Home_UpdateInfo()
            print("Home_UpdateInfo request")
            -- Prompt_UI_Table["Home_Status"]:showMsg("Syncing data ...")
            EP_Signals["MainInfo"] = done

        end
    },
    -- async: done() called synchronously at the end of fn
    -- wait() sees isDone=true and skips the yield — behaves like instant
    {
        type = "async",
        fn   = function(data, done)
            Home_RequestSkillsStats()
            print("Home_RequestSkillsStats request")
            Prompt_UI_Table["Home_Status"]:setMsg("Getting skills ...")
            EP_Signals["SkillInfo"] = done
        end,
    },

    -- async: done() called later, from inside a simulated callback
    -- wait() yields here, TM_addTask resumes it after 0.5s
    {
        type = "async",
        fn   = function(data,done)
            Home_RequestOwnedCharacterList()
            print("Home_RequestOwnedCharacterList request")
            Prompt_UI_Table["Home_Status"]:setMsg("Getting Characters ...")
            EP_Signals["CharacterInfo"] = done
        end
    },

    -- timed: runs fn, then auto-advances after duration seconds
    {
        type     = "async",
        fn       = function(data,done)
            Home_RequestFormations()
            print("Home_RequestFormations request")
            Prompt_UI_Table["Home_Status"]:setMsg("Getting Formations ...")
            EP_Signals["FormationInfo"] = done
        end,
    },

    -- final step — proves all previous steps finished in order
    {
        type = "instant",
        fn   = function(data)
            print("All data done, get ping")
            Prompt_UI_Table["Home_Status"]:show(false)
            local ping = ClientGetPing(data.clientScritping)
            print("ping is " .. ping)
        end,
    },
})
