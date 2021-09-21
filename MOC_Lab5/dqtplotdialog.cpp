#include "dqtplotdialog.h"
#include "qcustomplot.h"
#include "sample_complex.h"
#include "math.h"
#include "object.h"
#include "optical_system.h"

#include <QTableWidget>
#include <QMessageBox>
#include <QString>


using namespace std;

#define PI 3.14159265358979


dqtplotdialog::dqtplotdialog(QWidget *parent) :
    QDialog(parent)
{
    m_ui.setupUi(this);


    // создаем связь между сигналом(событием) от объекта и функцией-обработкой события
    connect(m_ui.m_PB_DrawCoh, SIGNAL(clicked()), this, SLOT(onBtnDrawCoh()));
    connect(m_ui.m_PB_DrawNonCoh, SIGNAL(clicked()), this, SLOT(onBtnDrawNonCoh()));
    connect(m_ui.m_PB_DrawNonCohExtra, SIGNAL(clicked()), this, SLOT(onBtnDrawNonCohExtra()));
    connect(m_ui.m_PB_DrawNonCoh_4, SIGNAL(clicked()), this, SLOT(onBtnSaveCoh()));
    connect(m_ui.m_PB_DrawNonCoh_3, SIGNAL(clicked()), this, SLOT(onBtnSaveNonCoh()));


    // создание таблицы
    m_ui.tableWidget->setRowCount(3);
    m_ui.tableWidget->setColumnCount(1);
    m_ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "Введенные значния");
    m_ui.tableWidget->setVerticalHeaderLabels(QStringList() << "Количество элементов" << "Охват зрачка" << "Период решетки");

    // Включаем кнопки
    m_ui.m_PB_DrawNonCoh->setCheckable(true);
    m_ui.m_PB_DrawNonCohExtra->setCheckable(true);

    // заполнение таблицы
    double example[3] = {256.,20.,4.};

    for(int i=0; i < m_ui.tableWidget->rowCount(); i++){
         QTableWidgetItem *item = new QTableWidgetItem(QString::number(example[i]));
         m_ui.tableWidget->setItem(i,0,item);
    }
}

dqtplotdialog::~dqtplotdialog()
{
}

//-------------------------------------------------------------------------------------------------
// перехватывается событие Resize для диалогового окна
// (это нужно чтобы сохранить одинаковоые масштабы по осям Х и Y для полутонового отображения)
void dqtplotdialog::resizeEvent(QResizeEvent *event)
{
    // на случай, если размер виджета не квадратный - задаем одинаковый масштаб по ося X и Y
    RescaleCustomPlot(m_ui.m_qW_Grayscale);
    // отрисовка
    m_ui.m_qW_Grayscale->replot();
}
//-------------------------------------------------------------------------------------------------
// отклик на нажатие кнопки "нарисовать"

