local scheduler = {}

function scheduler:wait(time, callback)
    table.insert(self, {time = time, callback = callback})
end

function scheduler:update(dt)
    -- print("update call ")
    for i = #self, 1, -1 do
        local task = self[i]
        print("task " .. task.time)
        task.time = task.time - dt
        if task.time <= 0 then
            task.callback()
            table.remove(self, i)
        end
    end
end

-- Example Usage
scheduler:wait(5, function() print("5 seconds passed!") end)
scheduler:wait(2, function() print("2 seconds passed!") end)


-- Simulating a game loop
local elapsed = 0
while true do
    scheduler:update(0.1)  -- Simulating 1 second per frame
    elapsed = elapsed + 0.1
end

print("end ")