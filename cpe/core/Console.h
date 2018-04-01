#ifndef PROJECT_CONSOLE_H
#define PROJECT_CONSOLE_H

#include <string>
#include <Windows.h>

namespace cpe::core {

namespace {
class Encoder;
}

class Console {
public:

    Console();

    /**
	 * Останавливает выполнение до ввода пользователя
	 */
    void pause();

    /**
	 * Очищает экран вывода
	 */
    void clear();

    /**
	 * Задает текст заголовка окна консоли
	 */
    void setTitle(std::string &&title);

    /**
    * Возвращает текст заголовка окна консоли
    */
    std::string &&getTitle() const;

    /**
     * Возвращает дескриптор стандартного потока вывода консоли Windows
     */
    HANDLE getOutputHandle() const;

    /**
     * Возвращает объект кодировки для ввода
     */
    const Encoder &getInputEncoder() const;

    /**
     * Возвращает объект кодировки для вывода
     */
    const Encoder &getOutputEncoder() const;

    /**
     * Задает и пременяет кодировку для потока ввода
     */
    bool applyEncoderInput(Encoder &&inEnc);

    /**
     * Задает и пременяет кодировку для потока вывода
     */
    bool applyEncoderOutput(const Encoder &outEnc);

private:
    std::string _title;
    extern Encoder _inputEncoder;
    extern Encoder _outputEncoder;
};

}

#endif //PROJECT_CONSOLE_H
