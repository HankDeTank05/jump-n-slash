pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

--[[
    this is the file for all code concerning the player character
]]

p1 = {
	sprite = 1, -- the sprite to draw
	x = 16, y = 100,
	dx = 0, -- delta x, since there's no horizontal acceleration
	y_vel = 0, -- y-velocity, since there is vertical acceleration
	w = 8, h = 8,
	lft = nil, -- left x
	rgt = nil, -- right x
	top = nil, -- top y
	btm = nil, -- bottom y
	ctr = nil, -- center x
	mdl = nil, -- middle y
	facing = 1, -- 1=right, -1=left
	bonked = false, -- did you bonk your head on a ceiling?
	landed = false, -- did you land on the ground?
}
jump_height = -4
walk_speed = 1
gravity = 0.2

debug_horizontal_collision = true
debug_vertical_collision = true
debug_landmarks = false

function p1_update()
	p1_read_inputs()
	
	p1_collision()
	
	p1_move()
	
	p1_update_landmarks()
	
end

function p1_read_inputs()
	-- read for inputs
	if btnp(⬆️) and p1.landed == true then
		set_y_velocity(jump_height)
		p1.landed = false
	end
	
	p1.dx = 0
	if btn(➡️) then
		p1.dx += walk_speed
		if p1.facing < 0 then
			p1.facing *= -1
		end
	end
	if btn(⬅️) then
	 p1.dx -= walk_speed
	 if p1.facing > 0 then
	 	p1.facing *= -1
	 end
	end
	
	p1_update_landmarks()
end

function p1_collision()
	p1_horizontal_collision()
	p1_vertical_collision()
end

function set_y_velocity(_new_vel)
    p1.y_vel = _new_vel
end

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

function p1_horizontal_collision()
	-- determine wall collision with three candidates
	-- 1. top ray
	-- 2. btm ray
	-- 3. vel ray

    p1_update_landmarks()

	cand_tx = p1.lft
	cand_bx = p1.lft

	cand_ty = p1.top
	cand_by = p1.btm

	if p1.dx > 0 then
		-- cast rays to right

		-- top ray
		while check_for_flag_at(cand_tx, cand_ty, 4) == false do
			cand_tx += 1
		end
		cand_tx -= p1.w

		-- bottom ray
		while check_for_flag_at(cand_bx, cand_by, 4) == false do
			cand_bx += 1
		end
		cand_bx -= p1.w

	elseif p1.dx < 0 then
		-- cast rays to left

		-- top ray
		while check_for_flag_at(cand_tx, cand_ty, 4) == false do
			cand_tx -= 1
		end
		cand_tx += 1
		
		-- bottom ray
		while check_for_flag_at(cand_bx, cand_by, 4) == false do
			cand_bx -= 1
		end
		cand_bx += 1

	end
	cand_vx = p1.x + p1.dx
	
	if p1.dx > 0 then
		-- facing right, so pick the smallest (leftmost number)
		p1.x = min(cand_vx, min(cand_tx, cand_bx))
	elseif p1.dx < 0 then
		-- facing left, so pick the largest (rightmost number)
		p1.x = max(cand_vx, max(cand_tx, cand_bx))
	end
end

function p1_vertical_collision()
	
	-- this is the landing algo. it ensures you never pass through platforms no matter how fast you're falling.
	-- every frame, two rays are cast straight downwards from both the left and right edges of the sprite.
	-- from each of these rays, a "candidate" landing height is determined
	-- we also determine a third candidate landing height based on the current y-pos and y-vel.
	-- the highest candidate height (vertically nearest below the sprite) is chosen
	-- this way, if you're falling faster than 8 pix/frame you will not pass through a one-tile-tall platform

    p1_update_landmarks()
    
	cand_lx = p1.lft
	cand_rx = p1.rgt

	cand_ly = p1.top
	cand_ry = p1.top

	if p1.y_vel >= 0 then
        -- cast rays downwards

        -- left ray
		while check_for_flag_at(cand_lx, cand_ly, 3) == false do
			cand_ly += 1
		end
        cand_ly -= p1.h

        -- right ray
		while check_for_flag_at(cand_rx, cand_ry, 3) == false do
			cand_ry += 1
		end
        cand_ry -= p1.h
	else
        -- cast rays upwards

        -- left ray
		while check_for_flag_at(cand_lx, cand_ly, 5) == false do
			cand_ly -= 1
		end
		cand_ly += 1

        -- right ray
		while check_for_flag_at(cand_rx, cand_ry, 5) == false do
			cand_ry -= 1
		end
		cand_ry += 1
	end
	
	-- determine candidate v using velocity
	cand_vy = p1.y + p1.y_vel
	
	-- reset the landed flag to false
	p1.landed = false

	if p1.y_vel >= 0 then
		p1.y = min(cand_vy, min(cand_ly, cand_ry))
		if p1.y == cand_ly or p1.y == cand_ry then
			p1.landed = true
		end
	else
		p1.y = max(cand_vy, max(cand_ly, cand_ry))
		if p1.y == cand_ly or p1.y == cand_ry then
			p1.bonked = true
		end
	end
