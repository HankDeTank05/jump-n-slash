pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

function init_enemies()
    assert(get_current_room_num() != nil) -- make sure rooms have been set up first
    enemies = {}

    assert(p1_sprs != nil)
    enemy_sprs = { -- lists of sprites for animation
		neutral = {16, 32,},
		walk = {17, 18, 19, 20,},
		jump = {1, 2, 3, 4,},
		fall = {33, 34, 35, 36,},
		attack = {49, 50, 51, 52,}
	}
    enemy_anim_spd = 10

    -- establish empty subarrays for room-based grouping
    for rn = 1, #rooms do
        add(enemies, {}) -- group enemies by the room they're in, indices match between "rooms" and "enemies"
    end

    -- populate enemy subarrays
    enemy_spawn_left = 6 -- sprite number for a spawn point for an enemy starting facing left
    enemy_spawn_right = 7-- sprite number for a spawn point for an enemy starting facing right

    for ty = 0, map_max_tile_y do
        for tx = 0, map_max_tile_x do
            local tile_spr = mget(tx, ty)
            
            -- TODO: fix this so enemy spawns in proper facing direction
            if tile_spr == enemy_spawn_left  then
                spawn_enemy(tx, ty, get_room_from_tile(tx, ty), -1)
                -- replace enemy spawn point tile with blank tile, cuz the player shouldn't see this
                mset(tx, ty, 0)
            elseif tile_spr == enemy_spawn_right then
                spawn_enemy(tx, ty, get_room_from_tile(tx, ty), 1)
                -- replace enemy spawn point tile with blank tile, cuz the player shouldn't see this
                mset(tx, ty, 0)
            end

        end
    end
end

