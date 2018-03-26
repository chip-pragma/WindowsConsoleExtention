#include "Table.h"

#include <utility>

namespace cpe::ui {

Table::Table(int maxCellLines,
             int maxHeaderLines,
             const Color &headerColor,
             const Color &sideColor,
             const TableBorder &displayedSide,
             const DualBorder &sideStyle)
{
	_maxCellLines = maxCellLines;
	_maxHeaderLines = maxHeaderLines;
	_sideColor = sideColor;
	_displayedSide = displayedSide;
	_sideStyle = sideStyle;
	_headerColor = headerColor;
}

Table::~Table()
{
	// �������
	for (auto &_col : _cols) {
		delete _col.second;
	}

	// ������ � ������
	for (auto row : _rows) {
		for (auto &cell : row->cells) {
			delete cell.second;
		}

		delete row;
	}
}



void Table::add_column(std::string name, std::string caption, int size)
{
	if (!_rows.empty())
		throw std::exception();

	auto column = new _TColumn();
	column->caption = std::move(caption);
	column->size = size < 1 ? 1 : size;
	_cols.emplace_back(name, column);
}

void Table::add_row()
{
	if (_cols.empty()) return;

	auto row = new _TRow();
	for (auto &_col : _cols) {
		auto cell = new _TCell();
		cell->text = "";
		cell->foreColor = cpe::COLOR_DEFAULT;
		row->cells.insert(std::pair<std::string, _TCell*>(_col.first, cell));

	}
	_rows.push_back(row);
}

void Table::set_cell(std::string columnName, std::string text, const Color &foreColor)
{
	auto column = _find_column(std::move(columnName));
	if (column == _cols.end())
		throw std::exception();
	if (_rows.empty())
		throw std::exception();

	auto row = *(_rows.end() - 1);
	row->cells[column->first]->text = std::move(text);
	row->cells[column->first]->foreColor = foreColor;
}



std::vector<std::string> Table::get_columns() const
{
	std::vector<std::string> cols; 

	for (const auto &_col : _cols) {
		cols.push_back(_col.first);
	}

	return cols;
}

int Table::get_rows_count() const
{
	return _rows.size();
}

std::vector<std::pair<std::string, Table::_TColumn*>>::iterator Table::_find_column(std::string name)
{
	for (auto it = _cols.begin();
		 it != _cols.end();
		 it++)
	{
		if (it->first == name)
			return it;
	}
	return _cols.end();
}


}