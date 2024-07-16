pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

function init_sword()
    sword_sprs = { -- lists of sprites for animation
        neutral = {52,},
        swing = {5, 21, 37, 53,},
    }
    sword_spr_state = sword_sprs.neutral -- assigned sword_sprs.<sublist>
    sword_spr_n = 1 -- the index of the sprite to draw
    sword_anim_spd = 10 -- speed control for animations, higher number = slower
    sword_anim_fcount = 0 -- frame counter for animation
    sword_active = false
    sword_draw_spr = nil

    sword_x = nil
    sword_y = nil

    sword_sx = nil
    sword_sy = nil

    sword_w = 8
    sword_h = 8

    -- state functions
    sword_animate = sword_animate_neutral
end

function sword_update()
    sword_move()

    if sword_active == true then
        sword_collision()
    end

    sword_update_animation()
end

function sword_move()
    sword_x = p1_get_mpx() + 8 * p1_get_facing()
    sword_y = p1_get_mpy()
end

function sword_update_screen_pos()
    sword_sx = sword_x % 128
    sword_sy = sword_y % 128
end

function sword_collision()
    -- check for collision with enemies
    local rn = get_current_room_num()
    local enemy_list = get_enemies_in_room(rn)
    if #enemy_list > 0 then
        for enemy_i = 1, #enemy_list do
            -- TODO: sword arguments should accessed with a get function!!
            local enemy = enemy_list[enemy_i]
            local collision = rectangle_overlap(sword_x, sword_y, sword_w, sword_h, enemy.x, enemy.y, enemy.w, enemy.h)
            if collision == true then
                --printh("sword collision with enemy")
                set_enemy_collision_with_sword(rn, enemy_i)
            end
        end
    end

    -- check for collision with breakable blocks
    local breakable_list = get_breakables_in_room(rn)
    if #breakable_list > 0 then
        for breakable_i = 1, #breakable_list do
            -- TODO: breakable arguments should be accessed with a get function!!
            local breakable = breakable_list[breakable_i]
            local collision = rectangle_overlap(sword_x, sword_y, sword_w, sword_h, breakable.x, breakable.y, breakable.w, breakable.h)
            if collision == true then
                --printh("sword collision with breakable")
                set_breakable_collision_with_sword(rn, breakable_i)
            end
        end
    end
end

function sword_activate()
    sword_set_animation(sword_animate_swing)
    sword_active = true
end

function sword_update_animation()
    --[[
    -- set animation state
    if sword_spr_n - 1 > #sword_sprs.swing then
        sword_set_animation(sword_sprs.neutral)
    end
    --]]

    sword_spr_n = flr(sword_anim_fcount / sword_anim_spd)
    
    sword_animate()

    sword_anim_fcount += 1
end

function sword_animate_neutral()
    sword_spr_n = index_loop_animation(sword_anim_fcount, sword_anim_spd, #sword_sprs.neutral)

    sword_draw_spr = sword_sprs.neutral[sword_spr_n]
end

function sword_animate_swing()
    
    -- determine next state
    if sword_anim_fcount >= p1_attack_frames then
        sword_set_animation(sword_animate_neutral)
        sword_active = false
    else
        sword_spr_n = index_animation_noloop(sword_anim_fcount, p1_attack_frames, #sword_sprs.swing)
        sword_draw_spr = sword_sprs.swing[sword_spr_n]
    end
end

function sword_set_animation(_anim)
    sword_animate = _anim
    sword_reset_animation()
end

function sword_reset_animation()
    sword_spr_n = 1
    sword_anim_fcount = 0
end

function sword_draw()

    sword_update_screen_pos()

    spr(sword_draw_spr, -- sprite number to draw
        sword_sx, sword_sy, -- position to draw at
        1, 1, -- number of tiles wide/tall
        p1_get_facing() == -1, false) -- whether or not to flip on x,y axis
end