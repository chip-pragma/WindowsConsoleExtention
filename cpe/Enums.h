#pragma once

namespace cpe {

typedef unsigned char Flags;

// ����� �������
enum Color : Flags
{
	COLOR_DEFAULT = 255,
	COLOR_BLACK = 0,
	COLOR_DK_BLUE = 1,
	COLOR_DK_GREEN = 2,
	COLOR_DK_TEAL = 3,
	COLOR_DK_RED = 4,
	COLOR_DK_PINK = 5,
	COLOR_DK_YELLOW = 6,
	COLOR_GRAY = 7,
	COLOR_DK_GRAY = 8,
	COLOR_BLUE = 9,
	COLOR_GREEN = 10,
	COLOR_TEAL = 11,
	COLOR_RED = 12,
	COLOR_PINK = 13,
	COLOR_YELLOW = 14,
	COLOR_WHITE = 15
};

// ������� �������
enum DoubleSide : Flags
{
	DSIDE_NONE = 0,
	DSIDE_LEFT = 1,
	DSIDE_RIGHT = 2,
	DSIDE_TOP = 4,
	DSIDE_BOTTOM = 8,
	DSIDE_OUTER = 15,
	DSIDE_VERTICAL = 16,
	DSIDE_HORIZONTAL = 32,
	DSIDE_LEFT_RIGHT = 3,
	DSIDE_TOP_BOTTOM = 12,
	DSIDE_INNER = 48,
	DSIDE_ALL = 63
};

// ����� ����� �������
enum TableSide : Flags
{
	TSIDE_NONE = 0,
	TSIDE_VERTICAL = 1,
	TSIDE_HORIZONTAL = 2,
	TSIDE_OUTER = 4,
	TSIDE_INNER = 3,
	TSIDE_ALL = 7
};

}