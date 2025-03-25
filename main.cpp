#include "triangle.h"

int main() {
    Triangle t;
    cout << "Введіть координати трикутника (x1 y1 x2 y2 x3 y3): ";
    cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;

    if (t.degenerate()) {
        cout << "Трикутник вироджений!" << endl;
        return 1;
    }

    int n;
    cout << "Введіть кількість точок: ";
    cin >> n;
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

    return 0;
}