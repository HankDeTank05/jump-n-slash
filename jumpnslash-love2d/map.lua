require("util")

local map_tileArray
local map_rooms
local map_tiles
local map_tileProps -- properties

-------------------
-- sanity checks --
-------------------

function Map_ValidateRoomNumber(_room_num)
end

----------------------
-- mutators/setters --
----------------------

function Map_SetCurrentRoom(_room_num)
end

function Map_ChangeRooms()
end

-----------------------
-- accessors/getters --
-----------------------

function Map_GetCurrentRoom()
end

function Map_GetCurrentRoomNum()
end

-- returns the x-position of the left edge of the current room (in world space)
function Map_GetCurrentLeftBounds()
end

-- returns the x-position of the right edge of the current room (in world space)
function Map_GetCurrentRightBounds()
end

-- returns the y-position of the top edge of the current room (in world space)
function Map_GetCurrentTopBounds()
end

-- returns the y-position of the top edge of the current room (in world space)
function Map_GetCurrentBottomBounds()
end

-- formerly known as "get_scrollability_horizontal()"
function Map_IsHorizontalScrolling()
end

-- formerly known as "get_scrollability_vertical()"
function Map_IsVerticalScrolling()
end

function Map_GetScrollLeftBounds()
end

function Map_GetScrollRightBounds()
end

function Map_GetScrollTopBounds()
end

function Map_GetScrollBottomBounds()
end

-- formerly known as "get_current_map_x()"
function Map_GetCurrentRoomOriginX()
end

-- formerly known as "get_current_map_y()"
function Map_GetCurrentRoomOriginY()
end

-- formerly known as "check_for_flag_at_pix(_map_pix_x, _map_pix_y, _flag)"
function Map_CheckForFlagAtWorldPos(_world_x, _world_y, _flag)
end

function Map_IsTileSolidTop(_tileX, _tileY)
	-- _tileX: x-index of the tile to get the solidTop property of
	-- _tileY: y-index of the tile to get the solidTop property of
	return map_tileProps[map_tileArray[_tileY][_tileX]].solidTop
end

function Map_IsTileSolidSide(_tileX, _tileY)
	-- _tileX: x-index of the tile to get the solidSide property of
	-- _tileY: y-index of the tile to get the solidSide property of
	return map_tileProps[map_tileArray[_tileY][_tileX]].solidSide
end

function Map_IsTileSolidBottom(_tileX, _tileY)
	-- _tileX: x-index of the tile to get the solidBottom property of
	-- _tileY: y-index of the tile to get the solidBottom property of
	return map_tileProps[map_tileArray[_tileY][_tileX]].solidBottom
end

function Map_IsTileBreakable(_tileX, _tileY)
	-- _tileX: x-index of the tile to get the breakable property of
	-- _tileY: y-index of the tile to get the breakable property of
	return map_tileProps[map_tileArray[_tileY][_tileX]].breakable
end

-- formerly known as "get_room_from_pixel(_pixel_x, _pixel_y)"
function Map_GetRoomFromWorldPos(_world_x, _world_y)
end

function Map_GetRoomFromTile(_tile_x, _tile_y)
end

--------------------
-- core functions --
--------------------

local function AddRoom(_mapX, _mapY, _tileWidth, _tileHeight)
	local room = {
		x = _mapX,
		y = _mapY,
		w = _tileWidth,
		h = _tileHeight,
		startX = nil,
		startY = nil,
		startFacing = nil,
	}
	table.insert(map_rooms, room)
end

function InitMap()
	--[[
	local cwd = love.filesystem.getWorkingDirectory()
	print(cwd)
	
	local dir = cwd.."/assets"
	print(dir)
	local dirInfo = love.filesystem.getInfo(dir)
	assert(dirInfo.type == "directory") -- if this gets triggered, the assets folder was not found

	dir = dir.."/leveldata"
	print(dir)
	dirInfo = love.filesystem.getInfo(dir)
	assert(dirInfo.type == "directory") -- if this gets triggered, the assets\leveldata folder was not found
	
	local level_fnames = love.filesystem.getDirectoryItems(dir)
	
	for i = 1, #level_fnames do
		print(dir..level_fnames[i])
		local iterator = love.filesystem.lines(cwd .. level_fnames[i])
		-- do stuff with the file (see https://love2d.org/wiki/love.filesystem.lines for example code)
	end
	]]

	ReadJsonFile("tools/formatting_rules.json")

	-- load all the sprites
	local tile_path = "assets/sprites/leveltiles/"
	local suffix = "_32.png"
	local tile_fnames = {
		"block_solid",
		"platform_semisolid",
		"block_hazard",
		"block_breakable",
		"indicator_room_origin_start",
		"indicator_room_origin",
		"indicator_room_width",
		"indicator_room_height",
	}
	map_tiles = {}
	map_tileProps = {}

	-- initialize tiles with undefined properties
	for i = 1, #tile_fnames do
		map_tiles[i] = love.graphics.newImage(tile_path .. tile_fnames[i] .. suffix)
		if i == 1 then
			-- solid block
			map_tileProps[i] = {
				solidTop = true,
				solidSide = true,
				solidBottom = true,
				breakable = false,
			}
		elseif i == 2 then
			-- semisolid platform
			map_tileProps[i] = {
				solidTop = true,
				solidSide = false,
				solidBottom = false,
				breakable = false,
			}
		elseif i == 3 then
			-- hazard block
			map_tileProps[i] = {
				solidTop = true,
				solidSide = true,
				solidBottom = true,
				breakable = false,
			}
		elseif i == 4 then
			-- breakable block
			map_tileProps[i] = {
				solidTop = true,
				solidSide = true,
				solidBottom = true,
				breakable = true,
			}
		end
	end

	-- create the map
	map_tileArray = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	}
end

function UpdateMap()
end

function DrawMap()
	for y = 1, #map_tileArray do
		for x = 1, #map_tileArray[y] do
			local tileIndex = map_tileArray[y][x]
			if tileIndex > 0 then
				local tile = map_tiles[tileIndex]
				local drawX = (x - 1) * TILE_SIZE
				local drawY = (y - 1) * TILE_SIZE
				love.graphics.draw(tile, drawX, drawY)

				-- debug stuff
				if true then
					love.graphics.points(drawX, drawY)
				end
			end
		end
	end
end
