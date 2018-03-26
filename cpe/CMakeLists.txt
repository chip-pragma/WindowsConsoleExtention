project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 17)

add_library(${LIBRARY_CPE_NAME}
            core/Console.cpp
            core/Console.h
            ui/Menu.cpp
            ui/Menu.h
            ui/Table.cpp
            ui/Table.h
            utils/text/TextRect.cpp
            utils/text/TextRect.h
            utils/text/Text.cpp
            utils/text/Text.h
            utils/Converter.cpp
            utils/Converter.h
            ui/style/DualBorder.h
            core/Color.h
            ui/style/TableBorder.h
            ui/style/Border.cpp
            ui/style/Border.h core/Encoder.cpp core/Encoder.h)