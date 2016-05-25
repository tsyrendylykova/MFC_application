#pragma once
#include "My2DObjectB11.h"
#include <vector>
class MyModel
{
    std::vector<CMy2DObjectB11 *> m_Objects;
public:
    MyModel();
    ~MyModel();

    double GetA(int figure_index);
    double GetA1(int figure_index);
    double GetA2(int figure_index);
    double GetA3(int figure_index);
    double GetAngle(int figure_index);
    CMy2DPoint GetCenter(int figure_index);

    void SetA(int figure_index, double A);
    void SetA1(int figure_index, double A1);
    void SetA2(int figure_index, double A2);
    void SetA3(int figure_index, double A3);
    void SetAngle(int figure_index, double Angle);
    void SetCenter(int figure_index, CMy2DPoint& point);
    void Draw(CDC &dc);

    // if the point is inside of a figure,
    // the function will return its number, otherwise -1
    int FindObject(double x, double y);
    void AddFigure(int max_x, int max_y);
    void MoveFigure(int figure_index, double dX, double dY);
    void Rotate(int figure_index, double dAngle);
    void Draw_buff(CDC &dc);
};

