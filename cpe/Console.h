#pragma once

#include <string>
#include <vector>
#include <Windows.h>

#include "Enums.h"

namespace cpe {


class Menu;
class Table;

/**
 * Класс-обертка для удобной работы с I/O консоли
 */
class Console
{
public:
	Console();
	~Console();

	/**
	 * Вывод строки
	 * @param str Выводимая строка
	 */
	void write(std::string str);
	/**
	 * Вывод строки и перевод курсора на новую строку
	 * @param str Выводимая строка
	 * @param nls Кол-во переходов на новую строку
	 */
	void write_line(std::string str, int nls = 1);
	/**
	 * Перевод курсора на новую строку
	 * @param nls Кол-во переходов на новую строку
	 */
	void write_line(int nls = 1);

	/**
	 * Получение строки с потока ввода
	 * @param inValue Указатель на объект, принимаемый значение ввода
	 * @param required Обязателен для ввода
	 * @return Результат ввода
	 */
	bool read_line(std::string* inValue, 
				   bool required = true);
	/**
	 * Получение числа с потока ввода
	 * @param inValue Указатель на объект, принимаемый значение ввода
	 * @param error Сообщение об ошибке при некорректном вводе
	 * @param required Обязателен для ввода
	 * @return Результат ввода
	 */
	bool read_int(int* inValue,
				  std::string error = "",
				  bool required = true);
	/**
	 * Получение числа с потока ввода с учетом указанного диапазона
	 * @param inValue Указатель для записи значения
	 * @param min Минимальное (включенное) значение диапазона
	 * @param max Максимальное (включенное) значение диапазона
	 * @param error Сообщение об ошибке ввода
	 * @param required Обязателен для ввода
	 * @return Результат ввода
	 */
	bool read_int_range(int* inValue,
						int min, 
						int max,
						std::string error = "",
						bool required = true);
	/**
	 * Получение времени (ЧЧ:ММ:СС) с потока ввода
	 * @param inTime Указатель для записи значения
	 * @param seconds Вводить секунды?
	 * @param error Сообщение об ошибке ввода
	 * @param required Обязателен для ввода
	 * @return Результат ввода
	 */
	bool read_time(time_t* inTime,
				   bool seconds,
				   std::string error = "",
				   bool required = true);
	/**
	 * Получение даты () с потока ввода
	 * @param inDate Указатель для записи значения
	 * @param error Сообщение об ошибке ввода
	 * @param required Обязателен для ввода
	 * @return Результат ввода
	 */
	bool read_date(time_t* inDate,
				   std::string error = "",
				   bool required = true);

	/**
	 * Вывод сообщения в рамке и с заголовком с пунктами выбора действий
	 * @param message Текст основного сообщения
	 * @param caption Текст заголовка
	 * @param iconSym Символ "иконки"
	 * @param menuItems Пункты выбора действия
	 * @param captionColor Цвет заголовка
	 * @param iconColor Цвет иконки
	 * @param sideColor Цвет рамки
	 * @param dSide Стиль рамки
	 * @param padding Добавить отступы между текстом и рамкой?
	 * @return Номер введеного пункт
	 */
	int message_box(std::string message,
					std::string caption,
					char iconSym,
					std::string menuItems,
					Color captionColor = Color::COLOR_DEFAULT,
					Color iconColor = Color::COLOR_DEFAULT,
					Color sideColor = Color::COLOR_DK_GRAY,
					int dSide = DoubleSide::DSIDE_NONE,
					bool padding = true);
	// ����� � ������� ����� ��� ��������
	void notification(std::string message,
					  Color sideColor = Color::COLOR_DK_GRAY,
					  int dSide = DoubleSide::DSIDE_NONE);
	// ��������� ����
	void write_menu(Menu* const menu);
	// ������� �������������� �������
	void write_table(Table* table);

	// ���������� �� ������� anykey
	void pause();
	// ������� ������
	void clear();
	// ������� <parts> ���������� ����������
	void clear(int parts);
	// �������� ���� ������
	void reset_fore_color();
	// ��������� ������� �������
	void part_new();
	// ����� ������� �����
	int part() const;

	// ������ ���� ������
	void fore_color(Color color);
	// �������� ���� ������
	Color fore_color() const;
	// ������ ���� �� �����.
	void default_fore_color(Color color);
	// �������� ���� �� �����.
	Color default_fore_color() const;
	// ������ ������� ���������
	void cp_input(int codePage);
	// �������� ������� ���������
	int cp_input() const;
	// ������ �������� ���������
	void cp_output(int codePage);
	// �������� �������� ���������
	int cp_output() const;
	// ������ ������������� �����
	void unfinished(std::string value);
	// �������� ������������� �����
	std::string unfinished() const;
	// ������ ������ ���������
	void tab_size(int size);
	// �������� ������ ���������
	int tab_size() const;
	// ������ ���������
	void title(std::string);
	// �������� ���������
	std::string title() const;

	// �������� ����� � �������
	std::vector<std::string> layout(
		std::string src, 
		int width, 
		int* maxWidth,
		int height = 0,
		bool fill = false) const;

	void debug(bool enabled);

private:
	// ���� ��������� ������ ������ ����������
	std::vector<COORD> _lastCursorPositions;
	// ���� ������ �������
	Color _foreColor;
	// ���� �� ���������
	Color _defaultForeColor;
	// ������� ���������
	int _cpInput;
	// �������� ���������
	int _cpOutput;
	// ������������� �����
	std::string _unfinished;
	// ������ ���������
	int _tabSize;
	// ��������� ����
	std::string _title;
	// ������� 
	bool _debug;

	// ������������� 
	std::string _encode(std::string src);
	// ������������ ������ (���� ����, ��������, �������� ��� ����� � �������)
	std::string _decode(std::string src);

	// ������ ������� �������
	void _cursor_position(COORD crd);
	// �������� ������� �������
	COORD _cursor_position() const;
	// �������� ������� �� �������� �������
	void _cursor_move(short x, short y);
	// �������� ��������� ������� ������� � ����
	void _add_last_curpos();
	// ������ ������ ���� �������
	int _buffer_width() const;

	// ������� ������� �������
	void _clear(COORD begin, COORD end);
};

}