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
end

function sword_update()
    sword_collision()

    sword_animate()
end

function sword_collision()
end

function sword_activate()
    sword_reset_animation()
    sword_set_animation(sword_sprs.swing)
end

function sword_animate()
    -- set animation state
    if sword_spr_n - 1 > #sword_sprs.swing then
        sword_set_animation(sword_sprs.neutral)
    end

    sword_spr_n = flr(sword_anim_fcount / sword_anim_spd) + 1

    sword_anim_fcount += 1
end

function sword_set_animation(_anim)
    assert(#_anim > 0)
    if sword_spr_state != _anim then
        sword_reset_animation()
    end
    sword_spr_state = _anim
end

function sword_reset_animation()
    sword_spr_n = 1
    sword_anim_fcount = 0
end

function sword_draw()
    if #sword_spr_state > 0 then
        spr(sword_spr_state[sword_spr_n], -- sprite number to draw
            p1_get_sx() + 8, p1_get_sy(), -- position to draw at
            1, 1, -- number of tiles wide/tall
            false, false) -- whether or not to flip on x,y axis
    end
end