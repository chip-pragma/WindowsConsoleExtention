#pragma once

#include <utility>
#include <vector>
#include <unordered_map>

#include "Enums.h"

namespace cpe::ui {

class Console;

class Menu
{
	friend class Console;

public:
	Menu();
	Menu(std::string caption, Color captionColor, Color sideColor);
	~Menu();

	/**
	 * Добавить пункт меню
	 * @param itemName Наименование пункта
	 * @param text Текст пункта
	 * @param foreColor Цвет пункта
	 */
	void add_item(std::string itemName, std::string text, Color foreColor = Color::COLOR_DEFAULT);
	/**
	 * Добавить разделитель
	 */
	void add_separator();

	/**
	 * Цвет заголовка
	 * @param color Цвет
	 */
	void caption_color(Color color);
	// �������� ���� ��������� � �����
	Color caption_color() const;
	// ������ ���� �����
	void side_color(Color color);
	// �������� ���� �����
	Color side_color() const;
	// ������ ���������
	void caption(std::string capt);
	// �������� ���������
	std::string caption() const;
	// ������ ������������ �������� ������
	void using_last(bool value = true);
	// �������� ������������ �������� ������
	bool using_last() const;

	// ������� ������ ������ ����
	bool operator[] (std::string itemName);

private:
	// ����� ����
	class _MItem
	{
	public:
		_MItem(bool s, int i, std::string t, Color c) :
			isSpecial(s),
			index(i),
			text(std::move(t)),
			foreColor(c)
		{
		}

		// ����������� ����� (�����������, ��������� � �.�.)
		bool isSpecial;
		// ������
		int index = 0;
		// ����� ������ ����
		std::string text;
		// ���� ������
		Color foreColor;
	};
	friend class _MItem;

	// ������ ����
	std::vector<std::pair<std::string, _MItem*>> _items;
	// ���-�� �� ����������� �������
	int _nNospec;
	// ��������� ����
	std::string _caption;
	// ���� ��������� � ����� 
	Color _captionColor;
	// ���� �����
	Color _sideColor;	
	// ������������ �������� ������
	bool _usingLast;

	// ����� ������ ����
	std::string* _choice;
	// ������� �� �������
	bool _choose(int i);
};

}

