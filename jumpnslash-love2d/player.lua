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

-- jumping
local player_jumpBtnTime -- amount of time the jump button has been held for
local player_jumpBtnReleased

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
	if love.keyboard.isDown(p1_controls.jump) then
		io.write("jumping\n")
		player_yVel = p1_jump_velocity
	end

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
		candLY = candLY - 2
		
		-- right ray
		while Map_IsTileSolidTop(candRX, candRY) == false do
			candRY = candRY + 1
		end
		candRY = candRY - 2
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

--[[
updates "player_screenX" and "player_screenY" using data from "player_x" and "player_y"
]]
local function Player_UpdateScreenPos()
	if player_facing > 0 then
		player_screenX = player_x * TILE_SIZE
	else
		player_screenX = (player_x + player_width) * TILE_SIZE
	end
	player_screenY = player_y * TILE_SIZE
end

--[[
CURRENTLY EMPTY
applies gravity to "player_y" variable
]]
local function Player_ApplyGravity()
	player_yVel = player_yVel + p1_gravity
end

--[[
updates "player_x" and "player_y"
]]
local function Player_Move(_dt)
	player_x = player_x + player_dx
	Player_ApplyGravity()
	candVY = player_y + player_yVel
	io.write(candLY .. " " .. candVY .. " " .. candRY .. "\n")
	player_y = math.min( candLY, candVY, candRY )
	if player_y == candLY or player_y == candRY then
		player_yVel = 0
	end
	

	Player_UpdateScreenPos()
end

--[[
CURRENTLY EMPTY
adjusts the "player_y" position manually whenever there is a transition to the room above
]]
local function Player_MoveToRoomUp()
end

--[[
CURRENTLY EMPTY
adjusts the "player_y" position manually whenever there is a transition to the room below
]]
local function Player_MoveToRoomDown()
end

--[[
CURRENTLY EMPTY
adjusts "player_x" position manually whenever there is a transition to the room to the left
]]
local function Player_MoveToRoomLeft()
end

--[[
CURRENTLY EMPTY
adjusts "player_y" position manually whenever there is a transition to the room to the right
]]
local function Player_MoveToRoomRight()
end

--[[
CURRENTLY EMPTY
MAY NOT NEED
updates player landmark positions for easy shorthand position usage. landmakr positions include:
top left
top center
top right
middle left
middle center
middle right
bottom left
bottom center
bottom right
]]
local function Player_UpdateLandmarks()
end

---------------
-- animation --
---------------

--[[
this is how animations work:
	- an array holds the images for each frame of the animation
	- some math is done to determine the index of the current frame of animation
		- this math is different based on whether the animation is looped or not (see util.lua)
	- once the animation frame is determined, it is assigned to the "player_sprite" variable, which will be drawn
	- animation uses a Finite State Machine to determine which animation to do at any given moment
]]

--[[
LEAVE EMPTY
this function is a callback that is called every frame by the Player_UpdateAnimation() function.
this callback will have a "Player_AnimStateXxx" function assigned to it based on the player's current
animation state
]]
local function Player_Animate()
end

--[[
this function is called every frame. it does/calls all the functions that calculate everything to do with
player animation
]]
local function Player_UpdateAnimation()
	Player_Animate()

	player_animTime = player_animTime + love.timer.getDelta()
end

--[[
ANIMATION STATE
this function represents the idle (standing) state and is called when it is assigned to the Player_Animate()
function.
as a state function it does two things:
	(1) do some logic specific to the state it represents
	(2) determine the next state (and transition to it)
]]
function Player_AnimStateIdle()
	-- do some logic
	player_animIndex = IndexLoopedAnimation(player_animTime, player_animSPF, #player_animIdle)
	player_sprite = player_animIdle[player_animIndex]

	-- determine next state
	if player_dx ~= 0 then
		Player_SetAnimation(Player_AnimStateWalk)
	end
end

--[[
ANIMATION STATE
this function represents the walking state (left or right, doesn't matter) and is called when it is assigned to
the Player_Animate() function.
as a state function it does two things:
	(1) do some logic specific to the state it represents
	(2) determine the next state (and transition to it)
]]
function Player_AnimStateWalk()
	-- do some logic
	player_animIndex = IndexLoopedAnimation(player_animTime, player_animSPF, #player_animWalk)
	player_sprite = player_animWalk[player_animIndex]

	-- determine next state
	if player_dx == 0 then
		Player_SetAnimation(Player_AnimStateIdle)
	end
end

--[[
ANIMATION STATE
this function represents the jumping state and is called when it is assigned to the Player_Animate() function.
as a state function it does two things:
	(1) do some logic specific to the state it represents
	(2) determine the next state (and transition to it)
]]
function Player_AnimStateJump()
	-- do some logic
	-- determine next state
end

--[[
ANIMATION STATE
this function represents the falling state and is called when it is assigned to the Player_Animate() function.
as a state function it does two things:
	(1) do some logic specific to the state it represents
	(2) determine the next state (and transition to it)
]]
function Player_AnimStateFall()
	-- do some logic
	-- determine next state
end

--[[
ANIMATION STATE
this function represents the attacking state and is called when it is assigned to the Player_Animate() function.
]]
function Player_AnimStateAttack()
	-- do some logic
	-- determine next state
end

--[[
this function resets the animation variables. it will work no matter the current animation state. it should
only be called inside of the Player_SetAnimation() function
]]
function Player_ResetAnimation()
	player_animIndex = 1
	player_animTime = 0
end

--[[
this function is used to set the next animation state and should only be called by a Player_AnimStateXxx function.
]]
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

--[[
the initialization function, called at the beginning of the game
]]
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

	player_x = (3 - 1) -- world position x
	player_y = (13 - 1) -- world position y
	player_facing = 1 -- 1=right, -1=left

	player_screenX = nil -- screen position x
	player_screenY = nil -- screen position y
	Player_UpdateScreenPos()

	player_dx = 0 -- delta x, since there's no horizontal acceleration
	player_yVel = 0 -- y-velocity, since there is vertical acceleration
	player_width = 1  -- width in number of tiles
	player_height = 1  -- height in number of tiles

	Player_Animate = Player_AnimStateIdle
	player_animFPS = 6
	player_animSPF = 1 / player_animFPS
	player_animTime = 0
end

--[[
the update function. contains all the behaviors of the player
]]
function UpdatePlayer(_dt)
	Player_ReadInputs(_dt)

	Player_CheckCollision() -- check for collision with other objects

	Player_ReceiveCollision() -- react to other objects colliding with it

	Player_Move(_dt)

	Player_UpdateAnimation()

	Player_UpdateLandmarks()
end

--[[
the draw function. contains all the logic involved in rendering the player
]]
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
