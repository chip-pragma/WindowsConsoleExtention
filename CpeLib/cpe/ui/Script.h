#pragma once

#include <functional>

#include "ACommand.h"
#include "Buffer.h"

namespace cpe {

namespace {

class IScriptItem {
public:
    virtual ~IScriptItem() {

    }

    virtual ACommand *_command() = 0;
};

}

//#region [ prototype ]

template<class TC, class TP>
class ScriptItem;

template<class TP>
class Script;

//#endregion

//# region [ declaration ]

template<class TP>
class Script {

public:
    explicit Script();

    ~Script();

    TP *processor() const;

    template<class TC>
    ScriptItem<TC, TP> *add();

    void run() const;

private:
    TP *mProcessor;
    std::vector<IScriptItem *> mItemList;
};

template<class TC, class TP>
class ScriptItem : private IScriptItem {

    friend class Script<TP>;

public:
    ~ScriptItem() override {
        delete mItem;
    }

    ScriptItem<TC, TP> *bind() {
        std::function<TC *(const ScriptItem<TC, TP> *)> fifa = &ScriptItem<TC, TP>::item;
        return this;
    }

    TC *item() const {
        return mItem;
    }

private:
    ScriptItem() : mItem(new TC()) {}

    ACommand *_command() override {
        return dynamic_cast<ACommand *>(mItem);
    }

    TC *mItem;
};

//#endregion

//#region [ difinition ]

template<class TP>
Script<TP>::Script() {
    static_assert(
            std::is_base_of<AProcessor, TP>::value,
            "'AProcessor' is not base for template-param 'TP'");

    mProcessor = new TP();
}

template<class TP>
Script<TP>::~Script() {
    for (auto item : mItemList)
        delete item;
    delete mProcessor;
}

template<class TP>
void Script<TP>::run() const {
    for (IScriptItem *com : mItemList) {
        com->_command()->run();
    }
}

template<class TP>
TP *Script<TP>::processor() const {
    return mProcessor;
}

template<class TP>
template<class TC>
ScriptItem<TC, TP> *Script<TP>::add() {
    static_assert(
            std::is_base_of<ACommand, TC>::value,
            "'ACommand' is not base for template-param 'TC'");

    auto *item = new ScriptItem<TC, TP>();
    mItemList.push_back(static_cast<IScriptItem *>(item));
    return item;
}

//#endregion

}

