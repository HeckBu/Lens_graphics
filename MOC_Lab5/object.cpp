#include "object.h"

// Last vertion
/*
//-------------------------------------------------------------------------------------------------
Object::Object(int size_x, int size_y, double dx) : SampleComplex(size_x, size_y), m_dx(dx)
{
}
//-------------------------------------------------------------------------------------------------
Object::~Object()
{

}
//-------------------------------------------------------------------------------------------------
// задание координаты
double Object::CalcCoord(int count, double dx)
{
    return (count * dx) / 256;
}
//-------------------------------------------------------------------------------------------------
// создание предмета в виде бинарной периодической решетки
void Object::CreateLineAndSpace(double period, double width)
{
    CreateLineAndSpaceCommon(period, width, 0., 0., 1., 0., 0.);
}
//-------------------------------------------------------------------------------------------------
// создание предмета в виде полутоновой периодической решетки
void Object::CreateLineAndSpaceAttenuaten(double period, double width)
{
    CreateLineAndSpaceCommon(period, width, 0.06, PI, 1., 0., 0);
}
//-------------------------------------------------------------------------------------------------
// создание предмета в виде периодической решетки
// period - период решетки (к.е.)
// width - ширина линии (к.е.)
void Object::CreateLineAndSpaceCommon(double period, double width,
    double ob_module_line, double ob_phase_line,
    double ob_module_space, double ob_phase_space, double ob_phase_space2)
{
    // период и ширина решетки в кол-ве элементов
    int i_period = period / m_dx;
    int i_width = width / m_dx;

    // значения для соs и sin части комплексного числа (представление по формуле Эйлера)
    // для линии и промежутков
    double ob_c_line = cos(ob_phase_line);
    double ob_s_line = sin(ob_phase_line);
    double ob_c_space = cos(ob_phase_space);
    double ob_s_space = sin(ob_phase_space);
    double ob_c_space2 = cos(ob_phase_space2);
    double ob_s_space2 = sin(ob_phase_space2);

    // для четного кол-ва элементов в выборке ширина линии должна быть четной, для нечетного - четной
    if ((512 % 2 == 0 && i_width % 2 != 0) || (256 % 2 != 0 && i_width % 2 == 0))
        i_width++;
    // ширина промежутка в кол-ве элементов
    int i_space = i_period - i_width;
    // определение, что должно быть на краю выборки - линия или промежуток
    bool bFirstline = false;
    int  i_first = (256 / 2 - i_width / 2) / i_period;
    i_first = 256 / 2 - i_width / 2 - i_first * i_period;
    if (i_first - i_space > 0)
    {
        i_first -= i_space;
        bFirstline = true;
    }

    // признаки, что будет следующее - линия или промежуток, и будет ли меняться фаза
    bool bPhase = true, bLine = false;
    for (int j = 0; j < 256; j++) // size
    {
        // промежуток
        if ((bFirstline && ((j >= (i_first + i_space) && j < (i_first + i_period)) || j < i_first)) ||
            (!bFirstline && (j >= (i_first) && j < (i_first + i_width))))
        {
            if (bLine)
                bPhase = !bPhase;
            for (int i = 0; i < 256; i++) // size
            {
                if (bPhase)
                    operator()(i, j) = ob_module_space * complex<double>(ob_c_space, ob_s_space);
                else
                    operator()(i, j) = ob_module_space * complex<double>(ob_c_space2, ob_s_space2);
            }
            bLine = false;
        }
        // линия
        else
        {
            for (int i = 0; i < 256; i++) // size
            {
                operator()(i, j) = ob_module_line * complex<double>(ob_c_line, ob_s_line);
            }
            bLine = true;
        }
        if ((j + 1) >= i_first + i_period)
            i_first += i_period;
    }
}
*/

