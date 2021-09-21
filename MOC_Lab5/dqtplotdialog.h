#ifndef DQTPLOTDIALOG_H
#define DQTPLOTDIALOG_H

#include <QDialog>
#include <QString>
#include <string>
#include <cstring>

#include "ui_dqtplotdialog.h"

class QCustomPlot;
class SampleComplex;

//QT_BEGIN_NAMESPACE
//namespace Ui { class dqtplotdialog; }
//QT_END_NAMESPACE

class dqtplotdialog : public QDialog
{
    Q_OBJECT

public:
    dqtplotdialog(QWidget *parent = 0);
    ~dqtplotdialog();


    // обработка событий
public slots:
    // отклик на нажатие кнопки "нарисовать"
    void onBtnDrawCoh();
    void onBtnDrawNonCoh();
    void onBtnDrawNonCohExtra();
    void onBtnSaveCoh();
    void onBtnSaveNonCoh();
    // перехватывается событие Resize для диалогового окна
    // (это нужно чтобы сохранить одинаковоые масштабы по осям Х и Y для полутонового отображения)
    void resizeEvent(QResizeEvent *event);






private slots:
    void on_pushButtonBack_clicked();

private:
    // рисование графика центральных сечений по Х и Y для двумерного массива
    // sample - массив комплексных чисел, отображается только вещественная часть
    // qGraph - имя виджета, на котором рисовать
    // параметры графика:
    // dx - шаг по оси Х
    // sXName, sYName - подписи к осям Х, Y
    void DrawGraph(SampleComplex& sample, QCustomPlot *qGraph, double dx, QString sXName, QString sYName);

    // рисование полутонового отображения двумерного массива
    // sample - массив комплексных чисел, отображается только вещественная часть
    // qGraph - имя виджета, на котором рисовать
    // параметры графика:
    // dx - шаг по оси Х
    // sXName, sYName - подписи к осям Х, Y
    void DrawGrayscale(SampleComplex& sample, QCustomPlot *qGrayscale, double dx, QString sXName, QString sYName);

    void DrawGraphSech(SampleComplex& object,SampleComplex& image, QCustomPlot *qGraph, double dx, QString sXName, QString sYName);
    // функция, задающая одинаковый масштаб по осям X и Y
    // должна вызываться при первоначальной отрисовке и при масштабировании
    void RescaleCustomPlot(QCustomPlot *qPlot);

    Ui::dqtplotdialog m_ui;
};
#endif // DQTPLOTDIALOG_H
