package.path = package.path .. ';../../Lua/system/renderer/?.lua;'

RenderContext_Host = nil

require "renderContext_wrapper"


function RenderContext_Init(host)
    RenderContext_Host = host
end


