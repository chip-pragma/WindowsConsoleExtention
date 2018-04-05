

#ifndef PROJECT_IELEMENTUI_H
#define PROJECT_IELEMENTUI_H

#include <cpe/ui/style/WriterFormat.h>

namespace cpe::ui {

using namespace cpe::ui::style;

class IPrintElement {
public:
    IPrintElement() = delete;
    virtual explicit IPrintElement(IPrintElement parent) = 0;

    virtual void print() = 0;

    const WriterFormat &getPrintFormat() const {
        return _printFormat;
    }

    void setPrintFormat(const WriterFormat &printFormat) {
        _printFormat = printFormat;
    }

protected:
    WriterFormat _printFormat;
    IPrintElement _parent;

private:

};

}

#endif //PROJECT_IELEMENTUI_H
