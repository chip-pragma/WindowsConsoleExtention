#ifndef CONSOLEPRESENTEXTENTION_CONSOLE_H
#define CONSOLEPRESENTEXTENTION_CONSOLE_H

#include <string>
#include <vector>
#include <Windows.h>

namespace _old {

class Menu;
class Table;
enum class Color;

/**
 * Класс-обертка для удобной работы с I/O консоли
 */
class Console
{
public:
	Console();
	~Console();

	/**
	 * Выводит строку
	 * @param str Выводимая строка
	 */
	void write(std::string str);
	/**
	 * Выводит строку и перевод курсора на новую строку
	 * @param str Выводимая строка
	 * @param nls Кол-во переходов на новую строку
	 */
	void writeLine(std::string str, int nls = 1);
	/**
	 * Получает число на новую строку
	 * @param nls Кол-во переходов на новую строку
	 */
	void writeLine(int nls = 1);

	/**
	 * Получает число с потока ввода
	 * @param inValue Указатель на объект, принимаемый значение ввода
	 * @param required Обязателен для ввода
	 * @return Результат ввода
	 */
	bool readLine(std::string *inValue,
                  bool required = true);
	/**
	 * Получает число с потока ввода
	 * @param inValue Указатель на объект, принимаемый значение ввода
	 * @param error Сообщение об ошибке при некорректном вводе
	 * @param required Обязателен для ввода
	 * @return Результат ввода
	 */
	bool readInt(int *inValue,
                 std::string error = "",
                 bool required = true);
	/**
	 * Получает число с потока ввода с учетом указанного диапазона
	 * @param inValue Указатель для записи значения
	 * @param min Минимальное (включенное) значение диапазона
	 * @param max Максимальное (включенное) значение диапазона
	 * @param error Сообщение об ошибке ввода
	 * @param required Обязателен для ввода
	 * @return Результат ввода
	 */
	bool readIntRange(int *inValue,
                      int min,
                      int max,
                      std::string error = "",
                      bool required = true);
	/**
	 * Получает временя (ЧЧ:ММ:СС) с потока ввода
	 * @param inTime Указатель для записи значения
	 * @param seconds Вводить секунды?
	 * @param error Сообщение об ошибке ввода
	 * @param required Обязателен для ввода
	 * @return Результат ввода
	 */
	bool readTime(time_t *inTime,
                  bool seconds,
                  std::string error = "",
                  bool required = true);
	/**
	 * Получает дату (ДД:ММ:ГГГГ) с потока ввода
	 * @param inDate Указатель для записи значения
	 * @param error Сообщение об ошибке ввода
	 * @param required Обязателен для ввода
	 * @return Результат ввода
	 */
	bool readDate(time_t *inDate,
                  std::string error = "",
                  bool required = true);

	/**
	 * Выводит сообщение в рамке и с заголовком с пунктами выбора действий
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
	int messageBox(std::string message,
                   std::string caption,
                   char iconSym,
                   std::string menuItems,
                   const Color& captionColor,
                   const Color& iconColor,
                   const Color& sideColor,
                   int dSide,
                   bool padding = true);
	/**
	 * Упрощенное сообщение в рамке (уведомление)
	 * @param message Сообщение уведомления
	 * @param sideColor Цвет рамки
	 * @param dSide Стиль рамки
	 */
	void notification(std::string message,
					  Color sideColor = Color::COLOR_DK_GRAY,
					  int dSide = DoubleSide::DSIDE_NONE);
	/**
	 * Выводит настроенное меню
	 * @param menu Объект меню
	 */
	void writeMenu(Menu *const menu);

    /**
     * Выводит заполненную таблицу
     * @param table Объект таблицы
     */
	void writeTable(Table *table);

	/**
	 * Сбрасывает цвет текста
	 */
	void resetForeColor();
	/**
	 * Создает участок вывода
	 */
	void addOutputPart();
	/**
	 * Возвращает кол-во участков вывода
	 */
	int outputPartCount() const;

	/**
	 * Задает цвет текста
	 */
	void setForeColor(Color color);
	/**
	 * Возвращает цвет текста
	 */
	Color getForeColor() const;
	/**
	 * Задает цвет текста поумолчанию
	 */
	void setDefaultForeColor(Color color);
	/**
	 * Возвращает цвет текста поумолчанию
	 */
	Color getDefaultForeColor() const;
	/*
	 * Задает кодировку потока ввода
	 */
	void setCpInput(int codePage);
	/**
	 * Возвращает кодировку потока ввода
	 */
	int getCpInput() const;
	/**
	 * Задает кодировку потока вывода
	 */
	void setCpOutput(int codePage);
    /**
     * Возвращает кодировку потока вывода
     */
	int getCpOutput() const;
	/**
	 * Задает строку символов выводимая при незавершенном тексте
	 */
	void setUnfinished(std::string value);
    /**
     * Возвращает строку символов выводимая при незавершенном тексте
     */
	std::string getUnfinished() const;
	/**
	 * Задает длину табуляции из пробелов
	 */
	void setTabLength(int size);
    /**
     * Возвращает длину табуляции из пробелов
     */
	int getTabLength() const;

	void debug(bool enabled);

private:
	// Последняя позиция курсора
	std::vector<COORD> _lastCursorPositions;
	// Цвет теста
	extern Color _foreColor;
	// Цвет текста по умолчанию
	extern Color _defaultForeColor;
	// Кодировка потока ввода
	int _cpInput;
	// Кодировка потока вывода
	int _cpOutput;
	// Последовательность символов "незавершенности" тектса
	std::string _unfinished;
	// Размер табуляции
	int _tabSize;
	// Заголовок окна
	std::string _title;
	// Режим отладки
	bool _debug;

	// Кодирование
	std::string _encode(std::string src);
	// Декодирование
	std::string _decode(std::string src);

	// Задает позицию курсора
	void _setCursorPosition(COORD crd);
	// Возвращает позицию курсора
	COORD _getCursorPosition() const;
	// Перемещает курсор
	void _moveCursor(short x, short y);
	// Добавить последнюю позицию курсора в стек
	void _addLastCurPos();
	// Возвращает ширину буфера (в символах)
	int _getBufferWidth() const;

	// Очищает область экрана консоли в заданном прямоугольнике
	void _clear(COORD begin, COORD end);
};

}

#endif