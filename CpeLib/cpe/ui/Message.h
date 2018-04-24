#pragma once

#include <string>

#include "ACommand.h"

namespace cpe {

// TODO подумать над биндингом данных. Можно сделать 2 класса BindingFrom<ResultType> И BindingTo<ResultType>
class Message : public ACommand {
public:
    const std::string &getCaption() const;

    Message *setCaption(const std::string &caption);

    const std::string &getText() const;

    Message *setText(const std::string &text);

    void run() override;

protected:
    std::string mCaption;
    std::string mText;
};


}




