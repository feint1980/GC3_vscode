local openlibs = function()
    -- Force load standard libraries manually
    _G.coroutine = require("coroutine")
    _G.package   = require("package")
    _G.string    = require("string")
    _G.table     = require("table")
    _G.math      = require("math")
    _G.io        = require("io")
    _G.os        = require("os")
    _G.debug     = require("debug")
end
openlibs()

local bit = require("bit32")  -- Lua 5.1 uses 'bit' from LuaBitOp or LuaJIT

function is_bit_set(value, bit_index)
    return bit.band(value, bit.lshift(1, bit_index)) ~= 0
end



local flags = 2  -- binary: 10

print(is_bit_set(flags, 1))  --> true (bit 1 is 1)
print(is_bit_set(flags, 0))  --> false (bit 0 is 0)