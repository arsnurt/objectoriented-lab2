#include <iostream>

class Point {
private:
    int y;

protected:
    int x;

public:
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
    Point b(2, 3);
    Point c(b);

    c.move(10, 0);

    std::cout << "b: ";
    b.print();

    std::cout << "c: ";
    c.print();

    return 0;
}
