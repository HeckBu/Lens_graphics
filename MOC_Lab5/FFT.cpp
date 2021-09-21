#include "FFT.h"

FFT::FFT(int size_x,
         int size_y,
         EDirection direction,
         EDimentions dimension) {
    m_direction = direction;
    m_dimension = dimension;
    m_size_x = size_x;
    m_size_y = size_y;
}
void FFT::ShiftSample(SampleComplex& sample) {
    for (int i = 0; i < sample.GetSizeX(); i++) {
        for (int j = 0; j < sample.GetSizeY(); j++) {
            sample(i, j) *= complex<double>(cos(i * PI), sin(i * PI));
            sample(i, j) *= complex<double>(cos(j * PI), sin(j * PI));
        }
    }
}
void FFT::Run(SampleComplex& sample) {
    if (sample.GetSizeY() == 1) {
        m_plan = fftw_plan_dft_1d(sample.GetSizeX(),
                                  (fftw_complex*)sample.GetPointer(),
                                  (fftw_complex*)sample.GetPointer(),
                                   FFTW_FORWARD, FFTW_ESTIMATE);
        ShiftSample(sample);
        fftw_execute(m_plan);
        sample *= complex<double>(1 / sqrt(sample.GetSizeX()), 0.);
        ShiftSample(sample);
        fftw_destroy_plan(m_plan);
    }
    else {
        m_plan = fftw_plan_dft_2d(sample.GetSizeX(),
                                  sample.GetSizeY(),
                                  (fftw_complex*)sample.GetPointer(),
                                  (fftw_complex*)sample.GetPointer(),
                                   FFTW_FORWARD, FFTW_ESTIMATE);
        ShiftSample(sample);
        fftw_execute(m_plan);
        sample *= complex<double>(1 / sqrt(sample.GetSizeX() * sample.GetSizeY()), 0.);
        ShiftSample(sample);
        fftw_destroy_plan(m_plan);
    }

}
void FFT::Run1(SampleComplex& sample) {
    m_plan = fftw_plan_dft_2d(sample.GetSizeX(),
                              sample.GetSizeY(),
                              (fftw_complex*)sample.GetPointer(),
                              (fftw_complex*)sample.GetPointer(),
                               FFTW_BACKWARD, FFTW_ESTIMATE);
    ShiftSample(sample);
    fftw_execute(m_plan);
    sample *= complex<double>(1 / sqrt(sample.GetSizeX() * sample.GetSizeY()), 0.);
    ShiftSample(sample);
    fftw_destroy_plan(m_plan);
}
