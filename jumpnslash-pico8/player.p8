pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

--[[
    this is the file for all code concerning the player character
]]

function init_player()

	----------------------
	-- pre-setup checks --
	----------------------

    -- assumes rooms have already been initialized and that the starting room has a spawn point defined
    assert(get_current_room().start_mx != nil)
    assert(get_current_room().start_my != nil)

	-- assertions for designer controls

	-- make sure the controls use a valid button code
	assert(0 <= controls.walk_left and controls.walk_left <= 5)
	assert(0 <= controls.walk_right and controls.walk_right <= 5)
	assert(0 <= controls.jump and controls.jump <= 5)
	assert(0 <= controls.attack and controls.attack <= 5)

	-- p1_jump_velocity must always be negative
	assert(p1_jump_velocity < 0) -- make sure it's negative

	-- p1_gravity must always be positive
	assert(p1_gravity > 0) -- make sure it's positive

	-- p1_max_jump_frames must always be a positive integer
	assert(p1_max_jump_frames > 0) -- make sure it's positive
	assert(p1_max_jump_frames % 1 == 0) -- make sure it's an integer

	-- p1_walk_speed must always be a positive integer
	assert(p1_walk_speed > 0) -- make sure it's positive
	assert(p1_walk_speed % 1 == 0) -- make sure it's an integer

	-- p1_attack_frames must always be a positive integer
	assert(p1_attack_frames > 0) -- make sure it's positive
	assert(p1_attack_frames % 1 == 0) -- make sure it's an integer

	-- p1_max_health must always be a positive integer
	assert(p1_max_health > 0) -- make sure it's positive
	assert(p1_max_health % 1 == 0) -- make sure it's an integer

	-----------------
	-- begin setup --
	-----------------

	p1_sprs = { -- lists of sprites for animation
		neutral = {16, 32,},
		walk = {17, 18, 19, 20,},
		jump = {1, 2, 3, 4,},
		fall = {33, 34, 35, 36,},
		attack = {48, 49, 50, 51,}
	}
	p1_spr_state = nil -- assigned p1_sprs.<sublist>
	p1_spr_n = 1 -- the index of the sprite to draw
	p1_anim_spd = 10 -- speed control for animations, higher number = slower
	p1_anim_fcount = 0 -- frame counter for animation
	p1_draw_spr = nil -- the sprite to draw in the current frame

	-- the following coordinates are in map pixels (*not* tiles)
	p1_x = get_current_room().start_mx * 8 -- get starting x position based on what the starting room defines it to be
	p1_y = get_current_room().start_my * 8 -- get starting y position based on what the starting room defines it to be
	p1_facing = get_current_room().start_facing -- 1 = right, -1 = left

	-- the following coordinates are in screen pixels
	p1_sx = nil
	p1_sy = nil
	p1_update_screen_pos()

	p1_dx = 0 -- delta x, since there's no horizontal acceleration
	p1_y_vel = 0 -- y-velocity, since there is vertical acceleration
	p1_w = 8 -- width of the sprite
	p1_h = 8 -- height of the sprite

	-- sprite landmarks (in map pixels)
	p1_lft = nil -- left x
	p1_rgt = nil -- right x
	p1_top = nil -- top y
	p1_btm = nil -- bottom y
	p1_ctr = nil -- center x
	p1_mdl = nil -- middle y

	-- sprite landmarks (in screen pixels)
	p1_s_lft = nil
	p1_s_rgt = nil
	p1_s_top = nil
	p1_s_btm = nil
	p1_s_ctr = nil
	p1_s_mdl = nil

	p1_landed = false -- did you land on the ground?
	p1_head_bonked = false -- did you bonk your head on a ceiling?
	p1_jump_btn_frames = 0 -- how many frames the jump button has been held for
	p1_jump_btn_released = true
	p1_weapon = "sword"
	p1_attacking = false

	p1_health = p1_max_health

	-- state functions
	p1_animate = p1_animate_neutral

	-- collision flags
	p1_prev_frame_collision_with_enemy = false
	p1_this_frame_collision_with_enemy = false
end

function p1_update_screen_pos()
	
	if get_scrollability_horizontal() and get_scroll_left_bounds() <= p1_x and p1_x < get_scroll_right_bounds() then
		p1_sx = get_scroll_left_bounds() - (get_current_map_x() * 8)
	else
		p1_sx = p1_x % 128
	end

	if get_scrollability_vertical() and get_scroll_top_bounds() <= p1_y and p1_y < get_scroll_bottom_bounds() then
		p1_sy = get_scroll_top_bounds() - (get_current_map_y() * 8)
	else
		p1_sy = p1_y % 128
	end

