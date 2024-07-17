pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

-- put stuff here to dodge the character or token limit
-- this file is not included in the project so it will not affect the character or token count

-- player.p8

-- currently unused
function cast_ray(_start_x, _start_y, _x_dir, _y_dir, _flag_num)
    -- cast a ray from a starting position, in a given direction, until it hits a map tile with the given flag
    -- note: raycast can only be in one of the four cardinal directions
    -- return the screen x,y position where the raycast ended

    -- _start_x: the x-pos to start from on the screen
    -- _start_y: the y-pos to start from on the screen
    -- _x_dir: the direction to move along the x-axis
    -- _y_dir: the direction to move along the y-axis
    -- _flag_num: stop casting the ray when you reach a map tile with this flag number

    assert(_x_dir == 0 or _y_dir == 0) -- make sure we're not casting diagonally
    assert(_x_dir != _y_dir) -- but also make sure the raycast will go in *some* direction

    -- make sure we will be moving one pixel at a time
    if _x_dir != 0 then
        assert(_x_dir == 1 or _x_dir == -1)
    elseif _y_dir != 0 then
        assert(_y_dir == 1 or _y_dir == -1)
    end

    local x, y = _start_x, _start_y

    -- while loop goes here
end