void dqtplotdialog::onBtnDrawCoh()
{
    // 0 - количество элементов, 1 - охват зрачка, 2 - период решетки
    double size = m_ui.tableWidget->item(0, 0)->text().toDouble();
    double Dzr = m_ui.tableWidget->item(1, 0)->text().toDouble();
    double t = m_ui.tableWidget->item(2, 0)->text().toDouble();
    double dx = 1/Dzr; // шаг по x
    Object grating((int)size,(int)size,dx);
    SampleComplex sample((int)size,(int)size);
    double lambda = 0.55, aperture = 0.55;
    OpticalSystem OSystem(lambda,aperture, size, dx, Dzr);
    grating.CreateLineAndSpace(t,t/2);
    OSystem.CalcCoherent(grating,sample);
    // рисуем график
    DrawGraphSech(grating,sample, m_ui.m_qW_Graph, dx, "x", "Sinc(x)*Sinc(2*y)");
    // рисуем полутоновое отображение
    DrawGrayscale(sample, m_ui.m_qW_Grayscale, dx, "x", "y");
}
void dqtplotdialog::onBtnDrawNonCoh()
{
    double size = m_ui.tableWidget->item(0, 0)->text().toDouble();
    double Dzr = m_ui.tableWidget->item(1, 0)->text().toDouble();
    double dx = 1/Dzr; // шаг по x
    double t = m_ui.tableWidget->item(2, 0)->text().toDouble();
    Object grating((int)size,(int)size,dx);
    SampleComplex sample((int)size,(int)size);
    double lambda = 0.55, aperture = 0.55;
    OpticalSystem OSystem(lambda,aperture, size, dx, Dzr);
    grating.CreateLineAndSpace(t,t/2);
    OSystem.CalcNonCoherent(grating,sample);
    DrawGraphSech(grating,sample, m_ui.m_qW_Graph_3, dx, "x", "Sinc(x)*Sinc(2*y)");
    DrawGrayscale(sample, m_ui.m_qW_Graph_2, dx, "x", "y");
}
void dqtplotdialog::onBtnDrawNonCohExtra()
{
    double size = m_ui.tableWidget->item(0, 0)->text().toDouble();
    double Dzr = m_ui.tableWidget->item(1, 0)->text().toDouble();
    double dx = 1/Dzr;; // шаг по x
    double t = m_ui.tableWidget->item(2, 0)->text().toDouble();
    Object grating((int)size,(int)size,dx);
    SampleComplex sample((int)size,(int)size);
    double lambda = 0.55, aperture = 0.55;
    OpticalSystem OSystem(lambda,aperture, size, dx, Dzr);
    grating.CreateLineAndSpace(t,t/2);
    OSystem.PSF(sample);
    DrawGraph(sample, m_ui.m_qW_Graph_2, dx, "x", "Sinc(x)*Sinc(2*y)");
    OSystem.OTF(sample);
    DrawGraph(sample, m_ui.m_qW_Graph_3, dx, "x", "Sinc(x)*Sinc(2*y)");
}
//-------------------------------------------------------------------------------------------------
// рисование графика центральных сечений по Х и Y для двумерного массива
// sample - массив комплексных чисел, отображается только вещественная часть
// qGraph - имя виджета, на котором рисовать
// параметры графика:
// dx - шаг по оси Х
// sXName, sYName - подписи к осям Х, Y
void dqtplotdialog::DrawGraph(SampleComplex& sample, QCustomPlot *qGraph, double dx, QString sXName, QString sYName)
{
    // размер выборки
    int dim = sample.GetSizeX();

    // очищаем предыдущий нарисованный график
    qGraph->clearGraphs();
    // рисование легенды
    qGraph->legend->setVisible(true);

    // параметры графика сечения по Х
    qGraph->addGraph();
    qGraph->graph(0)->setPen(QPen(Qt::red));
    qGraph->graph(0)->setName("Section X");

    // параметры графика сечения по Y
    qGraph->addGraph();
    qGraph->graph(1)->setPen(QPen(Qt::blue));
    qGraph->graph(1)->setName("Section Y");

    // параметры оси Х
    qGraph->xAxis->setLabel(sXName);
    // максимальное и минимальное значение по оси
    double min = sample.CalcCoordX(0, dx);
    double max = sample.CalcCoordX(dim, dx);
    qGraph->xAxis->setRange(min, max);
    // можно задать цену деления по оси (можно оставить автоматическое опеределение)
    qGraph->xAxis->setAutoTickStep(false);
    qGraph->xAxis->setTickStep(1.);

    // задаем значения графиков
    min=max=0;
    for (int i = 0; i < sample.GetSizeX(); i++)
    {
        // координата точки по Х
        double x = sample.CalcCoordX(i, dx);

        // значание в сечении по Х
        double value_x = sample(i, dim/2).real();
        qGraph->graph(0)->addData(x, value_x);

        // значание в сечении  по Y
        double value_y = sample(dim/2, i).real();
        qGraph->graph(1)->addData(x, value_y);

        // вычисляем min значение по оси Y
        if(min>value_x)
            min=value_x;
        if(min>value_y)
            min=value_y;
    }
    // параметры оси Y
    qGraph->yAxis->setLabel(sYName);
    // максимальное и минимальное значение по оси
    // (min вычислен, max предполагаем равным 1 (для интенсивности)
    qGraph->yAxis->setRange(min, 1.);
    // можно задать цену деления по оси (можно оставить автоматическое опеределение)
    qGraph->yAxis->setAutoTickStep(false);
    qGraph->yAxis->setTickStep(0.2);
    // нулевое значение по осям X и Y рисуем толстой линией
    QPen qAxisPen;
    qAxisPen.setWidth(2.);
    qGraph->xAxis->grid()->setZeroLinePen(qAxisPen);
    qGraph->yAxis->grid()->setZeroLinePen(qAxisPen);

    // рисуем сами графики
    qGraph->replot();
}
//-------------------------------------------------------------------------------------------------
// рисование полутонового отображения двумерного массива
// sample - массив комплексных чисел, отображается только вещественная часть
// qGraph - имя виджета, на котором рисовать
// параметры графика:
// dx - шаг по оси Х
// sXName, sYName - подписи к осям Х, Y
void dqtplotdialog::DrawGrayscale(SampleComplex& sample,
                                  QCustomPlot *qGrayscale,
                                  double dx,
                                  QString sXName,
                                  QString sYName)
{
    // размер выборки
    int dim = sample.GetSizeX();

    // очищаем предыдущий нарисованный график
    qGrayscale->clearPlottables();
    qGrayscale->legend->setVisible(false);
    // создаем карту уровней для отрисовки и задаем размерность
    QCPColorMap *qMap = new QCPColorMap(qGrayscale->xAxis, qGrayscale->yAxis);
    qMap->data()->setSize(dim, dim);

    // задаем максимальное и минимальное значение по осям
    double min = sample.CalcCoordX(0, dx);
    double max = sample.CalcCoordX(dim, dx);
    qMap->data()->setRange(QCPRange(min, max), QCPRange(min, max));
    // заполняем карту уровней значениями из массива sample
    for (int i = 0; i < sample.GetSizeX(); i++)
    {
        for (int j = 0; j < sample.GetSizeY(); j++)
        {
            qMap->data()->setCell(i, j, sample(i, j).real());
        }
    }
    // устанавливаем тип карты уровней - полутоновое отображение
    qMap->setGradient(QCPColorGradient::gpGrayscale);
    qMap->rescaleDataRange();

    // параметры оси X
    qGrayscale->xAxis->setLabel(sXName);
    // можно задать цену деления по оси (можно оставить автоматическое опеределение)
    qGrayscale->xAxis->setAutoTickStep(false);
    qGrayscale->xAxis->setTickStep(1);

    // параметры оси X
    qGrayscale->yAxis->setLabel(sYName);
    // можно задать цену деления по оси (можно оставить автоматическое опеределение)
    qGrayscale->yAxis->setAutoTickStep(false);
    qGrayscale->yAxis->setTickStep(1);

    // задаем заполненную карту уровней в QCustomPlot для отрисовки
    qGrayscale->addPlottable(qMap);
    // пересчитываем оси QCustomPlot под заданную карту уровней
    qGrayscale->rescaleAxes();
    // на случай, если размер виджета не квадратный - задаем одинаковый масштаб по осям X и Y
    RescaleCustomPlot(qGrayscale);
    // отрисовка
    qGrayscale->replot();
}
//-------------------------------------------------------------------------------------------------
// функция, задающая одинаковый масштаб по осям X и Y
// должна вызываться при первоначальной отрисовке и при масштабировании
void dqtplotdialog::RescaleCustomPlot(QCustomPlot *qPlot)
{
    // определяем ширину и высоту области для отрисовки
    QSize r=qPlot->axisRect()->size();
    // если ширина больше высоты - меняем ось X
    if(r.width() > r.height())
    {
        qPlot->xAxis->setScaleRatio(qPlot->yAxis, 1.);
    }
    // если ширина меньше высоты - меняем ось X
    else if(r.width() < r.height())
    {
        qPlot->yAxis->setScaleRatio(qPlot->xAxis, 1.);
    }
}

