pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

-- designer controls

--------------------
-- player options --
--------------------
-- 0 = ⬅️ = left arrow key
-- 1 = ➡️ = right arrow key
-- 2 = ⬆️ = up arrow key
-- 3 = ⬇️ = down arrow key
-- 4 = 🅾️ = z key on keyboard
-- 5 = ❎ = x key on keyboard
controls = {
    walk_left = 0,
    walk_right = 1,
    jump = 4,
    attack = 5,
}

p1_jump_velocity = -4 -- the jump velocity
-- this must always be a negative number (does not need to be an integer)
-- this velocity is applied as long as the player is holding the jump button

p1_gravity = 0.2 -- vertical acceleration per frame
-- this must always be a positive number (does not need to be an integer)
-- gravity is only applied after the player releases the jump button or after they've held the jump button for the max amount of time

p1_max_jump_frames = 15 -- the max number of frames a player can hold jump for
-- this must always be a positive integer
-- assume 60fps (30 = half second, 15 = quarter second, etc.)

p1_walk_speed = 1 -- horizontal movement speed
-- this must always be a positive integer
-- pixels per frame
-- screen res is 128x128
-- assume 60fps

p1_attack_frames = 10 -- number of frames that attack hitbox is active for
-- this must always be a positive integer
-- assume 60fps

p1_max_health = 1 -- amount of damage required to kill the player
-- this must always be a positive integer

-------------------
-- sword options --
-------------------
sword_damage_per_swing = 1 -- CURRENTLY DOES NOTHING!!

-------------------
-- enemy options --
-------------------
enemy_walk_speed = 1 -- horizontal movement speed
-- this must always be a positive integer
-- pixels per frame
-- screen res is 128x128
-- assume 60fps

enemy_base_health = 1 -- CURRENTLY DOES NOTHING!!

-----------------------
-- breakable options --
-----------------------
breakable_durability = 1 -- the amount of damage required to break the block
-- this must always be a positive integer