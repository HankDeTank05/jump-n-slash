pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

--[[
    this is the file for all code concerning the rooms
]]

rooms = {} -- holds all the rooms in a list
curr_room = 0 -- the index of the current room

function init_rooms()
    rooms = {
        -- room  1 (the test room)
		{ 
            x = 0, y = 0,
            start_x = 16, start_y = 100,
        },
        -- room  2
		{ 
            x = 16, y = 0,
            start_x = nil, start_y = nil,
        },
        -- room  3
		{ 
            x = 32, y = 0,
            start_x = nil, start_y = nil,
        },
        -- room  4
		{ 
            x = 48, y = 0,
            start_x = nil, start_y = nil,
        },
        -- room  5
		{ 
            x = 64, y = 0,
            start_x = nil, start_y = nil,
        },
        -- room  6
		{ 
            x = 80, y = 0,
            start_x = nil, start_y = nil,
        },
        -- room  7 (aka 2 w/o lava)
		{ 
            x = 16, y = 16,
            start_x = nil, start_y = nil,
        },
        -- room  8 (aka 3 w/o lava)
		{ 
            x = 32, y = 16,
            start_x = nil, start_y = nil,
        },
        -- room  9 (aka 4 w/o lava)
		{ 
            x = 48, y = 16,
            start_x = nil, start_y = nil,
        },
        -- room 10 (aka 5 w/o lava)
		{ 
            x = 64, y = 16,
            start_x = nil, start_y = nil,
        },
        -- room 11 (aka 6 w/o lava)
		{ 
            x = 80, y = 16,
            start_x = nil, start_y = nil,
        },
	}
    set_current_room(6)
end

function set_current_room(_num)
    assert(_num <= #rooms)
    curr_room = _num
end

function get_current_room()
    return rooms[curr_room]
end

function screen_x_to_map_x(_screen_x)
    -- convert from a screen x-pos to a tile x-pos on the map
    -- note: the map x-pos will be based on the current room
    return (_screen_x / 8) + get_current_room().x
end

function screen_y_to_map_y(_screen_y)
    -- convert from a screen y-pos to a tile y-pos on the map
    -- note: the map x-pos will be based on the current room
    return (_screen_y / 8) + get_current_room().y
end

function check_for_flag_at(_screen_x, _screen_y, _flag)
    return fget(mget(screen_x_to_map_x(_screen_x), screen_y_to_map_y(_screen_y)), _flag)
end

function update_room()
end

function draw_room(_debug)
	
	--draw the map
	map(rooms[curr_room].x, rooms[curr_room].y,
	    0, 0, -- x,y position to draw on screen
	    16, 16) -- w,h in tiles

    if _debug then
        -- code goes here
    end
end