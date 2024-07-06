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

    for ty = 1, map_max_tile_y do
        for tx = 1, map_max_tile_x do
            local tile_spr = mget(tx, ty)
            
            if tile_spr == enemy_spawn_left or tile_spr == enemy_spawn_right then
                spawn_enemy(tx, ty, get_room_from_tile(tx, ty))
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

        x = _tile_x * 8,
        y = _tile_y * 8,
    }
    add(enemies[_room_num], enemy)
end

function enemies_update()
    -- only update enemies in the current room
    local rn = get_current_room_num()
    for enemy_i = 1, #enemies[rn] do
        -- update ai
        enemy_update_ai(rn, enemy_i)
        -- check for collision
        enemy_check_collision(rn, enemy_i)
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

    -- code goes here

    enemies[_room_num][_enemy_i] = enemy
end

-- currently does nothing
function enemy_check_collision(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    -- code goes here

    enemies[_room_num][_enemy_i] = enemy
end

-- currently does nothing
function enemy_move(_room_num, _enemy_i)
    local enemy = enemies[_room_num][_enemy_i]

    -- code goes here

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
    -- code goes here
end

function enemies_draw()
    pal(1, 9)
    pal(12, 10)
    for enemy in all(enemies[get_current_room_num()]) do
        spr(enemy.spr_state[enemy.spr_n], enemy.x, enemy.y)
    end
    pal()
end