#include <iostream>

class Point {
private:
    int y;
protected:
    int x;
public:
    Point() : y(0), x(0) {
        std::cout << "Point()\n";
    }
    Point(int px, int py) : y(py), x(px) {
        std::cout << "Point(int, int)\n";
    }
    Point(const Point& other) : y(other.y), x(other.x) {
        std::cout << "Point(copy)\n";
    }
    Point& operator=(const Point&) = default;
    virtual ~Point() {
        std::cout << "~Point()\n";
    }
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }
    void print() const {
        std::cout << "x=" << x << ", y=" << y << '\n';
    }
};

class ColoredPoint : public Point {
private:
    int color;
public:
    ColoredPoint() : Point(), color(0) {
        std::cout << "ColoredPoint()\n";
    }
    ColoredPoint(int px, int py, int c)
        : Point(px, py), color(c) {
        std::cout << "ColoredPoint(int, int, int)\n";
    }
    ColoredPoint(const ColoredPoint& other)
        : Point(other), color(other.color) {
        std::cout << "ColoredPoint(copy)\n";
    }
    ~ColoredPoint() override {
        std::cout << "~ColoredPoint()\n";
    }
    void setX(int value) {
        x = value;
        // y = value; // Ошибка: private в Point.
    }
    void print() const {
        std::cout << "color=" << color << '\n';
        Point::print();
    }
};

int main() {
    {
        Point b(2, 3);
        Point c(b);
        c.move(10, 0);
        b.print();
        c.print();
    }

    std::cout << "--- dynamic ---\n";
    Point* saved = nullptr;
    {
        Point* p = new Point();
        saved = p;
    }
    std::cout << "--- after block ---\n";
    saved->move(4, 5);
    saved->print();
    delete saved;

    std::cout << "--- object assignment ---\n";
    {
        Point a(3, 8);
        Point b(9, 1);
        b = a;
        a.move(2, 0);
        b.move(0, 4);
        a.print();
        b.print();
    }

    std::cout << "--- pointer assignment ---\n";
    {
        Point* p = new Point(3, 8);
        Point* q = p;
        p->move(2, 0);
        q->move(0, 4);
        p->print();
        q->print();
        delete q;
    }

    std::cout << "--- inheritance ---\n";
    {
        ColoredPoint c(6, 2, 9);
        c.setX(11);
        c.print();
    }

    return 0;
}
