require("map")

require("util")
require("designer_controls")

-------------------------------
-- player "member" variables --
-------------------------------

-- drawing
local player_sprite
local player_screenX
local player_screenY

-- position and movement
local player_x
local player_y
local player_width
local player_height
local player_facing
local player_dx
local player_yVel

-- animation lists
local player_animIdle
local player_animWalk
local player_animJump
local player_animFall
local player_animAttack

-- animation
local player_animFPS -- frames per second
local player_animSPF -- seconds per frame
local player_animTime
local player_animIndex

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
	-- TODO: global for debugging purposes
	candLX = math.floor(Player_GetX())
	candLY = math.floor(Player_GetY())
	candLXStart = candLX
	candLYStart = candLY

	candRX = math.floor(Player_GetX() + Player_GetWidth())
	candRY = math.floor(Player_GetY())
	candRXStart = candRX
	candRYStart = candRY

	-- edge case #1
	-- if the player is not enclosed in solid tiles, the raycasting "while" loop will run forever
	-- in order to avoid this, there needs to be a second (fallback) condition that stops casting the ray when it
	-- hits the edge of the room

	if player_yVel >= 0 then -- cast ray downwards
		candLY = candLY + Player_GetHeight()
		candRY = candRY + Player_GetHeight()

		-- left ray
		while Map_IsTileSolidTop(candLX, candLY) == false do
			candLY = candLY + 1
		end
		candLY = candLY - 1

		-- right ray
		while Map_IsTileSolidTop(candRX, candRY) == false do
			candRY = candRY + 1
		end
		candRY = candRY - 1

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

-- callback
local function Player_Animate()
end

local function Player_UpdateAnimation()
	Player_Animate()

	player_animTime = player_animTime + love.timer.getDelta()
end

function Player_AnimStateIdle()
	player_animIndex = IndexLoopedAnimation(player_animTime, player_animSPF, #player_animIdle)
	player_sprite = player_animIdle[player_animIndex]

	-- determine next state
	if player_dx ~= 0 then
		Player_SetAnimation(Player_AnimStateWalk)
	end
end

function Player_AnimStateWalk()
	player_animIndex = IndexLoopedAnimation(player_animTime, player_animSPF, #player_animWalk)
	player_sprite = player_animWalk[player_animIndex]

	-- determine next state
	if player_dx == 0 then
		Player_SetAnimation(Player_AnimStateIdle)
	end
end

function Player_AnimStateJump()
end

function Player_AnimStateFall()
end

function Player_AnimStateAttack()
end

function Player_ResetAnimation()
	player_animIndex = 1
	player_animTime = 0
end

function Player_SetAnimation(_anim_function)
	Player_Animate = _anim_function
	Player_ResetAnimation()
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

function Player_GetWidth()
	return player_width
end

function Player_GetHeight()
	return player_height
end

function Player_GetScreenX()
	return player_screenX
end

function Player_GetScreenY()
	return player_screenY
end

function Player_GetFacingDir()
	return player_facing
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
	local spritePath = "assets/sprites/player/"
	local suffix = "_32.png"
	player_animIdle = {
		love.graphics.newImage(spritePath.."idle_1"..suffix),
		love.graphics.newImage(spritePath.."idle_2"..suffix),
		love.graphics.newImage(spritePath.."idle_3"..suffix),
		love.graphics.newImage(spritePath.."idle_4"..suffix),
	}
	player_animWalk = {
		love.graphics.newImage(spritePath.."walk_1"..suffix),
		love.graphics.newImage(spritePath.."walk_2"..suffix),
		love.graphics.newImage(spritePath.."walk_3"..suffix),
		love.graphics.newImage(spritePath.."walk_4"..suffix),
	}
	player_animAttack = {
		love.graphics.newImage(spritePath.."attack_1"..suffix),
		love.graphics.newImage(spritePath.."attack_2"..suffix),
		love.graphics.newImage(spritePath.."attack_3"..suffix),
		love.graphics.newImage(spritePath.."attack_4"..suffix),
	}

	player_x = (3 - 1) * TILE_SIZE -- world position x
	player_y = (15 - 1) * TILE_SIZE -- world position y
	player_facing = 1 -- 1=right, -1=left

	player_screenX = nil -- screen position x
	player_screenY = nil -- screen position y
	Player_UpdateScreenPos()

	player_dx = 0 -- delta x, since there's no horizontal acceleration
	player_yVel = 0 -- y-velocity, since there is vertical acceleration
	player_width = 32  -- width of the sprite
	player_height = 32  -- height of the sprite

	Player_Animate = Player_AnimStateIdle
	player_animFPS = 6
	player_animSPF = 1 / player_animFPS
	player_animTime = 0
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
		love.graphics.points(player_x, player_y)
		love.graphics.line(candLXStart, candLYStart, candLX, candLY)
		love.graphics.line(candRXStart, candRYStart, candRX, candRY)
	end
end
