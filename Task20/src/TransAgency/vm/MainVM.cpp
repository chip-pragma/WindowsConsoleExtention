#include "MainVM.h"

#include "TransAgency/common.h"

#include <iostream>
#include <cpe/core/terminal.h>

bool MainVM::main_menu_result(cpe::ReaderResult<uint32_t> &result) {
    bool exit = false;
    if (result.type() == cpe::ReaderResultType::VALUE) {
        std::string str;
        switch (result.value()) {
            case ID_MM_CARS:
                str = "Транспорт! (корректно)"_dos;
                break;
            case ID_MM_CLIENTS:
                str = "Клиенты! (корректно)"_dos;
                break;
            case ID_MM_RENT:
                str = "Аренда! (корректно)"_dos;
                break;
            case ID_MM_EXIT:
                str = "Выход?.. (корректно)"_dos;
                exit = true;
                break;
            default:
                str = "Пункт меню не определен. В ридере обшибка!"_dos;
                break;
        }
        std::cout << "VALUE: " << str;
        if (exit)
            return true;
    } else if (result.type() == cpe::ReaderResultType::COMMAND) {
        if (result.command() == "check") {
            std::cout << "COMMAND: проверка!.."_dos;
        } else {
            std::cout << "COMMAND: не определена (корректно)"_dos;
        }
    } else if (result.type() == cpe::ReaderResultType::CONVERT_FAIL) {
        std::cout << "CONVERT_FAIL: не определен пункт меню!"_dos;
    }
    cpe::term::pause();
    return false;
}
