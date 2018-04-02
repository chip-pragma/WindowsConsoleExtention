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
            #            ui/style/Color.h
            #            ui/style/TableBorder.h
            #            ui/style/Border.cpp
            #            ui/style/Border.h
            #            ui/IElement.h
            core/Console.cpp
            core/Console.h
            #            ui/Scene.cpp
            #            ui/Scene.h
            #            ui/style/TextFormat.cpp
            #            ui/style/TextFormat.h
            core/Encoding.cpp
            core/Encoding.h)