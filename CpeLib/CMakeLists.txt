project(ConsolePresentExtention)



add_library(${CPE_LIB_TARGET} STATIC
            src/cpe/tool/text.cpp src/cpe/tool/text.h src/cpe/core/terminal.cpp src/cpe/core/terminal.h
            src/cpe/ui/output/StyledString.cpp src/cpe/ui/output/StyledString.h src/cpe/tool/Encoder.cpp
            src/cpe/tool/Encoder.h src/cpe/core/draw/Point.cpp src/cpe/core/draw/Point.h src/cpe/platform.h
            src/cpe/core/draw/Color.cpp src/cpe/core/draw/Color.cpp src/cpe/ui/style/BorderStyle.h src/cpe/ui/style/BorderStyle.cpp
            src/cpe/core/draw/Color.h src/cpe/_platform/winapi.h src/cpe/core/Exception.cpp src/cpe/core/Exception.h
            src/cpe/ui/output/Buffer.cpp src/cpe/ui/output/Buffer.h
            src/cpe/ui/view/BaseView.h
            src/cpe/ui/output/OutputHelper.cpp src/cpe/ui/output/OutputHelper.h src/cpe/ui/output/StyledChar.cpp
            src/cpe/ui/output/StyledChar.h src/cpe/ui/style/TextColor.cpp
            src/cpe/ui/style/TextColor.h src/cpe/ui/reader/IValidator.h
            src/cpe/ui/writer/Notification.cpp src/cpe/ui/writer/Notification.h
            src/cpe/ui/output/StyledBorder.cpp src/cpe/ui/output/StyledBorder.h
            src/cpe/ui/reader/ReaderResult.h
            src/cpe/ui/IViewModel.h
            src/cpe/ui/writer/IWriter.h src/cpe/ui/ICuiElement.h
            src/cpe/ui/view/IView.h src/cpe/ui/writer/BaseWriter.h
            src/cpe/ui/IModel.h src/cpe/ui/BaseCuiElement.h src/cpe/ui/IElementData.h src/cpe/ui/writer/BaseWriterData.cpp
            src/cpe/ui/writer/BaseWriterData.h src/cpe/ui/reader/BaseReaderData.cpp
            src/cpe/ui/reader/BaseReaderData.h src/cpe/ui/reader/BaseReader.h
            src/cpe/ui/reader/ReaderData.h src/cpe/ui/reader/LineReader.cpp src/cpe/ui/reader/LineReader.h src/cpe/ui/output/StyledText.cpp src/cpe/ui/output/StyledText.h src/cpe/ui/output/IOutputable.h src/cpe/ui/output/IOutputable.cpp)

target_include_directories(${CPE_LIB_TARGET} PUBLIC src)
target_compile_features(${CPE_LIB_TARGET} PUBLIC cxx_std_17)
set_target_properties(${CPE_LIB_TARGET} PROPERTIES
                      OUTPUT_NAME "Cpe")