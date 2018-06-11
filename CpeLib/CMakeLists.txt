project(ConsolePresentExtention)

add_library(${CPE_LIB_TARGET} STATIC
            src/cpe/tool/text.cpp src/cpe/tool/text.h src/cpe/core/terminal.cpp src/cpe/core/terminal.h
            src/cpe/tool/Encoder.cpp
            src/cpe/tool/Encoder.h src/cpe/core/draw/Point.cpp src/cpe/core/draw/Point.h src/platform/platform.h
            src/cpe/core/draw/Color.cpp src/cpe/core/draw/Color.cpp src/cpe/ui/style/BorderStyle.h src/cpe/ui/style/BorderStyle.cpp
            src/cpe/core/draw/Color.h src/platform/winapi.h src/cpe/core/Exception.cpp src/cpe/core/Exception.h
            src/cpe/ui/output/Buffer.cpp src/cpe/ui/output/Buffer.h
            src/cpe/ui/output/OutputHelper.cpp src/cpe/ui/output/OutputHelper.h src/cpe/ui/output/StyledChar.cpp
            src/cpe/ui/output/StyledChar.h src/cpe/ui/style/TextColor.cpp
            src/cpe/ui/style/TextColor.h src/cpe/ui/IValidator.h
            src/cpe/ui/element/Notification.cpp src/cpe/ui/element/Notification.h
            src/cpe/ui/output/StyledBorder.cpp src/cpe/ui/output/StyledBorder.h
            src/cpe/ui/ReaderResult.h
            src/cpe/ui/IWriter.h src/cpe/ui/IElement.h
            src/cpe/ui/BaseWriter.h
            src/cpe/ui/IModel.h src/cpe/ui/BaseElement.h src/cpe/ui/BaseWriterData.cpp
            src/cpe/ui/BaseWriterData.h src/cpe/ui/BaseReaderData.cpp
            src/cpe/ui/BaseReaderData.h src/cpe/ui/BaseReader.h
            src/cpe/ui/ReaderData.h src/cpe/ui/element/LineReader.cpp src/cpe/ui/element/LineReader.h
            src/cpe/ui/output/StyledText.cpp src/cpe/ui/output/StyledText.h src/cpe/ui/output/IOutputable.h
            src/cpe/ui/output/IOutputable.cpp src/cpe/ui/element/Label.cpp src/cpe/ui/element/Label.h
            src/cpe/ui/element/menu/Menu.cpp src/cpe/ui/element/menu/Menu.h src/cpe/ui/element/menu/IMenuItem.h
            src/cpe/ui/element/menu/MenuItem.cpp src/cpe/ui/element/menu/MenuItem.h
            src/cpe/ui/BaseElementData.h src/cpe/ui/element/menu/BaseMenuItem.cpp src/cpe/ui/element/menu/BaseMenuItem.h
            src/cpe/ui/element/menu/MenuReader.cpp src/cpe/ui/element/menu/MenuReader.h
            src/cpe/ui/element/menu/MenuSeparator.cpp src/cpe/ui/element/menu/MenuSeparator.h
            src/cpe/core/draw/Rectangle.cpp src/cpe/core/draw/Rectangle.h src/cpe/core/ISerializable.cpp src/cpe/core/ISerializable.h
            src/cpe/ui/BaseController.h src/cpe/ui/element/table/DataTable.h
            src/cpe/ui/element/table/DataTableColumn.h
            src/cpe/ui/element/table/DataTableModel.h src/cpe/ui/BaseScript.cpp src/cpe/ui/BaseScript.h)

target_include_directories(${CPE_LIB_TARGET} PUBLIC src)
target_compile_features(${CPE_LIB_TARGET} PUBLIC cxx_std_17)

set_target_properties(${CPE_LIB_TARGET} PROPERTIES
                      OUTPUT_NAME ${CPE_LIB_TARGET}
                      ARCHIVE_OUTPUT_DIRECTORY ${STATIC_LIB_OUTPUT_DIRECTORY}/${CPE_LIB_TARGET})

file(COPY src/cpe src/platform
     DESTINATION ${STATIC_LIB_OUTPUT_DIRECTORY}/${CPE_LIB_TARGET}/include
     FILES_MATCHING PATTERN "*.h*")