end

function p1_move()
	
	if p1.landed == true then
		set_y_velocity(0)
	elseif p1.bonked == true then
		set_y_velocity(0)
		p1.bonked = false
	else
		p1.y_vel += gravity
	end
end

function p1_update_landmarks()
	p1.lft=p1.x
	p1.rgt=p1.x+p1.w-1
	p1.top=p1.y
	p1.btm=p1.y+p1.h-1
	p1.ctr=(p1.lft+p1.rgt)/2
	p1.mdl=(p1.top+p1.btm)/2
end
	
function p1_draw(_debug)
	spr(p1.sprite, p1.x, p1.y)
	
	if _debug then
		
		-- print/draw wall detection
		if debug_horizontal_collision then
			-- print numbers
			print(cand_tx,10,10,15) -- top
			print(cand_vx,10,16,15) -- velocity
			print(cand_bx,10,22,15) -- bottom
			
			-- draw rays
			if p1.dx>0 then
				--moving right
				line(p1.lft, p1.top, cand_tx, cand_ty, 11) -- top
				line(p1.lft, p1.mdl, cand_vx, p1.mdl, 11) -- velocity
				line(p1.lft, p1.btm, cand_bx, cand_by, 11) -- bottom
			elseif p1.dx<0 then
				--moving left
				line(p1.lft, p1.top, cand_tx, cand_ty, 11) -- top
				line(p1.lft, p1.mdl, cand_vx, p1.mdl, 11) -- velocity
				line(p1.lft, p1.btm, cand_bx, cand_by, 11) -- bottom
			end
		end
		
		-- print/draw bonk/land detection
		if debug_vertical_collision then
			-- print velocity
			print(p1.y_vel, 30, 10, 15)
			
			-- print numbers
			print(cand_ly, 30, 30, 15) -- left
			print(cand_vy, 40, 36, 15) -- velocity
			print(cand_ry, 50, 42, 15) -- right
			
			-- draw rays
			if p1.y_vel>0 then
				-- falling
				line(p1.lft, p1.top, cand_lx, cand_ly, 11) -- left
				line(p1.ctr, p1.top, p1.ctr, cand_vy, 11) -- velocity
				line(p1.rgt, p1.top, cand_rx, cand_ry, 11) -- right
			elseif p1.y_vel<0 then
				-- rising
				line(p1.lft, p1.top, cand_lx, cand_ly, 11) -- left
				line(p1.ctr, p1.top, p1.ctr, cand_vy, 11) -- velocity
				line(p1.rgt, p1.top, cand_rx, cand_ry, 11) -- right
			end
		end
		
		--draw landmark pixels
		if debug_landmarks then
			local pcol=8
			--draw top left corner pixel
			pset(p1.lft,
			     p1.top,
			     pcol)
			--draw top center pixel
			pset(p1.ctr,
			     p1.top,
			     pcol)
			--draw top right corner pixel
			pset(p1.rgt,
			     p1.top,
			     pcol)
			
			--draw left middle pixel
			pset(p1.lft,
			     p1.mdl,
			     pcol)
			--draw right middle pixel
			pset(p1.rgt,
			     p1.mdl,
			     pcol)
			
			--draw btm left corner pixel
			pset(p1.lft,
			     p1.btm,
			     pcol)
			--draw btm center pixel
			pset(p1.ctr,
			     p1.btm,
			     pcol)
			--draw btm right corner pixel
			pset(p1.rgt,
			     p1.btm,
			     pcol)
		end
	end
end