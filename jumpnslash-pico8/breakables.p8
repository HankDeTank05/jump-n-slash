pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

function init_breakables()

    ----------------------
    -- pre-setup checks --
    ----------------------

    assert(get_current_room_num() != nil) -- make sure rooms have been set up first

    -- assertions for designer controls

    -- breakable_durability must always be a positive integer
    assert(breakable_durability > 0) -- make sure it's positive
    assert(breakable_durability % 1 == 0) -- make sure it's an integer

    -----------------
    -- begin setup --
    -----------------

    breakables = {}

    -- establish subarrays for room-based grouping
    for rn = 1, #rooms do
        add(breakables, {})
    end

    -- populate subarrays
    breakable_spr = 11

    for ty = 0, map_max_tile_y do
        for tx = 0, map_max_tile_x do
            local tile_spr = mget(tx, ty)

            if tile_spr == breakable_spr then
                local rn = get_room_from_tile(tx, ty)
                if debug_breakable_creation then printh("creating a breakable block at "..tx..", "..ty.." in room "..rn) end
                create_breakable(tx, ty, rn)
            end
        end
    end
end

function create_breakable(_tile_x, _tile_y, _room_num)
    assert(#breakables == #rooms)
    validate_room_num(_room_num)
    local breakable = {
        tx = _tile_x,
        ty = _tile_y,
        x = _tile_x * 8,
        y = _tile_y * 8,
        w = 8,
        h = 8,
        hp = breakable_durability, -- defined in designer_controls.p8
        prev_frame_sword_collision = false,
        this_frame_sword_collision = false,
        flagged_for_destruction = false,
    }
    add(breakables[_room_num], breakable)
end

function update_breakables()
    local rn = get_current_room_num()

    -- update breakable blocks
    for breakable_i = 1, #breakables[rn] do
        breakable_receive_collision(rn, breakable_i)
    end

    -- remove any blocks flagged for destruction
    local i = 1
    while i <= #breakables[rn] do
        if breakables[rn][i].flagged_for_destruction == true then
            breakable_destroy(rn, i)
        else
            i += 1
        end
    end
end

-- currently does nothing
function breakable_receive_collision(_room_num, _breakable_i)
    local breakable = breakables[_room_num][_breakable_i]
    
    -- do things on first frame of collision
    if breakable.prev_frame_sword_collision == false and breakable.this_frame_sword_collision == true then
        breakable_collision_with_sword_enter(_room_num, _breakable_i)

    -- do things on middle frames of collision
    elseif breakable.prev_frame_sword_collision == true and breakable.this_frame_sword_collision == true then
        breakable_collision_with_sword_during(_room_num, _breakable_i)

    -- do things after the last frame of collision
    elseif breakable.prev_frame_sword_collision == true and breakable.this_frame_sword_collision == false then
        breakable_collision_with_sword_exit(_room_num, _breakable_i)
    end

    -- prep for next frame
    breakable.prev_frame_sword_collision = breakable.this_frame_sword_collision
    breakable.this_frame_sword_collision = false -- reset in case of no collision next frame

    breakables[_room_num][_breakable_i] = breakable
end

function set_breakable_collision_with_sword(_room_num, _breakable_i)
    local breakable = breakables[_room_num][_breakable_i]

    breakable.this_frame_sword_collision = true

    breakables[_room_num][_breakable_i] = breakable
end

function breakable_collision_with_sword_enter(_room_num, _breakable_i)
    local breakable = breakables[_room_num][_breakable_i]

    if debug_breakable_collision then printh("breakable collision with sword (enter)") end
    
    breakable.hp -= 1
    if breakable.hp <= 0 then
        breakable_flag_for_destruction(_room_num, _breakable_i)
    end

    breakables[_room_num][_breakable_i] = breakable
end

-- currently does nothing
function breakable_collision_with_sword_during(_room_num, _breakable_i)
    local breakable = breakables[_room_num][_breakable_i]

    if debug_breakable_collision then printh("breakable collision with sword (during)") end

    breakables[_room_num][_breakable_i] = breakable
end

-- currently does nothing
function breakable_collision_with_sword_exit(_room_num, _breakable_i)
    local breakable = breakables[_room_num][_breakable_i]

    if debug_breakable_collision then printh("breakable collision with sword (exit)") end

    breakables[_room_num][_breakable_i] = breakable
end

function get_breakables_in_room(_room_num)
    validate_room_num(_room_num)
    return breakables[_room_num]
end

function breakable_flag_for_destruction(_room_num, _breakable_i)
    local breakable = breakables[_room_num][_breakable_i]
    
    if debug_breakable_destruction then printh("breakable ".._breakable_i.." has been flagged for destruction") end

    breakable.flagged_for_destruction = true

    breakables[_room_num][_breakable_i] = breakable
end

function breakable_destroy(_room_num, _breakable_i)
    local breakable = breakables[_room_num][_breakable_i]
    
    if debug_breakable_destruction then printh("breakable ".._breakable_i.." has been destroyed") end

    mset(breakable.tx, breakable.ty, 0)
    deli(breakables[_room_num], _breakable_i)
end

function draw_breakables()
end