

EventPipeline.on("COMBAT_ON_MATCH_START", 
{
    {
        type = "instant",
        fn   = function()
            print("Combat OnMatchStart detected ##############################################")
            TM_addTask(function()
                CombatField_instance:showBannerMsg("Match Start")
            end,50)
        end
    },
})


-- EventPipeline.on("COMBAT_ON_PLAYER_TURN",{
--     {
--         type = "poll",
--         condition = function()
--             return EP_PollSignals["TurnDisplayerIsReady_2"] == true
--             end,
--         fn   = function(data)
--             print("Combat OnMatchStart detected ##############################################")
--             TM_addTask(function()
--                 CombatField_instance:showBannerMsg("Player " .. data.playerId .. "'s turn")
--             end,30)
--         end
--     },
-- })
