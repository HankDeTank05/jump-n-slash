require("designer_controls")

------------------------
-- inputs and actions --
------------------------

local function Player_ReadInputs(_dt)
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

local function Player_CheckTileCollisionHorizontal()
end

local function Player_CheckTileCollisionVertical()
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
	p1_sx = p1_x
	p1_sy = p1_y
end

local function Player_Move(_dt)
	p1_x = p1_x + p1_dx

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
	return p1_x
end

function Player_GetY()
	return p1_y
end

function Player_GetScreenX()
	return p1_sx
end

function Player_GetScreenY()
	return p1_sy
end

function Player_GetFacingDir()
	return p1_facing
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
	p1_sprite = love.graphics.newImage("assets/sprites/player/idle_1.png")

	p1_x = 64  -- world position x
	p1_y = 64  -- world position y
	p1_facing = 1 -- 1=right, -1=left

	p1_sx = nil -- screen position x
	p1_sy = nil -- screen position y
	p1_update_screen_pos()

	p1_dx = 0 -- delta x, since there's no horizontal acceleration
	p1_y_vel = 0 -- y-velocity, since there is vertical acceleration
	p1_w = 8  -- width of the sprite
	p1_h = 8  -- height of the sprite
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
	love.graphics.draw(p1_sprite, p1_sx, p1_sy, 0, SCREEN_SCALE, SCREEN_SCALE)
end
