#pragma once

#include <utility>
#include <vector>
#include <unordered_map>

namespace cpe::ui {

class Console;

enum class Color;

class Menu {
    friend class Console;

public:
    Menu();

    Menu(std::string &&caption, const Color &captionColor, const Color &sideColor);

    ~Menu();

    /**
     * Добавить пункт меню
     * @param itemName Наименование пункта
     * @param text Текст пункта
     * @param foreColor Цвет пункта
     */
    void addItem(std::string &&itemName, std::string &&text, const Color &foreColor);

    /**
     * Добавить разделитель
     */
    void addSeparator();

    /**
     * Задает цвет заголовка
     * @param color Цвет
     */
    void setCaptionColor(const Color &color);

    /**
     * Возвращает цвет заголовка
     */
    Color getCaptionColor() const;

    /**
     * Задает цвет рамки
     * @param color Цвет
     */
    void setBorderColor(const Color &color);

    /**
     * Возвращает цвет рамки
     */
    Color getBorderColor() const;

    void caption(std::string capt);

    std::string caption() const;

    void using_last(bool value);

    bool using_last() const;

    // ������� ������ ������ ����
    bool operator[](std::string itemName);

private:
    // ����� ����
    class _MItem {
    public:
        _MItem(bool s, int i, std::string t, const Color &c) :
                isSpecial(s),
                index(i),
                text(std::move(t)),
                foreColor(c) {
        }

        // ����������� ����� (�����������, ��������� � �.�.)
        bool isSpecial;
        // ������
        int index = 0;
        // ����� ������ ����
        std::string text;
        // ���� ������
        extern Color foreColor;
    };

    friend class _MItem;

    // ������ ����
    std::vector<std::pair<std::string, _MItem *>> _items;
    // ���-�� �� ����������� �������
    int _nNospec;
    // ��������� ����
    std::string _caption;
    // ���� ��������� � �����
    extern Color _captionColor;
    // ���� �����
    extern Color _sideColor;
    // ������������ �������� ������
    bool _usingLast;

    // ����� ������ ����
    std::string *_choice;

    // ������� �� �������
    bool _choose(int i);
};

}

