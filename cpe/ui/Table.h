#pragma once

#include <core/Console.h>
#include "core/Color.h"
#include <ui/style/TableBorder.h>
#include <ui/style/DualBorder.h>

#include <string>
#include <map>
#include <vector>


namespace {
typedef cpe::core::Color Color_;
typedef cpe::ui::style::DualBorder DualBorder_;
typedef cpe::ui::style::TableBorder TableBorder_;
}

namespace cpe::ui {

class Table
{
	friend class Console;

public:
	Table(int maxCellLines = 1,
		  int maxHeaderLines = 1,
          Color_ headerColor = Color_::DEFAULT,
          Color_ sideColor = Color_::DK_GRAY,
          TableBorder_ displayedSide = TableBorder_::NONE,
          DualBorder_ sideStyle = DualBorder_::NONE);
	~Table();

	// �������� �������
	void add_column(std::string name, std::string caption, int size = 1);
	// �������� ������ ������
	void add_row();
	// ��������� ������ ��������� ������
	void set_cell(std::string columnName, std::string text, Color_ foreColor = Color_::DEFAULT);

	// �������� ������� (�����)
	std::vector<std::string> get_columns() const;
	// ���-�� �����
	int get_rows_count() const;

private:
	// �������
	class _TColumn
	{
	public:
		// ��������� �����
		std::string caption;
		// ������������� ������ ��� ����������
		int size;
	};
	friend class _TColumn;
	// ������
	class _TCell
	{
	public:
		// �����
		std::string text;
		// ���� ������
        Color_ foreColor;
	};
	friend class _TCell;
	// ������
	class _TRow
	{
	public:
		// ������
		std::map<std::string, _TCell*> cells;
	};
	friend class _TRow;

	// ����. ���-�� ����� � ������
	int _maxCellLines;
	// ����. ���-�� ����� � �����
	int _maxHeaderLines;
	// �������
	std::vector<std::pair<std::string, _TColumn*>> _cols;
	// ������
	std::vector<_TRow*> _rows;
	// ���� �����
    Color_ _sideColor;
	// ���� ���������
    Color_ _headerColor;
	// ������������ �����
    TableBorder_ _displayedSide;
	// ����� �����
    DualBorder_ _sideStyle;

	// ����� ������ � �������� ������
	std::vector<std::pair<std::string, _TColumn*>>::iterator _find_column(std::string name);
};

}