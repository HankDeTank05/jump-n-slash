require("map")
require("player")

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
	UpdateMap(_dt)
end

function StatePlayDraw()
	DrawMap()
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