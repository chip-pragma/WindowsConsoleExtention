project(ConsolePresentExtention)



add_library(${CPE_LIB_TARGET} STATIC
            src/cpe/tool/text.cpp src/cpe/tool/text.h src/cpe/core/terminal.cpp src/cpe/core/terminal.h
            src/cpe/ui/write/StyledText.cpp src/cpe/ui/write/StyledText.h src/cpe/tool/Encoder.cpp
            src/cpe/tool/Encoder.h src/cpe/core/draw/Point.cpp src/cpe/core/draw/Point.h src/cpe/platform.h
            src/cpe/core/draw/Color.cpp src/cpe/core/draw/Color.cpp src/cpe/ui/style/Border.h src/cpe/ui/style/Border.cpp
            src/cpe/core/draw/Color.h src/cpe/_platform/winapi.h src/cpe/core/Exception.cpp src/cpe/core/Exception.h
            src/cpe/ui/write/Buffer.cpp src/cpe/ui/write/Buffer.h src/cpe/ui/element/ElementBase.h src/cpe/macros.h
            src/cpe/ui/element/ElementBase.cpp src/cpe/ui/ViewBase.h src/cpe/ui/reader/Reader.h
            src/cpe/ui/write/WriteHelper.cpp src/cpe/ui/write/WriteHelper.h src/cpe/ui/write/StyledChar.cpp
            src/cpe/ui/write/StyledChar.h src/cpe/tool/Nullable.h src/cpe/ui/style/TextColor.cpp
            src/cpe/ui/style/TextColor.h src/cpe/ui/reader/IValidator.h src/cpe/ui/reader/IConverter.h
            src/cpe/ui/element/MessageBox.cpp src/cpe/ui/element/MessageBox.h src/cpe/tool/NullableException.h
            src/cpe/ui/write/StyledBorder.cpp src/cpe/ui/write/StyledBorder.h src/cpe/ui/ViewBase.cpp
            src/cpe/ui/reader/LineReader.cpp src/cpe/ui/reader/LineReader.h src/cpe/ui/reader/ReaderResult.h
            src/cpe/ui/reader/ReaderWorkBase.h)

target_include_directories(${CPE_LIB_TARGET} PUBLIC src)
target_compile_features(${CPE_LIB_TARGET} PUBLIC cxx_std_17)
set_target_properties(${CPE_LIB_TARGET} PROPERTIES
                      OUTPUT_NAME "Cpe")