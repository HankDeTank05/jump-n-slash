
function IndexLoopedAnimation(_animTime, _animSPF, _numFrames)
	return (math.floor(_animTime / _animSPF) % _numFrames) + 1
end

function CheckRectangleOverlap(_rect1X, _rect1Y, _rect1Width, _rect1Height, _rect2X, _rect2Y, _rect2Width, _rect2Height)
	assert(_rect1Width > 0)
	assert(_rect1Height > 0)
	assert(_rect2Width > 0)
	assert(_rect2Height > 0)

	if _rect1X == _rect2X and _rect1Y == _rect2Y then
		-- case 1: the rectangles occupy the same position
		return true
	else
		-- general case
		local rect1LeftX = _rect1X
		local rect1RightX = _rect1X + _rect1Width
		local rect1TopY = _rect1Y
		local rect1BottomY = _rect1Y + _rect1Height

		local rect2LeftX = _rect2X
		local rect2RightX = _rect2X + _rect2Width
		local rect2TopY = _rect2Y
		local rect2BottomY = _rect2Y + _rect2Height

		-- check if the left edge of rect2 overlaps rect1 (on the x-axis)
		local overlapXLeft = rect1LeftX <= rect2LeftX and rect2LeftX <= rect1RightX
		-- check if the right edge of rect2 overlaps rect1 (on the x-axis)
		local overlapXRight = rect1LeftX <= rect2RightX and rect2RightX <= rect1RightX

		-- determine if there was any overlap on x-axis at all
		local overlapOnX = overlapXLeft or overlapXRight

		-- check if the top edge of rect2 overlaps rect1 (on the y-axis)
		local overlapYTop = rect1TopY <= rect2TopY and rect2TopY <= rect1BottomY
		-- check if the bottom edge of rect2 overlaps rect1 (on the y-axis)
		local overlapYBottom = rect1TopY <= rect2BottomY and rect2BottomY <= rect1BottomY

		-- determine if there was any overlap on y-axis at all
		local overlapOnY = overlapYTop or overlapYBottom

		return overlapOnX and overlapOnY
	end
end

function CheckPointInRectangle(_pointX, _pointY, _rectX, _rectY, _rectWidth, _rectHeight)
	assert(_rectWidth > 0)
	assert(_rectHeight > 0)

	local rectLeftX = _rectX
	local rectRightX = _rectX + _rectWidth

	local containedX = rectLeftX <= _pointX and _pointX <= rectRightX

	local rectTopY = _rectY
	local rectBottomY = _rectY + _rectHeight

	local containedY = rectTopY <= _rectY and _rectY <= rectBottomY

	return containedX and containedY
end

-- pattern matching in lua
-- https://www.lua.org/manual/5.3/manual.html#6.4.1

local function ReadJsonLine(_line)
end

function ReadJsonFile(_filePath)
	local jsonLines = {}
	local jsonData = {}

	local keyStack = {}
	-- push with table.insert(keyStack, key)
	-- pop with table.remove(keyStack)

	for line in love.filesystem.lines(_filePath) do
		table.insert(jsonLines, line)
		io.write(line)
		io.write("\n")
	end

	-- define string patterns
	local indentPattern = "%s+"
	local keyPattern = "\"%g+\""
	local valPattern = ": %g+"
	local sublistEndPattern = "}[,]?"

	-- don't need to deal with the first and last lines
	assert(jsonLines[1] == "{")
	table.remove(jsonLines, 1) -- remove the first line
	assert(jsonLines[#jsonLines] == "}")
	table.remove(jsonLines) -- remove the last line
	
	local tableStack = {}   -- keep track of the parent tables when we create subtables
	local currentSubtable = jsonData

	-- parse the json for data
	for i = 1, #jsonLines do
		local line = jsonLines[i]

		if string.match(line, "{") ~= nil then
			-- begin a new subtable

			-- find the key first
			local key = string.match(line, keyPattern)
			assert(key ~= nil)
			--io.write("starting a new subtable with the following key: " .. key .. "\n")

			-- create the subtable with the key
			currentSubtable[key] = {}
			table.insert(tableStack, currentSubtable)
			currentSubtable = currentSubtable[key]
			--io.write("tableStack size = " .. #tableStack .. "\n")

		elseif string.match(line, "}") ~= nil then
			-- return to the parent table
			--io.write("returning to the parent table\n")
			assert(#tableStack > 0)
			currentSubtable = table.remove(tableStack)

		else
			assert(currentSubtable ~= nil)
			-- deal with key/value pairs
			
			local key = string.match(line, keyPattern)
			assert(key ~= nil)

			local val = string.match(line, valPattern)
			assert(val ~= nil)

			currentSubtable[key] = val

		end
	end

	PrintTable(jsonData)
end

function PrintTable(_table, _indent)
	if _indent == nil then _indent = 0 end

	for k, v in pairs(_table) do
		-- indent your shit properly
		for t = 1, _indent do
			io.write("\t")
		end

		if type(v) == "table" then
			io.write(k .. " = (table)\n")
			PrintTable(v, _indent + 1)
		else
			io.write(k .. " = " .. v .. "\n")
		end
	end
end

function ReadTxtFile(_filePath)
end