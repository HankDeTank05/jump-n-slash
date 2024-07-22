
function Game_SetStartingState()
	Game_SetStatePlay()
end

------------------------------
-- game state: title screen --
------------------------------

function Game_SetStateTitle()
	UpdateState = StateTitleUpdate
	DrawState = StateTitleDraw
end

function StateTitleUpdate(_dt)
end

function StateTitleDraw()
end

----------------------
-- game state: play --
----------------------

function Game_SetStatePlay()
	UpdateState = StatePlayUpdate
	DrawState = StatePlayDraw
end

function StatePlayUpdate(_dt)
	UpdatePlayer(_dt)
	-- update sword
	-- update enemies
	-- update breakables
	-- update map
end

function StatePlayDraw()
	love.graphics.print("hello world", 64, 64)

	draw_map()
	-- draw enemies
	DrawPlayer()
	-- draw sword
end

-----------------------
-- game state: pause --
-----------------------

function Game_SetStatePause()
	UpdateState = StatePauseUpdate
	DrawState = StatePauseDraw
end

function StatePauseUpdate(_dt)
end

function StatePauseDraw()
end

---------------------------
-- game state: game over --
---------------------------

function Game_SetStateGameover()
	UpdateState = StateGameoverUpdate
	DrawState = StateGameoverDraw
end

function StateGameoverUpdate(_dt)
end

function StateGameoverDraw()
end