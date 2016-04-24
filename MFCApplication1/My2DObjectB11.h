#pragma once
#include <iostream>
#include "My2DPoint.h"
#include <math.h>

class CMy2DObjectB11 {
    double A, A1, A2, A3;
    double m_dAngle;    // radians
    CMy2DPoint m_center;

    bool static isValid(double A, double A1, double A2, double A3) {
        if (A <= 0) return false;
        if (A1 < 0) return false;
        if (A2 < 0) return false;
        if (A3 < 0) return false;

        // стороны треугольников и квадрата не должны превышать сторону фигуры
        if ((A1 > A) ||
            (A2 > A) ||
            (A3 > A))
            return false;

        //  проверка на вхождение верхней левой точки квадрата A1 во внешний треугольник A2 
        if (A1 > 0 && A2 > 0 && IsInTriangle(
            CMy2DPoint(-A / 2, A / 2),
            CMy2DPoint(-A / 2 + A2, A / 2),
            CMy2DPoint(-A / 2, A / 2 - A2),
            CMy2DPoint(A / 2 - A1, A1 / 2))) {
            std::cout << "Пересечение сторон!";
            return false;
        }

        // проверка на вхождение нижней левой точки квадрата A1 во внешний треугольник A3
        if (A1 > 0 && A3 > 0 && IsInTriangle(
            CMy2DPoint(-A / 2, A / 2),
            CMy2DPoint(-A / 2 + A2, A / 2),
            CMy2DPoint(-A / 2, A / 2 - A2),
            CMy2DPoint(A / 2 - A1, -(A1 / 2)))) {
            std::cout << "Пересечение сторон!";
            return false;
        }

        // сумма сторон треугольников А2 и А3 не должна быть больше стороны фигуры
        if (A2 + A3 > A) return false;

        return true;
    }

public:
    CMy2DObjectB11() : m_center(0, 0) {
		this->A = 0;
        this->A1 = 0;
        this->A2 = 0;
        this->A3 = 0;
        this->m_dAngle = 0;
    }
    CMy2DObjectB11(double centerX, double centerY, double A, double A1, double A2, double A3, double Angle) : m_center(centerX, centerY) {
        this->A = A;
        this->A1 = A1;
        this->A2 = A2;
        this->A3 = A3;
        this->m_dAngle = Angle;
    };

    CMy2DObjectB11(const CMy2DPoint& center, double A, double A1, double A2, double A3, double Angle)
        : m_center(center.GetX(), center.GetY()) {
	    this->A = A;
        this->A1 = A1;
        this->A2 = A2;
        this->A3 = A3;
        this->m_dAngle = Angle;
	};

    double GetA()  const;
    double GetA1() const;
    double GetA2() const;
    double GetA3() const;
    double GetAngle() const;
    CMy2DPoint GetCenter() const;

    void SetA(double);
    void SetA1(double);
    void SetA2(double);
    void SetA3(double);
    void SetAngle(double);
    void SetCenter(const CMy2DPoint&);

    void Move(double dX, double dY, double dAngle = 0);
    void Move(const CMy2DPoint& delta, double dAngle = 0);
    void Rotate(double dAngle);
    bool IsInside(const CMy2DPoint& point);
    bool IsInside(double x, double y);
    bool static IsInTriangle(const CMy2DPoint& P1, const CMy2DPoint& P2, const CMy2DPoint& P3, const CMy2DPoint& PTest);

    void Draw(CDC &dc);
};



