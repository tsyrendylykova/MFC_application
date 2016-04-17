#include "stdafx.h"
#include "MyModel.h"
#define _USE_MATH_DEFINES
#include <math.h>


MyModel::MyModel()
{
}


MyModel::~MyModel()
{
    // clear the memory allocated for the circles
    for (int i = 0; m_Objects.size(); i++) {
        delete m_Objects[i];
    }
}

void MyModel::Draw(CDC &dc)
{
    for (int i = 0; i < m_Objects.size(); i++) {
        m_Objects[i]->Draw(dc);
    }
}

void MyModel::AddFigure(int max_x, int max_y)
{
    this->m_Objects.push_back(new CMy2DObjectB11(rand() % max_x, rand() % max_y, 6, 3, 2, 1, 0));
}

int MyModel::FindObject(double x, double y) {
    int nObj = -1;
    for (int i = m_Objects.size() - 1; i >= 0; i--) {
        if (m_Objects[i]->IsInside(x, y)) {
            nObj = i;
            break;
        }
    }
    return nObj;
}