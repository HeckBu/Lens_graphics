///////////////////////////////////////////////////////////////////////////////////////////////////
// sample_complex.cpp
// Двумерная комплексная выборка. Размер выборки по x и y одинаковый.
//
// Кафедра Прикладной и компьютерной оптики, http://aco.ifmo.ru
// Университет ИТМО
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "sample_complex.h"
//-------------------------------------------------------------------------------------------------
// полный конструктор
SampleComplex::SampleComplex(int size_x, int size_y) : Sample<complex<double>> (size_x, size_y)
{
}
//-------------------------------------------------------------------------------------------------
// деструктор
SampleComplex::~SampleComplex()
{

}
//-------------------------------------------------------------------------------------------------
// вычисление интенсивности выборки (квадрат модуля)
// записывается в вещественную часть, мнимая часть обнуляется
void SampleComplex::CalcIntens()
{
    for(int i=0; i < m_size_x; ++i)
    {
        for(int j=0; j < m_size_y; ++j)
        {
            double res = operator()(i,j).real()*operator()(i,j).real() + operator()(i,j).imag()*operator()(i,j).imag();
            operator()(i,j) = complex<double>(res, 0.);
        }
    }
}
//-------------------------------------------------------------------------------------------------
// вывод в файл только вещественной части выборки
ostream& SampleComplex::PrintReal(ostream& out)
{
    for(int i = 0; i < m_size_x;i++)
    {
        for (int j=0; j < m_size_y; j++)
        {
            out << operator()(i,j).real() << " ";
        }
        out<<endl;
    }
    return out;
}
//-------------------------------------------------------------------------------------------------
// вывод в файл только мнимой части выборки
ostream& SampleComplex::PrintImag(ostream& out)
{
    for( int i=0;i<m_size_x;i++)
    {
        for (int j=0; j<m_size_y; j++)
        {
            out << operator()(i,j).imag()<<" ";
        }
        out << endl;
    }
    return out;
}
//-------------------------------------------------------------------------------------------------
// вывод в файл модуля выборки
ostream& SampleComplex::PrintModule(ostream& out)
{
    for( int i=0;i<m_size_x;i++)
    {
        for (int j=0; j<m_size_y; j++)
        {
            double res = sqrt(operator()(i,j).real()*operator()(i,j).real() + operator()(i,j).imag()*operator()(i,j).imag());
            out << res << " ";
        }
        out << endl;
    }
    return out;
}
//-------------------------------------------------------------------------------------------------
// вывод в файл модуля выборки
ostream& SampleComplex::PrintPhase(ostream& out)
{
    for( int i=0;i<m_size_x;i++)
    {
        for (int j=0; j<m_size_y; j++)
        {
            double res = atan2(operator()(i,j).imag(), operator()(i,j).real());
            out << res << " ";
        }
        out << endl;
    }
    return out;
}
//-------------------------------------------------------------------------------------------------
// вывод в файл интенсивности выборки (квадрат модуля)
ostream& SampleComplex::PrintIntens(ostream& out)
{
    for( int i=0;i<m_size_x;i++)
    {
        for (int j=0; j<m_size_y; j++)
        {
            double res = operator()(i,j).real()*operator()(i,j).real() + operator()(i,j).imag()*operator()(i,j).imag();
            out << res<<" ";
        }
        out<<endl;
    }
    return out;
}
//-------------------------------------------------------------------------------------------------
void SampleComplex::Create1DFunc(double dx)
{
    m_size_y = 1;
    for (int i = 0; i < m_size_x; i++) {
        this -> operator()(i, 0) = 1 + cos(PI * (-8 + dx * i));
    }
}
double SampleComplex::CreateCirc(double dx)
{
    for (int i = 0; i < m_size_x; i++) {
        for (int j = 0; j < m_size_y; j++) {
            //double x = -10 + dx * i, y = -10 + dx * j;
            double x = -1*m_size_x*dx/2 + dx * i, y = -1*m_size_y*dx/2 + dx * j;
            if (x * x + y * y <= 1) this -> operator()(i, j) = 1.;
            else this -> operator()(i, j) = 0.;
        }
    }
    return 0;
}
double SampleComplex::CreatePupil(double dx)
{
    for (int i = 0; i < m_size_x; i++) {
        for (int j = 0; j < m_size_y; j++) {
            //double x = -8 + dx * i, y = -8 + dx * j;
            double x = -1*m_size_x*dx/2 + dx * i, y = -1*m_size_y*dx/2 + dx * j;
            if (x * x + y * y <= 1) this -> operator()(i, j) = exp(-PI * (x * x + y * y));
            else this -> operator()(i, j) = 0.;
        }
    }
    return 0;
}

