#pragma once

#include <vector>

#include "cpe/macros.h"
#include "ReaderInterface.h"

namespace cpe {

class ReaderManager {
public:
    ~ReaderManager();

    template <class TReader>
    TReader& addReader();

    void runRead(ConsoleApplication &app, ObserverInterface &observer);
private:
    std::vector<ReaderInterface*> mReaders;
};

template<class TReader>
TReader &ReaderManager::addReader() {
    CPE_MACROS_StaticCheckBaseClass(ReaderInterface, TReader);

    auto elem = new TReader();
    mReaders.push_back(elem);
    return *elem;
}

}