#include "TestProcessor.h"

TestProcessor::TestProcessor() {
    propCreate(state);
}

TestProcessor::~TestProcessor() {
    destroyProperties();
}
