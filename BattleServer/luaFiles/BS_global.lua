ID_DISCONNECTION_NOTIFICATION = 21
ID_NEW_INCOMING_CONNECTION  = 19
ID_INCOMPATIBLE_PROTOCOL_VERSION = 25
ID_CONNECTED_PING = 0
ID_UNCONNECTED_PING = 1
ID_DISCONNECTION_NOTIFICATION = 21
ID_CONNECTION_LOST = 22
ID_CONNECTION_REQUEST_ACCEPTED = 16
ID_CONNECTION_ATTEMPT_FAILED = 17

CommonPacketHandling = {}

InternalPacketHandling = {}

ClientPacketHandling = {}

---@type table of BattleFormation
ClientFormations = {}

ClientOwnedCharacters = {}

MainInfo = {
    guid = ""
}

BattleLobbyState = {
    CLOSED = 0,
    OPEN = 1,
    INGAME = 2,
    EXPIRED = 3,
    FULL = 4,
    LOCK_IN = 5,
}

BattleLobby_List = {}
BattleClientEP_List = {}


--- Skills section 
Skills_Table = {} -- format Skills_Table[CharacterID][SkillID] 



---- Text color ( for Battle server)
TextColor = {}
TextColor.color_red = "<color=#ff1200>"
TextColor.color_orange = "<color=#FF5D00>"
TextColor.color_green = "<color=#00ff1d>"
TextColor.color_blue = "<color=#2B83FF>"
TextColor.color_close = "</color>"

TextColor.color_TB_VIT = "<color=#FF0800>"
TextColor.color_TB_STR = "<color=#FB8C00>"
TextColor.color_TB_DEX = "<color=#50FF0A>"
TextColor.color_TB_AGI = "<color=#00FFED>"
TextColor.color_TB_INT = "<color=#FF00DC>"
TextColor.color_TB_WIS = "<color=#0094FF>"
TextColor.color_TB_title = "<color=#ADB5FF>"

TextColor.color_TB_PHYSIC_DMG = "color=FF352B>"
TextColor.color_TB_MAGIC_DMG = "color=9666FF>"