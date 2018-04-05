#pragma once

namespace cpe::ui {

class BaseReader {
protected:
    virtual void receiveSymbol(char symbol) = 0;
    virtual void receiveCommand(char command) = 0;

    void read();

    void endRead();

private:
    bool _endRead;
};

}
