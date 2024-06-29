pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

--[[
    this is the file for all code concerning the rooms
]]



function init_rooms()
    rooms = {} -- holds all the rooms in a list
    curr_room = nil -- the index of the current room
    scroll_x_offset = 0
    scroll_y_offset = 0

    debug_room_number = true
    map_max_tile_x = 127
    map_max_tile_y = 63
    map_max_pix_x = (map_max_tile_x * 8) - 1
    map_max_pix_y = (map_max_tile_y * 8) - 1

    -- room 1
    add_room(0, 16, 2, 30)
    --set_connections(1, 9, nil, nil, 2)
    set_connection_up(1, 9)
    set_connection_right(1, 2)

    -- room 2
    add_room(16, 16, nil, nil)
    --set_connections(2, nil, nil, 1, 3)
    set_connection_left(2, 1)
    set_connection_right(2, 3)

    -- room 3
    add_room(32, 16, nil, nil)
    --set_connections(3, nil, nil, 2, 4)
    set_connection_left(3, 2)
    set_connection_right(3, 4)

    -- room 4
    add_room(48, 16, nil, nil)
    --set_connections(4, nil, nil, 3, 5)
    set_connection_left(4, 3)
    set_connection_right(4, 5)

    -- room 5
    add_room(64, 16, nil, nil)
    --set_connections(5, nil, nil, 4, 6)
    set_connection_left(5, 4)
    set_connection_right(5, 6)

    -- room 6
    add_room(80, 16, nil, nil)
    --set_connections(6, 7, 8, 5, nil)
    set_connection_up(6, 7)
    set_connection_down(6, 8)
    set_connection_left(6, 5)

    -- room 7
    add_room(80, 0, nil, nil)
    --set_connections(7, nil, 6, nil, nil)
    set_connection_down(7, 6)

    -- room 8
    add_room(80, 32, nil, nil)
    --set_connections(8, 6, nil, nil, nil)
    set_connection_up(8, 6)

    -- room 9
    add_room(0, 0, nil, nil)
    --set_connections(9, nil, 1, nil, nil)
    set_connection_down(9, 1)

    validate_room_connections() -- note: room connections are validate at the end, so you can set connections ahead of time without crashing the program

    set_current_room(1)
end

function add_room(_map_x, _map_y, _start_x, _start_y)
    -- _map_x: the tile x-coordinate of the top-left of the room to be added
    -- _map_y: the tile y-coordinate of the top-left of the room to be added
    -- _start_x: the map tile x-coordinate where the player should start (set to nil if this room should not be a checkpoint)
    -- _start_y: the map tile y-coordinate where the player should start (set to nil if this room should not be a checkpoint)
    local room = {
        mx = _map_x,
        my = _map_y,
        start_mx = _start_x,
        start_my = _start_y,
        scroll_x = false, -- does this room scroll horizontally?
        scroll_y = false, -- does this room scroll vertically?
        mx_end = nil,
        my_end = nil,

        -- direction    U    D    L    R
        -- index        1    2    3    4
        connections = {nil, nil, nil, nil},
    }
    add(rooms, room)
end

function set_connection_up(_room_num, _conn_num)
    set_connection_generic(_room_num, 1, _conn_num)
end

function set_connection_down(_room_num, _conn_num)
    set_connection_generic(_room_num, 2, _conn_num)
end

function set_connection_left(_room_num, _conn_num)
    set_connection_generic(_room_num, 3, _conn_num)
end

function set_connection_right(_room_num, _conn_num)
    set_connection_generic(_room_num, 4, _conn_num)
end

function set_connection_generic(_room_num, _conn_dir, _conn_num)
    validate_room_num(_room_num)
    validate_direction_index(_conn_dir)
    rooms[_room_num].connections[_conn_dir] = _conn_num
end

function validate_room_num(_room_num)
    local msg = "_room_num=".._room_num
    assert(_room_num > 0, msg)
    assert(_room_num <= #rooms, msg)
end

function validate_direction_index(_conn_dir)
    assert(_conn_dir > 0)
    assert(_conn_dir <= 4)
end

function validate_room_connections()
    for rm in all(rooms) do
        for conn_dir=1,4 do
            local conn_num = rm.connections[conn_dir]
            if conn_num != nil then validate_room_num(conn_num) end
        end
    end
end

function set_current_room(_num)
    validate_room_num(_num)
    curr_room = _num
    
    if get_current_room().scroll_x == false then
        scroll_x_offset = 0
    end
    if get_current_room().scroll_y == false then
        scroll_y_offset = 0
    end
end

function get_current_room()
    return rooms[get_current_room_num()]
end

function get_current_room_num()
    assert(curr_room != nil) -- ensure the rooms have been initialized before doing anything
    return curr_room
end

function check_for_flag_at(_map_pix_x, _map_pix_y, _flag)
    return fget(mget(_map_pix_x / 8, _map_pix_y / 8), _flag)
end

-- currently does nothing
function update_room()
    -- code goes here
end

function trans_room_up()
    printh("trans room up")
    trans_room_generic(1)
end

function trans_room_down()
    printh("trans room down")
    trans_room_generic(2)
end

function trans_room_left()
    printh("trans room left")
    trans_room_generic(3)
end

function trans_room_right()
    printh("trans room right")
    trans_room_generic(4)
end

function trans_room_generic(_conn_dir)
    validate_direction_index(_conn_dir)
    local conn_num = get_current_room().connections[_conn_dir]
    validate_room_num(conn_num)
    set_current_room(conn_num)
end

function draw_room(_debug)
	
	--draw the map
    local rm = get_current_room()
	map(rm.mx, rm.my,
	    0, 0, -- x,y position to draw on screen
	    16, 16) -- w,h in tiles

    if _debug then
        
        if debug_room_number then
            print("room num: "..curr_room, 0, 12, 6)
        end
    end
end