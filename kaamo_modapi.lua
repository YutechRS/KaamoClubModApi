---@meta

---API Version string
---@type string
API_VERSION = "2.0"

---@class Player
---@field money integer Player's credits
---@field cargo integer Current cargo amount
---@field maxcargo integer Maximum cargo capacity
---@field armor integer Ship armor value
---@field maxhealth integer Maximum ship health
---@field enemieskilled integer Number of enemies killed
---@field level integer Player level
---@field visitedstations integer Number of stations visited
---@field jumpgateusedcount integer Number of times jump gates used
---@field cargotookcount integer Number of cargo items taken
player = {}

---Check if player's ship has armor
---@return boolean # True if ship has armor
function player:HasShipArmor() end

---@class System
---@field id integer System ID
---@field risk integer Risk level (0-5)
---@field faction integer Faction ID
---@field jumpgatestationid integer Jump gate station ID
---@field mapcoordinate_x integer Map X coordinate
---@field mapcoordinate_y integer Map Y coordinate
---@field mapcoordinate_z integer Map Z coordinate
system = {}

---@class Station
---@field id integer Station ID
---@field name string Station name
---@field level integer Tech level (1-10)
station = {}

---@class Mission
---@field id integer Current mission ID
---@field completedsidemissions integer Number of completed side missions
mission = {}

---@class Asset
asset = {}

---Get asset file path by offset
---@param offset integer Asset offset identifier
---@return string # File path of the asset
function asset:GetAssetFilePath(offset) end

---Set asset file path by offset
---@param offset integer Asset offset identifier
---@param path string New file path to set
function asset:SetAssetFilePath(offset, path) end

---Wait for specified milliseconds
---@param milliseconds integer Time to wait in milliseconds
function wait(milliseconds) end

---Log a message to console
---@param message string Message to log
function log(message) end

---Register a callback for an event
---
---Available events:
---  - "OnUpdate": Called every tick (~100Hz)
---  - "OnSystemChanged": Called when system changes (parameter: system_id)
---  - "OnMoneyChanged": Called when money changes (parameter: money)
---  - "IsInGame": Called when entering game
---  - "IsInMainMenu": Called when entering main menu
---
---@param event_name string Name of the event to register for
---@param callback function Function to call when event triggers
function RegisterEvent(event_name, callback) end

---Register a callback for an event with typed arguments
---Similar to RegisterEvent but provides better parameter handling
---@param event_name string Name of the event to register for
---@param callback function Function to call when event triggers with args
function RegisterEventWithArgs(event_name, callback) end
