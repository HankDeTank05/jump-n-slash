require("designer_controls")

-------------------------------
-- player "member" variables --
-------------------------------

local player_sprite
local player_x
local player_y
local player_facing
local player_screenX
local player_screenY
local player_dx
local player_yVel
local player_width
local player_height

-- flags
local player_atkBtnHeldPrevFrame
local player_atkBtnReleased

------------------------
-- inputs and actions --
------------------------

local function Player_ReadInputs(_dt)
	-- read for attack
	if love.keyboard.isDown(p1_controls.attack) then
		if player_atkBtnReleased == true then
			print("attack")
		end
		player_atkBtnReleased = false
	else
		player_atkBtnReleased = true
	end
	
	-- read for jumping

	-- walk right/left
	player_dx = 0
	-- walk right?
	if love.keyboard.isDown(p1_controls.walk_right) then
		--print("walking right")
		player_dx = player_dx + p1_walk_speed * _dt-- defined in designer controls
		player_facing = 1
	end

	-- walk left?
	if love.keyboard.isDown(p1_controls.walk_left) then
		--print("walking left")
		player_dx = player_dx - p1_walk_speed * _dt
		player_facing = -1
	end
end

local function Player_Attack()
end

local function Player_TriggerDeath()
end

---------------
-- collision --
---------------

function Player_SetCollisionWithEnemy()
end

local function Player_OnCollisionWithEnemyEnter()
end

local function Player_OnCollisionWithEnemyDuring()
end

local function Player_OnCollisionWithEnemyExit()
end

local function Player_ReceiveCollision()
end

local function Player_CastRay(_start_x, _start_y, _end_x, _end_y)
end

local function Player_CheckTileCollisionHorizontal()

	-- edge case #1
	-- if the player is not enclosed in solid tiles, the raycasting "while" loop will run forever
	-- in order to avoid this, there needs to be a second (fallback) condition that stops casting the ray when it
	-- hits the edge of the room

	if player_dx > 0 then -- cast rays to right
		-- code goes here
	elseif player_dx < 0 then -- cast rays to left
		-- code goes here
	end

end

local function Player_CheckTileCollisionVertical()

	-- edge case #1
	-- if the player is not enclosed in solid tiles, the raycasting "while" loop will run forever
	-- in order to avoid this, there needs to be a second (fallback) condition that stops casting the ray when it
	-- hits the edge of the room

	if player_yVel >= 0 then -- cast ray downwards
		-- code goes here
	else -- cast ray upwards
		-- code goes here
	end

end

local function Player_CheckEnemyCollision()
end

local function Player_CheckTileCollision()
	Player_CheckTileCollisionHorizontal()
	Player_CheckTileCollisionVertical()
end

local function Player_CheckCollision()
	Player_CheckTileCollision()
	Player_CheckEnemyCollision()
end

-----------------------
-- movement/position --
-----------------------

local function Player_UpdateScreenPos()
	if player_facing > 0 then
		player_screenX = player_x
	else
		player_screenX = player_x + player_width
	end
	player_screenY = player_y
end

local function Player_Move(_dt)
	player_x = player_x + player_dx

	Player_UpdateScreenPos()
end

local function Player_ApplyGravity()
end

local function Player_MoveToRoomUp()
end

local function Player_MoveToRoomDown()
end

local function Player_MoveToRoomLeft()
end

local function Player_MoveToRoomRight()
end

local function Player_UpdateLandmarks()
end

---------------
-- animation --
---------------

local function Player_UpdateAnimation()
end

function Player_AnimStateIdle()
end

function Player_AnimStateWalk()
end

function Player_AnimStateJump()
end

function Player_AnimStateFall()
end

function Player_AnimStateAttack()
end

function Player_ResetAnimation()
end

function Player_SetAnimation(_anim)
end

-----------------------
-- accessors/getters --
-----------------------

function Player_GetX()
	return player_x
end

function Player_GetY()
	return player_y
end

function Player_GetScreenX()
	return Player_screenX
end

function Player_GetScreenY()
	return Player_screenY
end

function Player_GetFacingDir()
	return Player_facing
end

--------------------
-- core functions --
--------------------

function InitPlayer()
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
	assert(p1_max_jump_secs > 0) -- make sure it's positive

	-- p1_walk_speed must always be a positive integer
	assert(p1_walk_speed > 0) -- make sure it's positive

	-- p1_attack_frames must always be a positive integer
	assert(p1_attack_secs > 0) -- make sure it's positive

	-- p1_max_health must always be a positive integer
	assert(p1_max_health > 0)   -- make sure it's positive
	assert(p1_max_health % 1 == 0) -- make sure it's an integer

	-----------------
	-- begin setup --
	-----------------

	-- load player sprites
	player_sprite = love.graphics.newImage("assets/sprites/player/idle_1.png")

	player_x = (3 - 1) * TILE_WIDTH -- world position x
	player_y = (15 - 1) * TILE_HEIGHT -- world position y
	player_facing = 1 -- 1=right, -1=left

	player_screenX = nil -- screen position x
	player_screenY = nil -- screen position y
	Player_UpdateScreenPos()

	player_dx = 0 -- delta x, since there's no horizontal acceleration
	player_yVel = 0 -- y-velocity, since there is vertical acceleration
	player_width = 8  -- width of the sprite
	player_height = 8  -- height of the sprite
end

function UpdatePlayer(_dt)

	Player_ReadInputs(_dt)

	Player_CheckCollision() -- check for collision with other objects

	Player_ReceiveCollision() -- react to other objects colliding with it

	Player_Move(_dt)

	Player_UpdateAnimation()

	Player_UpdateLandmarks()
end

function DrawPlayer()
	--print(player_facing)
	love.graphics.draw(player_sprite, player_screenX, player_screenY, 0, player_facing, 1)

	-- debug stuff
	if true then
		love.graphics.points(player_screenX, player_screenY)

		-- draw bounds
		love.graphics.line(player_screenX, player_screenY,
							player_screenX + player_facing * player_width, player_screenY,
							player_screenX + player_facing * player_width, player_screenY + player_height,
							player_screenX, player_screenY + player_height,
							player_screenX, player_screenY)
	end
end
