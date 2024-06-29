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
    
    map_max_tile_x = 127
    map_max_tile_y = 63
    map_max_pix_x = (map_max_tile_x * 8) - 1
    map_max_pix_y = (map_max_tile_y * 8) - 1
    
    -- room 1
    add_room(0, 16, 16, 16, 2, 30)
    set_connection_up(1, 9)
    set_connection_right(1, 2)

    -- room 2
    add_room(16, 16, 16, 16, nil, nil)
    set_connection_up(2, 9)
    set_connection_left(2, 1)
    set_connection_right(2, 3)

    -- room 3
    add_room(32, 16, 16, 16, nil, nil)
    set_connection_left(3, 2)
    set_connection_right(3, 4)

    -- room 4
    add_room(48, 16, 16, 16, nil, nil)
    set_connection_left(4, 3)
    set_connection_right(4, 5)

    -- room 5
    add_room(64, 16, 16, 16, nil, nil)
    set_connection_left(5, 4)
    set_connection_right(5, 6)

    -- room 6
    add_room(80, 16, 16, 16, nil, nil)
    set_connection_up(6, 7)
    set_connection_down(6, 8)
    set_connection_left(6, 5)

    -- room 7
    add_room(80, 0, 16, 16, nil, nil)
    set_connection_down(7, 6)

    -- room 8
    add_room(80, 32, 16, 16, nil, nil)
    set_connection_up(8, 6)

    -- room 9
    add_room(0, 0, 32, 16, nil, nil)
    set_connection_down(9, 1)

    validate_room_connections() -- note: room connections are validate at the end, so you can set connections ahead of time without crashing the program

    set_current_room(1)
end

function add_room(_map_x, _map_y, _tile_width, _tile_height, _start_x, _start_y)
    -- _map_x: the tile x-coordinate of the top-left of the room to be added
    -- _map_y: the tile y-coordinate of the top-left of the room to be added
    -- _tile_width: the width of the room in number of tiles
    -- _tile_height: the height of the room in number of tiles
    -- _start_x: the map tile x-coordinate where the player should start (set to nil if this room should not be a checkpoint)
    -- _start_y: the map tile y-coordinate where the player should start (set to nil if this room should not be a checkpoint)

    -- make sure rooms are no smaller than 16x16 tiles
    assert(_tile_width >= 16)
    assert(_tile_height >= 16)
    
    -- make sure rooms dimensions are multiples of 16
    assert(_tile_width % 16 == 0)
    assert(_tile_height % 16 == 0)

    local room = {
        mx = _map_x,
        my = _map_y,
        mw = _tile_width,
        mh = _tile_height,

        -- pixel boundaries: when player crosses these boundaries, trigger screen transition
        mpx_min = _map_x * 8,
        mpx_max = (_map_x + _tile_width) * 8,
        mpy_min = _map_y * 8,
        mpy_max = (_map_y + _tile_height) * 8,

        -- spawn point in room (not every room needs to have one)
        start_mx = _start_x,
        start_my = _start_y,

        scroll_h = _tile_width > 16, -- does this room scroll horizontally?
        scroll_v = _tile_height > 16, -- does this room scroll vertically?

        -- pixel boundaries for screen scrolling: when player crosses these boundaries, start/end screen scrolling
        scroll_h_min_mpx = (_map_x + 8) * 8,
        scroll_h_max_mpx = (_map_x + _tile_width - 8) * 8,
        scroll_v_min_mpy = (_map_y + 8) * 8,
        scroll_v_max_mpy = (_map_y + _tile_height - 8) * 8,

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
    
    if get_current_room().scroll_h == false then
        scroll_x_offset = 0
    end
    if get_current_room().scroll_v == false then
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

function get_current_left_bounds()
    return get_current_room().mpx_min
end

function get_current_right_bounds()
    return get_current_room().mpx_max
end

function get_current_top_bounds()
    return get_current_room().mpy_min
end

function get_current_bottom_bounds()
    return get_current_room().mpy_max
end

function get_scrollability_horizontal()
    return get_current_room().scroll_h
end

function get_scrollability_vertical()
    return get_current_room().scroll_v
end

function get_scroll_left_bounds()
    return get_current_room().scroll_h_min_mpx
end

function get_scroll_right_bounds()
    return get_current_room().scroll_h_max_mpx
end

function get_scroll_top_bounds()
    return get_current_room().scroll_v_min_mpx
end

function get_scroll_bottom_bounds()
    return get_current_room().scroll_v_max_mpx
end

function check_for_flag_at(_map_pix_x, _map_pix_y, _flag)
    return fget(mget(_map_pix_x / 8, _map_pix_y / 8), _flag)
end

-- currently does nothing
function update_room()

    -- if there is horizontal scrolling and no vertical scrolling...
    if get_scrollability_horizontal() and not(get_scrollability_vertical()) then

        if p1_get_mpx() <= get_scroll_left_bounds() then
            scroll_x_offset = 0
        elseif get_scroll_left_bounds() < p1_get_mpx() and p1_get_mpx() <= get_scroll_right_bounds() then
            scroll_x_offset = -(p1_get_mpx() - get_scroll_left_bounds())
        elseif get_scroll_right_bounds() < p1_get_mpx() then
            scroll_x_offset = -(get_scroll_right_bounds() - get_scroll_left_bounds())
        end
    end

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
	    scroll_x_offset, 0, -- x,y position to draw on screen
	    rm.mw, rm.mh) -- w,h in tiles

    if _debug then
        
        if debug_room_number then
            print("room num: "..curr_room, 0, 12, 6)
        end

        if debug_scroll_bounds then
            if get_scrollability_horizontal() then
                local col = 9 -- orange

                local left_bound_draw_x = get_scroll_left_bounds() + scroll_x_offset
                local right_bound_draw_x = get_scroll_right_bounds() + scroll_x_offset

                -- draw left line if it's on the screen
                line(left_bound_draw_x, 0, left_bound_draw_x, 127, col)
                print("l: "..get_scroll_left_bounds(), left_bound_draw_x + 2, 64)
                
                -- draw right line of it's on the scren
                line(right_bound_draw_x, 0, right_bound_draw_x, 127, col)
                print("r: "..get_scroll_right_bounds(), right_bound_draw_x + 2, 64)

                col = 2 -- maroon

                -- draw player distance from/between scroll bounds
                line(left_bound_draw_x, p1_get_sy(), p1_get_sx(), p1_get_sy(), col)
                local dist_l = abs(scroll_x_offset)
                local dist_l_print_x = max(left_bound_draw_x + 2, 2)
                print("dist: "..dist_l, dist_l_print_x, p1_get_sy() - 6, col)
            end
        end
    end
end