end

function p1_update()
	p1_read_inputs()
	
	p1_check_collision() -- check for collision with other objects

	p1_receive_collision() -- react to other objects colliding with it
	
	p1_move()

	p1_update_animation()
	
	p1_update_landmarks()
	
end

function p1_read_inputs()
	-- read for inputs

	if btnp(controls.attack) then
		p1_attack()
	end

	-- variable height jumping
	if btn(controls.jump) -- if the jump button is down
	and p1_y_vel <= 0 -- and the player is not falling (aka vertically not moving, or moving upwards)
	and p1_jump_btn_frames < p1_max_jump_frames -- and the button has been held for less than the max allowed num of frames
	and p1_head_bonked == false then -- and the player has not bonked their head on the ceiling

		if (p1_jump_btn_frames == 0 and p1_jump_btn_released == true) -- case 1: it is the first frame the button is being pressed
		or (p1_jump_btn_frames > 0 and p1_jump_btn_released == false) then -- case 2: the button has been held for more than one frame
			p1_jump_btn_released = false
			p1_jump_btn_frames += 1
			set_y_velocity(p1_jump_velocity) -- defined in designer_controls.p8
			p1_landed = false
		end

	elseif btn(controls.jump) == false then

		p1_jump_btn_released = true
		if p1_landed == true then
			p1_jump_btn_frames = 0
		end

	end

	if p1_head_bonked == true then
		p1_head_bonked = false
	end
	

	-- walk left/right
	p1_dx = 0
	-- walk right?
	if btn(controls.walk_right) then
		p1_dx += p1_walk_speed -- defined in designer_controls.p8
		if p1_facing < 0 then
			p1_facing *= -1
		end
	end
	-- walk left?
	if btn(controls.walk_left) then
	 p1_dx -= p1_walk_speed -- defined in designer_controls.p8
	 if p1_facing > 0 then
	 	p1_facing *= -1
	 end
	end
	
	p1_update_landmarks()
end

function p1_attack()
	if p1_spr_state != p1_sprs.attack then
		if debug_attacking then printh("attacking") end
		if p1_weapon == "sword" then
			sword_activate()
			if debug_attacking then printh("\twith sword") end
		end
		p1_attacking = true
	end
end

function p1_check_collision()
	p1_tile_collision()
	p1_enemy_collision()
end

function p1_tile_collision()
	p1_horizontal_collision()
	p1_vertical_collision()
end

function p1_enemy_collision()
	collision_check_with_enemies_in_room(p1_x, p1_y, p1_w, p1_h, set_enemy_collision_with_player, set_player_collision_with_enemy)
end

-- currently does nothing
function p1_receive_collision()

	-- do things on first frame of collision
	if p1_prev_frame_collision_with_enemy == false and p1_this_frame_collision_with_enemy == true then
		p1_collision_with_enemy_enter()

	-- do things on middle frames of collision
	elseif p1_prev_frame_collision_with_enemy == true and p1_this_frame_collision_with_enemy == true then
		p1_collision_with_enemy_during()

	-- do things the frame after the last frame of collision
	elseif p1_prev_frame_collision_with_enemy == true and p1_this_frame_collision_with_enemy == false then
		p1_collision_with_enemy_exit()
	end

	-- prep for next frame
	p1_prev_frame_collision_with_enemy = p1_this_frame_collision_with_enemy
	p1_this_frame_collision_with_enemy = false -- reset in case of no collision next frame
end

function set_player_collision_with_enemy()
	p1_this_frame_collision_with_enemy = true
end

-- currently does nothing
function p1_collision_with_enemy_enter()
	if debug_player_collision then printh("player collision with enemy (enter)") end
	p1_health = 0
end

-- currently does nothing
function p1_collision_with_enemy_during()
	if debug_player_collision then printh("player collision with enemy (during)") end
end

-- currently does nothing
function p1_collision_with_enemy_exit()
	if debug_player_collision then printh("player collision with enemy (exit)") end
end

function set_y_velocity(_new_vel)
    p1_y_vel = _new_vel
end

