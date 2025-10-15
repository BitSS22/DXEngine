#pragma once

struct IntVector2
{
public:
	IntVector2() = default;
	IntVector2(int _x, int _y)
		: x(_x)
		, y(_y) {}
	~IntVector2() = default;

public:
	int x = {};
	int y = {};

public:
	IntVector2 operator+ (IntVector2 _Other) const noexcept
	{
		return IntVector2(x + _Other.x, y + _Other.y);
	}
	IntVector2 operator- (IntVector2 _Other) const noexcept
	{
		return IntVector2(x - _Other.x, y - _Other.y);
	}

};
