
function GetJudgeLabelY(rowNumber)
	if (IsRidiculousTimingEnabled()) then
		return 13 * rowNumber
	else
		return 16 * (rowNumber - 1)
	end
end

function GetJudgeRidiculousLabelY(rowNumber)
	if (IsRidiculousTimingEnabled()) then
		return 13 * rowNumber
	else
		return -9000
	end
end

function GetJudgeLabelZoom()
	if (IsRidiculousTimingEnabled()) then
		return "zoom,0.45;"
	else
		return "zoom,0.5;"
	end
end
