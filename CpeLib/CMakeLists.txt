project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 17)

add_library(${CPE_LIB_TARGET} STATIC
            src/cpe/utils/text.cpp
            src/cpe/utils/text.h
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
        src/cpe/core/Color.h src/cpe/_platform/winapi.cpp src/cpe/_platform/winapi.h src/cpe/core/Exception.cpp src/cpe/core/Exception.h src/cpe/ui/element/reader/LineReader.cpp src/cpe/ui/element/reader/LineReader.h src/cpe/ui/Buffer.cpp src/cpe/ui/Buffer.h src/cpe/ui/ControllerInterface.h src/cpe/ui/element/ElementInterface.h src/cpe/ui/BufferManip.cpp src/cpe/ui/BufferManip.h src/cpe/macros.h src/cpe/ui/style/DualBorder.h.cpp src/cpe/ui/element/ElementInterface.cpp src/cpe/ui/ViewAbstract.cpp src/cpe/ui/ViewAbstract.h src/cpe/ui/ViewInterface.h src/cpe/ui/element/reader/ReaderAbstract.cpp src/cpe/ui/element/reader/ReaderAbstract.h src/cpe/ui/ObserverInterface.h src/cpe/ui/ProviderInterface.h src/cpe/ui/ViewException.cpp src/cpe/ui/ViewException.h src/cpe/ui/WriterAbstract.cpp src/cpe/ui/WriterAbstract.h)

target_include_directories(${CPE_LIB_TARGET} PUBLIC src)
set_target_properties(${CPE_LIB_TARGET} PROPERTIES
                      OUTPUT_NAME "Cpe"
                      VERSION 0.1.0
                      SOVERSION 0)