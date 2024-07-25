
local map

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

-- formerly known as "check_for_flag_at_tile(_tile_x, _tile_y, _flag)"
function Map_CheckForFlagAtTile(_tile_x, _tile_y, _flag)
end

-- formerly known as "get_room_from_pixel(_pixel_x, _pixel_y)"
function Map_GetRoomFromWorldPos(_world_x, _world_y)
end

function Map_GetRoomFromTile(_tile_x, _tile_y)
end

--------------------
-- core functions --
--------------------

local function AddRoom(_map_x, _map_y, _tile_width, _tile_height)
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

	-- load all the sprites
	local tile_path = "assets/sprites/leveltiles/"
	local tile_fnames = {
		"solid_block.png",
		"semisolid_platform.png",
		"hazard_block.png",
		"breakable_block.png",
		"start_room_origin_indicator.png",
		"room_origin_indicator.png",
		"room_width_indicator.png",
		"room_height_indicator.png",
	}
	tiles = {}
	for i = 1, #tile_fnames do
		tiles[i] = love.graphics.newImage(tile_path..tile_fnames[i])
	end

	-- create the map
	map = {
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
	for y = 1, #map do
		for x = 1, #map[y] do
			local tileIndex = map[y][x]
			if tileIndex > 0 then
				local tile = tiles[tileIndex]
				local drawX = (x - 1) * TILE_WIDTH
				local drawY = (y - 1) * TILE_HEIGHT
				love.graphics.draw(tile, drawX, drawY)

				-- debug stuff
				if true then
					love.graphics.points(drawX, drawY)
				end
			end
		end
	end
end