function p1_horizontal_collision()
	-- determine wall collision with three candidates
	-- 1. top ray
	-- 2. btm ray
	-- 3. vel ray

    p1_update_landmarks()

	cand_tx = p1_lft
	cand_bx = p1_lft

	cand_ty = p1_top
	cand_by = p1_btm

    -- edge case #1
    -- if the player is not enclosed in solid tiles, the raycasting "while" loop will run forever.
    -- in order to avoid this, there needs to be a second (fallback) condition that stops casting the ray when it
    -- hits the edge of the map.

    -- note: we're actually gonna allow it to go one pixel off the edge of the screen to allow it to trigger
    -- a screen transition

	if p1_dx > 0 then -- cast rays to right
        --                                                        account for edge case #1
		-- top ray                                                vvvvvvvvvvvvvvvvvvvvvvvv
		while check_for_flag_at_pix(cand_tx, cand_ty, 4) == false and cand_tx <= map_max_pix_x do
			cand_tx += 1
		end
		cand_tx -= p1_w

        --                                                        account for edge case #1
		-- bottom ray                                             vvvvvvvvvvvvvvvvvvvvvvvv
		while check_for_flag_at_pix(cand_bx, cand_by, 4) == false and cand_bx <= map_max_pix_x do
			cand_bx += 1
		end
		cand_bx -= p1_w

	elseif p1_dx < 0 then -- cast rays to left
        --                                                        account for edge case #1
		-- top ray                                                vvvvvvvvvvvv
		while check_for_flag_at_pix(cand_tx, cand_ty, 4) == false and cand_tx >= 0 do
			cand_tx -= 1
		end
		cand_tx += 1
		
        --                                                        account for edge case #1
		-- bottom ray                                             vvvvvvvvvvvv
		while check_for_flag_at_pix(cand_bx, cand_by, 4) == false and cand_bx >= 0 do
			cand_bx -= 1
		end
		cand_bx += 1

	end
	cand_vx = p1_x + p1_dx
end

function p1_vertical_collision()
	
	-- this is the landing algo. it ensures you never pass through platforms no matter how fast you're falling.
	-- every frame, two rays are cast straight downwards from both the left and right edges of the sprite.
	-- from each of these rays, a "candidate" landing height is determined
	-- we also determine a third candidate landing height based on the current y-pos and y-vel.
	-- the highest candidate height (vertically nearest below the sprite) is chosen
	-- this way, if you're falling faster than 8 pix/frame you will not pass through a one-tile-tall platform

    p1_update_landmarks()
    
	-- these coords are all in map pixels
	cand_lx = p1_lft
	cand_rx = p1_rgt

	cand_ly = p1_top
	cand_ry = p1_top

    -- edge case #1
    -- if the player is not enclosed in solid tiles, the raycasting "while" loop will run forever.
    -- in order to avoid this, there needs to be a second (fallback) condition that stops casting the ray when it
    -- hits the edge of the screen.

	if p1_y_vel >= 0 then -- cast rays downwards
        -- if we're casting downwards, start from the bottom of the sprite rather than the top
        cand_ly += p1_h - 1
        cand_ry += p1_h - 1

        -- edge case #2
        -- if we're inside a semisolid platform, the rays will start from inside a landable tile and never be cast.
        -- if this is the case, we need to cast them until they're outside of the tile they started inside of, and
        -- then resume casting like normal

        -- left ray

        -- account for edge case #2 with left ray
        if check_for_flag_at_pix(cand_lx, cand_ly, 3) then
            if debug_vertical_collision then printh("edge case, left ray") end
            -- cast until the ray is below the block
            while check_for_flag_at_pix(cand_lx, cand_ly, 3) == true do
                cand_ly += 1
            end
            assert(check_for_flag_at_pix(cand_lx, cand_ly, 3) == false) -- make sure it works properly
        end

        --                                                            account for edge case #1
        -- cast left ray                                              vvvvvvvvvvvvvvvvvvvvvvvv
		while check_for_flag_at_pix(cand_lx, cand_ly, 3) == false and cand_ly <= map_max_pix_y do
			cand_ly += 1
		end
        cand_ly -= p1_h

        -- right ray

        -- account for edge case #2 with right ray
        if check_for_flag_at_pix(cand_rx, cand_ry, 3) then
            if debug_vertical_collision then printh("edge case, right ray") end
            -- cast until the ray is below the block
            while check_for_flag_at_pix(cand_rx, cand_ry, 3) == true do
                cand_ry += 1
            end
            assert(check_for_flag_at_pix(cand_rx, cand_ry, 3) == false) -- make sure it works properly
        end

        --                                                            account for edge case #1
        -- cast right ray                                             vvvvvvvvvvvvvvvvvvvvvvvv
		while check_for_flag_at_pix(cand_rx, cand_ry, 3) == false and cand_ry <= map_max_pix_y do
			cand_ry += 1
		end
        cand_ry -= p1_h
	
    else -- cast rays upwards
        --                                                        account for edge case #1
        -- left ray                                               vvvvvvvvvvvv
		while check_for_flag_at_pix(cand_lx, cand_ly, 5) == false and cand_ly >= 0 do
			cand_ly -= 1
		end
		cand_ly += 1

        --                                                        account for edge case #1
        -- right ray                                              vvvvvvvvvvvv
		while check_for_flag_at_pix(cand_rx, cand_ry, 5) == false and cand_ry >= 0 do
			cand_ry -= 1
		end
		cand_ry += 1
	end
	
	-- determine candidate v using velocity
	cand_vy = p1_y + p1_y_vel
