project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 17)

add_library(${LIBRARY_CPE_NAME}
            #            ui/Menu.cpp
            #            ui/Menu.h
            #            ui/Table.cpp
            #            ui/Table.h
            #            ui/TextBlock.cpp
            #            ui/TextBlock.h
            cpe/utils/Text.cpp
            cpe/utils/Text.h
            #            utils/Converter.cpp
            #            utils/Converter.h
            #            ui/style/DualBorder.h
            #            ui/style/TableBorder.h
            #            ui/style/Border.cpp
            #            ui/style/Border.h
            #            ui/IPrintElement.h
            cpe/core/Terminal.cpp
            cpe/core/Terminal.h
            cpe/ui/WriterFormat.cpp
            cpe/ui/WriterFormat.h
            cpe/core/Encoder.cpp
            cpe/core/Encoder.h
            cpe/core/Point.cpp
            cpe/core/Point.h
        cpe/Platform.h
            cpe/core/Color.cpp
        cpe/core/Color.h cpe/ui/IWriter.cpp cpe/ui/IWriter.h cpe/core/ReaderFormat.cpp cpe/core/ReaderFormat.h cpe/_platform/winapi.cpp cpe/_platform/winapi.h cpe/core/Exception.cpp cpe/core/Exception.h cpe/ui/AReader.cpp cpe/ui/AReader.h cpe/ui/LineReader.cpp cpe/ui/LineReader.h cpe/ui/Buffer.cpp cpe/ui/Buffer.h cpe/ui/AProcessor.cpp cpe/ui/AProcessor.h cpe/ui/ACommand.cpp cpe/ui/ACommand.h cpe/ui/Script.cpp cpe/ui/Script.h cpe/ui/BufferManip.cpp cpe/ui/BufferManip.h cpe/ui/command/Label.cpp cpe/ui/command/Label.h cpe/ui/property/AProperties.cpp cpe/ui/property/AProperties.h cpe/ui/property/IProperty.cpp cpe/ui/property/IProperty.h cpe/ui/property/AProperty.cpp cpe/ui/property/AProperty.h cpe/ui/property/Property.cpp cpe/ui/property/Property.h cpe/Macros.h)