//-------------------------------------------------------------------------------------------------

void dqtplotdialog::on_pushButtonBack_clicked()
{
    // 0 - количество элементов, 1 - охват зрачка, 2 - период решетки
    double data[3];
    for(int i=0; i < m_ui.tableWidget->rowCount(); i++){
         data[i] = m_ui.tableWidget->item(i, 0)->text().toDouble();
    }
    if(data[0] <= 0){
        data[0] = 256;
        m_ui.tableWidget->item(0, 0)->setText("256");
    }
    if(data[1] <= 0){
        data[1] = 20;
        m_ui.tableWidget->item(1, 0)->setText("20");
    }
    if(data[2] <= 0){
        data[2] = 4;
        m_ui.tableWidget->item(2, 0)->setText("4");
    }
    QMessageBox::information(this, "Введенные значения",
                             "Количество элементов: " + QString::number(data[0]) +
                             " Охват зрачка: " + QString::number(data[1]) +
                             " Период решетки: " + QString::number(data[2]));

//    OpticalSystem(0.55,0.55,data[0],data[2],data[1]);
}

// Функция конпи сохранения для когерентного излучения
void dqtplotdialog::onBtnSaveCoh() {
ofstream out("CoherentGraphs.txt");
// 0 - количество элементов, 1 - охват зрачка, 2 - период решетки
double size = m_ui.tableWidget->item(0, 0)->text().toDouble(); // размер выборки
double Dzr = m_ui.tableWidget->item(1, 0)->text().toDouble();
double period = m_ui.tableWidget->item(2, 0)->text().toDouble();
double dx = 1/Dzr;
// для картинки
string Sname;
QString qSname = QString::fromStdString(Sname);


// сечение
qSname="Coh_N";
qSname+=QString::number(size);
qSname+="_Dzr";
qSname+=QString::number(Dzr);
qSname+="_Period";
qSname+=QString::number(period);
qSname+=".png";
m_ui.m_qW_Graph->savePng(qSname, 640, 640, 1, 100);

// полутоновое
qSname="GrayCoh_N";
qSname+=QString::number(size);
qSname+="_Dzr";
qSname+=QString::number(Dzr);
qSname+="_Period";
qSname+=QString::number(period);
qSname+=".png";
m_ui.m_qW_Grayscale->savePng(qSname, 640, 640, 1, 100);
QMessageBox::information(this, "Done!", "Картинки сечения и полутонового изображения созданы!");

// для файла
Object grating((int)size,(int)size,dx);
SampleComplex sample((int)size,(int)size);
double lambda = 0.55, aperture = 0.55;
OpticalSystem OSystem(lambda,aperture, size, dx, Dzr);
grating.CreateLineAndSpace(period,period/2);
OSystem.CalcCoherent(grating,sample);
out << "Reshetka:\n";
grating.PrintReal(out);
out << "Sechenie:\n";
for (int i = 0; i < (int)size; i++) {
out << grating(0, i).real() << "\t";
}
out << endl;
for (int i = 0; i < (int)size; i++) {
out << (i/Dzr - size/2/Dzr) * lambda / aperture << "\t";
}
out << "\nImage, intensity:\n";
sample.PrintIntens(out);
out << "Sechenie:\n";
for (int i = 0; i < (int)size; i++) {
out << sample((int)(size-1)/2, i).real() << "\t";
}
out << endl;
for (int i = 0; i < (int)size; i++) {
out << (i/Dzr - size/2/Dzr)* lambda/ aperture << "\t";
}
out.close();
}

