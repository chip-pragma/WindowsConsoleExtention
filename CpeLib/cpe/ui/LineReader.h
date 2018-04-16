#pragma once

#include <string>
#include <iostream>

#include "cpe/core/io/AReader.h"
#include "AView.h"

namespace cpe::ui {

class LineReader : public cpe::core::io::AReader<std::string>,
                   public AView {
public:

    std::string read() const override;

    void run() override;
};

}

