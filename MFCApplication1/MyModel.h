#pragma once
#include "My2DObjectB11.h"
#include <vector>
class MyModel
{
    std::vector<CMy2DObjectB11 *> m_Objects;
public:
    MyModel();
    ~MyModel();

    void Draw(CDC &dc);
    
    // if the point is inside of a figure,
    // the function will return its number, otherwise -1
    int FindObject(double x, double y);

    void AddFigure(int max_x, int max_y);

    void MoveFigure(int figure_index, double dX, double dY);
};

