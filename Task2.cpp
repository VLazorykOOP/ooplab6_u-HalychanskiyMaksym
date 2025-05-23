#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
using namespace std;

// ---------- Абстрактний клас Shape ----------
// Це базовий клас, який визначає інтерфейс для всіх фігур
// Має чисто віртуальні функції, тому не може бути створений напряму
class Shape {
public:
    Shape() {
        cout << "[Shape] Created" << endl;
    }

    virtual ~Shape() {
        cout << "[Shape] Destroyed" << endl;
    }

    // Абстрактний метод для обчислення площі (має бути реалізований у похідних класах)
    virtual double area() const = 0;

    // Абстрактні методи для введення даних з різних джерел
    virtual void inputFromKeyboard() = 0;
    virtual void inputFromFile(ifstream& fin) = 0;
    virtual void inputRandom() = 0;

    // Абстрактний метод для виводу інформації
    virtual void print() const = 0;
};

// ---------- Клас Rectangle ----------
// Прямокутник — має ширину і висоту
class Rectangle : public Shape {
    double width, height;

public:
    Rectangle() : width(0), height(0) {
        cout << "[Rectangle] Created" << endl;
    }

    ~Rectangle() {
        cout << "[Rectangle] Destroyed" << endl;
    }

    // Площа прямокутника — ширина × висота
    double area() const override {
        return width * height;
    }

    // Введення з клавіатури
    void inputFromKeyboard() override {
        cout << "Enter width and height: ";
        cin >> width >> height;
    }

    // Зчитування з файлу
    void inputFromFile(ifstream& fin) override {
        fin >> width >> height;
    }

    // Генерація випадкових значень
    void inputRandom() override {
        width = rand() % 100 + 1;
        height = rand() % 100 + 1;
    }

    // Вивід інформації про прямокутник
    void print() const override {
        cout << "Rectangle: " << width << " x " << height
             << ", Area = " << area() << endl;
    }
};

// ---------- Клас Circle ----------
// Коло — описується радіусом
class Circle : public Shape {
    double radius;

public:
    Circle() : radius(0) {
        cout << "[Circle] Created" << endl;
    }

    ~Circle() {
        cout << "[Circle] Destroyed" << endl;
    }

    // Площа круга — π * r^2
    double area() const override {
        return M_PI * radius * radius;
    }

    void inputFromKeyboard() override {
        cout << "Enter radius: ";
        cin >> radius;
    }

    void inputFromFile(ifstream& fin) override {
        fin >> radius;
    }

    void inputRandom() override {
        radius = rand() % 100 + 1;
    }

    void print() const override {
        cout << "Circle: radius = " << radius
             << ", Area = " << area() << endl;
    }
};

// ---------- Клас RightTriangle ----------
// Прямокутний трикутник — описується основою та висотою
class RightTriangle : public Shape {
    double base, height;

public:
    RightTriangle() : base(0), height(0) {
        cout << "[RightTriangle] Created" << endl;
    }

    ~RightTriangle() {
        cout << "[RightTriangle] Destroyed" << endl;
    }

    // Площа трикутника — 0.5 × основа × висота
    double area() const override {
        return 0.5 * base * height;
    }

    void inputFromKeyboard() override {
        cout << "Enter base and height: ";
        cin >> base >> height;
    }

    void inputFromFile(ifstream& fin) override {
        fin >> base >> height;
    }

    void inputRandom() override {
        base = rand() % 100 + 1;
        height = rand() % 100 + 1;
    }

    void print() const override {
        cout << "RightTriangle: base = " << base
             << ", height = " << height
             << ", Area = " << area() << endl;
    }
};

// ---------- Клас Trapezoid ----------
// Трапеція — має дві основи і висоту
class Trapezoid : public Shape {
    double base1, base2, height;

public:
    Trapezoid() : base1(0), base2(0), height(0) {
        cout << "[Trapezoid] Created" << endl;
    }

    ~Trapezoid() {
        cout << "[Trapezoid] Destroyed" << endl;
    }

    // Площа трапеції — 0.5 × (base1 + base2) × height
    double area() const override {
        return 0.5 * (base1 + base2) * height;
    }

    void inputFromKeyboard() override {
        cout << "Enter base1, base2 and height: ";
        cin >> base1 >> base2 >> height;
    }

    void inputFromFile(ifstream& fin) override {
        fin >> base1 >> base2 >> height;
    }

    void inputRandom() override {
        base1 = rand() % 100 + 1;
        base2 = rand() % 100 + 1;
        height = rand() % 100 + 1;
    }

    void print() const override {
        cout << "Trapezoid: base1 = " << base1
             << ", base2 = " << base2
             << ", height = " << height
             << ", Area = " << area() << endl;
    }
};

// ---------- Основна функція ----------

int main() {
    srand(time(nullptr)); // Ініціалізація генератора випадкових чисел

    const int N = 4; // Кількість фігур
    Shape* shapes[N]; // Масив вказівників на базовий клас

    // Створення об'єктів різних фігур і збереження їх у масиві
    shapes[0] = new Rectangle();
    shapes[1] = new Circle();
    shapes[2] = new RightTriangle();
    shapes[3] = new Trapezoid();

    // --- Введення з клавіатури ---
    cout << "\n--- Введення з клавіатури ---\n";
    for (int i = 0; i < N; ++i) {
        shapes[i]->inputFromKeyboard();
        shapes[i]->print(); // Вивід інформації про фігуру
    }

    // --- Генерація випадкових значень ---
    cout << "\n--- Випадкові значення ---\n";
    for (int i = 0; i < N; ++i) {
        shapes[i]->inputRandom();
        shapes[i]->print();
    }

    // --- Зчитування з файлу ---
    cout << "\n--- З файлу ---\n";
    ifstream fin("task2.txt");
    if (fin) {
        for (int i = 0; i < N; ++i) {
            shapes[i]->inputFromFile(fin);
            shapes[i]->print();
        }
        fin.close();
    } else {
        cout << "Cannot open shapes.txt\n";
    }

    // Звільнення пам’яті
    for (int i = 0; i < N; ++i) {
        delete shapes[i];
    }

    return 0;
}
