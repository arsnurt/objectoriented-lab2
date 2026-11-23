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
    void print() const;
};
void Point::print() const {
    std::cout << "x=" << x << ", y=" << y << '\n';
}


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

class Segment {
private:
    Point start;
    Point finish;

public:
    Segment() : start(), finish() {
        std::cout << "Segment()\n";
    }

    Segment(int x1, int y1, int x2, int y2)
        : start(x1, y1), finish(x2, y2) {
        std::cout << "Segment(int, int, int, int)\n";
    }

    Segment(const Segment& other)
        : start(other.start), finish(other.finish) {
        std::cout << "Segment(copy)\n";
    }

    ~Segment() {
        std::cout << "~Segment()\n";
    }

    void move(int dx, int dy) {
        start.move(dx, dy);
        finish.move(dx, dy);
    }

    void print() const {
        std::cout << "start: ";
        start.print();
        std::cout << "finish: ";
        finish.print();
    }
};

class PlainPoint : public Point {
};

class PointHolder {
private:
    Point* point;

public:
    PointHolder() : point(new Point()) {
        std::cout << "PointHolder()\n";
    }

    PointHolder(int x, int y) : point(new Point(x, y)) {
        std::cout << "PointHolder(int, int)\n";
    }

    PointHolder(const PointHolder& other)
        : point(new Point(*other.point)) {
        std::cout << "PointHolder(copy)\n";
    }

    PointHolder& operator=(const PointHolder&) = delete;

    ~PointHolder() {
        std::cout << "~PointHolder(): begin\n";
        delete point;
        std::cout << "~PointHolder(): end\n";
    }

    void move(int dx, int dy) {
        point->move(dx, dy);
    }

    void print() const {
        point->print();
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

    std::cout << "--- base pointer ---\n";
    {
        Point* p = new ColoredPoint(4, 7, 3);
        p->move(2, 1);
        p->print();
        // p->setX(20);
        delete p;
    }

        std::cout << "--- composition: objects ---\n";
    {
        Segment s(2, 5, 8, 9);
        s.move(3, 0);
        s.print();
    }

        std::cout << "--- implicit constructors ---\n";
    {
        PlainPoint p;
        p.move(7, 2);
        p.print();
    }

        std::cout << "--- composition: pointer ---\n";
    {
        PointHolder holder(8, 3);
        holder.move(1, 2);
        holder.print();
    }

        std::cout << "--- copying PointHolder ---\n";
    {
        PointHolder a(2, 7);
        PointHolder b(a);
        b.move(5, 1);

        std::cout << "a: ";
        a.print();
        std::cout << "b: ";
        b.print();
    }

        std::cout << "--- slicing ---\n";
    {
        ColoredPoint source(3, 8, 5);
        Point copy = source;

        source.setX(12);

        std::cout << "source:\n";
        source.print();
        std::cout << "copy:\n";
        copy.print();
    }

    return 0;
}

