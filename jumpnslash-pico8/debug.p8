pico-8 cartridge // http://www.pico-8.com
version 42
__lua__

-- debug master flag (prints a message to indicate the game has been restarted)
debug_all = true

-- debug options for player
debug_player_draw = false

debug_position = false
debug_horizontal_collision = false
debug_vertical_collision = true
debug_landmarks = false
debug_player_room_transition = false
debug_attacking = false
debug_player_death = false
debug_player_animation_state = false

-- debug options for rooms
debug_room_draw = false

debug_room_number = false
debug_room_creation = false
debug_room_switching = false
debug_scroll_bounds = false

-- debug options for enemies
debug_enemy_draw = true

debug_enemy_creation = true
debug_ai = true
debug_enemy_movement = false
debug_enemy_animation = true
debug_enemy_screen_pos = false

-- debug options for breakables
debug_breakable_creation = true
debug_breakable_destruction = true

-- debug options for collision
debug_generic_collision = false
debug_player_collision = false
debug_sword_collision = false
debug_enemy_collision = false
debug_breakable_collision = true