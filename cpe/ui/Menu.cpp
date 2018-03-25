#include "Menu.h"
#include "core/Console.h"

#include <string>
#include <utility>
#include <utility>

namespace cpe::ui {

Menu::Menu() :
	_caption("Меню:"),
	_captionColor(Color::COLOR_WHITE),
	_sideColor(Color::COLOR_DK_GRAY),
	_usingLast(false),
	_nNospec(0)
{
}

Menu::Menu(std::string caption, Color captionColor, Color sideColor) :
	_caption(std::move(caption)),
	_captionColor(captionColor),
	_sideColor(sideColor),
	_usingLast(false),
	_nNospec(0)
{
}

Menu::~Menu()
{
	for (auto &_item : _items) {
		delete (_item.second);
	}
}



void Menu::add_item(std::string itemName, std::string text, Color foreColor)
{
	auto item = new _MItem(false, ++_nNospec, std::move(text), foreColor);
	_items.emplace_back(itemName, item);
}

void Menu::add_separator()
{
	auto item = new _MItem(true, 0, "separator", Color::COLOR_WHITE);
	_items.emplace_back(std::to_string(reinterpret_cast<intptr_t>(item)), item);
}




void Menu::caption_color(Color color)
{
	_captionColor = color;
}

Color Menu::caption_color() const
{
	return _captionColor;
}

void Menu::side_color(Color color)
{
	_sideColor = color;
}

Color Menu::side_color() const
{
	return _sideColor;
}

void Menu::caption(std::string capt)
{
	_caption = std::move(capt);
}

std::string Menu::caption() const
{
	return _caption;
}

void Menu::using_last(bool value)
{
	_usingLast = value;
}

bool Menu::using_last() const
{
	return _usingLast;
}



bool Menu::operator[](std::string itemName)
{
	return (_choice != nullptr && *_choice == itemName);
}

bool Menu::_choose(int i)
{

	delete _choice;
	if (!_usingLast && i == 0) return false;
	if (_usingLast && i == _nNospec) return false;

	for (auto &_item : _items) {
		// Пропуск специальных
		if (_item.second->isSpecial) continue;
		// ЕСЛИ индекс совпадает ИЛИ доступен возвращающий и индекс 0
		if ((i == _item.second->index) ||
			(i == 0 && _item.second->index == _nNospec))
		{
			_choice = new std::string(_item.first);
			return true;
		}
	}

	return false;
}

}