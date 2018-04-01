#pragma once

#include <_old/Console.h>
#include "ui/style/Color.h"
#include <ui/style/TableBorder.h>
#include <ui/style/DualBorder.h>

#include <string>
#include <map>
#include <vector>

namespace cpe::ui {

enum class Color;
enum class DualBorder;
enum class TableBorder;

// TODO Обновить логику. Вывод из метода с параметром Console.
class Table
{
	friend class Console;

public:
	explicit Table(int maxCellLines = 1,
                   int maxHeaderLines = 1,
                   const Color &headerColor,
                   const Color &sideColor,
                   const TableBorder &displayedSide,
                   const DualBorder &sideStyle);
	~Table();

	// �������� �������
	void add_column(std::string name, std::string caption, int size = 1);
	// �������� ������ ������
	void add_row();
	// ��������� ������ ��������� ������
	void set_cell(std::string columnName, std::string text, const Color &foreColor);

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
        extern Color foreColor;
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
    extern Color _sideColor;
	// ���� ���������
    extern Color _headerColor;
	// ������������ �����
    extern TableBorder _displayedSide;
	// ����� �����
    extern DualBorder _sideStyle;

	// ����� ������ � �������� ������
	std::vector<std::pair<std::string, _TColumn*>>::iterator _find_column(std::string name);
};

}