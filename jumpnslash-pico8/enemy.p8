pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

function init_enemies()
    assert(get_current_room_num() != nil) -- make sure rooms have been set up first
    enemies = {}

    assert(p1_sprs != nil)
    enemy_sprs = p1_sprs
    enemy_anim_spd = 10

    -- establish empty subarrays for room-based grouping
    for rn = 1, #rooms do
        add(enemies, {}) -- group enemies by the room they're in, indices match between "rooms" and "enemies"
    end

    -- populate enemy subarrays
    enemy_spawn_left = 6 -- sprite number for a spawn point for an enemy starting facing left
    enemy_spawn_right = 7-- sprite number for a spawn point for an enemy starting facing right

    for ty = 1, map_max_tile_y do
        for tx = 1, map_max_tile_x do
            local tile_spr = mget(tx, ty)
            
            if tile_spr == enemy_spawn_left then
                -- spawn enemy facing left
            elseif tile_spr == enemy_spawn_right then
                -- spawn enemy facing right
            end

        end
    end
end

function spawn_enemy(_tile_x, _tile_y, _room_num)
    assert(#enemies == #rooms)
    validate_room_num(_room_num)
    local enemy = {
        spr_state = enemy_sprs.neutral,
        spr_n = 1,
        anim_fcount = 0,
    }
    add(enemies[_room_num], enemy)
end

function enemies_update()
    -- only update enemies in the current room
    for enemy in all(enemies[get_current_room_num()]) do
        -- update ai
        -- check for collision
        -- move
        -- animate
        -- update landmarks
    end
end

function enemy_update_ai(_room_num, _enemy_i)
    -- code goes here
end

function enemy_check_collision(_room_num, _enemy_i)
    -- code goes here
end

function enemy_move(_room_num, _enemy_i)
    -- code goes here
end

function enemy_animate(_room_num, _enemy_i)
    -- code goes here
end

function enemy_update_landmarks(_room_num, _enemy_i)
    -- code goes here
end

function enemies_draw()
    -- code goes here
end