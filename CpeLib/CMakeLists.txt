project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 17)

add_library(${LIBRARY_CPE_NAME}
        #            ui/Menu.cpp
        #            ui/Menu.h
        #            ui/Table.cpp
        #            ui/Table.h
        #            ui/TextBlock.cpp
        #            ui/TextBlock.h
        #            utils/Text.cpp
        #            utils/Text.h
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
        #            ui/style/OutputFormat.cpp
        #            ui/style/OutputFormat.h
        cpe/core/Encoding.cpp
        cpe/core/Encoding.h
        cpe/core/Point.cpp
        cpe/core/Point.h
        cpe/Core.h
        cpe/core/Platform.cpp
        cpe/core/Platform.h
        cpe/core/Color.cpp
        cpe/core/Color.h cpe/ui/BaseInput.cpp cpe/ui/BaseInput.h cpe/core/KeyType.h cpe/ui/BaseOutput.cpp cpe/ui/BaseOutput.h cpe/ui/InputFormat.cpp cpe/ui/InputFormat.h)