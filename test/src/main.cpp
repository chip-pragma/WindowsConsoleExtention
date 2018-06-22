#include <iostream>
#include <cstddef>
#include <memory>
#include <set>
#include <iomanip>

template<class TReturn, class ...TParams>
class BaseDelegate {
public:
    virtual ~BaseDelegate() { }

    virtual TReturn invoke(TParams...) = 0;

    virtual bool isSet() const = 0;

    bool operator==(std::nullptr_t) {
        return !isSet();
    }

    bool operator!=(std::nullptr_t) {
        return isSet();
    }

    operator bool() { // NOLINT
        return isSet();
    }

    TReturn operator()(TParams... params) {
        return invoke(params...);
    }
};

template<class TIns, class TReturn, class ...TParams>
class MemberDelegate : public BaseDelegate<TReturn, TParams...> {
public:
    using InstanceType = TIns;
    using MemberType = TReturn(TIns::*)(TParams...);

    ~MemberDelegate() override { }

    TReturn invoke(TParams... params) override {
        std::cout << "MEMBER INVOKE: ";
        return (m_instance->*m_function)(params...);
    }

    void set(InstanceType &instance, MemberType memFunc) {
        m_instance = &instance;
        m_function = memFunc;
    }

    void unset() {
        m_instance = nullptr;
        m_function = nullptr;
    }

    bool isSet() const override {
        return m_instance != nullptr && m_function != nullptr;
    }

private:
    TIns *m_instance = nullptr;
    MemberType m_function = nullptr;
};

template<class TReturn, class ...TParams>
class FunctionDelegate : public BaseDelegate<TReturn, TParams...> {
public:
    using FuncType = TReturn(*)(TParams...);

    ~FunctionDelegate() override { }

    TReturn invoke(TParams... params) override {
        std::cout << "FUNC INVOKE: ";
        return (*m_function)(params...);
    }

    void set(FuncType memFunc) {
        m_function = memFunc;
    }

    void unset() {
        m_function = nullptr;
    }

    bool isSet() const override {
        return m_function != nullptr;
    }

private:
    FuncType m_function = nullptr;
};

class Test {
public:
    void func1() {
        std::cout << "member func1" << "\n";
    }

    void func2(int i) {
        std::cout << "member func2 with " << i << "\n";
    }

    bool func3(bool i) {
        std::cout << "member func3 with " << i << " and return " << i << "\n";
    }
};

void func1() {
    std::cout << "func1" << "\n";
}

void func2(int i) {
    std::cout << "func2 with " << i << "\n";
}

bool func3(bool i) {
    std::cout << "func3 with " << i << " and return " << i << "\n";
}

int main() {
    system("title EXPERIMENT");
    system("pause");

    Test t1;
    FunctionDelegate<void> fd1;
    MemberDelegate<Test, void, int> md1;
    MemberDelegate<Test, void> md2;
    MemberDelegate<Test, bool, bool> md3;
    BaseDelegate<void, int>& bd1 = md1;
    BaseDelegate<bool, bool>& bd2 = md3;

    fd1.set(func1);
    md1.set(t1, &Test::func2);
    md2.set(t1, &Test::func1);
    md3.set(t1, &Test::func3);

    fd1();
    md1(3);
    md2();
    md3(true);
    bd1(17);
    bd2(false);

    system("pause");
}