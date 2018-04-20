#pragma once

#include <vector>
#include <type_traits>

#include "IController.h"

namespace cpe::ui {

template<class TController>
class AView;

class ConsoleApp {
public:

private:
};

//template<class TController, class TView>
//const IController &ConsoleApp::launch(bool clear) {
//    if (!std::is_same<TController, IController>::value)
//        throw core::Exception("Тип параметра TController не является наследником IController");
//    if (!std::is_same<TView, AView<TController>>::value)
//        throw core::Exception("Тип параметра TView не является наследником AView<TController>");
//
//    if (clear)
//        core::term::clear();
//
//
//}

}




