require("designer_controls")
--------------------
-- core functions --
--------------------

function init_player()
	
	----------------------
	-- pre-setup checks --
	----------------------

	-- assertions for designer controls
	
	-- make sure the controls use a valid button code
	assert(p1_controls.walk_left ~= nil)
	assert(p1_controls.walk_right ~= nil)
	assert(p1_controls.jump ~= nil)
	assert(p1_controls.attack ~= nil)

	-- p1_jump_velocity must always be negative
	assert(p1_jump_velocity < 0) -- make sure it's negative

	-- p1_gravity must always be positive
	assert(p1_gravity > 0) -- make sure it's positive

	-- p1_max_jump_frames must always be a positive integer
	assert(p1_max_jump_secs > 0)   -- make sure it's positive

	-- p1_walk_speed must always be a positive integer
	assert(p1_walk_speed > 0)   -- make sure it's positive

	-- p1_attack_frames must always be a positive integer
	assert(p1_attack_secs > 0)   -- make sure it's positive

	-- p1_max_health must always be a positive integer
	assert(p1_max_health > 0)   -- make sure it's positive
	assert(p1_max_health % 1 == 0) -- make sure it's an integer

	-----------------
	-- begin setup --
	-----------------

	-- load player sprites
	p1_sprite = love.graphics.newImage("assets/sprites/player/idle_1.png")

	p1_x = 64 -- world position x
	p1_y = 64 -- world position y
	p1_facing = 1 -- 1=right, -1=left
	
	p1_sx = nil -- screen position x
	p1_sy = nil -- screen position y
	p1_update_screen_pos()

	p1_dx = 0 -- delta x, since there's no horizontal acceleration
	p1_y_vel = 0 -- y-velocity, since there is vertical acceleration
	p1_w = 8 -- width of the sprite
	p1_h = 8 -- height of the sprite
end

function update_player(_dt)
	p1_read_inputs(_dt)

	p1_check_collision() -- check for collision with other objects

	p1_receive_collision() -- react to other objects colliding with it

	p1_move(_dt)

	p1_update_animation()

	p1_update_landmarks()
end

function draw_player()
	love.graphics.draw(p1_sprite, p1_sx, p1_sy, 0, SCREEN_SCALE, SCREEN_SCALE)
end

------------------------
-- inputs and actions --
------------------------

function p1_read_inputs(_dt)
	-- read for attack

	-- read for jumping

	-- walk right/left
	p1_dx = 0
	-- walk right?
	if love.keyboard.isDown(p1_controls.walk_right) then
		print("walking right")
		p1_dx = p1_dx + p1_walk_speed * _dt-- defined in designer controls
		p1_facing = 1
	end

	-- walk left?
	if love.keyboard.isDown(p1_controls.walk_left) then
		print("walking left")
		p1_dx = p1_dx - p1_walk_speed * _dt
		p1_facing = -1
	end
end

function p1_attack()
	-- code goes here
end

function p1_trigger_death()
	-- code goes here
end

---------------
-- collision --
---------------

function p1_check_collision()
	-- code goes here
end

function p1_tile_collision()
	-- code goes here
end

function p1_enemy_collision()
	-- code goes here
end

function p1_receive_collision()
	-- code goes here
end

function p1_set_collision_with_enemy()
	-- code goes here
end

function p1_collision_with_enemy_enter()
	-- code goes here
end

function p1_collision_with_enemy_during()
	-- code goes here
end

function p1_collision_with_enemy_exit()
	-- code goes here
end

-----------------------
-- movement/position --
-----------------------

function p1_move(_dt)
	p1_x = p1_x + p1_dx

	p1_update_screen_pos()
end

function p1_update_screen_pos()
	p1_sx = p1_x
	p1_sy = p1_y
end

function p1_tile_collision_horizontal()
	-- code goes here
end

function p1_tile_collision_vertical()
	-- code goes here
end

function p1_apply_gravity()
	-- code goes here
end

function p1_move_to_room_up()
	-- code goes here
end

function p1_move_to_room_down()
	-- code goes here
end

function p1_move_to_room_left()
	-- code goes here
end

function p1_move_to_room_right()
	-- code goes here
end

function p1_update_landmarks()
	-- code goes here
end

---------------
-- animation --
---------------

function p1_update_animation()
	-- code goes here
end

function p1_animate_neutral()
	-- code goes here
end

function p1_animate_walk()
	-- code goes here
end

function p1_animate_jump()
	-- code goes here
end

function p1_animate_fall()
	-- code goes here
end

function p1_animate_attack()
	-- code goes here
end

function p1_reset_animation()
	-- code goes here
end

function p1_set_animation(_anim)
	-- code goes here
end

-----------------------
-- accessors/getters --
-----------------------

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