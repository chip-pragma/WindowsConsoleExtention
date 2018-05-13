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
        src/cpe/core/draw/Point.cpp
        src/cpe/core/draw/Point.h
        src/cpe/platform.h
        src/cpe/core/draw/Color.cpp
        src/cpe/core/draw/Color.cpp
        src/cpe/ui/style/Border.h
        src/cpe/ui/style/Border.cpp
        src/cpe/core/draw/Color.h src/cpe/_platform/winapi.h src/cpe/core/Exception.cpp src/cpe/core/Exception.h src/cpe/ui/write/TextCanvas.cpp src/cpe/ui/write/TextCanvas.h src/cpe/ui/element/ElementBase.h src/cpe/macros.h src/cpe/ui/style/DualBorder.h.cpp src/cpe/ui/element/ElementBase.cpp src/cpe/ui/IView.h src/cpe/ui/element/reader/Reader.h src/cpe/ui/write/WriteHelper.cpp src/cpe/ui/write/WriteHelper.h src/cpe/ui/write/StyledChar.cpp src/cpe/ui/write/StyledChar.h src/cpe/tool/Nullable.h src/cpe/ui/style/TextCharStyle.cpp src/cpe/ui/style/TextCharStyle.h src/cpe/ui/element/reader/IValidator.h src/cpe/ui/element/reader/IConverter.h src/cpe/ui/element/MessageBox.cpp src/cpe/ui/element/MessageBox.h src/cpe/tool/NullableException.h)

target_include_directories(${CPE_LIB_TARGET} PUBLIC src)
set_target_properties(${CPE_LIB_TARGET} PROPERTIES
        OUTPUT_NAME "Cpe"
        VERSION 0.1.0
        SOVERSION 0)