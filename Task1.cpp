#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// ======= Ієрархія без віртуального успадкування =======

class A {
protected:
    int value;
public:
    A() : value(0) { cout << "A створено\n"; }
    virtual ~A() { cout << "A знищено\n"; }

    virtual void info() const {
        cout << "Це клас A, значення = " << value << endl;
    }

    void inputFromKeyboard() {
        cout << "[Клавіатура] Введіть значення для A: ";
        cin >> value;
    }

    void inputFromFile(const string& filename) {
        ifstream fin(filename);
        if (fin >> value)
            cout << "[Файл] Значення для A: " << value << endl;
        else
            cout << "[Файл] Помилка читання!" << endl;
        fin.close();
    }

    void inputRandom() {
        value = rand() % 100;
        cout << "[Random] Згенеровано значення для A: " << value << endl;
    }
};

class B : public A {
    int bData;
public:
    B() : bData(1) { cout << "B створено\n"; }
    ~B() { cout << "B знищено\n"; }

    void info() const override {
        cout << "Це клас B, значення = " << value << ", bData = " << bData << endl;
    }
};

class C : public A {
    double cData;
public:
    C() : cData(2.5) { cout << "C створено\n"; }
    ~C() { cout << "C знищено\n"; }

    void info() const override {
        cout << "Це клас C, значення = " << value << ", cData = " << cData << endl;
    }
};

class D : public B {
    string dNote;
public:
    D() : dNote("D-note") { cout << "D створено\n"; }
    ~D() { cout << "D знищено\n"; }
};

class E : public C {
    char eChar;
public:
    E() : eChar('E') { cout << "E створено\n"; }
    ~E() { cout << "E знищено\n"; }
};

class F : public D, public E {
    bool fFlag;
public:
    F() : fFlag(true) { cout << "F створено (без virtual)\n"; }
    ~F() { cout << "F знищено (без virtual)\n"; }
};

// ======= Ієрархія з віртуальним успадкуванням =======

class VA {
protected:
    int value;
public:
    VA() : value(0) { cout << "VA створено\n"; }
    virtual ~VA() { cout << "VA знищено\n"; }

    virtual void info() const {
        cout << "Це клас VA, значення = " << value << endl;
    }

    void inputFromKeyboard() {
        cout << "[Клавіатура] Введіть значення для VA: ";
        cin >> value;
    }

    void inputFromFile(const string& filename) {
        ifstream fin(filename);
        if (fin >> value)
            cout << "[Файл] Значення для VA: " << value << endl;
        else
            cout << "[Файл] Помилка читання!" << endl;
        fin.close();
    }

    void inputRandom() {
        value = rand() % 100;
        cout << "[Random] Згенеровано значення для VA: " << value << endl;
    }
};

class VB : virtual public VA {
    int vbCode;
public:
    VB() : vbCode(10) { cout << "VB створено\n"; }
    ~VB() { cout << "VB знищено\n"; }

    void info() const override {
        cout << "Це клас VB, значення = " << value << ", vbCode = " << vbCode << endl;
    }
};

class VC : virtual public VA {
    float vcLevel;
public:
    VC() : vcLevel(3.14f) { cout << "VC створено\n"; }
    ~VC() { cout << "VC знищено\n"; }

    void info() const override {
        cout << "Це клас VC, значення = " << value << ", vcLevel = " << vcLevel << endl;
    }
};

class VD : public VB {
    string vdName;
public:
    VD() : vdName("VD") { cout << "VD створено\n"; }
    ~VD() { cout << "VD знищено\n"; }
};

class VE : public VC {
    bool veState;
public:
    VE() : veState(false) { cout << "VE створено\n"; }
    ~VE() { cout << "VE знищено\n"; }
};

class VF : public VD, public VE {
    long vfId;
public:
    VF() : vfId(999) { cout << "VF створено (з virtual)\n"; }
    ~VF() { cout << "VF знищено (з virtual)\n"; }

    void info() const override {
        cout << "Це клас VF, значення = " << value << ", vfId = " << vfId << endl;
    }
};

// ======= Виведення розмірів =======

void printSizes() {
    cout << "\n[Розміри об'єктів]\n";
    cout << "F (без virtual): " << sizeof(F) << " байт\n";
    cout << "VF (з virtual): " << sizeof(VF) << " байт\n";
}

// ======= Головна функція =======

int main() {
    srand(time(0)); // ініціалізація генератора випадкових чисел

    cout << "=== Ієрархія без віртуального успадкування ===\n";
    F f;
    ((B&)f).inputFromKeyboard();
    ((B&)f).inputFromFile("input.txt");
    ((B&)f).inputRandom();
    ((B&)f).info();

    cout << "\n=== Ієрархія з віртуальним успадкуванням ===\n";
    VF vf;
    ((VB&)vf).inputFromKeyboard();
    ((VB&)vf).inputFromFile("input.txt");
    ((VB&)vf).inputRandom();
    vf.info();

    printSizes();

    return 0;
}
