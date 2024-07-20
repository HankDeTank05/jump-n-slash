pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

function collision_check_with_enemies_in_room(_obj_mx, _obj_my, _obj_w, _obj_h, _enemy_callback, _obj_callback)
    -- _obj_mx: the x-coordinate of the top-left of the object to check collision for (map pixels)
    -- _obj_mx: the y-coordinate of the top-left of the object to check collision for (map pixels)
    -- _obj_w: the width of the object in pixels
    -- _obj_h: the height of the object in pixels
    -- _enemy_callback: the function to call to notify enemies of collision
    --            - must be a "set_enemy_collision_with_xxx" function!!
    --            - must take exactly two arguments: a room number, and an enemy index!!
    -- _obj_callback: the function to call to notify the object of collision
    --                - can be nil if no callback is needed
    --                - must take exactly zero arguments!!

    local rn = get_current_room_num()
    local enemy_list = get_enemies_in_room(rn)
    
    if #enemy_list > 0 then
        for enemy_i = 1, #enemy_list do
            -- TODO: enemy arguments should accessed with a get function!!
            local enemy = enemy_list[enemy_i]
            local collision = rectangle_overlap(_obj_mx, _obj_my, _obj_w, _obj_h, enemy.x, enemy.y, enemy.w, enemy.h)
            if collision == true then
                if debug_generic_collision then printh("object collision with enemy") end
                _enemy_callback(rn, enemy_i)
                if _obj_callback != nil then
                    _obj_callback()
                end
            end
        end
    end
end