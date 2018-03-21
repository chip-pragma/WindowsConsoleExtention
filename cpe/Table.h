#pragma once

#include <string>
#include <map>
#include <vector>

#include "Enums.h"

namespace cpe {

class Table
{
	friend class Console;

public:
	Table(int maxCellLines = 1, 
		  int maxHeaderLines = 1, 
		  Color headerColor = cpe::COLOR_DEFAULT,
		  Color sideColor = cpe::COLOR_DK_GRAY,
		  Flags displayedSide = cpe::TSIDE_NONE,
		  Flags sideStyle = cpe::DSIDE_NONE);
	~Table();

	// �������� �������
	void add_column(std::string name, std::string caption, int size = 1);
	// �������� ������ ������
	void add_row();
	// ��������� ������ ��������� ������
	void set_cell(std::string columnName, std::string text, Color foreColor = cpe::COLOR_DEFAULT);

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
		Color foreColor;
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
	Color _sideColor;
	// ���� ���������
	Color _headerColor;
	// ������������ �����
	Flags _displayedSide;
	// ����� �����
	Flags _sideStyle;

	// ����� ������ � �������� ������
	std::vector<std::pair<std::string, _TColumn*>>::iterator _find_column(std::string name);
};

}