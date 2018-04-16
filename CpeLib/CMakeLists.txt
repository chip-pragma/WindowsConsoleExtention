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
            cpe/core/Console.cpp
            cpe/core/Console.h
            #            ui/Scene.cpp
            #            ui/Scene.h
            cpe/core/OutputFormat.cpp
            cpe/core/OutputFormat.h
            cpe/core/Encoding.cpp
            cpe/core/Encoding.h
            cpe/core/Point.cpp
            cpe/core/Point.h
            cpe/core/Platform.h
            cpe/core/Color.cpp
            cpe/core/Color.h cpe/core/io/AWriter.cpp cpe/core/io/AWriter.h cpe/core/InputFormat.cpp cpe/core/InputFormat.h cpe/_platform/winapi.cpp cpe/_platform/winapi.h cpe/core/except/Exception.cpp cpe/core/except/Exception.h cpe/core/io/AReader.cpp cpe/core/io/AReader.h cpe/core/IModel.h cpe/ui/LineReader.cpp cpe/ui/LineReader.h cpe/ui/AView.h cpe/core/IModel.cpp cpe/ui/AView.cpp)