end

-- currently does nothing
function p1_trigger_death()
	if debug_player_death then printh("ur ded lmao") end
	-- set death animation
end

function p1_move()
	
    -- move player horizontally
	if p1_dx > 0 then
		-- facing right, so pick the smallest (leftmost number)
		p1_x = min(cand_vx, min(cand_tx, cand_bx))

		-- determine if you walked into a hazard or not
		if check_for_flag_at_pix(p1_x + p1_w, p1_y + 4, 0) == true then
			p1_health = 0
		end
	elseif p1_dx < 0 then
		-- facing left, so pick the largest (rightmost number)
		p1_x = max(cand_vx, max(cand_tx, cand_bx))

		-- determine if you walked into a hazard or not
		if check_for_flag_at_pix(p1_x - 1, p1_y + 4, 0) == true then
			p1_health = 0
		end
	end

	-- move player vertically
	if p1_y_vel >= 0 then
        -- move player
		p1_y = min(cand_vy, min(cand_ly, cand_ry))

        -- determine if they landed or not
		if p1_y == cand_ly or p1_y == cand_ry then
			p1_landed = true
		    set_y_velocity(0)
			-- determine if you landed on a hazard or not
			if check_for_flag_at_pix(p1_x + 4, p1_y + 8, 0) == true then
				p1_health = 0
			end
        else
            p1_landed = false
            p1_apply_gravity()
		end
	else
        -- move player
		p1_y = max(cand_vy, max(cand_ly, cand_ry))

        -- determine if they bonked their head or not
		if p1_y == cand_ly or p1_y == cand_ry then
			p1_head_bonked = true
		    set_y_velocity(0)
			-- determine if you bonked your head on a hazard or not
			if check_for_flag_at_pix(p1_x + 4, p1_y - 1, 0) == true then
				p1_health = 0
			end
        else
            p1_apply_gravity()
		end
	end

    -- check if player is positioned to trigger screen transitions
    if p1_y < get_current_top_bounds() then -- move up
        move_player_to_room_up()

    elseif p1_y + (p1_h - 1) >= get_current_bottom_bounds() then -- move down
        move_player_to_room_down()

    elseif p1_x < get_current_left_bounds() then -- move left
        move_player_to_room_left()

    elseif p1_x + (p1_w - 1) >= get_current_right_bounds() then -- move right
        move_player_to_room_right()
    end

	-- check for player death
	if p1_health <= 0 then
		p1_trigger_death()
	end
end

function p1_update_animation()
	p1_animate()

	p1_anim_fcount += 1
end

