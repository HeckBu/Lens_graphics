///////////////////////////////////////////////////////////////////////////////////////////////////
// sample.h
// Шаблон двумерной выборки. Размер выборки по x и y одинаковый.
//
// Кафедра Прикладной и компьютерной оптики, http://aco.ifmo.ru
// Университет ИТМО
///////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined  SAMPLE_H
#define SAMPLE_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <exception>
#include <vector>

//-------------------------------------------------------------------------------------------------
using namespace std;

template <class PAR>
class Sample
{
protected:
    // число элементов выборки (одинаковое по x и y)
    //int m_size;
    // число элементов выборки по x и y
    int m_size_x, m_size_y;
    // указатель на динамический массив данных
    std::vector<PAR> m_data;

public:
    // пустой конструктор запрещен
    explicit Sample();
    // полный конструктор
    // size - количество элементов, одинаковое по x и y (size*size)
    Sample(int size_x, int size_y);
    // деструктор
    virtual ~Sample();

    // размер выборки
    //int GetSize() const;
    // размер выборки по X
    int GetSizeX() const;
    // размер выборки по Y
    int GetSizeY() const;

    // оператор получения значения элемента с номером i,j
    PAR& operator()(int i, int j);
    // оператор получения const значения элемента с номером i,j
    const PAR& operator()(int i, int j) const;

    // получение указателя на массив данных
    PAR* GetPointer();

    // инициализация всех элементов выборки одинаковым значением value
    void SetValue(PAR value);

    // операции с выборкой и числом
    // сложение всех элементов выборки и числа
    Sample<PAR>& operator+=(PAR value);
    // умножение всех элементов выборки на число
    Sample<PAR>& operator*=(PAR value);
    // деление всех элементов выборки на число
    Sample<PAR>& operator/=(PAR value);

    // операции с двумя выборками
    // присваивание
    Sample<PAR>& operator= (const Sample<PAR> &temp);
    // поэлементное сложение двух выборок
    Sample<PAR>& operator+=(const Sample<PAR> &temp);
    // поэлементное перемножение двух выборок
    Sample<PAR>& operator*=(const Sample<PAR> &temp);

    // перегрузка оператора вывода выборки в файл
    friend ostream& operator<< (ostream& out, const Sample& other);


    // вычисление реальной координаты точки с координатами i
    // (выборка квадратная, поэтому достаточно одной функции)
    // i - номер точки
    // dx - шаг по выборке
    double CalcCoordX(int i, double dx=1.) const;

