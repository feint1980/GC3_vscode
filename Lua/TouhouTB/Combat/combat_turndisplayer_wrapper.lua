package.path = package.path .. ';../../Lua/TouhouTB/Combat/?.lua;' 

function CTD_AddPortrait(host, characterID,side)
    cpp_TurnDisplayer_AddPortrait(host, characterID,side)
end