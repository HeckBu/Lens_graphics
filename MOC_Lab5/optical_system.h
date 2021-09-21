#if !defined  OPTICAL_SYSTEM_H
#define OPTICAL_SYSTEM_H

#include "sample_complex.h"
#include "object.h"
#include "FFT.h"
#include <fftw3.h>
#include <math.h>


class OpticalSystem
{
private:
    // оптические параметры
    // длина волны
    double m_lambda;
    // апертура
    double m_aperture;
    // вычислительные параметры
    // охват зрачка (размер всей выборки в к.е.)
    double m_pupil_coverage;
    // шаг по зрачку в к.е.
    double m_dro;
    // шаг по предмету в к.е.
    double m_dx;

public:
    // конструктор
    // lambda - длина волны
    // aperture - апертура
    // dro - шаг по зрачку в к.е.
    // pupil_coverage - охват зрачка (размер всей выборки в к.е.)
    OpticalSystem(double lambda, double aperture, double dro, double dx, double pupil_coverage);
    //деструктор
    ~OpticalSystem();

    // вычисление когерентного изображения
    // object - предмет
    // image - изображение
    void CalcCoherent(const Object& object, SampleComplex& image);
    // вычисление некогерентного изображения
    // object - предмет
    // image - изображение
    void CalcNonCoherent(const Object& object, SampleComplex& image);
    // вычисление ЧКХ
    void OTF(SampleComplex& image);
    // вычисление ФРТ
    void PSF(SampleComplex& image);

private:
    // распространение поля через оптическую систему(зрачок)
    // field - поле, проходящее через зрачок
    void Pupil(SampleComplex& field);
};
//-------------------------------------------------------------------------------------------------
#endif // OPTICAL_SYSTEM.H

