#include "Console.h"

namespace cpe::core::console {

void pause() {
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
    return (bool)SetConsoleCP(codePage);
}

bool setOutputCp(uint32_t codePage) {
    return (bool)SetConsoleOutputCP(codePage);
}

uint32_t getInputCp() {
    return GetConsoleCP();
}

uint32_t getOutputCp() {
    return GetConsoleOutputCP();
}

}