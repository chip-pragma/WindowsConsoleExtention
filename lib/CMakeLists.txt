project(wce_lib)

add_library(wce_lib STATIC
            src/wce/tool/text.cpp src/wce/tool/text.h src/wce/core/console.cpp src/wce/core/console.h
            src/wce/tool/Encoder.cpp
            src/wce/tool/Encoder.h src/wce/core/Point.cpp src/wce/core/Point.h
            src/wce/core/Color.cpp src/wce/core/Color.cpp src/wce/ui/style/BorderStyle.h
            src/wce/ui/style/BorderStyle.cpp
            src/wce/core/Color.h src/wce/core/Exception.cpp src/wce/core/Exception.h
            src/wce/ui/output/Buffer.cpp src/wce/ui/output/Buffer.h
            src/wce/ui/output/OutputHelper.cpp src/wce/ui/output/OutputHelper.h src/wce/ui/output/StyledChar.cpp
            src/wce/ui/output/StyledChar.h src/wce/ui/style/TextColor.cpp
            src/wce/ui/style/TextColor.h src/wce/ui/IValidator.h
            src/wce/ui/element/Notification.cpp src/wce/ui/element/Notification.h
            src/wce/ui/output/StyledBorder.cpp src/wce/ui/output/StyledBorder.h
            src/wce/ui/ReaderResult.h
            src/wce/ui/IElement.h
            src/wce/ui/BaseWriter.h
            src/wce/ui/IModel.h src/wce/ui/BaseElement.h src/wce/ui/BaseReader.h
            src/wce/ui/element/LineReader.cpp src/wce/ui/element/LineReader.h
            src/wce/ui/output/StyledText.cpp src/wce/ui/output/StyledText.h src/wce/ui/output/IOutputable.h
            src/wce/ui/output/IOutputable.cpp src/wce/ui/element/Label.cpp src/wce/ui/element/Label.h
            src/wce/ui/element/menu/Menu.cpp src/wce/ui/element/menu/Menu.h src/wce/ui/element/menu/IMenuItem.h
            src/wce/ui/element/menu/MenuItem.cpp src/wce/ui/element/menu/MenuItem.h src/wce/ui/element/menu/BaseMenuItem.cpp
            src/wce/ui/element/menu/BaseMenuItem.h
            src/wce/ui/element/menu/MenuReader.cpp src/wce/ui/element/menu/MenuReader.h
            src/wce/ui/element/menu/MenuSeparator.cpp src/wce/ui/element/menu/MenuSeparator.h
            src/wce/core/Rectangle.cpp src/wce/core/Rectangle.h src/wce/core/ISerializable.cpp
            src/wce/core/ISerializable.h src/wce/ui/element/table/DataTable.h
            src/wce/ui/element/table/DataTableColumn.h
            src/wce/ui/BaseScript.cpp src/wce/ui/BaseScript.h src/wce/core/ColorIndex.cpp src/wce/core/ColorIndex.h src/wce/core/ColorTable.cpp src/wce/core/ColorTable.h)

target_include_directories(wce_lib PUBLIC src)
set_target_properties(wce_lib PROPERTIES
                      OUTPUT_NAME WCE)

#file(COPY src/wce src/platform
#     DESTINATION ${STATIC_LIB_OUTPUT_DIRECTORY}/${CPE_LIB_TARGET}/include
#     FILES_MATCHING PATTERN "*.h*")