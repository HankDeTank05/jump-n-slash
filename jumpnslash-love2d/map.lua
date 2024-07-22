
--------------------
-- core functions --
--------------------

function init_map()
	local cwd = love.filesystem.getWorkingDirectory()
	print(cwd)
	local level_fnames = {}
	for i = 1, #level_fnames do
		print(cwd..level_fnames[i])
		local iterator = love.filesystem.lines(cwd..level_fnames[i])
		-- do stuff with the file (see https://love2d.org/wiki/love.filesystem.lines for example code)
	end
end

function add_room(_map_x, _map_y, _tile_width, _tile_height)
end

function update_map()
end

function draw_map()
end

-------------------
-- sanity checks --
-------------------

function validate_room_number(_room_num)
end

----------------------
-- mutators/setters --
----------------------

function set_current_room(_room_num)
end

function change_rooms()
end

-----------------------
-- accessors/getters --
-----------------------

function map_get_current_room()
end

function map_get_current_room_num()
end

-- returns the x-position of the left edge of the current room (in world space)
function map_get_current_left_bounds()
end

-- returns the x-position of the right edge of the current room (in world space)
function map_get_current_right_bounds()
end

-- returns the y-position of the top edge of the current room (in world space)
function map_get_current_top_bounds()
end

-- returns the y-position of the top edge of the current room (in world space)
function map_get_current_bottom_bounds()
end

-- formerly known as "get_scrollability_horizontal()"
function map_is_horizontal_scrolling()
end

-- formerly known as "get_scrollability_vertical()"
function map_is_vertical_scrolling()
end

function map_get_scroll_left_bounds()
end

function map_get_scroll_right_bounds()
end

function map_get_scroll_top_bounds()
end

function map_get_scroll_bottom_bounds()
end

-- formerly known as "get_current_map_x()"
function map_get_current_room_origin_x()
end

-- formerly known as "get_current_map_y()"
function map_get_current_room_origin_y()
end

-- formerly known as "check_for_flag_at_pix(_map_pix_x, _map_pix_y, _flag)"
function map_check_for_flag_at_world_pos(_world_x, _world_y, _flag)
end

-- formerly known as "check_for_flag_at_tile(_tile_x, _tile_y, _flag)"
function map_check_for_flag_at_tile(_tile_x, _tile_y, _flag)
end

-- formerly known as "get_room_from_pixel(_pixel_x, _pixel_y)"
function map_get_room_from_world_pos(_world_x, _world_y)
end

function map_get_room_from_tile(_tile_x, _tile_y)
end