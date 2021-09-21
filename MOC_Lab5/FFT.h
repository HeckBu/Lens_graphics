#ifndef FFT_H
#define FFT_H

#include "fftw3.h"
#include "sample_complex.h"
#include <math.h>


class FFT
{
public:
    // направление преобразования Фурье:
    enum EDirection
    {
        eDirect,   // прямое
        eReverse   // обратное
    };
    // размерность преобразования Фурье:
    enum EDimentions
    {
        e1D,      // одномерное
        e2D       // двумерное
    };
    //конструктор
    // size_x, size_y - размеры выборки, по умолчанию size_y=1 (одномерная выборка)
    // direction - направление (прямое | обратное), по умолчанию прямое
    // dimension - размерность (одномерное | двумерное), по умолчанию одномерное

    FFT(int size_x, int size_y = 1, EDirection direction = eDirect, EDimentions dimension = e1D);

    // функция полного сдвигового преобразования Фурье
    //		(сдвиг выборки и спектра и учет коэф-та 1/sqrt(n*m) )
    // sample - исходная выборка и результат преобразования
    void Run(SampleComplex& sample);
    void Run1(SampleComplex& sample);

private:
    // план вычислений преобразования Фурье
    fftw_plan m_plan;
    // направление (прямое | обратное)
    EDirection m_direction;
    // размерность (одномерное | двумерное)
    EDimentions m_dimension;
    // размер выборки по X, Y
    int m_size_x, m_size_y;
    // сдвиг выборки или спектра на size/2
    // sample - выборка
    void ShiftSample(SampleComplex& sample);


};
#endif // FFT_H
