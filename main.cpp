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

    ~Point() {
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

    return 0;
}
