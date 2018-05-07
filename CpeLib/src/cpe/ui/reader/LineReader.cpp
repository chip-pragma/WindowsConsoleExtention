#include "LineReader.h"
#include "cpe/tool/text.h"
#include "cpe/ui/ControllerAbstract.h"



namespace cpe {

void LineReader::runRead(ConsoleApplication &app, ControllerAbstract &ctrl) {
    propGetFromProvider(value, ctrl);
    propGetFromProvider(hint, ctrl);
    propGetFromProvider(hintStyle, ctrl);
    propGetFromProvider(readStyle, ctrl);

    auto hintFull = hint();
    text::replace(hintFull, HINT_VALUE_PARAM, value());


    app.getOut();
}
}



