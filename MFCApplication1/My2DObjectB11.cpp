#include "stdafx.h"
#include "My2DObjectB11.h"

#define _USE_MATH_DEFINES
#include <math.h>

// p1 - p3: вершины треугольника, ptest: проверяемая точка.
// Возвращается TRUE, если принадлежит, иначе - FALSE.
bool CMy2DObjectB11::IsInTriangle(const CMy2DPoint& P1, const CMy2DPoint& P2, const CMy2DPoint& P3, const CMy2DPoint& PTest) {
    double a = (P1.GetX() - PTest.GetX()) * (P2.GetY() - P1.GetY()) - (P2.GetX() - P1.GetX()) * (P1.GetY() - PTest.GetY());
    double b = (P2.GetX() - PTest.GetX()) * (P3.GetY() - P2.GetY()) - (P3.GetX() - P2.GetX()) * (P2.GetY() - PTest.GetY());
    double c = (P3.GetX() - PTest.GetX()) * (P1.GetY() - P3.GetY()) - (P1.GetX() - P3.GetX()) * (P3.GetY() - PTest.GetY());

    if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
        return true;
    else
        return false;
}

double CMy2DObjectB11::GetA()  const { return this->A; }
double CMy2DObjectB11::GetA1() const { return this->A1; }
double CMy2DObjectB11::GetA2() const { return this->A2; }
double CMy2DObjectB11::GetA3() const { return this->A3; }
double CMy2DObjectB11::GetAngle() const { return this->m_dAngle; }
CMy2DPoint CMy2DObjectB11::GetCenter() const { return this->m_center; }

void CMy2DObjectB11::SetA(double A) { if (isValid(A, this->A1, this->A2, this->A3)) this->A = A; }
void CMy2DObjectB11::SetA1(double A1) { if (isValid(this->A, A1, this->A2, this->A3)) this->A1 = A1; }
void CMy2DObjectB11::SetA2(double A2) { if (isValid(this->A, this->A1, A2, this->A3)) this->A2 = A2; }
void CMy2DObjectB11::SetA3(double A3) { if (isValid(this->A, this->A1, this->A2, A3)) this->A3 = A3; }
void CMy2DObjectB11::SetAngle(double angle) { this->m_dAngle = angle; }
void CMy2DObjectB11::SetCenter(const CMy2DPoint& center) { this->m_center = center; }

void CMy2DObjectB11::Move(double dX, double dY, double dAngle) {
    this->Move(CMy2DPoint(dX, dY), dAngle);
};

void CMy2DObjectB11::Move(const CMy2DPoint& delta, double dAngle) {
    this->m_center = this->m_center + delta;
    this->m_dAngle += dAngle;
};

void CMy2DObjectB11::Rotate(double dAngle) {
    this->m_dAngle += dAngle;
};

bool CMy2DObjectB11::IsInside(const CMy2DPoint& point) {
    return this->IsInside(point.GetX(), point.GetY());
};
bool CMy2DObjectB11::IsInside(double x, double y) {
    double new_x, new_y;
    // перенос
    x -= this->m_center.GetX();
    y -= this->m_center.GetY();
    // поворот
    new_x = x * cos(this->m_dAngle) + y * sin(this->m_dAngle);
    new_y = -x * sin(this->m_dAngle) + y * cos(this->m_dAngle);

    // проверка на выход за границы фигуры по оси X
    if (new_x > (this->A / 2) || new_x < -(this->A / 2)) {
        return false;
    }
    // проверка на выход за границы фигуры по оси Y
    if (new_y >(this->A / 2) || new_y < -(this->A / 2)) {
        return false;
    }

    // проверка на выход за прямоугольник A1
    if ((new_x > this->A / 2 - this->A1) &&
        (-this->A1 / 2 < new_y) && (new_y < this->A1 / 2)) {
        return false;
    }

    // проверка на выход за треугольник A2
    bool isInA2Square =
        (-this->A / 2 <= new_x && new_x <= -this->A / 2 + this->A2) &&
        (this->A / 2 - this->A2 <= new_y && new_y <= this->A / 2);
    if (isInA2Square) {
        bool isInInnerA2Triangle = IsInTriangle(
            CMy2DPoint(-this->A / 2 + this->A2, this->A / 2),
            CMy2DPoint(-this->A / 2 + this->A2, this->A / 2 - this->A2),
            CMy2DPoint(-this->A / 2, this->A / 2 - this->A2),
            CMy2DPoint(new_x, new_y));
        if (!isInInnerA2Triangle) {
            return false;
        }
    }

    // проверка на выход за треугольник A3
    bool isInA3Square =
        (-this->A / 2 <= new_x && new_x <= -this->A / 2 + this->A3) &&
        (-this->A / 2 <= new_y && new_y <= -this->A / 2 + this->A3);
    if (isInA3Square) {
        bool isInnerA3Triangle = IsInTriangle(
            CMy2DPoint(-this->A / 2, -this->A / 2 + this->A3),
            CMy2DPoint(-this->A / 2 + this->A3, -this->A / 2 + this->A3),
            CMy2DPoint(-this->A / 2 + this->A3, -this->A / 2),
            CMy2DPoint(new_x, new_y));
        if (!isInnerA3Triangle) {
            return false;
        }
    }

    // все проверки прошли успешно, точка внутри фигуры.
    return true;
}