function spawn_enemy(_tile_x, _tile_y, _room_num, _facing_dir)
    assert(#enemies == #rooms)
    validate_room_num(_room_num)
    local enemy = {
        spr_state = enemy_sprs.neutral,
        spr_n = 1,
        anim_fcount = 0,

        x = _tile_x * 8,
        y = _tile_y * 8,
        sx = nil,
        sy = nil,
        w = 8,
        h = 8,

        dx = 0,

        facing = _facing_dir, -- 1 = right, -1 = left

        -- sprite landmarks (in map pixels)
        lft = nil, -- left x
        rgt = nil, -- right x
        top = nil, -- top y
        btm = nil, -- bottom y
        ctr = nil, -- center x
        mdl = nil, -- middle y

        -- sprite landmarks (in screen pixels)
        s_lft = nil,
        s_rgt = nil,
        s_top = nil,
        s_btm = nil,
        s_ctr = nil,
        s_mdl = nil,

        prev_frame_sword_collision = false,
        this_frame_sword_collision = false,
    }
    add(enemies[_room_num], enemy)
    enemy_update_screen_pos(_room_num, #enemies[_room_num])
    enemy_update_landmarks(_room_num, #enemies[_room_num])
end

function enemy_update_screen_pos(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    enemy.sx = enemy.x % 128
    enemy.sy = enemy.y % 128

    enemies[_room_num][_enemy_i] = enemy
end

function enemies_update()
    -- only update enemies in the current room
    local rn = get_current_room_num()
    for enemy_i = 1, #enemies[rn] do
        -- update ai
        enemy_update_ai(rn, enemy_i)
        -- check for collision with other objects
        enemy_check_collision(rn, enemy_i)
        -- react to other objects colliding with it
        enemy_receive_collision(rn, enemy_i)
        -- move
        enemy_move(rn, enemy_i)
        -- animate
        enemy_animate(rn, enemy_i)
        -- update landmarks
        enemy_update_landmarks(rn, enemy_i)
    end
end

-- currently does nothing
function enemy_update_ai(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    local ray_y = enemy.mdl
    -- cast a ray forward until it hits a wall or the edge of the map
    -- if that ray hits the player, stop casting and walk forward
    
    local ray_x = nil
    if enemy.facing == 1 then
        ray_x = enemy.x + enemy.h - 1
    else
        ray_x = enemy.x
    end
    assert(ray_x != nil)

    while check_for_flag_at(ray_x, ray_y, 4) == false and 0 <= ray_x and ray_x <= map_max_pix_x do

        if point_in_rectangle(ray_x, ray_y, p1_get_mpx(), p1_get_mpy(), p1_w, p1_h) then
            --         vvvvvvvvvvvvvvvv defined in designer_controls.p8
            enemy.dx = enemy_walk_speed * enemy.facing
            printh("enemy ".._enemy_i.." can see the player")
            break
        else
            enemy.dx = 0
        end

        ray_x += enemy.facing
    end

    enemy.ray_x = ray_x
    enemy.ray_y = ray_y

    enemies[_room_num][_enemy_i] = enemy
end

-- currently does nothing
function enemy_check_collision(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]
    
    -- code goes here

    enemies[_room_num][_enemy_i] = enemy
end

function enemy_receive_collision(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]
    
    -- do things on first frame of collision
    if enemy.prev_frame_sword_collision == false and enemy.this_frame_sword_collision == true then
        enemy_collision_with_sword_enter(_room_num, _enemy_i)

    -- do things on middle frames of collision
    elseif enemy.prev_frame_sword_collision == true and enemy.this_frame_sword_collision == true then
        enemy_collision_with_sword_during(_room_num, _enemy_i)

    -- do things after the last frame of collision
    elseif enemy.prev_frame_sword_collision == true and enemy.this_frame_sword_collision == false then
        enemy_collision_with_sword_exit(_room_num, _enemy_i)
    end
        
    -- prep for next frame
    enemy.prev_frame_sword_collision = enemy.this_frame_sword_collision
    enemy.this_frame_sword_collision = false -- reset in case of no collision on next frame

    enemies[_room_num][_enemy_i] = enemy
end

function set_enemy_collision_with_sword(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    enemy.this_frame_sword_collision = true

    enemies[_room_num][_enemy_i] = enemy
end

-- currently does nothing
function enemy_collision_with_sword_enter(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    printh("enemy collision with sword (enter)")

    enemies[_room_num][_enemy_i] = enemy
end

-- currently does nothing
function enemy_collision_with_sword_during(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    printh("enemy collision with sword (during)")

    enemies[_room_num][_enemy_i] = enemy
end

-- currently does nothing
function enemy_collision_with_sword_exit(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    printh("enemy collision with sword (exit)")

    enemies[_room_num][_enemy_i] = enemy
end

-- currently does nothing
function enemy_move(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    enemy.x += enemy.dx
    --printh("enemy ".._enemy_i.." dx = "..enemy.dx)

    enemies[_room_num][_enemy_i] = enemy
end

function enemy_animate(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    enemy.spr_n = (flr(enemy.anim_fcount / enemy_anim_spd) % #enemy.spr_state) + 1
    enemy.anim_fcount += 1

    enemies[_room_num][_enemy_i] = enemy
end

function enemy_set_animation(_room_num, _enemy_i, _anim)
    local enemy = enemies[_room_num][_enemy_i]

    assert(#_anim > 0)
    if enemy.spr_state != _anim then
        enemy_reset_animation(_room_num, _enemy_i)
    end
    enemy.spr_state = _anim

    enemies[_room_num][_enemy_i] = enemy
end

function enemy_reset_animation(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    enemy.spr_n = 1
    enemy.anim_fcount = 0

    enemies[_room_num][_enemy_i] = enemy
end

-- currently does nothing
function enemy_update_landmarks(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

	-- update map-pixel landmarks
	enemy.lft = enemy.x
	enemy.rgt = enemy.x + enemy.w - 1
	enemy.top = enemy.y
	enemy.btm = enemy.y + enemy.h - 1
	enemy.ctr = (enemy.lft + enemy.rgt) / 2
	enemy.mdl = (enemy.top + enemy.btm) / 2

	-- update screen-pixel landmarks
	enemy.s_lft = enemy.lft % 128
	enemy.s_rgt = enemy.rgt % 128
	enemy.s_top = enemy.top % 128
	enemy.s_btm = enemy.btm % 128
	enemy.s_ctr = enemy.ctr % 128
	enemy.s_mdl = enemy.mdl % 128

    enemies[_room_num][_enemy_i] = enemy
end

function get_enemies_in_room(_room_num)
    validate_room_num(_room_num)
    return enemies[_room_num]
end

function enemies_draw(_debug)

    pal(1, 9)
    pal(12, 10)
    local rn = get_current_room_num()
    for enemy_i = 1, #enemies[rn] do
        enemy_update_landmarks(rn, enemy_i)
        enemy_update_screen_pos(rn, enemy_i)

        local enemy = enemies[rn][enemy_i]

        spr(enemy.spr_state[enemy.spr_n], enemy.sx, enemy.sy)
        if _debug then
            if debug_ai then
                line(enemy.s_ctr, enemy.s_mdl, enemy.ray_x, enemy.ray_y, 11)
            end
        end
    end
    pal()
end