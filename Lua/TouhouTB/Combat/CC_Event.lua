CC_Event = {}

local pending = {}

---@Description Yield the current coroutine until eventKey is fired.
---Must be called from inside a coroutine (e.g. via coroutine.wrap).
---@param eventKey string
function CC_Event.wait(eventKey)
    local co = coroutine.running()
    if not co then
        print("CC_Event.wait called outside a coroutine for key: " .. eventKey)
        return
    end
    pending[eventKey] = co
    coroutine.yield()
end

---@Description Resume whichever coroutine is waiting on eventKey, if any.
---Called from C++ via CombatCharacter::fireLuaEvent.
---@param eventKey string
function CC_Event.fire(eventKey)
    local co = pending[eventKey]
    if not co then
        return -- nothing waiting on this, ignore
    end
    pending[eventKey] = nil

    local ok, err = coroutine.resume(co)
    if not ok then
        print("CC_Event: coroutine resume error on " .. eventKey .. ": " .. tostring(err))
    end
end