require("util")

local map_tileArray
local map_rooms
local map_tiles
local map_tileProps -- properties
local map_tileLookupByID
local map_tileLookupByName

-------------------
-- sanity checks --
-------------------

--[[
make sure a given room number is a valid index
this is just a manual index-out-of-bounds check
]]
function Map_ValidateRoomNumber(_roomNum)
	assert(1 <= _roomNum)
	assert(_roomNum <= #map_rooms)
end

--[[
make sure a given x/y position on the tile grid has valid indices
this is just a manual index-out-of-bounds check on two indices for a 2D array
]]
function Map_ValidateIndices(_tileX, _tileY)
	assert(_tileX % 1 == 0) -- if triggered, tile x-index is not an int
	assert(_tileY % 1 == 0) -- if triggered, tile y-index is not an int

	assert(1 <= _tileY) -- if triggered, tile y-index is too low
	io.write(#map_tileArray .. "\n")
	assert(_tileY <= #map_tileArray) -- if triggered, tile y-index is too high

	assert(1 <= _tileX) -- if triggered, tile x-index is too low
	assert(_tileX <= #map_tileArray[_tileY]) -- if triggered, tile x-index is too high
end

--[[
MIGHT GET RID OF THIS FUNCTION
]]
function Map_ValidateCoordinates(_posX, _posY)
	assert(1 <= _posY) -- if triggered, y-position is above the map
	assert(_posY < #map_tileArray + 1) -- if triggered, y-position is below the map

	assert(1 <= _posX) -- if triggered, x-position is outside the left bounds of the map
	assert(_posX < #map_tileArray[math.floor(_posY)] + 1) -- if triggered, x-position is outside the right bounds of the map
end

----------------------
-- mutators/setters --
----------------------

--[[
used to set the current room based on room number
]]
function Map_SetCurrentRoom(_roomNum)
	Map_VallidateRoomNumber(_roomNum)
end

--[[
this function automatically determines which room should be the current room based on player position
]]
function Map_ChangeRooms()
	-- do some logic based on player position
	-- call Map_SetCurrentRoom()
end

-----------------------
-- accessors/getters --
-----------------------

function Map_GetCurrentRoom()
end

function Map_GetCurrentRoomNum()
end

--[[
returns the x-position of the left edge of the current room (in world space)
]]
function Map_GetCurrentLeftBounds()
end

--[[
returns the x-position of the right edge of the current room (in world space)
]]
function Map_GetCurrentRightBounds()
end

--[[
returns the y-position of the top edge of the current room (in world space)
]]
function Map_GetCurrentTopBounds()
end

--[[
returns the y-position of the top edge of the current room (in world space)
]]
function Map_GetCurrentBottomBounds()
end

-- formerly known as "get_scrollability_horizontal()"
--[[
returns true or false based on whether the room at the given room number has horizontal scrolling
]]
function Map_IsHorizontalScrolling()
end

-- formerly known as "get_scrollability_vertical()"
--[[
returns true or false based on whether the room at the given room number has vertical scrolling
]]
function Map_IsVerticalScrolling()
end

--[[
get the left-x boundary of the camera when horizontal scrolling is available
]]
function Map_GetScrollLeftBounds()
end

--[[
get the right-x boundary of the camera when horizontal scrolling is available
]]
function Map_GetScrollRightBounds()
end

--[[
get the top-y boundary of the camera when vertical scrolling is available
]]
function Map_GetScrollTopBounds()
end

--[[
get the bottom-y boundary of the camera when vertical scrolling is available
]]
function Map_GetScrollBottomBounds()
end

-- formerly known as "get_current_map_x()"
--[[
get the x-index of the top-left tile in the current room
]]
function Map_GetCurrentRoomOriginX()
end

-- formerly known as "get_current_map_y()"
--[[
get the y-index of the top-left tile in the current room
]]
function Map_GetCurrentRoomOriginY()
end

-- formerly known as "check_for_flag_at_pix(_map_pix_x, _map_pix_y, _flag)"
--[[
get the properties of a tile at a given world position
]]
function Map_CheckForFlagAtWorldPos(_world_x, _world_y, _flag)
end

--[[
returns true or false based on whether the tile at the given x/y index is solid on top.
"can it be landed on?"
]]
function Map_IsTileSolidTop(_tileX, _tileY)
	-- _tileX: x-index of the tile to get the solidTop property of
	-- _tileY: y-index of the tile to get the solidTop property of
	io.write(_tileX .. " " .. _tileY .. "\n")
	Map_ValidateIndices(_tileX, _tileY)
	local idFromMap = map_tileArray[_tileY][_tileX]
	for y = 1, #map_tileArray do
		io.write(y .. ": ")
		for x = 1, #map_tileArray[y] do
			io.write(map_tileArray[y][x] .. " ")
		end
		io.write("\n")
	end
	io.write("idFromMap=" .. idFromMap .. "\n")
	local idLookupResult = map_tileLookupByID[idFromMap]
	io.write(idLookupResult .. "\n")
	local property = map_tileProps[idLookupResult].solidTop
	io.write(property .. "\n")
	return property
end

--[[
returns true or false based on whether the tile at the given x/y index is solid on the sides.
"will it prevent horizontal movement?"
]]
function Map_IsTileSolidSide(_tileX, _tileY)
	-- _tileX: x-index of the tile to get the solidSide property of
	-- _tileY: y-index of the tile to get the solidSide property of
	Map_ValidateIndices(_tileX, _tileY)
	return map_tileProps[map_tileLookupByID[map_tileArray[_tileY][_tileX]]].solidSide
end

--[[
returns true or false based on whether the tile at the given x/y index is solid on the underside
"will I hit my head if it's above me when I jump?"
]]
function Map_IsTileSolidBottom(_tileX, _tileY)
	-- _tileX: x-index of the tile to get the solidBottom property of
	-- _tileY: y-index of the tile to get the solidBottom property of
	Map_ValidateIndices(_tileX, _tileY)
	return map_tileProps[map_tileLookupByID[map_tileArray[_tileY][_tileX]]].solidBottom
end

--[[
returns true or false based on whether the tile at the given x/y index is breakable with a sword slash
"will it break when I slash it with my sword?"
]]
function Map_IsTileBreakable(_tileX, _tileY)
	-- _tileX: x-index of the tile to get the breakable property of
	-- _tileY: y-index of the tile to get the breakable property of
	Map_ValidateIndices(_tileX, _tileY)
	return map_tileProps[map_tileLookupByID[map_tileArray[_tileY][_tileX]]].breakable
end

-- formerly known as "get_room_from_pixel(_pixel_x, _pixel_y)"
--[[
returns the room number the given coordinates are in. returns nil if the coordinates are not in any room.
]]
function Map_GetRoomFromWorldPos(_world_x, _world_y)
end

--[[
returns the number of the room containing the tile at the given x/y indices
]]
function Map_GetRoomFromTile(_tileX, _tileY)
	assert(#map_rooms > 0)
	assert(_tileX % 1 == 0) -- replace with a sanity check function
	assert(_tileY % 1 == 0) -- ^^^ what he said ^^^
	for i = 1, #map_rooms do
		local room = map_rooms[i]
		if room.x <= _tileX and _tileX <= room.x + room.w - 1 and room.y <= _tileY and _tileY <= room.y + room.h - 1 then
			return i
		end
	end
	return nil
end

--------------------
-- core functions --
--------------------

--[[
called by the InitMap function at the beginning of the game
]]
local function AddRoom(_mapX, _mapY, _tileWidth, _tileHeight, _startX, _startY, _startFacing)
	if _startX == nil or _startY == nil or _startFacing == nil then -- if one of them is nil, all of them should be
		assert(_startX == nil)
		assert(_startY == nil)
		assert(_startFacing == nil)
	else
		assert(_mapX <= _startX and _startX <= _mapX + _tileWidth - 1) -- if triggered, your spawn point is outside the room (along the x-axis)
		assert(_mapY <= _startY and _startY <= _mapY + _tileHeight - 1) -- if triggered, your spawn point is outside the room (along the y-axis)
		assert(_startFacing == 1 or _startFacing == -1) -- how tf did you trigger this one?
	end

	local room = {
		x = _mapX,
		y = _mapY,
		w = _tileWidth,
		h = _tileHeight,
		startX = _startX,
		startY = _startY,
		startFacing = _startFacing,
	}
	table.insert(map_rooms, room)
	io.write("created a room at (" .. room.x .. ", " ..	room.y .. "), " .. room.w .. " tiles tall and " .. room.h .. " tiles wide")
	if _startX ~= nil then
		io.write(" with a spawn point ")
	end
	io.write("\n")
end

--[[
the initialization function. called at the beginning of the game
]]
function InitMap()

	local jsonData = ReadJsonFile("tools/formatting_rules.json")

	assert(jsonData.editorInfo ~= nil) -- make sure the data in the editorInfo section exists
	assert(jsonData.editorInfo.encodeTiles ~= nil) -- make sure the tile encoding table exists
	
	assert(jsonData.gameInfo ~= nil) -- make sure the data in the gameInfo section exists
	assert(jsonData.gameInfo.tileReadPath ~= nil) -- make sure the tile read path exists
	assert(#jsonData.gameInfo.tileReadPath > 0) -- make sure the tile read path isn't an empty string
	assert(jsonData.gameInfo.levelReadPath ~= nil) -- make sure the level read path exists
	assert(#jsonData.gameInfo.levelReadPath > 0) -- make sure the level read path isn't an empty string
	assert(jsonData.gameInfo.decodeTiles ~= nil) -- make sure the tile decoding table exists

	assert(jsonData.genericInfo ~= nil) -- make sure the genericInfo section exists
	assert(jsonData.genericInfo.tileSize ~= nil) -- make sure the tile size exists
	assert(jsonData.genericInfo.tileSize > 0) -- make sure the tile size is a positive number
	assert(jsonData.genericInfo.tileFileExt ~= nil) -- make sure the tile file extension exists
	assert(#jsonData.genericInfo.tileFileExt > 1) -- make sure the tile file extension is an actual extension

	-- load all the sprites
	local tilePath = jsonData.gameInfo.tileReadPath .. "/"
	local suffix = "_" .. jsonData.genericInfo.tileSize .. jsonData.genericInfo.tileFileExt
	--io.write("suffix = " .. suffix .. "\n")
	--io.write(#suffix .. "\n")
	local tileIDs = {}
	local tileFileNames = {}
	for k, _ in pairs(jsonData.gameInfo.decodeTiles) do
		table.insert(tileIDs, k)
	end
	-- tiles are not necessarily in sorted order by tileID, so we need to sort them
	-- lets do bubble sort cuz this function doesn't have to be optimal XD
	local sorted = false
	while not sorted do
		-- check if it's sorted or not
		sorted = true
		for i = 2, #tileIDs do
			if tonumber(tileIDs[i-1]) >= tonumber(tileIDs[i]) then
				sorted = false
				local temp = tileIDs[i-1]
				tileIDs[i-1] = tileIDs[i]
				tileIDs[i] = temp
			end
		end
	end

	map_tileLookupByID = {}
	map_tileLookupByName = {}
	for i = 1, #tileIDs do
		local fileName = jsonData.gameInfo.decodeTiles[tileIDs[i]]
		table.insert(tileFileNames, fileName)
		local tileName = string.sub(fileName, 1, -#suffix - 1)
		--io.write("tile name: " .. tileName .. "\n")
		map_tileLookupByID[tonumber(tileIDs[i])] = tileName
		map_tileLookupByName[tileName] = tonumber(tileIDs[i])
	end
	--PrintTable(map_tileLookupByID)

	map_tiles = {}
	map_tileProps = {}

	-- initialize tiles with undefined properties
	for i = 1, #tileFileNames do
		table.insert(map_tiles, love.graphics.newImage(tilePath .. tileFileNames[i]))
	end

	map_tileProps["block_breakable"] = {
		solidTop = true,
		solidSide = true,
		solidBottom = true,
		breakable = true,
	}

	map_tileProps["block_hazard"] = {
		solidTop = true,
		solidSide = true,
		solidBottom = true,
		breakable = false,
	}

	map_tileProps["block_solid"] = {
		solidTop = true,
		solidSide = true,
		solidBottom = true,
		breakable = false,
	}

	map_tileProps["platform_semisolid"] = {
		solidTop = true,
		solidSide = false,
		solidBottom = false,
		breakable = false,
	}

	-- populate the tileArray table
	map_tileArray = {}
	local levelPath = jsonData.gameInfo.levelReadPath .. "/"
	local levelFileName = "test.txt"
	local textLines = ReadTxtFile(levelPath .. levelFileName)
	local tileIDPattern = "%d%d"
	for y = 1, #textLines do
		local line = textLines[y]
		table.insert(map_tileArray, {})
		for tileID in string.gmatch(line, tileIDPattern) do
			--io.write(tileID .. " ")
			table.insert(map_tileArray[y], tonumber(tileID))
		end
		--io.write("\n")
	end
	--[[
	for y = 1, #map_tileArray do
		for x = 1, #map_tileArray[y] do
			io.write(map_tileArray[y][x] .. " ")
		end
		io.write("\n")
	end
	--]]

	map_rooms = {}
	-- populate the map_rooms array
	local processing = true
	local startingRoomIndex = nil
	local roomOriginID = map_tileLookupByName["indicator_room_origin"]
	local startRoomOriginID = map_tileLookupByName["indicator_room_origin_start"]
	local roomWidthID = map_tileLookupByName["indicator_room_width"]
	local roomHeightID = map_tileLookupByName["indicator_room_height"]
	local currentX = 1
	local currentY = 1
	while processing do
		local nextX = nil
		local nextY = nil
		-- search for room origin tiles
		local currentID = map_tileArray[currentY][currentX]
		--io.write("current ID = " .. currentID .. "\n")
		if currentID == roomOriginID or currentID == startRoomOriginID then
			-- search for width indicator
			local iSearch = currentX
			local foundWidth = false
			while iSearch < #map_tileArray[currentY] and not foundWidth do
				iSearch = iSearch + 1
				local searchID = map_tileArray[currentY][iSearch]
				local foundSomethingElse = searchID == roomOriginID or searchID == startRoomOriginID or searchID == roomHeightID
				assert(foundSomethingElse == false) -- if triggered, some other indicator is in between the origin and the width indicators, or you forgot your width indicator
				foundWidth = searchID == roomWidthID
				nextX = iSearch
			end
			assert(iSearch <= #map_tileArray[currentY]) -- if triggered, no width indicator was found between the origin indicator and the right edge of the map

			iSearch = currentY
			local foundHeight = false
			while iSearch < #map_tileArray and not foundHeight do
				iSearch = iSearch + 1
				local searchID = map_tileArray[iSearch][currentX]
				local foundSomethingElse = searchID == roomOriginID or searchID == startRoomOriginID or searchID == roomWidthID
				assert(foundSomethingElse == false) -- if triggered, some other indicator is in between the origin and the height indicators, or you forgot your height indicator
				foundHeight = searchID == roomHeightID
				nextY = iSearch
			end
			assert(iSearch <= #map_tileArray) -- if triggered, no height indicator was found between the origin indicator and the bottom edge of the map

			assert(foundWidth and foundHeight)

			local width = nextX - (currentX - 1)
			local height = nextY - (currentY - 1)

			local startX = nil
			local startY = nil
			local startFacing = nil

			local spawnLeft = map_tileLookupByName["indicator_spawn_player_left"]
			local spawnRight = map_tileLookupByName["indicator_spawn_player_right"]
			-- search for a player spawn indicator
			for y = currentY, currentY + height - 1 do
				for x = currentX, currentX + width - 1 do
					local spawnID = map_tileArray[y][x]
					if spawnID == spawnLeft or spawnID == spawnRight then
						startX = x
						startY = y
						if spawnID == spawnLeft then
							startFacing = -1
						else
							startFacing = 1
						end
					end
				end
			end

			if currentID == startRoomOriginID then
				assert(startingRoomIndex == nil) -- if triggered, you have more than one starting room origin indcator in your level
				startingRoomIndex = #map_rooms + 1

				assert(startX ~= nil and startY ~= nil and startFacing ~= nil) -- if triggered, you have no spawn point in your starting room
			end
			AddRoom(currentX, currentY, width, height, startX, startY, startFacing)

			io.write("\n")
		end
		while Map_GetRoomFromTile(currentX, currentY) ~= nil do
			currentX = currentX + 1
		end
		if currentX > #map_tileArray[currentY] then
			currentX = 1
			while Map_GetRoomFromTile(currentX, currentY) ~= nil do
				currentY = currentY + 1
			end
			if currentY > #map_tileArray then
				processing = false
			end
		end
	end
	assert(startingRoomIndex ~= nil)
end

--[[
the update function. contains all the behaviors of the map
]]
function UpdateMap(_dt)
end

--[[
the draw function. contains all the logic involved in rendering the map
]]
function DrawMap()
	for y = 1, #map_tileArray do
		for x = 1, #map_tileArray[y] do
			local tileIndex = map_tileArray[y][x]
			if tileIndex > 0 then
				local tile = map_tiles[tileIndex]
				local drawX = (x - 1) * TILE_SIZE
				local drawY = (y - 1) * TILE_SIZE
				love.graphics.draw(tile, drawX, drawY)

				-- debug stuff
				if true then
					love.graphics.points(drawX, drawY)
				end
			end
		end
	end
end
