#include "Menu.h"
#include "core/Color.h"

#include <string>
#include <utility>
#include <utility>

namespace cpe::ui {

using cpe::core::Color;

Menu::Menu() :
	_caption("Меню:"),
	_captionColor(Color::WHITE),
	_sideColor(Color::DK_GRAY),
	_usingLast(false),
	_nNospec(0)
{
}

Menu::Menu(std::string &&caption, const Color &captionColor, const Color &sideColor) :
	_caption(caption),
	_captionColor(captionColor),
	_sideColor(sideColor),
	_usingLast(false),
	_nNospec(0)
{
}

Menu::~Menu() = default
{
	for (auto &_item : _items) {
		delete (_item.second);
	}
}



void Menu::addItem(std::string &&itemName, std::string &&text, const Color &foreColor = Color::DEFAULT)
{
	auto item = new _MItem(false, ++_nNospec, std::move(text), foreColor);
	_items.emplace_back(itemName, item);
}

void Menu::addSeparator()
{
	auto item = new _MItem(true, 0, "separator", Color::WHITE);
	_items.emplace_back(std::to_string(reinterpret_cast<intptr_t>(item)), item);
}




void Menu::setCaptionColor(const Color &color)
{
	_captionColor = color;
}

Color Menu::getCaptionColor() const
{
	return _captionColor;
}

void Menu::setBorderColor(const Color &color)
{
	_sideColor = color;
}

Color Menu::getBorderColor() const
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