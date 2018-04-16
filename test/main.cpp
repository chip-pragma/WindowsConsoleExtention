#include <iostream>

#include "cpe/core/Encoding.h"
#include "cpe/core/Console.h"
#include "cpe/ui/LineReader.h"
#include "cpe/ui/IModel.h"

using namespace cpe::core;
using namespace cpe::ui;

namespace {

std::string encode(const std::string &src) {
    return encoding::encode(866, encoding::decode(65001, src));
}

}

class Test : public IModel {
public:
    const std::string &getValue() const {
        return mValue;
    }

    void setValue(const std::string &value) {
        mValue = value;
    }

private:
    std::string mValue;
};

int main() {
    console::setTitle(encode("Текст консоли"));
    std::cout << "CP out: " << console::getOutputCp() << std::endl;
    std::cout << "CP in: " << console::getInputCp() << std::endl << std::endl;

    console::setInputCp(866);
    console::setOutputCp(866);

    // TODO проверка ui::View



    console::pause();

    return 0;
}
