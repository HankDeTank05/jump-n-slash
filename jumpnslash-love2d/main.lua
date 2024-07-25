require("constants")
require("player")
require("map")
require("game_states")

function love.load()
	-- set up the display
	love.window.setMode(SCREEN_WIDTH * SCREEN_SCALE, SCREEN_HEIGHT * SCREEN_SCALE)
	love.graphics.setDefaultFilter("linear", "nearest")

	-- load game
	InitMap()
	InitPlayer()
	-- init sword
	-- init enemies
	-- init breakables

	Game_SetStartingState()
end

function UpdateState(_dt)
end

function DrawState()
end

function love.update(_dt)
	UpdateState(_dt)
end

function love.draw()
	love.graphics.scale(SCREEN_SCALE)
	DrawState()
end