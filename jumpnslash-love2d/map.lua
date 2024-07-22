
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
	local cwd = love.filesystem.getWorkingDirectory()
	print(cwd)
	local level_fnames = {}
	for i = 1, #level_fnames do
		print(cwd .. level_fnames[i])
		local iterator = love.filesystem.lines(cwd .. level_fnames[i])
		-- do stuff with the file (see https://love2d.org/wiki/love.filesystem.lines for example code)
	end
end

function UpdateMap()
end

function DrawMap()
end
