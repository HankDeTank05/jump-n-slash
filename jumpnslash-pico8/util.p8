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