//-----------------------------------------------------------------------------------------------—
Object::Object(int size_x, int size_y, double dx) : SampleComplex(size_x, size_y), m_dx(dx)
{
    size = size_x;
}
//-----------------------------------------------------------------------------------------------—
Object::~Object()
{
}
//-----------------------------------------------------------------------------------------------—
// создание предмета в виде полуплоскости
void Object::CreateHalfPlane()
{
    for (int j = 0; j < size; j++)
{
    for (int i = 0; i < size; i++)
{
    if (i < size / 2)
        operator()(i, j) = complex<double>(0., 0.);
    else
    operator()(i, j) = complex<double>(1., 0.);
}
}
}
//-----------------------------------------------------------------------------------------------—
// задание координаты
double Object::CalcCoord(int count, double dx)
{
    return (count * dx) / (double)size;
}
//-----------------------------------------------------------------------------------------------—
// создание предмета в виде радиальной миры
void Object::CreateTargetStar(int count)
{
    double dStep = 180 / count;
    for (int j = 0; j < size; j++)
    {
        double y = CalcCoord(j, m_dx);
        for (int i = 0; i < size; i++)
        {
            double x = CalcCoord(i, m_dx);
            double dAngle = atan2(y, x) * 180 / PI + 180; // вычисление угла в диапазоне 0 - 360 град.
            if (int(dAngle / dStep) % 2 != 0)
                operator()(i, j) = complex<double>(0., 0.);
            else
            operator()(i, j) = complex<double>(1., 0.);
        }
    }
}
//-----------------------------------------------------------------------------------------------—
// создание предмета в виде бинарной периодической решетки
void Object::CreateLineAndSpace(double period, double width)
{
    CreateLineAndSpaceCommon(period, width, 0., 0., 1., 0., 0.);
}
//-----------------------------------------------------------------------------------------------—
// создание предмета в виде полутоновой периодической решетки
void Object::CreateLineAndSpaceAttenuaten(double period, double width)
{
    CreateLineAndSpaceCommon(period, width, 0.06, PI, 1., 0., 0);
}
//-----------------------------------------------------------------------------------------------—
// создание предмета в виде чередующейся полутоновой периодической решетки
void Object::CreateLineAndSpaceAlternating(double period, double width)
{
    CreateLineAndSpaceCommon(period, width, 0., 0., 1., 0., PI);
}
//-----------------------------------------------------------------------------------------------—
// создание предмета в виде периодической решетки
// period - период решетки (к.е.)
// width - ширина линии (к.е.)
void Object::CreateLineAndSpaceCommon(double period,
                                      double width,
                                      double ob_module_line,
                                      double ob_phase_line,
                                      double ob_module_space,
                                      double ob_phase_space,
                                      double ob_phase_space2)
{
// период и ширина решетки в кол-ве элементов
int i_period = period / m_dx;
int i_width = width / m_dx;

// значения для соs и sin части комплексного числа (представление по формуле Эйлера)
// для линии и промежутков
double ob_c_line = cos(ob_phase_line);
double ob_s_line = sin(ob_phase_line);
double ob_c_space = cos(ob_phase_space);
double ob_s_space = sin(ob_phase_space);
double ob_c_space2 = cos(ob_phase_space2);
double ob_s_space2 = sin(ob_phase_space2);

// для четного кол-ва элементов в выборке ширина линии должна быть четной, для нечетного - четной
if ((size % 2 == 0 && i_width % 2 != 0) || (size % 2 != 0 && i_width % 2 == 0)) {
    i_width++;
}
// ширина промежутка в кол-ве элементов
int i_space = i_period - i_width;
// определение, что должно быть на краю выборки - линия или промежуток
bool bFirstline = false;
int i_first = (size / 2 - i_width / 2) / i_period;
i_first = size / 2 - i_width / 2 - i_first * i_period;
if (i_first - i_space > 0)
{
    i_first -= i_space;
    bFirstline = true;
}

// признаки, что будет следующее - линия или промежуток, и будет ли меняться фаза
bool bPhase = true, bLine = false;
for (int j = 0; j < size; j++)
{
    if ((bFirstline && ((j >= (i_first + i_space) && j < (i_first + i_period)) || j < i_first)) ||
            (!bFirstline && (j >= (i_first) && j < (i_first + i_width))))
    {
    if (bLine)
        bPhase = !bPhase;
    for (int i = 0; i < size; i++)
    {
        if (bPhase)
            operator()(i, j) = ob_module_space * complex<double>(ob_c_space, ob_s_space);
        else
            operator()(i, j) = ob_module_space * complex<double>(ob_c_space2, ob_s_space2);
    }
    bLine = false;
}
// линия
else
{
    for (int i = 0; i < size; i++)
    {
        operator()(i, j) = ob_module_line * complex<double>(ob_c_line, ob_s_line);
    }
    bLine = true;
    }
    if ((j + 1) >= i_first + i_period)
        i_first += i_period;
    }
}
//-------------------------------------------------------------------------------------------------
