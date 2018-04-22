#include <iostream>
#include <vector>
#include <cmath>

#include "cpe/core/Encoder.h"
#include "cpe/core/Terminal.h"
#include "cpe/core/Exception.h"
#include "cpe/ui/Buffer.h"
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
        // TODO расчет используемых ширины и высоты для буффера
        // TODO запись буфера в буфер
        // TODO передавать настройки буфера через оператор потока <<

        cpe::WriterFormat wf;
        wf.setTabLength(5);

        cpe::Buffer buf(wf, 50, 5);
        buf.setForeColor(cpe::Colors::LT_RED);
        buf << encode("Проверка перехода на новую строку (автоматический и ручной):\n");
        buf.setForeColor(cpe::Colors::LT_GREEN);
        buf << encode("Выполнено\n");

        buf.setForeColor(cpe::Colors::LT_RED);
        buf.setBackColor(cpe::Colors::RED);
        buf << encode("Проверка сброса цвета:\n");
        buf.unsetForeColor();
        buf << encode("Текст - ");
        buf.setForeColor(cpe::Colors::LT_GREEN);
        buf << encode("Выполнено\n");
        buf.unsetForeColor();
        buf.unsetBackColor();
        buf << encode("Фон - ");
        buf.setForeColor(cpe::Colors::LT_GREEN);
        buf << encode("Выполнено\n");

        buf.setForeColor(cpe::Colors::LT_RED);
        buf << encode("Проверка табуляции:\n");
        buf.unsetForeColor();
        buf << encode("1\t22\t333\t4444\t55555\t666666\t7777777\t\n");
        buf.setForeColor(cpe::Colors::LT_GREEN);
        buf << encode("Выполнено");

        buf.flush();
    }
    catch (std::exception &e) {
        std::cout << e.what();
    }

    cpe::term::pause();

    return 0;
}
