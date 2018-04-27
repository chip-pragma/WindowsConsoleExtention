project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 17)

add_library(${CPE_LIB_TARGET} STATIC
            src/cpe/utils/Text.cpp
            src/cpe/utils/Text.h
            src/cpe/core/Terminal.cpp
            src/cpe/core/Terminal.h
            src/cpe/ui/WriterFormat.cpp
            src/cpe/ui/WriterFormat.h
            src/cpe/core/Encoder.cpp
            src/cpe/core/Encoder.h
            src/cpe/core/Point.cpp
            src/cpe/core/Point.h
            src/cpe/platform.h
            src/cpe/core/Color.cpp
            src/cpe/core/Color.cpp
            src/cpe/core/Color.h src/cpe/core/ReaderFormat.cpp src/cpe/core/ReaderFormat.h src/cpe/_platform/winapi.cpp src/cpe/_platform/winapi.h src/cpe/core/Exception.cpp src/cpe/core/Exception.h src/cpe/ui/reader/AReader.cpp src/cpe/ui/reader/AReader.h src/cpe/ui/reader/LineReader.cpp src/cpe/ui/reader/LineReader.h src/cpe/ui/Buffer.cpp src/cpe/ui/Buffer.h src/cpe/ui/AProcessor.h src/cpe/ui/ACommand.h src/cpe/ui/AScript.h src/cpe/ui/BufferManip.cpp src/cpe/ui/BufferManip.h src/cpe/ui/command/Label.cpp src/cpe/ui/command/Label.h src/cpe/ui/AProperties.h src/cpe/ui/IProperty.h src/cpe/ui/Property.h src/cpe/macros.h src/cpe/ui/command/MessageBox.cpp src/cpe/ui/command/MessageBox.h src/cpe/ui/AContainer.h src/cpe/ui/IProperty.cpp src/cpe/ui/AProperties.cpp src/cpe/ui/AContainer.cpp src/cpe/ui/style/DualBorder.h.cpp)

target_include_directories(${CPE_LIB_TARGET} PUBLIC src)
set_target_properties(${CPE_LIB_TARGET} PROPERTIES
                      OUTPUT_NAME "Cpe"
                      VERSION 0.1.0
                      SOVERSION 0)