void CMy2DObjectB11::Draw(CDC &dc) {
    CMy2DPoint x0y0(200, 200);

    int myArray[10][2] = {
    { this->A / 2,
      -this->A / 2},
    { -this->A / 2 + this->A2,
      -this->A / 2},
    { -this->A / 2,
      -this->A / 2 + this->A2},
    { -this->A / 2,
      this->A / 2 - this->A3},
    { -this->A / 2 + this->A3,
      this->A / 2},
    { this->A / 2,
      this->A / 2},
    { this->A / 2,
      this->A / 2 - this->A1 / 2},
    { this->A / 2 - this->A1,
      this->A / 2 - this->A1 / 2},
    { this->A / 2 - this->A1,
      -this->A1 / 2},
    { this->A / 2,
      -this->A1 / 2}
    };
    int newArray[10][2];

    // поворот точек относительно начала координат
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 1; j++) {
            if (j == 0) {
                newArray[i][j] = myArray[i][j] * cos(this->m_dAngle) + myArray[i][j + 1] *sin(this->m_dAngle);
            }
            else {
                newArray[i][j] = -myArray[i][j-1] * sin(this->m_dAngle) + myArray[i][j] * cos(this->m_dAngle);
            }
        }    
    }

    dc.MoveTo(this->m_center.GetX() + newArray[0][0], this->m_center.GetY() + newArray[0][1]);
                                                                              
    dc.LineTo(this->m_center.GetX() + newArray[1][0], this->m_center.GetY() + newArray[1][1]);
    dc.LineTo(this->m_center.GetX() + newArray[2][0], this->m_center.GetY() + newArray[2][1]);
    dc.LineTo(this->m_center.GetX() + newArray[3][0], this->m_center.GetY() + newArray[3][1]);
    dc.LineTo(this->m_center.GetX() + newArray[4][0], this->m_center.GetY() + newArray[4][1]);
    dc.LineTo(this->m_center.GetX() + newArray[5][0], this->m_center.GetY() + newArray[5][1]);
    dc.LineTo(this->m_center.GetX() + newArray[6][0], this->m_center.GetY() + newArray[6][1]);
    dc.LineTo(this->m_center.GetX() + newArray[7][0], this->m_center.GetY() + newArray[7][1]);
    dc.LineTo(this->m_center.GetX() + newArray[8][0], this->m_center.GetY() + newArray[8][1]);
    dc.LineTo(this->m_center.GetX() + newArray[9][0], this->m_center.GetY() + newArray[9][1]);
    dc.LineTo(this->m_center.GetX() + newArray[10][0],this->m_center.GetY() + newArray[10][1]);
    dc.LineTo(this->m_center.GetX() + newArray[0][0], this->m_center.GetY() + newArray[0][1]);

    // построение координатной сетки
    dc.MoveTo(0, x0y0.GetY());
    dc.LineTo(500, x0y0.GetY());
    dc.MoveTo(x0y0.GetX(), 0);
    dc.LineTo(x0y0.GetX(), 500);
}



