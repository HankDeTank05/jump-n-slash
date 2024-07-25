
--------------------
-- player options --
--------------------

-- see https://love2d.org/wiki/KeyConstant for what each key is called
p1_controls = {
	walk_left = "left",
	walk_right = "right",
	jump = "z",
	attack = "x",
}

p1_jump_velocity = -1.75 -- the jump velocity
-- this must always be a negative number (does not need to be an integer)
-- this velocity is applied as long as the player is holding the jump button

p1_gravity = 0.2 -- vertical acceleration per frame
-- this must always be a positive number (does not need to be an integer)
-- gravity is only applied after the player releases the jump button or after they've held the jump button for the max amount of time

p1_max_jump_secs = 0.25 -- the max number of seconds a player can hold jump for
-- this must always be a positive number (does not need to be an integer)

p1_walk_speed = 10 -- horizontal movement speed
-- this must always be a positive number (does not need to be an integer)

p1_attack_secs = 0.167 -- number of seconds that attack hitbox is active for
-- this must always be a positive number (does not need to be an integer)

p1_max_health = 1 -- amount of damage required to kill the player
-- this must always be a positive integer