function p1_animate_neutral()
	p1_spr_n = index_loop_animation(p1_anim_fcount, p1_anim_spd, #p1_sprs.neutral)
	p1_draw_spr = p1_sprs.neutral[p1_spr_n]

	-- determine next state
	if p1_attacking == true then
		if debug_player_animation_state then printh("neutral --> attack") end
		p1_set_animation(p1_animate_attack)
	elseif p1_dx != 0 then
		if debug_player_animation_state then printh("neutral --> walk") end
		p1_set_animation(p1_animate_walk)
	elseif p1_y_vel < 0 then
		if debug_player_animation_state then printh("neutral --> jump") end
		p1_set_animation(p1_animate_jump)
	elseif p1_y_vel > 0 then
		if debug_player_animation_state then printh("neutral --> fall") end
		p1_set_animation(p1_animate_fall)
	end
end

function p1_animate_walk()
	p1_spr_n = index_loop_animation(p1_anim_fcount, p1_anim_spd, #p1_sprs.walk)
	p1_draw_spr = p1_sprs.walk[p1_spr_n]

	-- determine next state
	if p1_attacking == true then
		if debug_player_animation_state then printh("walk --> attack") end
		p1_set_animation(p1_animate_attack)
	elseif p1_dx == 0 then
		if debug_player_animation_state then printh("walk --> neutral") end
		p1_set_animation(p1_animate_neutral)
	elseif p1_y_vel < 0 then
		if debug_player_animation_state then printh("walk --> jump") end
		p1_set_animation(p1_animate_jump)
	elseif p1_y_vel > 0 then
		if debug_player_animation_state then printh("walk --> fall") end
		p1_set_animation(p1_animate_fall)
	end
end

function p1_animate_jump()
	p1_spr_n = index_loop_animation(p1_anim_fcount, p1_anim_spd, #p1_sprs.jump)
	p1_draw_spr = p1_sprs.jump[p1_spr_n]

	-- determine next state
	if p1_attacking == true then
		if debug_player_animation_state then printh("jump --> attack") end
		p1_set_animation(p1_animate_attack)
	elseif p1_y_vel > 0 then
		if debug_player_animation_state then printh("jump --> fall") end
		p1_set_animation(p1_animate_fall)
	end
end

function p1_animate_fall()
	p1_spr_n = index_loop_animation(p1_anim_fcount, p1_anim_spd, #p1_sprs.fall)
	p1_draw_spr = p1_sprs.fall[p1_spr_n]
	
	-- determine next state
	if p1_attacking == true then
		if debug_player_animation_state then printh("fall --> attack") end
		p1_set_animation(p1_animate_attack)
	elseif p1_y_vel == 0 then
		if p1_dx != 0 then
			if debug_player_animation_state then printh("fall --> walk") end
			p1_set_animation(p1_animate_walk)
		elseif p1_dx == 0 then
			if debug_player_animation_state then printh("fall --> neutral") end
			p1_set_animation(p1_animate_neutral)
		end
	elseif p1_y_vel < 0 then
		if debug_player_animation_state then printh("fall --> jump") end
		p1_set_animation(p1_animate_jump)
	end
end

function p1_animate_attack()
	
	if p1_anim_fcount >= p1_attack_frames then
		p1_attacking = false
		if p1_y_vel < 0 then
			if debug_player_animation_state then printh("attack --> jump") end
			p1_set_animation(p1_animate_jump)
		elseif p1_y_vel > 0 then
			if debug_player_animation_state then printh("attack --> fall") end
			p1_set_animation(p1_animate_fall)
		elseif p1_dx != 0 then
			if debug_player_animation_state then printh("attack --> walk") end
			p1_set_animation(p1_animate_walk)
		else
			if debug_player_animation_state then printh("attack --> neutral") end
			p1_set_animation(p1_animate_neutral)
		end
	else
		-- use a different method of calculating animation frame
		p1_spr_n = index_animation_noloop(p1_anim_fcount, p1_attack_frames, #p1_sprs.attack)
		p1_draw_spr = p1_sprs.attack[p1_spr_n]
	end
end

function p1_reset_animation()
	p1_spr_n = 1
	p1_anim_fcount = 0
end

function p1_set_animation(_anim)
	p1_animate = _anim
	p1_reset_animation()
end

function p1_apply_gravity()
    p1_y_vel += p1_gravity -- defined in designer_controls.p8
end

function move_player_to_room_up()
	if debug_player_room_transition then printh("move player to room up") end
    p1_y -= p1_h - 1
	change_rooms()
end

function move_player_to_room_down()
	if debug_player_room_transition then printh("move player to room down") end
    p1_y += p1_h - 1
	change_rooms()
end

function move_player_to_room_left()
	if debug_player_room_transition then printh("move player to room left") end
	p1_x -= p1_w - 1
	change_rooms()

end

function move_player_to_room_right()
	if debug_player_room_transition then printh("move player to room right") end
    p1_x += p1_w - 1
	change_rooms()
end

function p1_update_landmarks()
	-- update map-pixel landmarks
	p1_lft = p1_x
	p1_rgt = p1_x + p1_w - 1
	p1_top = p1_y
	p1_btm = p1_y + p1_h - 1
	p1_ctr = (p1_lft + p1_rgt) / 2
	p1_mdl = (p1_top + p1_btm) / 2

	-- update screen-pixel landmarks
	p1_s_lft = p1_lft % 128
	p1_s_rgt = p1_rgt % 128
	p1_s_top = p1_top % 128
	p1_s_btm = p1_btm % 128
	p1_s_ctr = p1_ctr % 128
	p1_s_mdl = p1_mdl % 128
end

function p1_get_x()
	return p1_x
end

function p1_get_y()
	return p1_y
end

function p1_get_sx()
	return p1_sx
end

function p1_get_sy()
	return p1_sy
end

function p1_get_facing()
	return p1_facing
end
	
function p1_draw()

	p1_update_screen_pos()

	-- print sprite index
	if debug_player_draw then
		if p1_draw_spr == nil then
			printh(p1_spr_n)
		end
	end

	assert(p1_draw_spr != nil)

	spr(p1_draw_spr, -- sprite number to draw
        p1_sx, p1_sy, -- position to draw at
        1, 1, -- number of tiles wide/tall
        p1_facing == -1, false) -- whether or not to flip on x,y axis
	
	if debug_player_draw then

		-- print screen and world positions
		if debug_position then
			print("world pos: ("..p1_x..", "..p1_y..")", 0, 0 ,6)
			print("scren pos: ("..p1_sx..", "..p1_sy..")", 0, 6, 6)
		end
		
		-- print/draw wall detection
		if debug_horizontal_collision then
			-- print numbers
			print(cand_tx, 10, 6 * 6, 15) -- top
			print(cand_vx, 10, 7 * 6, 15) -- velocity
			print(cand_bx, 10, 8 * 6, 15) -- bottom
			
			-- draw rays
			if p1_dx>0 then
				--moving right
				line(p1_s_lft, p1_s_top, cand_tx % 128, cand_ty % 128, 11) -- top
				line(p1_s_lft, p1_s_mdl, cand_vx % 128, p1_s_mdl, 11) -- velocity
				line(p1_s_lft, p1_s_btm, cand_bx % 128, cand_by % 128, 11) -- bottom
			elseif p1_dx<0 then
				--moving left
				line(p1_s_lft, p1_s_top, cand_tx % 128, cand_ty % 128, 11) -- top
				line(p1_s_lft, p1_s_mdl, cand_vx % 128, p1_s_mdl, 11) -- velocity
				line(p1_s_lft, p1_s_btm, cand_bx % 128, cand_by % 128, 11) -- bottom
			end
		end
		
		-- print/draw bonk/land detection
		if debug_vertical_collision then
			-- print velocity
			print(p1_y_vel, 30, 10, 15)
			
			-- print numbers
			print(cand_ly, 30, 30, 15) -- left
			print(cand_vy, 40, 36, 15) -- velocity
			print(cand_ry, 50, 42, 15) -- right
			
			-- draw rays
			if p1_y_vel>0 then
				-- falling
				line(p1_s_lft, p1_s_top + p1_h - 1, cand_lx % 128, cand_ly % 128, 11) -- left
				line(p1_s_ctr, p1_s_top, p1_s_ctr, cand_vy % 128, 11) -- velocity
				line(p1_s_rgt, p1_s_top + p1_h - 1, cand_rx % 128, cand_ry % 128, 11) -- right
			elseif p1_y_vel<0 then
				-- rising
				line(p1_s_lft, p1_s_top, cand_lx % 128, cand_ly % 128, 11) -- left
				line(p1_s_ctr, p1_s_top, p1_s_ctr, cand_vy % 128, 11) -- velocity
				line(p1_s_rgt, p1_s_top, cand_rx % 128, cand_ry % 128, 11) -- right
			end
		end
		
		--draw landmark pixels
		if debug_landmarks then
        	p1_update_landmarks()

			local pcol=8
			--draw top left corner pixel
			pset(p1_lft,
			     p1_top,
			     pcol)
			--draw top center pixel
			pset(p1_ctr,
			     p1_top,
			     pcol)
			--draw top right corner pixel
			pset(p1_rgt,
			     p1_top,
			     pcol)
			
			--draw left middle pixel
			pset(p1_lft,
			     p1_mdl,
			     pcol)
			--draw right middle pixel
			pset(p1_rgt,
			     p1_mdl,
			     pcol)
			
			--draw btm left corner pixel
			pset(p1_lft,
			     p1_btm,
			     pcol)
			--draw btm center pixel
			pset(p1_ctr,
			     p1_btm,
			     pcol)
			--draw btm right corner pixel
			pset(p1_rgt,
			     p1_btm,
			     pcol)
		end
	end
end