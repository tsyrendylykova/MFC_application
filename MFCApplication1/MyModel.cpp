#include "stdafx.h"
#include "MyModel.h"
#define _USE_MATH_DEFINES
#include <math.h>


MyModel::MyModel()
{
}


MyModel::~MyModel()
{
    for (int i = 0; m_Objects.size(); i++) {
        delete m_Objects[i];
    }
}


double MyModel::GetA(int figure_index) { return this->m_Objects[figure_index]->GetA(); }
double MyModel::GetA1(int figure_index) { return this->m_Objects[figure_index]->GetA1(); }
double MyModel::GetA2(int figure_index) { return this->m_Objects[figure_index]->GetA2(); }
double MyModel::GetA3(int figure_index) { return this->m_Objects[figure_index]->GetA3(); }
double MyModel::GetAngle(int figure_index) { return this->m_Objects[figure_index]->GetAngle(); }
CMy2DPoint MyModel::GetCenter(int figure_index) { return this->m_Objects[figure_index]->GetCenter(); }

void MyModel::SetA(int figure_index, double A) { this->m_Objects[figure_index]->SetA(A); }
void MyModel::SetA1(int figure_index, double A1) { this->m_Objects[figure_index]->SetA1(A1); }
void MyModel::SetA2(int figure_index, double A2) { this->m_Objects[figure_index]->SetA2(A2); }
void MyModel::SetA3(int figure_index, double A3) { this->m_Objects[figure_index]->SetA3(A3); }
void MyModel::SetAngle(int figure_index, double Angle) { this->m_Objects[figure_index]->SetAngle(Angle); }
void MyModel::SetCenter(int figure_index, CMy2DPoint& point) { this->m_Objects[figure_index]->SetCenter(point); }

void MyModel::Draw(CDC &dc)
{
    for (int i = 0; i < m_Objects.size(); i++) {
        m_Objects[i]->Draw(dc);
    }
}

void MyModel::AddFigure(int max_x, int max_y)
{
    this->m_Objects.push_back(new CMy2DObjectB11(rand() % max_x, rand() % max_y, 120, 60, 40, 20, M_PI / 4));
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

void MyModel::MoveFigure(int figure_index, double dX, double dY) {
    this->m_Objects[figure_index]->Move(dX, dY);
}

void MyModel::Rotate(int figure_index, double dAngle) {
    this->m_Objects[figure_index]->SetAngle(dAngle);
}

void MyModel::Draw_buff(CDC &dcMem) {

    for (int i = 0; i < m_Objects.size(); i++) {
        m_Objects[i]->Draw(dcMem);
    }
}