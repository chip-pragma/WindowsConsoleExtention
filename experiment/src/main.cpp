#include <iostream>
#include <cstdlib>
#include <memory>

class Testable {
public:
    Testable() {
        mCount++;
    }

    ~Testable() {
        mCount--;
    }

    static int getCount() {
        return mCount;
    }

private:
    static int mCount;
};

int Testable::mCount = 0;

class Tester {
public:
    Tester()
        : mTestable(new Testable()),
          mOwnerTestable(true) { }

    ~Tester() {
        if (mOwnerTestable)
            delete mTestable;
    }

    explicit Tester(Testable *testable)
        : mTestable(testable),
          mOwnerTestable(false) { }

    Testable *getTestable() const {
        return mTestable;
    }

private:
    Testable *mTestable;
    bool mOwnerTestable;
};

int main() {
    system("title EXPERIMENT");
    system("pause");

    std::cout << Testable::getCount() << std::endl;
    auto t1 = new Tester();
    auto t11 = t1->getTestable();
    std::cout << Testable::getCount() << std::endl;
    delete t1;
    std::cout << Testable::getCount() << std::endl;
    auto t21 = new Testable();
    auto t2 = new Tester(t21);
    std::cout << Testable::getCount() << std::endl;
    delete t2;
    std::cout << Testable::getCount() << std::endl;
    system("pause");
}