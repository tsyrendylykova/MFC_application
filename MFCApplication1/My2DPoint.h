#pragma once
#include<iostream>
#include<assert.h>
#define eps 1e-10

class CMy2DPoint {
private:
    double m_x, m_y;
public:
    CMy2DPoint();
    CMy2DPoint(double x, double y) { m_x = x; m_y = y; };
    ~CMy2DPoint();

    double GetX() const { return m_x; }
    double GetY() const { return m_y; }

    void SetX(double new_x) { m_x = new_x; }
    void SetY(double new_y) { m_y = new_y; }

    CMy2DPoint operator +(const CMy2DPoint& rp) {
        return CMy2DPoint(m_x + rp.m_x, m_y + rp.m_y);
    }
    CMy2DPoint operator -(const CMy2DPoint& rp) {
        return CMy2DPoint(m_x - rp.m_x, m_y - rp.m_y);
    }
    CMy2DPoint operator *(double k) {
        return CMy2DPoint(k * m_x, k * m_y);
    }
    double operator *(const CMy2DPoint& rp) {
        return (rp.m_x * m_x + rp.m_y * m_y);
    }

    bool operator ==(const CMy2DPoint& rp) {
        return (abs(m_x - rp.m_x) < eps && abs(m_y - rp.m_y) < eps);
    }
    bool operator !=(const CMy2DPoint& rp) {
        return !(*this == rp);
    }

    CMy2DPoint operator /(double k) {
        assert(k != 0);
        return (*this) * (1 / k);
    }

    friend CMy2DPoint operator*(double k, const CMy2DPoint& rp);
    friend std::ostream& operator <<(std::ostream& out, CMy2DPoint& rp);
    friend std::istream& operator >>(std::istream& in, CMy2DPoint& rp);

};

CMy2DPoint operator*(double k, const CMy2DPoint& rp);
std::ostream& operator <<(std::ostream& out, CMy2DPoint& rp);
std::istream& operator >>(std::istream& in, CMy2DPoint& rp);
