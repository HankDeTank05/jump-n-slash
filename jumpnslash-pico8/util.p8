pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

-- utility functions
function index_loop_animation(_anim_fcount, _anim_spd, _num_frames)
    -- _anim_fcount: the amount of time (in frames) spent in the current animation state
    -- _anim_spd: the speed control for the animation
    -- _num_frames: the number of frames in the current animation
    assert(_num_frames > 0)
    return (flr(_anim_fcount / _anim_spd) % _num_frames) + 1
end

function index_animation_noloop(_anim_fcount, _anim_max_frames, _num_frames)
    -- _anim_fcount: the amount of time (in frames) spent in the current animation state
    -- _anim_max_frames: the amount of time (in frames) the animation should last for
    -- _num_frames: the number of frames in the current animation
    assert(_anim_fcount < _anim_max_frames)
    assert(_anim_max_frames > 0)
    assert(_num_frames > 0)
    return flr((_anim_fcount / _anim_max_frames) * _num_frames) + 1
end

function rectangle_overlap(_r1x, _r1y, _r1w, _r1h, _r2x, _r2y, _r2w, _r2h)
    -- _r1x: the x-position of the top-left of the 1st rectangle (in map pixels)
    -- _r1y: the y-position of the top-left of the 1st rectangle (in map pixels)
    -- _r1w: the width of the 1st rectangle
    -- _r1h: the height of the 1st rectangle
    -- _r2x: the x-position of the top-left of the 2nd rectangle (in map pixels)
    -- _r2y: the y-position of the top-left of the 2nd rectangle (in map pixels)
    -- _r2w: the width of the 2nd rectangle
    -- _r2h: the height of the 2nd rectangle

    -- ensure valid dimensions for rectangle 1
    assert(_r1x >= 0)
    assert(_r1y >= 0)
    assert(_r1w > 0)
    assert(_r1h > 0)

    -- ensure valid dimensions for rectangle 2
    assert(_r2x >= 0)
    assert(_r2y >= 0)
    assert(_r2w > 0)
    assert(_r2h > 0)
    
    -- check for rectangle overlap

    -- case 1: the rectangles occupy the same position
    if _r1x == _r2x and _r1y == _r2y then
        return true
    else
        -- case 2: the rectangles overlap but are not at the same position
        local r1_lft_x = _r1x
        local r1_rgt_x = _r1x + _r1w - 1
        local r1_top_y = _r1y
        local r1_btm_y = _r1y + _r1h - 1

        local r2_lft_x = _r2x
        local r2_rgt_x = _r2x + _r2w - 1
        local r2_top_y = _r2y
        local r2_btm_y = _r2y + _r2h - 1

        -- check if the left edge of r2 overlaps r1 (on x-axis)
        local overlap_x_lft = r1_lft_x <= r2_lft_x and r2_lft_x <= r1_rgt_x
        -- check if the right edge of r2 overlaps r1 (on x-axis)
        local overlap_x_rgt = r1_lft_x <= r2_rgt_x and r2_rgt_x <= r1_rgt_x

        -- determine if there was any overlap on x-axis at all
        local overlap_on_x = overlap_x_lft or overlap_x_rgt

        -- check if the top edge of r2 overlaps r1 (on y-axis)
        local overlap_y_top = r1_top_y <= r2_top_y and r2_top_y <= r1_btm_y
        --check if the bottom edge of r2 overlaps r1 (on y-axis)
        local overlap_y_btm = r1_top_y <= r2_btm_y and r2_btm_y <= r1_btm_y

        -- determine if there was any overlap on y-axis at all
        local overlap_on_y = overlap_y_top or overlap_y_btm

        return overlap_on_x and overlap_on_y
    end
end