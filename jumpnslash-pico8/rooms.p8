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

    --[[

    layout:

    +----+----+----+----+----+----+
    |  1 =  2 =  3 =  4 =  5 =  6 |
    +-||-+-||-+----+----+----+-||-+
    |    8    =    |         |  7 |
    +---------+  9 |         +----+
    |         =    |
    |    10   +----+
    |         |
    +---------+

    --]]
    
    -- room 1
    add_room(0, 0, 16, 16, 2, 14)

    -- room 2
    add_room(16, 0, 16, 16, nil, nil)

    -- room 3
    add_room(32, 0, 16, 16, nil, nil)

    -- room 4
    add_room(48, 0, 16, 16, nil, nil)

    -- room 5
    add_room(64, 0, 16, 16, nil, nil)

    -- room 6
    add_room(80, 0, 16, 16, nil, nil)

    -- room 7
    add_room(80, 16, 16, 16, nil, nil)

    -- room 8
    add_room(0, 16, 32, 16, nil, nil)

    -- room 9
    add_room(32, 16, 16, 32, nil, nil)

    -- room 10
    add_room(0, 32, 32, 32, nil, nil)

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

    -- make sure _start_x and _start_y are matching
    -- they must either be (both a number) or (both nil)!!
    assert((_start_x != nil and _start_y != nil) or (_start_x == nil and _start_y == nil))

    -- make sure the spawn point for this room is actually inside the room
    if _start_x != nil then
        assert(_map_x < _start_x)
        assert(_start_x < _map_x + _tile_width - 1)
        assert(_map_y < _start_y)
        assert(_start_y < _map_y + _tile_height - 1)
    end

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
    }

    add(rooms, room)
    printh("room "..#rooms)
    printh("\tscroll_v_min_mpy: "..room.scroll_v_min_mpy)
    printh("\tscroll_v_max_mpy: "..room.scroll_v_max_mpy)
end

function validate_room_num(_room_num)
    local msg = "_room_num=".._room_num
    assert(_room_num > 0, msg)
    assert(_room_num <= #rooms, msg)
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
    return get_current_room().scroll_v_min_mpy
end

function get_scroll_bottom_bounds()
    return get_current_room().scroll_v_max_mpy
end

function get_current_map_x()
    return get_current_room().mx
end

function get_current_map_y()
    return get_current_room().my
end

function check_for_flag_at(_map_pix_x, _map_pix_y, _flag)
    return fget(mget(_map_pix_x / 8, _map_pix_y / 8), _flag)
end

-- currently does nothing
function update_room()

    if get_scrollability_horizontal() then -- horizontal scrolling

        if p1_get_mpx() < get_scroll_left_bounds() then -- if left of scroll zone
            scroll_x_offset = 0
            
        elseif get_scroll_left_bounds() <= p1_get_mpx() and p1_get_mpx() < get_scroll_right_bounds() then -- if inside scroll zone
            scroll_x_offset = -(p1_get_mpx() - get_scroll_left_bounds())
            
        elseif get_scroll_right_bounds() <= p1_get_mpx() then
            scroll_x_offset = -(get_scroll_right_bounds() - get_scroll_left_bounds()) -- if right of scroll zone
            
        end

    end
        
    if get_scrollability_vertical() then -- vertical scrolling
        
        if p1_get_mpy() < get_scroll_top_bounds() then -- if above scroll zone
            scroll_y_offset = 0

        elseif get_scroll_top_bounds() <= p1_get_mpy() and p1_get_mpy() < get_scroll_bottom_bounds() then -- if inside scroll zone
            scroll_y_offset = -flr(p1_get_mpy() - get_scroll_top_bounds())

        elseif get_scroll_bottom_bounds() <= p1_get_mpy() then -- if below scroll zone
            scroll_y_offset = -(get_scroll_bottom_bounds() - get_scroll_top_bounds())

        end
    end

end

function change_rooms()
    local room_i = get_room_from_tile(p1_get_mpx(), p1_get_mpy())
    assert(room_i != nil)
    printh("changing to room "..room_i)
    set_current_room(room_i)
end

function get_room_from_tile(_tile_x, _tile_y)
    -- algo to determine which room a given tile is in. returns nil if given tile is not in a room

    local i = 0
    local rm = nil
    repeat
        i += 1
        rm = rooms[i]
    until (i > #rooms) or (rm.mpx_min <= _tile_x and _tile_x < rm.mpx_max and rm.mpy_min <= _tile_y and _tile_y < rm.mpy_max)

    if i <= #rooms then
        return i
    else
        return nil
    end
end

function draw_room(_debug)
	
	--draw the map
    local rm = get_current_room()
	map(rm.mx, rm.my,
	    scroll_x_offset, scroll_y_offset, -- x,y position to draw on screen
	    rm.mw, rm.mh) -- w,h in tiles

    if _debug then
        
        if debug_room_number then
            print("room num: "..curr_room, 0, 12, 6)
        end

        if debug_scroll_bounds then
            if get_scrollability_horizontal() then
                local col = 9 -- orange

                local left_bound_draw_x = get_scroll_left_bounds() + scroll_x_offset - (get_current_room().mx * 8)
                local right_bound_draw_x = get_scroll_right_bounds() + scroll_x_offset - (get_current_room().mx * 8)

                -- draw left line if it's on the screen
                line(left_bound_draw_x, 0, left_bound_draw_x, 127, col)
                print("l: "..get_scroll_left_bounds(), left_bound_draw_x + 2, 66)
                
                -- draw right line of it's on the scren
                line(right_bound_draw_x, 0, right_bound_draw_x, 127, col)
                print("r: "..get_scroll_right_bounds(), right_bound_draw_x + 2, 66)

                col = 6 -- gray

                -- draw the scroll x offset
                line(left_bound_draw_x, 64, left_bound_draw_x - scroll_x_offset, 64, col)
                print("xoff: "..scroll_x_offset, max(left_bound_draw_x + 2, 1), 64 - 6, col)
            end

            if get_scrollability_vertical() then
                local col = 10

                local top_bound_draw_y = get_scroll_top_bounds() + scroll_y_offset - (get_current_room().my * 8)
                local bottom_bound_draw_y = get_scroll_bottom_bounds() + scroll_y_offset - (get_current_room().my * 8)

                -- draw top line if it's on screen
                line(0, top_bound_draw_y, 127, top_bound_draw_y, col)
                print("t: "..get_scroll_top_bounds(), 64 + 2, top_bound_draw_y + 2)

                -- draw bottom line if it's on screen
                line(0, bottom_bound_draw_y, 127, bottom_bound_draw_y, col)
                print("b: "..get_scroll_bottom_bounds(), 64 + 2, bottom_bound_draw_y + 2)

                col = 7 -- white

                -- draw the scroll y offset
                line(64, top_bound_draw_y, 64, top_bound_draw_y - scroll_y_offset, col)
                print("yoff: "..scroll_y_offset, 64 + 2, max(top_bound_draw_y + 8, 12), col)
            end
        end
    end
end