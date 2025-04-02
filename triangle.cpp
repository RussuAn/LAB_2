#include "triangle.h"

int choice = 1;

double distance(const Point &p1, const Point &p2){
    return sqrt(pow (p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double heronArea(const Triangle &t) {
    double a = distance(t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2;
    return sqrt( s * (s - a) * (s - b) * (s - c));
}

double gaussArea(const Triangle &t){
    return 0.5 * fabs(t.A.x * (t.B.y - t.C.y) + t.B.x * (t.C.y - t.A.y) + t.C.x * (t.A.y - t.B.y));
}

double cross_product(const Point &p1, const Point &p2, const Point &p3) {
    return ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}


double Triangle::area() const {
    if (choice == 1) {
        return heronArea(*this);
    } else {
        return gaussArea(*this);
    }
}

bool Triangle::contains(const Point &P) const {
    if (degenerate()) return false;

    if (choice == 1) {
        double S1 = heronArea({A, B, P});
        double S2 = heronArea({B, C, P});
        double S3 = heronArea({C, A, P});
        double S_main = area();

        return fabs(S_main - (S1 + S2 + S3)) < 1e-9;
    } else {
        double CP1 = cross_product(A, B, P);
        double CP2 = cross_product(B, C, P);
        double CP3 = cross_product(C, A, P);

        return(CP1 >= 0 && CP2 >= 0 && CP3 >= 0) || (CP1 <= 0 && CP2 <= 0 && CP3 <= 0);
    }
}

bool Triangle::degenerate() const {
    return area() < 1e-9;
}

bool Triangle::on_border(const Point &P) const {

    return (fabs(cross_product(A, B, P)) < 1e-9 &&
    min(A.x, B.x) <= P.x && P.x <= max(A.x, B.x) &&
    min(A.y, B.y) <= P.y && P.y <= max(A.y, B.y)) ||

    (fabs(cross_product(B, C, P)) < 1e-9 &&
    min(B.x, C.x) <= P.x && P.x <= max(B.x, C.x) &&
    min(B.y, C.y) <= P.y && P.y <= max(B.y, C.y)) ||

    (fabs(cross_product(C, A, P)) < 1e-9 &&
    min(C.x, A.x) <= P.x && P.x <= max(C.x, A.x) &&
    min(C.y, A.y) <= P.y && P.y <= max(C.y, A.y));
}

void runcode() {
    Triangle t;
    cout << "Введіть координати трикутника (x1 y1 x2 y2 x3 y3): ";
    cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;

    cout << "Площа трикутника: " << t.area() << endl;

    cout << "Оберіть метод перевірки приналежності:\n";
    cout << "1 - Метод площі (Герон)\n";
    cout << "2 - Метод векторного добутку\n";
    cout << "Ваш вибір: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Використовується метод площі (Герон)\n";
    } else if (choice == 2) {
        cout << "Використовується метод векторного добутку\n";
    } else {
        cout << "Невірний вибір! Використовується метод за замовчуванням (Герон)\n";
        choice = 1;
    }

    if (t.degenerate()) {
        cout << "Трикутник вироджений!" << endl;
    }

    int n;
    cout << "Введіть кількість точок: ";
    cin >> n;
    while (n < 0 || n > 100) {
        cout << "Неможливо перевірити приналежність для данної кількості точок. Введіть кількість точок: ";
        cin >> n;
    }
    vector<Point> points(n);

    for (int i = 0; i < n; ++i) {
        cout << "Введіть координати точки " << i + 1 << " (x y): ";
        cin >> points[i].x >> points[i].y;

        if (t.on_border(points[i])) {
            cout << "Точка лежить на межі трикутника." << endl;
        } else if (t.contains(points[i])) {
            cout << "Точка належить трикутнику." << endl;
        } else {
            cout << "Точка не належить трикутнику." << endl;
        }
    }
}