// Функция конпи сохранения для некогерентного излучения
void dqtplotdialog::onBtnSaveNonCoh() {
ofstream out("NonCoherentGraphs.txt");
double size = m_ui.tableWidget->item(0, 0)->text().toDouble(); // размер выборки
double Dzr = m_ui.tableWidget->item(1, 0)->text().toDouble();
double period = m_ui.tableWidget->item(2, 0)->text().toDouble();
double dx = 1/Dzr;
// для картинки
string Sname;
QString qSname = QString::fromStdString(Sname); // сечение

if(m_ui.m_PB_DrawNonCoh->isChecked()){
    // сечение
    qSname="NonCoh_N";
    qSname+=QString::number(size);
    qSname+="_Dzr";
    qSname+=QString::number(Dzr);
    qSname+="_Period";
    qSname+=QString::number(period);
    qSname+=".png";
    m_ui.m_qW_Graph_3->savePng(qSname, 640, 640, 1, 100);

    // полутоновое
    qSname="GrayNonCoh_N";
    qSname+=QString::number(size);
    qSname+="_Dzr";
    qSname+=QString::number(Dzr);
    qSname+="_Period";
    qSname+=QString::number(period);
    qSname+=".png";
    m_ui.m_qW_Graph_2->savePng(qSname, 640, 640, 1, 100);
    m_ui.m_PB_DrawNonCoh->setChecked(false);
    m_ui.m_PB_DrawNonCohExtra->setChecked(false);
    QMessageBox::information(this, "Done!", "Картинки сечения и полутонового изображения созданы!");
}

if (m_ui.m_PB_DrawNonCohExtra->isChecked()){
    // ЧКХ
    qSname="OTF_N";
    qSname+=QString::number(size);
    qSname+="_Dzr";
    qSname+=QString::number(Dzr);
    qSname+="_Period";
    qSname+=QString::number(period);
    qSname+=".png";
    m_ui.m_qW_Graph_3->savePng(qSname, 640, 640, 1, 100);

    // ФРТ
    qSname="FRT_N";
    qSname+=QString::number(size);
    qSname+="_Dzr";
    qSname+=QString::number(Dzr);
    qSname+="_Period";
    qSname+=QString::number(period);
    qSname+=".png";
    m_ui.m_qW_Graph_2->savePng(qSname, 640, 640, 1, 100);
    m_ui.m_PB_DrawNonCoh->setChecked(false);
    m_ui.m_PB_DrawNonCohExtra->setChecked(false);
    QMessageBox::information(this, "Done!", "Картинки ЧКХ и ФРТ созданы!");
}


// для файла
Object grating((int)size,(int)size,dx);
SampleComplex sample((int)size,(int)size),sample1((int)size,(int)size);
double lambda = 0.55, aperture = 0.55;
OpticalSystem OSystem(lambda,aperture, size, dx, Dzr);
grating.CreateLineAndSpace(period,period/2);
OSystem.CalcNonCoherent(grating,sample);
out << "Reshetka:\n";
grating.PrintReal(out);
out << "Sechenie:\n";
for (int i = 0; i < (int)size; i++) {
out << grating(0, i).real() << "\t";
}
out << endl;
out << "Image, intensity:\n";
sample.PrintIntens(out);
out << "Sechenie:\n";
for (int i = 0; i < (int)size; i++) {
out << sample((int)(size-1)/2, i).real() << "\t";
}
out << endl;
for (int i = 0; i < (int)size; i++) {
out << (i/Dzr - size/2/Dzr)* lambda/ aperture << "\t";
}
out << endl;
out << "FRT:\n";
OSystem.PSF(sample1);
for (int i = 0; i < (int)size; i++) {
out << sample1((int)(size-1)/2, i).real() << "\t";
}
out << endl;
out << "ChKH:\n";
OSystem.OTF(sample1);
for (int i = 0; i < (int)size; i++) {
out << sample1((int)(size-1)/2, i).real() << "\t";
}
out << endl;
out.close();
}

