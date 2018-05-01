project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 17)

add_library(${CPE_LIB_TARGET} STATIC
            src/cpe/utils/Text.cpp
            src/cpe/utils/Text.h
            src/cpe/core/terminal.cpp
            src/cpe/core/terminal.h
            src/cpe/ui/WriterFormat.cpp
            src/cpe/ui/WriterFormat.h
            src/cpe/utils/Encoder.cpp
            src/cpe/utils/Encoder.h
            src/cpe/core/Point.cpp
            src/cpe/core/Point.h
            src/cpe/platform.h
            src/cpe/core/Color.cpp
            src/cpe/core/Color.cpp
            src/cpe/core/Color.h src/cpe/_platform/winapi.cpp src/cpe/_platform/winapi.h src/cpe/core/Exception.cpp src/cpe/core/Exception.h src/cpe/ui/element/reader/LineReader.cpp src/cpe/ui/element/reader/LineReader.h src/cpe/ui/Buffer.cpp src/cpe/ui/Buffer.h src/cpe/ui/ControllerAbstract.h src/cpe/ui/element/ElementAbstract.h src/cpe/ui/BufferManip.cpp src/cpe/ui/BufferManip.h src/cpe/ui/property/PropertyProviderAbstract.h src/cpe/ui/property/PropertyInterface.h src/cpe/macros.h src/cpe/ui/style/DualBorder.h.cpp src/cpe/ui/property/PropertyAbstract.cpp src/cpe/ui/property/PropertyAbstract.h src/cpe/ui/property/PropertyReadInterface.h src/cpe/ui/property/PropertyWriteInterface.h src/cpe/ui/property/Property.cpp src/cpe/ui/property/Property.h src/cpe/ui/property/PropertyException.cpp src/cpe/ui/property/PropertyException.h src/cpe/ui/property/PropertyObserverInterface.cpp src/cpe/ui/property/PropertyObserverInterface.h src/cpe/ui/element/ElementAbstract.cpp src/cpe/ui/property/PropertyProviderAbstract.cpp src/cpe/ui/ViewAbstract.cpp src/cpe/ui/ViewAbstract.h src/cpe/ui/property/PropertyObservableAbstract.cpp src/cpe/ui/property/PropertyObservableAbstract.h src/cpe/ui/ViewInterface.h src/cpe/ui/element/reader/ReaderAbstract.cpp src/cpe/ui/element/reader/ReaderAbstract.h)

target_include_directories(${CPE_LIB_TARGET} PUBLIC src)
set_target_properties(${CPE_LIB_TARGET} PROPERTIES
                      OUTPUT_NAME "Cpe"
                      VERSION 0.1.0
                      SOVERSION 0)