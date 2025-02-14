--- cppDoQuery
--- cppGenKey
---
---

--- Classes declare
---@class pointer


--- function wrapper of cppDoQuery
---@Description: call a server to do a query
---@param host pointer instance of ServerScriptingManager
---@param query string the query command
function SV_DoQuery(host,query)
    cppDoQuery(host,query)
    SV_GetQueryResults(host)
end


--- function wrapper of cppGetQueryResults
---@Description: get the result of a query
---@param host pointer instance of ServerScriptingManager
function SV_GetQueryResults(host)
    return cppGetQueryResults(host)
end

