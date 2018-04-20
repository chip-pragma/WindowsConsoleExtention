#include <iostream>
#include <vector>
#include <cmath>

#include "cpe/core/Encoder.h"
#include "cpe/core/Terminal.h"
#include "cpe/core/Exception.h"

// PROTOTYPE
namespace test {

class ConsoleApp;

class BufferSymbol;

class Buffer;

class AController;

class IElement;

template<class TController>
class AView;

}

// INTERFACES & ABSTRACTS
namespace test {

class AController {
public:
    virtual void preprocess() = 0;

    virtual void postprocess() = 0;
};

class IElement {
public:
    virtual void write(Buffer &buf) const = 0;
};

template<class TController>
class AView {
public:
    AView();

    ~AView();

    virtual TController &controller() const final;

    virtual void launch() final;

protected:

    virtual void initialize(TController &ctrl, std::vector<IElement> &elemList) = 0;

private:
    TController *mController;
    std::vector<IElement> mElementList;
    bool firstLaunch = false;
    Buffer *mBuffer;
};

}

// DECLARATION
namespace test {

class BufferSymbol {
public:
    BufferSymbol() {

    }

    explicit BufferSymbol(char c) : mChar(c) {

    }

    BufferSymbol(char aChar, cpe::Color *fore) : mFore(fore),
                                                 mChar(aChar) {

    }

    BufferSymbol(char aChar, const cpe::Color &fore, const cpe::Color &back) : mFore(new cpe::Color(fore)),
                                                                               mBack(new cpe::Color(back)),
                                                                               mChar(aChar) {

    }

    ~BufferSymbol() {
        delete mBack;
        delete mFore;
    }

    bool getForeColor(cpe::Color &color) const {
        if (mFore == nullptr)
            return false;
        color = *mFore;
        return true;
    }

    void setForeColor(const cpe::Color &fore) {
        delete mFore;
        mFore = new cpe::Color(fore);
    }

    bool getBackColor(cpe::Color &color) const {
        if (mBack == nullptr)
            return false;
        color = *mBack;
        return true;
    }

    void setBackColor(const cpe::Color &back) {
        delete mBack;
        mBack = new cpe::Color(back);
    }

    void clearForeColor() {
        delete mFore;
        mFore = nullptr;
    }

    void clearBackColor() {
        delete mBack;
        mBack = nullptr;
    }

    char get() const {
        return mChar;
    }

    operator char() {
        return mChar;
    }

    BufferSymbol &operator=(char c) {
        mChar = c;
        return *this;
    }

private:
    cpe::Color *mFore = nullptr;
    cpe::Color *mBack = nullptr;
    char mChar = ' ';
};

class Buffer {
public:

    Buffer() : mFore(cpe::term::getForeColor()),
               mBack(cpe::term::getBackColor()) {

    }

    ~Buffer() {
        clear();
    }

    const cpe::Color &getForeColor() const {
        return mFore;
    }

    void setForeColor(const cpe::Color &fore) {
        mFore = fore;
    }

    const cpe::Color &getBackColor() const {
        return mBack;
    }

    void setBackColor(const cpe::Color &back) {
        mBack = back;
    }


    void write(const std::string &str) {
        std::vector<BufferSymbol> &line = mLines.back();
        if (mLines.empty())
            line = mLines.emplace_back();

        for (char c : str) {
            if (c == '\n' || c == '\r') {
                line = mLines.emplace_back();
            } else {
                line.emplace_back(c, mFore, mBack);
            }
        }
    }

    void flush() {
        bool useAutoFlush = std::cout.flags() & std::ios_base::unitbuf;
        if (useAutoFlush)
            std::cout << std::nounitbuf;

        auto fc = mFore;
        auto bc = mBack;

        for (const auto &line : mLines) {
            std::cout << '\n';
            for (const auto &sym : line) {
                if (sym.getForeColor(mFore))
                    cpe::term::setForeColor(mFore);
                if (sym.getBackColor(mBack))
                    cpe::term::setBackColor(mBack);

                std::cout << sym.get();
            }
        }
        clear();

        std::cout.flush();
        if (useAutoFlush)
            std::cout << std::unitbuf;
    }

    void back(uint64_t count) {
        if (count <= 0)
            return;
        std::vector<BufferSymbol> line = mLines.back();
        while (true) {
            auto minCount = count < line.size() ? count : line.size();
            auto lineEnd = line.end();
            line.erase(lineEnd - minCount, lineEnd);

            if (line.empty()) {
                mLines.pop_back();
                if (mLines.empty())
                    break;
                line = mLines.back();
            }

            count -= minCount;
            if (count <= 0)
                break;
        }

    }

    void lineBack() {
        mLines.pop_back();
    }

    void clear() {
        mLines.clear();
    }

    Buffer &operator<<(const std::string &str) {
        write(str);
        return *this;
    }

private:
    std::vector<std::vector<BufferSymbol>> mLines;
    cpe::Color mFore;
    cpe::Color mBack;
};

class ControllerImpl : public AController {
public:

    void addState(const std::string &state) {
        mState += "=> " + state;
    }

    const std::string &getState() const {
        return mState;
    }

    void preprocess() override {
        addState("PREprocess");
    }

    void postprocess() override {
        addState("POSTprocess");
    }

private:
    std::string mState = "Start";
};

class ViewImpl : public AView<ControllerImpl> {
public:
    ViewImpl() : AView() {

    }

protected:
    void initialize(ControllerImpl &ctrl, std::vector<IElement> &elemList) override {

    }
};

}

// DEFINITION
namespace test {

template<class TController>
AView<TController>::AView() {
    static_assert(
            std::is_base_of<AController, TController>::value,
            "'AController' is not base for 'TController'");

    mController = new TController();
    mBuffer = new Buffer();
}

template<class TController>
AView<TController>::~AView() {
    delete mController;
    delete mBuffer;
}

template<class TController>
TController &AView<TController>::controller() const {
    return *mController;
}

template<class TController>
void AView<TController>::launch() {
    if (firstLaunch) {
        initialize(*mController, mElementList);
        firstLaunch = false;
    }

    for (const auto &elem : mElementList) {
        elem.write(*mBuffer);
    }
}

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

    std::cout << ::encode("Кодировка вывода: ") << cpe::term::getWriterCp() << "\n";
    std::cout << ::encode("Кодировка ввода: ") << cpe::term::getWriterCp() << std::endl;
    std::cout << ::encode("\u255F");

    // TODO реализация MVC

    std::string line;

    std::getline(std::cin, line);

    test::ViewImpl view;
    auto ctrl = view.controller();
    ctrl.preprocess();
    ctrl.addState("One more state");
    view.launch();
    ctrl.postprocess();

    try {
        test::Buffer buf;
        buf << encode("Пиписька!\nЭТО СТРОКА ДВА!");
        buf << encode("\n");
        buf << encode("line 3");
        buf.flush();
        buf.flush();
        buf.flush();
    }
    catch (std::exception &e) {
        std::cout << e.what();
    }


    cpe::term::pause();

    return 0;
}
