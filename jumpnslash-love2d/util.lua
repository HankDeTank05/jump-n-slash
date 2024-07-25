
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