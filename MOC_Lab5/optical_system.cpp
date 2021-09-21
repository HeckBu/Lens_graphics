#include "optical_system.h"
using namespace std;

OpticalSystem::OpticalSystem(double lambda,
                             double aperture,
                             double dro,
                             double dx,
                             double pupil_coverage)
{
m_lambda = lambda;
m_aperture = aperture;
m_pupil_coverage = pupil_coverage;
m_dro = dro;
m_dx = dx;
}


//-----------------------------------------------------------------------------------------------—
OpticalSystem::~OpticalSystem()
{
}
//-----------------------------------------------------------------------------------------------—
void OpticalSystem::CalcCoherent(const Object& object, SampleComplex& image)
{
image = object;
this->Pupil(image);
FFT res((int)m_dro, (int)m_dro);
res.Run1(image);
}
//-------------------------------------------------------------------------------------—
void OpticalSystem::CalcNonCoherent(const Object& object, SampleComplex& image)
{
FFT tranform((int)m_dro, (int)m_dro);
//вычисление фурье-образа распределения интенсивности на предмете
image = object;
image.CalcIntens();
tranform.Run(image);
image *= m_dro / m_pupil_coverage/m_pupil_coverage;
//вычисление нормированной ФРТ (PSF)
SampleComplex field((int)m_dro, (int)m_dro);
field.CreateCirc(m_pupil_coverage / m_dro);
tranform.Run1(field);
field *= m_pupil_coverage*m_pupil_coverage / m_dro;
field.CalcIntens();
field *= 1 / (PI * PI);
//вычисление нормированной ОПФ
tranform.Run(field);
field *= m_dro / m_pupil_coverage/m_pupil_coverage;
field *= PI;
//вычисление фурье-образа распределения интенсивности на изображении
image *= field;
//вычисление распределения интенсивности на изображении
tranform.Run1(image);
image *= m_pupil_coverage*m_pupil_coverage / m_dro;
}
//-------------------------------------------------------------------------------------—
//вычисление ЧКХ (OTF)
void OpticalSystem::OTF(SampleComplex& image) {
FFT transform((int)m_dro, (int)m_dro);
//вычисление нормированной ФРТ
SampleComplex field((int)m_dro, (int)m_dro);
field.CreateCirc(m_pupil_coverage / m_dro);
image = field;
transform.Run1(image);
image *= m_pupil_coverage*m_pupil_coverage / m_dro;
image.CalcIntens();
image *= 1 / (PI * PI);
//вычисление нормированной ОПФ
transform.Run(image);
image *= m_dro / m_pupil_coverage/m_pupil_coverage;
image *= PI;
}
//вычисление ФРТ
void OpticalSystem::PSF(SampleComplex& image) {
FFT transform ((int)m_dro, (int)m_dro);
SampleComplex field((int)m_dro, (int)m_dro);
image = field;
image.CreateCirc(m_pupil_coverage / m_dro);
transform.Run1(image);
image *= m_pupil_coverage *m_pupil_coverage / m_dro;
image.CalcIntens();
image *= 1 / (PI * PI);
}

//-----------------------------------------------------------------------------------------------—
void OpticalSystem::Pupil(SampleComplex& field)
{
SampleComplex flag((int)m_dro, (int)m_dro);
flag.CreateCirc(m_pupil_coverage/m_dro);
FFT res((int)m_dro, (int)m_dro);
res.Run(field);
field *= flag;
}
