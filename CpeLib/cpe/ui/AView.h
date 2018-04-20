#pragma once

#include <cstdint>
#include <vector>
#include <type_traits>

#include "cpe/core/Exception.h"
#include "cpe/core/Color.h"
#include "IElement.h"
#include "ConsoleApp.h"
#include "IController.h"

namespace cpe::ui {

using namespace cpe;

template<class TController>
class AView {
public:
    AView() = delete;

    explicit AView(const ConsoleApp &app);

    TController &getController();

protected:
    virtual void onCreate(std::vector<IElement> &elements) = 0;

private:
    const ConsoleApp &mApp;
    TController mCtrlr;
    std::vector<IElement> mElements;

    class OutChar {
    public:
        char symbol = 0;
        cpe::Color foreColor;
        cpe::Color backColor;
    };

    using OutCharList = std::vector<OutChar>;
    using OutLineList = std::vector<OutCharList>;

    OutLineList mLines;

    void initController();

    void onClose();

    void show();
};

template<class TController>
void AView<TController>::onCreate(std::vector<IElement> &elements) {
    // VOID
}

template<class TController>
AView<TController>::AView(const ConsoleApp &app) : mApp(app) {

}

template<class TController>
TController &AView<TController>::getController() {
    return mCtrlr;
}

template<class TController>
void AView<TController>::onClose() {

}

template<class TController>
void AView<TController>::initController() {
    if (!std::is_same<TController, IController>::value)
        throw cpe::Exception("");

    // TODO передать onClose с корректным static_cast'ом
}

template<class TController>
void AView<TController>::show() {
    onCreate(mElements);
}

}