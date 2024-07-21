require("constants")
require("player")

function love.load()
	-- set up the display
	love.window.setMode(SCREEN_WIDTH * SCREEN_SCALE, SCREEN_HEIGHT * SCREEN_SCALE)
	love.graphics.setDefaultFilter("linear", "nearest")

	-- load game
	init_player()
end

function love.update(_dt)
	update_player(_dt)
end

function love.draw()
	love.graphics.print("hello world", 64, 64)
	draw_player()
end