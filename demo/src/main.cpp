#include "main.h"
#include "common.h"

#include <wce/core/console.h>
#include <wce/ui/style/BorderStyle.h>
#include <wce/tool/Encoder.h>
#include <wce/core/functional/Event.h>
#include <wce/core/functional/FunctionDelegate.h>
#include <wce/core/functional/MemberDelegate.h>

#include <iostream>

using namespace wce;

class Test {
public:
    Event<Test, int, int> ValueChanged;

    int get() const {
        return m_value;
    }

    void set(int v) {
        ValueChanged.invoke(m_value, v);
        m_value = v;
    }

    void onSetValue(int oldVal, int newVal) {
        std::cout << "S] OLD:" << oldVal << " NEW:" << newVal << "\n";
    }

private:
    int m_value = 0;
};

int main() {
    console::setTitle("Текст консоли"_dos);
    console::setForeground(console::C_WHITE);
    console::setBackground(console::C_BLACK);

    console::waitAnyKey();
    onTesting();
    console::waitAnyKey();

    return 0;
}

void onValueChanged(int oldVal, int newVal) {
    std::cout << "1] " << oldVal << " => " << newVal << "\n";
}

void onValueChanged2(int oldVal, int newVal) {
    std::cout << "2] " << oldVal << " => " << newVal << "\n";
}

void onTesting() {
    BorderStyle::finalEncoding = Encoder(Encoder::CP866);

    Test t1;

    auto &event = t1.ValueChanged;
    auto delegate = make::delegate(onValueChanged);
    event += delegate;

    t1.ValueChanged += delegate;
    t1.ValueChanged += make::delegate(onValueChanged2);
    t1.set(3);
    t1.set(1);

    t1.ValueChanged += make::delegate(t1, &Test::onSetValue);
    t1.set(-6);
    t1.set(7);

    t1.ValueChanged -= delegate;
    t1.set(5);
    t1.set(-3);
}
