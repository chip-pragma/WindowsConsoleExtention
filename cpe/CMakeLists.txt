project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 17)

add_library(${LIBRARY_CPE_NAME}
            _old/Console.cpp
            _old/Console.h
            ui/Menu.cpp
            ui/Menu.h
            ui/Table.cpp
            ui/Table.h
            ui/TextBlock.cpp
            ui/TextBlock.h
            utils/Text.cpp
            utils/Text.h
            utils/Converter.cpp
            utils/Converter.h
            ui/style/DualBorder.h
            ui/style/Color.h
            ui/style/TableBorder.h
            ui/style/Border.cpp
            ui/style/Border.h core/Encoder.cpp core/Encoder.h ui/IElement.h core/Console.cpp core/Console.h ui/Scene.cpp ui/Scene.h ui/style/TextStyle.cpp ui/style/TextStyle.h)