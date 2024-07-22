require("constants")
require("player")
require("map")
require("game_states")

function love.load()
	-- set up the display
	love.window.setMode(SCREEN_WIDTH * SCREEN_SCALE, SCREEN_HEIGHT * SCREEN_SCALE)
	love.graphics.setDefaultFilter("linear", "nearest")

	-- load game
	init_map()
	init_player()
	-- init sword
	-- init enemies
	-- init breakables

	game_set_starting_state()
end

function update_state(_dt)
end

function draw_state()
end

function love.update(_dt)
	update_state(_dt)
end

function love.draw()
	draw_state()
end