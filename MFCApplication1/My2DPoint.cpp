#include "stdafx.h"
#include "My2DPoint.h"


CMy2DPoint::CMy2DPoint()
{
}

CMy2DPoint::~CMy2DPoint()
{
}

CMy2DPoint operator*(double k, const CMy2DPoint& rp) {
    return CMy2DPoint(k * rp.m_x, k * rp.m_y);
}

std::ostream& operator <<(std::ostream& out, CMy2DPoint& rp) {
    out << "(" << rp.m_x << "," << rp.m_y << ")";
    return out;
}
std::istream& operator >>(std::istream& in, CMy2DPoint& rp) {
    in >> rp.m_x >> rp.m_y;
    return in;
}
