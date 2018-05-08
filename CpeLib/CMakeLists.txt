project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 17)

add_library(${CPE_LIB_TARGET} STATIC
            src/cpe/tool/text.cpp
            src/cpe/tool/text.h
            src/cpe/core/terminal.cpp
            src/cpe/core/terminal.h
        src/cpe/ui/write/TextFormat.cpp
        src/cpe/ui/write/TextFormat.h
            src/cpe/tool/Encoder.cpp
            src/cpe/tool/Encoder.h
            src/cpe/core/Point.cpp
            src/cpe/core/Point.h
            src/cpe/platform.h
            src/cpe/core/Color.cpp
            src/cpe/core/Color.cpp
        src/cpe/core/Color.h src/cpe/_platform/winapi.cpp src/cpe/_platform/winapi.h src/cpe/core/Exception.cpp src/cpe/core/Exception.h src/cpe/ui/element/reader/LineReader.cpp src/cpe/ui/element/reader/LineReader.h src/cpe/ui/write/TextCanvas.cpp src/cpe/ui/write/TextCanvas.h src/cpe/ui/element/ElementAbstract.h src/cpe/macros.h src/cpe/ui/style/DualBorder.h.cpp src/cpe/ui/element/ElementAbstract.cpp src/cpe/ui/ViewInterface.h src/cpe/ui/element/reader/ReaderAbstract.cpp src/cpe/ui/element/reader/ReaderAbstract.h src/cpe/ui/WriteHelper.cpp src/cpe/ui/WriteHelper.h src/cpe/ui/write/TextChar.cpp src/cpe/ui/write/TextChar.h src/cpe/ui/write/TextLine.cpp src/cpe/ui/write/TextLine.h src/cpe/tool/Nullable.h src/cpe/ui/style/TextCharStyle.cpp src/cpe/ui/style/TextCharStyle.h)

target_include_directories(${CPE_LIB_TARGET} PUBLIC src)
set_target_properties(${CPE_LIB_TARGET} PROPERTIES
                      OUTPUT_NAME "Cpe"
                      VERSION 0.1.0
                      SOVERSION 0)