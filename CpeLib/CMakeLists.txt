project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 17)

include_directories(cpe)

add_library(${LIBRARY_CPE_NAME} STATIC
            cpe/utils/Text.cpp
            cpe/utils/Text.h
            cpe/core/Terminal.cpp
            cpe/core/Terminal.h
        cpe/ui/WriterFormat.cpp
        cpe/ui/WriterFormat.h
            cpe/core/Encoder.cpp
            cpe/core/Encoder.h
            cpe/core/Point.cpp
            cpe/core/Point.h
        cpe/platform.h
            cpe/core/Color.cpp
        cpe/core/Color.cpp
        cpe/core/Color.h cpe/core/ReaderFormat.cpp cpe/core/ReaderFormat.h cpe/_platform/winapi.cpp cpe/_platform/winapi.h cpe/core/Exception.cpp cpe/core/Exception.h cpe/ui/reader/AReader.cpp cpe/ui/reader/AReader.h cpe/ui/reader/LineReader.cpp cpe/ui/reader/LineReader.h cpe/ui/Buffer.cpp cpe/ui/Buffer.h cpe/ui/AProcessor.h cpe/ui/ACommand.h cpe/ui/AScript.h cpe/ui/BufferManip.cpp cpe/ui/BufferManip.h cpe/ui/command/Label.cpp cpe/ui/command/Label.h cpe/ui/AProperties.h cpe/ui/IProperty.h cpe/ui/Property.h cpe/macros.h cpe/ui/command/MessageBox.cpp cpe/ui/command/MessageBox.h cpe/ui/AContainer.h cpe/ui/IProperty.cpp cpe/ui/AProperties.cpp cpe/ui/AContainer.cpp cpe/ui/style/DualBorder.h.cpp)