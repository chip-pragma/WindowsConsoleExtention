#include <iostream>
#include <vector>
#include <cmath>

#include "cpe/core/Encoder.h"
#include "cpe/core/Terminal.h"
#include "cpe/core/Exception.h"
#include "cpe/ui/Buffer.h"
#include "cpe/ui/BufferManip.h"
#include "cpe/ui/AController.h"
#include "cpe/ui/AElement.h"
#include "cpe/ui/AScript.h"

// DECLARATION
namespace test {

class ControllerImpl : public cpe::AController {
public:

    void addState(const std::string &state) {
        mStateText += "=> " + state;
    }

    const std::string &getStateText() const {
        return mStateText;
    }

    void preprocess() override {
        addState("PREprocess");
    }

    void postprocess() override {
        addState("POSTprocess");
    }

private:
    std::string mStateText = "Start";
};

class ElementImpl : public cpe::AElement {
private:
    using PFuncAddState = void (ControllerImpl::*)(const std::string &);

public:
    ElementImpl &bind(PFuncAddState func) {
        mFunc = static_cast<PFuncAddState>(func);
        return *this;
    }

    void run(cpe::AController &ctrlr, cpe::Buffer &buf) override {
//        static_assert(
//                std::is_base_of<ControllerImpl, typeof(ctrlr)>::value,
//                "'ControllerImpl' is not base for 'TController'");

        try {
            auto &correctCtrl = dynamic_cast<ControllerImpl &>(ctrlr);
            if (mFunc)
                (correctCtrl.*mFunc)(mState);
        }
        catch (std::bad_cast &e) {

        }


    }

    const std::string &getState() const {
        return mState;
    }

    ElementImpl &setStateText(const std::string &state) {
        mState = state;
        return *this;
    }

protected:
    std::string mState;

private:
    PFuncAddState mFunc = nullptr;
};

class ViewImpl : public cpe::AScript<ControllerImpl> {
public:
    ViewImpl() : AScript() {

    }

protected:
    void initialize(cpe::ElementList &elemList) override {
        auto elem1 = new ElementImpl();
        elem1->bind(&ControllerImpl::addState);
        elem1->setStateText("[element 1]");

        auto elem2 = new ElementImpl();
        elem2->bind(&ControllerImpl::addState);
        elem2->setStateText("[element 2]");

        elemList << elem1 << elem2;
    }
};

}

namespace {

cpe::Encoder<cpe::Encoding::UTF8> encUtf8;
cpe::Encoder<cpe::Encoding::CP866> encCp866;

std::string encode(const std::string &src) {
    return encCp866.to(encUtf8.from(src));
}

}

int main() {
    cpe::term::setTitle(L"Текст консоли");
    cpe::term::setForeColor(cpe::Colors::WHITE);
    cpe::term::setBackColor(cpe::Colors::BLACK);

    std::cout << encode("Кодировка вывода: ") << cpe::term::getWriterCp() << "\n";
    std::cout << encode("Кодировка ввода: ") << cpe::term::getWriterCp() << std::endl;
    std::cout << encode("\u255F");

    // TODO реализация MVC (подобие)

//    test::ViewImpl view;
//    auto ctrl = view.controller();
//    ctrl.preprocess();
//    ctrl.addState("One more state");
//    view.run();
//    ctrl.postprocess();

//    std::cout << ctrl.getStateText() << std::endl;

    cpe::term::pause();

    try {
        cpe::WriterFormat wf;
        wf.setTabLength(5);
        wf.setUnfinished("~");

        cpe::Buffer buf3;
        buf3.setFormat(wf);
        buf3.setWidth(15);
        buf3.setHeight(3);
        buf3 << cpe::Colors::LT_TEAL
             << encode("Это мини буфер номер 3.\nДолжен поместиться в пятиклеточное поле.");

        cpe::Buffer buf2;
        buf2.setFormat(wf);
        buf2 << cpe::Colors::LT_YELLOW
             << encode("Проверка вывода под-2-буфера: ")
             << buf3
             << cpe::Colors::LT_YELLOW
             << encode("\nЭто второй вывод с таб-отступом:\t")
             << buf3
             << cpe::bg
             << cpe::Colors::GREEN
             << "\n"
             << encode("Вроде все.");

        cpe::Buffer buf1;
        buf1.setFormat(wf);
        buf1 << cpe::Colors::LT_RED
             << encode("Проверка перехода на новую строку (автоматический и ручной):\n")
             << cpe::Colors::LT_GREEN
             << encode("Выполнено\n") << cpe::unset
             << cpe::Colors::LT_RED
             << cpe::bg
             << cpe::Colors::RED
             << encode("Проверка сброса цвета:\n")
             << cpe::unset
             << encode("Фон - ")
             << cpe::fg
             << cpe::Colors::LT_GREEN
             << encode("Выполнено\n") << cpe::unset
             << cpe::bg
             << cpe::unset
             << encode("Текст - ")
             << cpe::fg
             << cpe::Colors::LT_GREEN
             << encode("Выполнено\n") << cpe::unset
             << cpe::Colors::LT_RED
             << encode("Проверка подбуфера: ")
             << buf2
             << buf3
             << "\n"
             << cpe::Colors::LT_RED
             << encode("Проверка табуляции:\n")
             << cpe::unset
             << encode("1\t22\t333\t4444\t55555\t666666\t7777777\t\n")
             << cpe::Colors::LT_GREEN
             << encode("Выполнено") << cpe::unset
             << "\n"
             << cpe::flush;
    }
    catch (std::exception &e) {
        std::cout << e.what();
    }

    cpe::term::pause();

    return 0;
}
