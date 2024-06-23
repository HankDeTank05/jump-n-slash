pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

--[[
    this is the file for all code concerning the rooms
]]

rooms = {} -- holds all the rooms in a list
curr_room = nil -- the index of the current room

function init_rooms()
    rooms = {
		{ -- room  1 (the test room)
            x = 0, y = 0,
            start_x = 16, start_y = 100,
            -- connections to other rooms
            connections = {
                u = nil, -- connection when exiting up
                d = nil, -- connection when exiting down
                l = nil, -- connection when exiting left
                r = 2, -- connection when exiting right
            }
        },
		{ -- room  2
            x = 16, y = 0,
            start_x = nil, start_y = nil,
            -- connections to other rooms
            connections = {
                u = nil, -- connection when exiting up
                d = nil, -- connection when exiting down
                l = 1, -- connection when exiting left
                r = 3, -- connection when exiting right
            }
        },
		{ -- room  3
            x = 32, y = 0,
            start_x = nil, start_y = nil,
            -- connections to other rooms
            connections = {
                u = nil, -- connection when exiting up
                d = nil, -- connection when exiting down
                l = 2, -- connection when exiting left
                r = 4, -- connection when exiting right
            }
        },
		{ -- room  4
            x = 48, y = 0,
            start_x = nil, start_y = nil,
            -- connections to other rooms
            connections = {
                u = nil, -- connection when exiting up
                d = nil, -- connection when exiting down
                l = 3, -- connection when exiting left
                r = 5, -- connection when exiting right
            }
        },
		{ -- room  5
            x = 64, y = 0,
            start_x = nil, start_y = nil,
            -- connections to other rooms
            connections = {
                u = nil, -- connection when exiting up
                d = nil, -- connection when exiting down
                l = 4, -- connection when exiting left
                r = 6, -- connection when exiting right
            }
        },
		{ -- room  6
            x = 80, y = 0,
            start_x = nil, start_y = nil,
            -- connections to other rooms
            connections = {
                u = nil, -- connection when exiting up
                d = nil, -- connection when exiting down
                l = 5, -- connection when exiting left
                r = nil, -- connection when exiting right
            }
        },
	}
    set_current_room(1)
end

function set_current_room(_num)
    assert(_num > 0) -- ensure we have a valid room number
    assert(_num <= #rooms) -- ^^what he said^^
    curr_room = _num
end

function get_current_room()
    assert(curr_room != nil) -- ensure the rooms have been initialized before doing anything
    return rooms[curr_room]
end

function get_current_room_num()
    assert(curr_room != nil) -- ensure the rooms have been initialized before doing anything
    return curr_room
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

-- currently does nothing
function update_room()
    -- code goes here
end

-- not yet implemented
function trans_room_up()
    assert(get_current_room().connections.u != nil)
    assert(false)
    -- code goes here
end

-- not yet implemented
function trans_room_down()
    assert(get_current_room().connections.d != nil)
    assert(false)
    -- code goes here
end

function trans_room_left()
    assert(get_current_room().connections.l != nil)
    set_current_room(get_current_room().connections.l)
end

function trans_room_right()
    assert(get_current_room().connections.r != nil)
    set_current_room(get_current_room().connections.r)
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