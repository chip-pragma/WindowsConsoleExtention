#include "BaseOutput.h"

namespace cpe::ui {

BaseOutput::BaseOutput() :
        _outFormat() {

}

const OutputFormat &BaseOutput::getOutputFormat() const {
    return _outFormat;
}

void BaseOutput::setOutputFormat(const OutputFormat &outFormat) {
    _outFormat = outFormat;
}
}