//-------------------------------------------------------------------------------------------------
// рисование графика центральных сечений по Х и Y для двумерного массива
// sample - массив комплексных чисел, отображается только вещественная часть
// qGraph - имя виджета, на котором рисовать
// параметры графика:
// dx - шаг по оси Х
// sXName, sYName - подписи к осям Х, Y
void dqtplotdialog::DrawGraphSech(SampleComplex& object,
                                  SampleComplex& image,
                                  QCustomPlot *qGraph,
                                  double dx,
                                  QString sXName,
                                  QString sYName)
{
    // размер выборки
    int dim = object.GetSizeX();

    // очищаем предыдущий нарисованный график
    qGraph->clearGraphs();
    // рисование легенды
    qGraph->legend->setVisible(true);

    // параметры графика сечения по Х
    qGraph->addGraph();
    qGraph->graph(0)->setPen(QPen(Qt::red));
    qGraph->graph(0)->setName("Object");

    // параметры графика сечения по Y
    qGraph->addGraph();
    qGraph->graph(1)->setPen(QPen(Qt::blue));
    qGraph->graph(1)->setName("Image");

    // параметры оси Х
    qGraph->xAxis->setLabel(sXName);
    // максимальное и минимальное значение по оси
    double min = object.CalcCoordX(0, dx);
    double max = object.CalcCoordX(dim, dx);
    if (min>image.CalcCoordX(0, dx)) min=image.CalcCoordX(0, dx);
    if (max<image.CalcCoordX(dim, dx)) max=image.CalcCoordX(dim, dx);
    qGraph->xAxis->setRange(min, max);
    // можно задать цену деления по оси (можно оставить автоматическое опеределение)
    qGraph->xAxis->setAutoTickStep(false);
    qGraph->xAxis->setTickStep(1.);

    // задаем значения графиков
    min=0;
    //max=0;
    for (int i = 0; i < object.GetSizeX(); i++)
    {
        // координата точки по Х
        double x = object.CalcCoordX(i, dx);

        // значение в сечении по Х
        double value_x = object(dim/2, i).real();
        qGraph->graph(0)->addData(x, value_x);

        // значение в сечении  по Y
        double value_y = image(dim/2, i).real();
        qGraph->graph(1)->addData(x, value_y);

        // вычисляем min значение по оси Y
        if(min>value_x)
            min=value_x;
        if(min>value_y)
            min=value_y;
    }
    // параметры оси Y
    qGraph->yAxis->setLabel(sYName);
    // максимальное и минимальное значение по оси
    // (min вычислен, max предполагаем равным 1.4 (для интенсивности)
    qGraph->yAxis->setRange(min, 1.2);
    // можно задать цену деления по оси (можно оставить автоматическое опеределение)
    qGraph->yAxis->setAutoTickStep(false);
    qGraph->yAxis->setTickStep(0.2);
    // нулевое значение по осям X и Y рисуем толстой линией
    QPen qAxisPen;
    qAxisPen.setWidth(2.);
    qGraph->xAxis->grid()->setZeroLinePen(qAxisPen);
    qGraph->yAxis->grid()->setZeroLinePen(qAxisPen);

    // рисуем сами графики
    qGraph->replot();
}


