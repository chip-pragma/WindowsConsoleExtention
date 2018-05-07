#include "ReaderManager.h"

namespace cpe {

ReaderManager::~ReaderManager() {
    for (auto reader : mReaders)
        delete reader;
    mReaders.clear();
}

void ReaderManager::runRead(ConsoleApplication &app, ObserverInterface &observer) {
    for (auto reader : mReaders)
        reader->runRead(app, observer);
}

}


