project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 14)

add_library(${LIBRARY_CPE_NAME}
        core/Console.cpp
        core/Console.h
        Enums.h
        ui/Menu.cpp
        ui/Menu.h
        ui/Table.cpp
        ui/Table.h
        utils/tools.cpp
        utils/tools.h
        utils/text/TextRect.cpp
        utils/text/TextRect.h utils/text/Text.cpp utils/text/Text.h utils/Converter.cpp utils/Converter.h ui/style/Style.cpp ui/style/Style.h ui/style/DualBorder.h ui/style/BorderChar.h core/Color.h ui/style/TableBorder.h)