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
            cpe/core/WriterFormat.cpp
            cpe/core/WriterFormat.h
            cpe/core/Encoder.cpp
            cpe/core/Encoder.h
            cpe/core/Point.cpp
            cpe/core/Point.h
            cpe/core/Platform.h
            cpe/core/Color.cpp
            cpe/core/Color.h cpe/ui/IWriter.cpp cpe/ui/IWriter.h cpe/core/ReaderFormat.cpp cpe/core/ReaderFormat.h cpe/_platform/winapi.cpp cpe/_platform/winapi.h cpe/core/Exception.cpp cpe/core/Exception.h cpe/ui/AReader.cpp cpe/ui/AReader.h cpe/ui/IModel.h cpe/ui/LineReader.cpp cpe/ui/LineReader.h cpe/ui/IModel.cpp cpe/ui/ABinding.h cpe/ui/Buffer.cpp cpe/ui/Buffer.h cpe/ui/AController.cpp cpe/ui/AController.h cpe/ui/AElement.cpp cpe/ui/AElement.h cpe/ui/AScript.cpp cpe/ui/AScript.h)