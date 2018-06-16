#include "console.h"
#include "Exception.h"
#include "wce/tool/text.h"
#include "wce/tool/Convert.h"

#include <cstdlib>

#include <windows.h>

namespace wce::console {

namespace {

inline Point _toPoint(const COORD &coord) {
    return Point(coord.X, coord.Y);
}

inline COORD _fromPoint(const Point &point) {
    return COORD{
        .X = static_cast<SHORT>(point.x),
        .Y = static_cast<SHORT>(point.y)
    };
}

inline Color _toColor(COLORREF ref) {
    Color color;
    color.red = static_cast<uint8_t>(ref & 255);
    color.green = static_cast<uint8_t>((ref >> 8) & 255);
    color.blue = static_cast<uint8_t>((ref >> 16) & 255);
    return color;
}

inline COLORREF _fromColor(Color color) {
    COLORREF ref = (color.blue << 16) | (color.green << 8) | (color.red);
    return ref;
}

inline HANDLE _getOutputHandle() noexcept {
    return ::GetStdHandle(STD_OUTPUT_HANDLE);
}

inline HANDLE _getInputHandle() noexcept {
    return ::GetStdHandle(STD_INPUT_HANDLE);
}

inline CONSOLE_SCREEN_BUFFER_INFOEX _getBufferInfo() noexcept {
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    info.cbSize = 96;
    GetConsoleScreenBufferInfoEx(_getOutputHandle(), &info);
    return info;
}

inline bool _setBufferInfo(CONSOLE_SCREEN_BUFFER_INFOEX &info) {
    return static_cast<bool>(
        SetConsoleScreenBufferInfoEx(_getOutputHandle(), &info));
}

}

void waitAnyKey() {
    system("pause");
}

void clear() {
    system("cls");
}

void setTitle(const std::string &title) {
    SetConsoleTitleA(title.c_str());
}

std::string getTitle() {
    char title[MAX_PATH];
    GetConsoleTitleA(title, MAX_PATH);
    return std::string(title);
}

bool setInputCp(uint32_t codePage) {
    return (bool) SetConsoleCP(codePage);
}

bool setOutputCp(uint32_t codePage) {
    return (bool) SetConsoleOutputCP(codePage);
}

uint32_t getInputCp() {
    return GetConsoleCP();
}

uint32_t getOutputCp() {
    return GetConsoleOutputCP();
}

bool setBufferSize(const Point &size) {
    if (size.getLocation() != Point::PL_SECTOR_I)
        throw Exception("Invalid width");

    return static_cast<bool>(
        SetConsoleScreenBufferSize(_getOutputHandle(), _fromPoint(size)));
}

Point getBufferSize() {
    auto info = _getBufferInfo();
    return _toPoint(info.dwSize);
}

bool setCursorPos(const Point &point) {
    return static_cast<bool>(
        SetConsoleCursorPosition(_getOutputHandle(), _fromPoint(point)));

}

Point getCursorPos() {
    auto info = _getBufferInfo();
    return _toPoint(info.dwCursorPosition);
}

bool setColorTable(const ColorTable &table) {
    auto info = _getBufferInfo();
    for (int i = 0; i < 16; i++)
        info.ColorTable[i] = _fromColor(table.getColor(i));
    return _setBufferInfo(info);
}

ColorTable getColorTable() {
    ColorTable table;
    auto info = _getBufferInfo();
    for (int i = 0; i < 16; i++)
        table.setColor(i, _toColor(info.ColorTable[i]));
    return table;
}

bool resetColorTable() {
    ColorTable table;
    table.setColor(WceStdColors::cBlack, Color(0, 0, 0));
    table.setColor(WceStdColors::cRed, Color(200, 0, 0));
    table.setColor(WceStdColors::cGreen, Color(78, 154, 6));
    table.setColor(WceStdColors::cYellow, Color(196, 160, 0));
    table.setColor(WceStdColors::cBlue, Color(52, 101, 164));
    table.setColor(WceStdColors::cPurple, Color(117, 80, 123));
    table.setColor(WceStdColors::cTeal, Color(6, 152, 154));
    table.setColor(WceStdColors::cGrayLt, Color(211, 215, 207));
    table.setColor(WceStdColors::cGray, Color(85, 87, 83));
    table.setColor(WceStdColors::cRedLt, Color(239, 41, 41));
    table.setColor(WceStdColors::cGreenLt, Color(138, 226, 52));
    table.setColor(WceStdColors::cYellowLt, Color(252, 233, 79));
    table.setColor(WceStdColors::cBlueLt, Color(114, 159, 207));
    table.setColor(WceStdColors::cPurpleLt, Color(173, 127, 168));
    table.setColor(WceStdColors::cTealLt, Color(52, 226, 226));
    table.setColor(WceStdColors::cWhite, Color(238, 238, 236));
    return setColorTable(table);
}

bool setForeground(const ColorIndex &color) {
    auto info = _getBufferInfo();
    auto attr = (info.wAttributes & ~uint16_t(15)) | color.get();
    return static_cast<bool>(
        SetConsoleTextAttribute(_getOutputHandle(), attr));
}

ColorIndex getForeground() {
    auto info = _getBufferInfo();
    return ColorIndex(static_cast<uint8_t>(info.wAttributes & 15));
}

bool setBackground(const ColorIndex &color) {
    auto info = _getBufferInfo();
    auto attr = (info.wAttributes & ~uint16_t(15 << 4)) | (color.get() << 4);
    return (bool) SetConsoleTextAttribute(_getOutputHandle(), attr);
}

ColorIndex getBackground() {
    auto info = _getBufferInfo();
    return ColorIndex(static_cast<uint8_t>(info.wAttributes & (15 << 4)) >> 4);
}

}