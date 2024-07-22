
function game_set_starting_state()
	game_set_state_play()
end

------------------------------
-- game state: title screen --
------------------------------

function game_set_state_title()
	update_state = state_title_update
	draw_state = state_title_draw
end

function state_title_update(_dt)
end

function state_title_draw()
end

----------------------
-- game state: play --
----------------------

function game_set_state_play()
	update_state = state_play_update
	draw_state = state_play_draw
end

function state_play_update(_dt)
	update_player(_dt)
	-- update sword
	-- update enemies
	-- update breakables
	-- update map
end

function state_play_draw()
	love.graphics.print("hello world", 64, 64)

	draw_map()
	-- draw enemies
	draw_player()
	-- draw sword
end

-----------------------
-- game state: pause --
-----------------------

function game_set_state_pause()
	update_state = state_pause_update
	draw_state = state_pause_draw
end

function state_pause_update(_dt)
end

function state_pause_draw()
end

---------------------------
-- game state: game over --
---------------------------

function game_set_state_gameover()
	update_state = state_gameover_update
	draw_state = state_gameover_draw
end

function state_gameover_update(_dt)
end

function state_gameover_draw()
end