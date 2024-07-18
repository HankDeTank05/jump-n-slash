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
    map_max_pix_x = ((map_max_tile_x + 1) * 8) - 1
    map_max_pix_y = ((map_max_tile_y + 1) * 8) - 1

    -- automagically detect rooms
    local corner_txs = {}
    local corner_tys = {}

    local starting_tx = nil
    local starting_ty = nil
    
    for tx = 0, map_max_tile_x do
        for ty = 0, map_max_tile_y do
            if check_for_flag_at_tile(tx, ty, 6) then
                starting_tx = tx
                starting_ty = ty
            end
            if check_for_flag_at_tile(tx, ty, 1) then
                add(corner_txs, tx)
                add(corner_tys, ty)
            end
        end
    end

    assert(starting_tx != nil) -- if either of these are triggered it means
    assert(starting_ty != nil) -- you never defined the starting room!!

    assert(#corner_txs == #corner_tys)
    if debug_room_creation then printh(#corner_txs) end

    local loop_max = #corner_txs -- do this because we'll be modifying the list during the loop
    local starting_i = nil
    for i = 1, loop_max do
        local origin_tx = corner_txs[i]
        local origin_ty = corner_tys[i]

        -- set the index of the starting room
        if origin_tx == starting_tx and origin_ty == starting_ty then
            starting_i = i
        end

        -- iterate right to find h bounds
        local right_bounds_tx = origin_tx
        while check_for_flag_at_tile(right_bounds_tx, origin_ty, 2) == false do
            right_bounds_tx += 1
            --if debug_room_creation then printh("searching width at x = "..right_bounds_tx) end
            assert(right_bounds_tx <= map_max_tile_x) -- if this gets triggered then you misplaced or forgot your room width tile!
            assert(check_for_flag_at_tile(right_bounds_tx, origin_ty, 1) == false) -- if this gets triggered, you put a corner tile before your right-edge tile!
        end

        -- add the corner coords to be replaced later
        add(corner_txs, right_bounds_tx)
        add(corner_tys, origin_ty)
        if debug_room_creation then printh("right: "..right_bounds_tx..", "..origin_ty) end

        -- iterate down to find v bounds
        local bottom_bounds_ty = origin_ty
        while check_for_flag_at_tile(origin_tx, bottom_bounds_ty, 2) == false do
            bottom_bounds_ty += 1
            --if debug_room_creation then printh("searching height at y = "..bottom_bounds_ty) end
            assert(bottom_bounds_ty <= map_max_tile_y) -- if this gets triggered then you misplaced or forgot your room height tile!
            assert(check_for_flag_at_tile(origin_tx, bottom_bounds_ty, 1) == false) -- if this gets triggered, you put a corner tile before your bottom-edge tile!
        end

        -- add the corner coords to be replaced later
        add(corner_txs, origin_tx)
        add(corner_tys, bottom_bounds_ty)
        if debug_room_creation then printh("bottom: "..origin_tx..", "..bottom_bounds_ty) end

        -- determine room dimensions and add it to the list
        add_room(origin_tx, origin_ty, (right_bounds_tx - origin_tx) + 1, (bottom_bounds_ty - origin_ty) + 1)
    end
    assert(starting_i != nil)

    assert(#corner_txs == #corner_tys)
    for i = 1, #corner_txs do
        mset(corner_txs[i], corner_tys[i], 8) -- set the corner sprites to the default block sprite, player shouldn't see these
    end

    set_current_room(starting_i)
end

function add_room(_map_x, _map_y, _tile_width, _tile_height)

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
        start_mx = nil,
        start_my = nil,
        start_facing = nil,

        scroll_h = _tile_width > 16, -- does this room scroll horizontally?
        scroll_v = _tile_height > 16, -- does this room scroll vertically?

        -- pixel boundaries for screen scrolling: when player crosses these boundaries, start/end screen scrolling
        scroll_h_min_mpx = (_map_x + 8) * 8,
        scroll_h_max_mpx = (_map_x + _tile_width - 8) * 8,
        scroll_v_min_mpy = (_map_y + 8) * 8,
        scroll_v_max_mpy = (_map_y + _tile_height - 8) * 8,
    }

    -- search for any player spawn markers in the defined room
    local player_spawn_left = 22
    local player_spawn_right = 23

    for my = room.my, room.my + room.mh - 1 do
        for mx = room.mx, room.mx + room.mw - 1 do
            local tile_spr_num = mget(mx, my)
            -- TODO: fix this so player spawns in proper facing direction
            if tile_spr_num == player_spawn_left or tile_spr_num == player_spawn_right then
                room.start_mx = mx
                room.start_my = my
                
                if tile_spr_num == player_spawn_left then
                    room.start_facing = -1
                elseif tile_spr_num == player_spawn_right then
                    room.start_facing = 1
                end

                -- replace the spawn point tile with a blank tile, cuz the player shouldn't see this
                mset(mx, my, 0)
            end
        end
    end

    add(rooms, room)
    if debug_room_creation then printh("room "..#rooms) end
    if debug_scroll_bounds then printh("\tscroll_v_min_mpy: "..room.scroll_v_min_mpy) end
    if debug_scroll_bounds then printh("\tscroll_v_max_mpy: "..room.scroll_v_max_mpy) end
end

function validate_room_num(_room_num)
    assert(_room_num != nil)
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

function check_for_flag_at_pix(_map_pix_x, _map_pix_y, _flag)
    return fget(mget(flr(_map_pix_x / 8), flr(_map_pix_y / 8)), _flag)
end

function check_for_flag_at_tile(_tile_x, _tile_y, _flag)
    return fget(mget(_tile_x, _tile_y), _flag)
end

function update_room()

    if get_scrollability_horizontal() then -- horizontal scrolling

        if p1_get_x() < get_scroll_left_bounds() then -- if left of scroll zone
            scroll_x_offset = 0
            
        elseif get_scroll_left_bounds() <= p1_get_x() and p1_get_x() < get_scroll_right_bounds() then -- if inside scroll zone
            scroll_x_offset = -(p1_get_x() - get_scroll_left_bounds())
            
        elseif get_scroll_right_bounds() <= p1_get_x() then
            scroll_x_offset = -(get_scroll_right_bounds() - get_scroll_left_bounds()) -- if right of scroll zone
            
        end

    end
        
    if get_scrollability_vertical() then -- vertical scrolling
        
        if p1_get_y() < get_scroll_top_bounds() then -- if above scroll zone
            scroll_y_offset = 0

        elseif get_scroll_top_bounds() <= p1_get_y() and p1_get_y() < get_scroll_bottom_bounds() then -- if inside scroll zone
            scroll_y_offset = -flr(p1_get_y() - get_scroll_top_bounds())

        elseif get_scroll_bottom_bounds() <= p1_get_y() then -- if below scroll zone
            scroll_y_offset = -(get_scroll_bottom_bounds() - get_scroll_top_bounds())

        end
    end

end

function change_rooms()
    local room_i = get_room_from_pix(p1_get_x(), p1_get_y())
    assert(room_i != nil)
    if debug_room_switching then printh("changing to room "..room_i) end
    set_current_room(room_i)
end

-- algo to determine which room a given pixel is in. returns nil if given tile is not in any room
function get_room_from_pix(_pixel_x, _pixel_y)

    local i = 0
    local rm = nil
    repeat
        i += 1
        rm = rooms[i]
    until (i > #rooms) or (rm.mpx_min <= _pixel_x and _pixel_x < rm.mpx_max and rm.mpy_min <= _pixel_y and _pixel_y < rm.mpy_max)

    assert(i <= #rooms) -- the room was not found

    if i <= #rooms then
        return i
    else
        return nil
    end
end

-- algo to determine which room a given tile is in. returns nil if given tile is not in any room
function get_room_from_tile(_tile_x, _tile_y)

    local i = 0
    local rm = nil
    repeat
        i += 1
        rm = rooms[i]
    until (i > #rooms) or (rm.mx <= _tile_x and _tile_x < rm.mx + rm.mw and rm.my <= _tile_y and _tile_y < rm.my + rm.mh)

    assert(i <= #rooms) -- the room was not found

    if i <= #rooms then
        return i
    else
        return nil
    end
end

function draw_room()
	
	--draw the map
    local rm = get_current_room()
	map(rm.mx, rm.my,
	    scroll_x_offset, scroll_y_offset, -- x,y position to draw on screen
	    rm.mw, rm.mh) -- w,h in tiles

    if debug_room_draw then
        
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