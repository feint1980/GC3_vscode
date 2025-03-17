--- Classes declare


--- split data into multiple part with special character and no of split
---@return table table of string data split
function SplitMessgae(message, character, no_of_split)
    local tTable;
    tTable = {};
    for str in string.gmatch(message, "([^" .. character .. "]+)") do
        table.insert(tTable, str);
    end
    return tTable
end