    // вычисление реальной координаты точки с координатами i
    // (выборка квадратная, поэтому достаточно одной функции)
    // i - номер точки
    // dx - шаг по выборке
    double CalcCoordY(int i, double dx=1.) const;
};
//-------------------------------------------------------------------------------------------------
// полный конструктор
template <class PAR>
Sample<PAR>::Sample(int size_x, int size_y)
{
    m_size_x = size_x;
    m_size_y = size_y;
    m_data.resize(m_size_x * m_size_y);
}
//-------------------------------------------------------------------------------------------------
// деструктор
template <class PAR>
Sample<PAR>::~Sample()
{
}
//-------------------------------------------------------------------------------------------------
// размер выборки
/*template <class PAR>
int Sample<PAR>::GetSize() const
{
    return(m_size);
}*/
// размер выборки по X
template <class PAR>
int Sample<PAR>::GetSizeX() const
{
    return(m_size_x);
}
// размер выборки по Y
template <class PAR>
int Sample<PAR>::GetSizeY() const
{
    return(m_size_y);
}
//-------------------------------------------------------------------------------------------------
// оператор получения значения элемента с номером i,j
template <class PAR>
PAR& Sample<PAR>::operator()(int i, int j)
{
    return (m_data[i*m_size_x+j]);
}
//-------------------------------------------------------------------------------------------------
// оператор получения const значения элемента с номером i,j
template <class PAR>
const PAR& Sample<PAR>::operator()(int i, int j) const
{
    return (m_data[i*m_size_x+j]);
}
//-------------------------------------------------------------------------------------------------
// получение указателя
template <class PAR>
PAR* Sample<PAR>::GetPointer()
{
    return &m_data[0];
}
//-------------------------------------------------------------------------------------------------
// инициализация всех элементов выборки одинаковым значением
template <class PAR>
void Sample<PAR>::SetValue(PAR value)
{
    for(int i=0;i<m_size_x*m_size_y;i++)
    {
        m_data[i]=value;
    }
}
//-------------------------------------------------------------------------------------------------
// сложение всех элементов выборки и числа
template <class PAR>
Sample<PAR>& Sample<PAR>::operator+=(PAR value)
{
    for(int i=0;i<m_size_x*m_size_y;i++)
    {
        m_data[i]+=value;
    }
    return *this;
}
//-------------------------------------------------------------------------------------------------
// умножение всех элементов выборки на число
template <class PAR>
Sample<PAR>& Sample<PAR>::operator*=(PAR value)
{
    for(int i=0;i<m_size_x*m_size_y;i++)
    {
        m_data[i]*=value;
    }
    return *this;
}
//-------------------------------------------------------------------------------------------------
// деление всех элементов выборки на число
template <class PAR>
Sample<PAR>& Sample<PAR>::operator/=(PAR value)
{
    for(int i=0;i<m_size_x*m_size_y;i++)
    {
        m_data[i]/=value;
    }
    return *this;
}
//-------------------------------------------------------------------------------------------------
// присваивание
template <class PAR>
Sample<PAR>& Sample<PAR>::operator=(const Sample<PAR> &temp)
{
    m_size_x = temp.m_size_x;
    m_size_y = temp.m_size_y;
    m_data = temp.m_data;

    return *this;
    /*m_size=temp.m_size;
    delete[] m_data;
    m_data=new PAR[m_size*m_size];

    for(int i=0;i<m_size*m_size;i++)
    {
        m_data[i]=temp.m_data[i];
    }
    return *this;*/
}

//-------------------------------------------------------------------------------------------------
// поэлементное сложение двух выборок
template <class PAR>
Sample<PAR>& Sample<PAR>::operator+=(const Sample<PAR> &temp)
{
    if(m_size_x != temp.m_size_x || m_size_y != temp.m_size_y)
        throw("Sample::operator+= - samples sizes not valid");

    for(int i=0;i<m_size_x*m_size_y;i++)
    {
        m_data[i]+=temp.m_data[i];
    }
    return *this;
}
//-------------------------------------------------------------------------------------------------
// поэлементное перемножение двух выборок
template <class PAR>
Sample<PAR>& Sample<PAR>::operator*=(const Sample<PAR> &temp)
{
    if(m_size_x != temp.m_size_x || m_size_y != temp.m_size_y)
        throw("Sample::operator+= - samples sizes not valid");

    for(int i=0;i<m_size_x*m_size_y;i++)
    {
        m_data[i]*=temp.m_data[i];
    }
    return *this;
}
//-------------------------------------------------------------------------------------------------
// вычисление реальной координаты точки
// i - номер точки
// dx - шаг по выборке
template <class PAR>
double Sample<PAR>::CalcCoordX(int i, double dx) const
{
    return (i - m_size_x/2.)*dx;
}

template <class PAR>
double Sample<PAR>::CalcCoordY(int i, double dy) const
{
    return (i - m_size_y/2.)*dy;
}
//-------------------------------------------------------------------------------------------------
// перегрузка оператора вывода выборки в файл
template <class PAR>
ostream& operator<< (ofstream& out, const Sample<PAR> &other)
{
    for(int i = 0; i < other.m_size_x ;i++)
    {
        for (int j = 0; j < other.m_size_y; j++)
        {
            out << other(i,j) << "\t";
        }
        out << "\n";
    }
    return out;
}



//-------------------------------------------------------------------------------------------------
#endif //defined SAMPLE_H
