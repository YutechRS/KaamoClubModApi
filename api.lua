---@meta

---@class ShipInfo
---@field max_cargo number
---@field cargo number
---@field armor number

---@class SystemInfo
---@field id number

---@class Player
---@field money number
---@field ship ShipInfo

---@return Player
function GetPlayer() end

---@return SystemInfo
function GetSystem() end

---@param eventName string
---@param callback function
function RegisterEvent(eventName, callback) end

API_VERSION = "2.0"
