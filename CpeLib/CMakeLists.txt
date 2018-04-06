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
            cpe/core/Platform.cpp
            cpe/core/Platform.h
            cpe/core/Color.cpp
            cpe/core/Color.h cpe/core/BaseInput.cpp cpe/core/BaseInput.h cpe/core/KeyType.h cpe/core/BaseOutput.cpp cpe/core/BaseOutput.h cpe/core/InputFormat.cpp cpe/core/InputFormat.h cpe/core/format/LineReader.cpp cpe/core/format/LineReader.h)