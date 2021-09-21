// Предыдущая версия
/*
#ifndef OBJECT_H
#define OBJECT_H
//#define size 256

#include "sample_complex.h"


//-------------------------------------------------------------------------------------------------
class Object : public SampleComplex
{
private:
    // шаг по предмету (к.е.)
    double m_dx;

public:
    // конструктор
    // size - количество элементов, одинаковое по x и y (size*size)
    // dx - шаг по предмету (к.е.)
    Object(int size_x, int size_y, double dx);
    ~Object();
    //задание координаты в канонических ед.
    double CalcCoord(int count, double dx);
    // создание предмета в виде бинарной периодической решетки
    // period - период решетки (к.е.)
    // width  - ширина линии (к.е.)
    void CreateLineAndSpace(double period, double width);
    // создание предмета в виде полутоновой периодической решетки
    // period - период решетки (к.е.)
    // width  - ширина линии (к.е.)
    void CreateLineAndSpaceAttenuaten(double period, double width);
    // создание предмета в виде чередующейся полутоновой периодической решетки
    // period - период решетки (к.е.)
    // width  - ширина линии (к.е.)

private:
    // универсальная функция создания предмета в виде чередующейся периодической решетки
    // period - период решетки (к.е.)
    // width  - ширина линии (к.е.)
    // ob_module_line, ob_phase_line - модуль и фаза "линии", т.е. непрозрачной части решетки
    // ob_module_space, ob_phase_space - модуль и фаза "промежутка", т.е. прозрачной части решетки
    // ob_phase_space2 - фаза второго "промежука", для чередующейся решетки
    void CreateLineAndSpaceCommon(double period, double width,
        double ob_module_line = 1., double ob_phase_line = 0,
        double ob_module_space = 0., double ob_phase_space = 0,
        double ob_phase_space2 = 0);
};
*/

#if !defined OBJECT_H
#define OBJECT_H

#include "sample_complex.h"
//-----------------------------------------------------------------------------------------------—
class Object : public SampleComplex
{
private:
// шаг по предмету (к.е.)
double m_dx;
int size;
public:
// конструктор
// size - количество элементов, одинаковое по x и y (size*size)
// dx - шаг по предмету (к.е.)
Object(int size_x, int size_y, double dx);
~Object();
//задание координаты в канонических ед.
double CalcCoord(int count, double dx);
// создание предмета в виде бинарной периодической решетки
// period - период решетки (к.е.)
// width - ширина линии (к.е.)
void CreateLineAndSpace(double period, double width);
// создание предмета в виде полутоновой периодической решетки
// period - период решетки (к.е.)
// width - ширина линии (к.е.)
void CreateLineAndSpaceAttenuaten(double period, double width);
// создание предмета в виде чередующейся полутоновой периодической решетки
// period - период решетки (к.е.)
// width - ширина линии (к.е.)
void CreateLineAndSpaceAlternating(double period, double width);
// создание предмета в виде полуплоскости
void CreateHalfPlane();

// создание предмета в виде радиальной миры
// count - количество секторов (линий)
void CreateTargetStar(int count);

private:
// универсальная функция создания предмета в виде чередующейся периодической решетки
// period - период решетки (к.е.)
// width - ширина линии (к.е.)
// ob_module_line, ob_phase_line - модуль и фаза "линии", т.е. непрозрачной части решетки
// ob_module_space, ob_phase_space - модуль и фаза "промежутка", т.е. прозрачной части решетки
// ob_phase_space2 - фаза второго "промежука", для чередующейся решетки
void CreateLineAndSpaceCommon(double period, double width,
double ob_module_line = 1., double ob_phase_line = 0,
double ob_module_space = 0., double ob_phase_space = 0,
double ob_phase_space2 = 0);
};

#endif // OBJECT_H

