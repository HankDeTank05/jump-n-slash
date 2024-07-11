pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

function init_sword()
    sword_sprs = { -- lists of sprites for animation
        neutral = {},
        swing = {5, 21, 37, 53,},
    }
    sword_spr_state = sword_sprs.neutral -- assigned sword_sprs.<sublist>
    sword_spr_n = 1 -- the index of the sprite to draw
    sword_anim_spd = 10 -- speed control for animations, higher number = slower
    sword_anim_fcount = 0 -- frame counter for animation
    sword_active = false
    sword_draw_spr = nil

    -- state functions
    sword_animate = sword_animate_neutral
end

function sword_update()
    sword_collision()

    sword_update_animation()
end

function sword_collision()
end

function sword_activate()
    sword_set_animation(sword_animate_swing)
end

function sword_update_animation()
    --[[
    -- set animation state
    if sword_spr_n - 1 > #sword_sprs.swing then
        sword_set_animation(sword_sprs.neutral)
    end
    --]]

    sword_spr_n = flr(sword_anim_fcount / sword_anim_spd)

    sword_anim_fcount += 1

    sword_animate()
end

function sword_animate_neutral()
    sword_draw_spr = 0
end

function sword_animate_swing()
    sword_spr_n += 1

    -- determine next state
    if sword_spr_n > #sword_sprs.swing then
        sword_set_animation(sword_animate_neutral)
        sword_active = false
    else
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
    spr(sword_draw_spr, -- sprite number to draw
        p1_get_sx() + 8, p1_get_sy(), -- position to draw at
        1, 1, -- number of tiles wide/tall
        false, false) -- whether or not to flip on x,y axis
end