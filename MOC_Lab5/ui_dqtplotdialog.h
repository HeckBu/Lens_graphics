/********************************************************************************
** Form generated from reading UI file 'dqtplotdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DQTPLOTDIALOG_H
#define UI_DQTPLOTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_dqtplotdialog
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QPushButton *m_PB_DrawCoh;
    QPushButton *m_PB_DrawNonCoh_4;
    QCustomPlot *m_qW_Grayscale;
    QCustomPlot *m_qW_Graph;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QPushButton *m_PB_DrawNonCohExtra;
    QCustomPlot *m_qW_Graph_2;
    QPushButton *m_PB_DrawNonCoh;
    QCustomPlot *m_qW_Graph_3;
    QPushButton *m_PB_DrawNonCoh_3;
    QWidget *tab_5;
    QPushButton *pushButtonBack;
    QTableWidget *tableWidget;

    void setupUi(QDialog *dqtplotdialog)
    {
        if (dqtplotdialog->objectName().isEmpty())
            dqtplotdialog->setObjectName(QString::fromUtf8("dqtplotdialog"));
        dqtplotdialog->resize(790, 455);
        gridLayout = new QGridLayout(dqtplotdialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(dqtplotdialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_PB_DrawCoh = new QPushButton(tab);
        m_PB_DrawCoh->setObjectName(QString::fromUtf8("m_PB_DrawCoh"));

        gridLayout_2->addWidget(m_PB_DrawCoh, 0, 0, 1, 1);

        m_PB_DrawNonCoh_4 = new QPushButton(tab);
        m_PB_DrawNonCoh_4->setObjectName(QString::fromUtf8("m_PB_DrawNonCoh_4"));

        gridLayout_2->addWidget(m_PB_DrawNonCoh_4, 0, 1, 1, 1);

        m_qW_Grayscale = new QCustomPlot(tab);
        m_qW_Grayscale->setObjectName(QString::fromUtf8("m_qW_Grayscale"));

        gridLayout_2->addWidget(m_qW_Grayscale, 1, 0, 1, 1);

        m_qW_Graph = new QCustomPlot(tab);
        m_qW_Graph->setObjectName(QString::fromUtf8("m_qW_Graph"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(m_qW_Graph->sizePolicy().hasHeightForWidth());
        m_qW_Graph->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_qW_Graph, 1, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_PB_DrawNonCohExtra = new QPushButton(tab_2);
        m_PB_DrawNonCohExtra->setObjectName(QString::fromUtf8("m_PB_DrawNonCohExtra"));

        gridLayout_3->addWidget(m_PB_DrawNonCohExtra, 0, 1, 1, 1);

        m_qW_Graph_2 = new QCustomPlot(tab_2);
        m_qW_Graph_2->setObjectName(QString::fromUtf8("m_qW_Graph_2"));
        sizePolicy.setHeightForWidth(m_qW_Graph_2->sizePolicy().hasHeightForWidth());
        m_qW_Graph_2->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_qW_Graph_2, 1, 0, 1, 1);

        m_PB_DrawNonCoh = new QPushButton(tab_2);
        m_PB_DrawNonCoh->setObjectName(QString::fromUtf8("m_PB_DrawNonCoh"));

        gridLayout_3->addWidget(m_PB_DrawNonCoh, 0, 0, 1, 1);

        m_qW_Graph_3 = new QCustomPlot(tab_2);
        m_qW_Graph_3->setObjectName(QString::fromUtf8("m_qW_Graph_3"));
        sizePolicy.setHeightForWidth(m_qW_Graph_3->sizePolicy().hasHeightForWidth());
        m_qW_Graph_3->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_qW_Graph_3, 1, 1, 1, 1);

        m_PB_DrawNonCoh_3 = new QPushButton(tab_2);
        m_PB_DrawNonCoh_3->setObjectName(QString::fromUtf8("m_PB_DrawNonCoh_3"));

        gridLayout_3->addWidget(m_PB_DrawNonCoh_3, 2, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        pushButtonBack = new QPushButton(tab_5);
        pushButtonBack->setObjectName(QString::fromUtf8("pushButtonBack"));
        pushButtonBack->setGeometry(QRect(179, 130, 131, 21));
        tableWidget = new QTableWidget(tab_5);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 10, 291, 111));
        tableWidget->horizontalHeader()->setDefaultSectionSize(150);
        tabWidget->addTab(tab_5, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(dqtplotdialog);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(dqtplotdialog);
    } // setupUi

    void retranslateUi(QDialog *dqtplotdialog)
    {
        dqtplotdialog->setWindowTitle(QCoreApplication::translate("dqtplotdialog", "Dialog", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget->setToolTip(QCoreApplication::translate("dqtplotdialog", "<html><head/><body><p>\320\232\320\276\320\263\320\265\321\200\320\265\320\275\321\202\320\275\320\276\320\265 \320\270\320\267\320\273\321\203\321\207\320\265\320\275\320\270\320\265</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        m_PB_DrawCoh->setText(QCoreApplication::translate("dqtplotdialog", "\320\235\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272\320\270", nullptr));
        m_PB_DrawNonCoh_4->setText(QCoreApplication::translate("dqtplotdialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("dqtplotdialog", "\320\232\320\276\320\263\320\265\321\200\320\265\320\275\321\202\320\275\320\276\320\265 \320\270\320\267\320\273\321\203\321\207\320\265\320\275\320\270\320\265", nullptr));
        m_PB_DrawNonCohExtra->setText(QCoreApplication::translate("dqtplotdialog", "\320\235\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272\320\270 \320\244\320\240\320\242 \320\270 \320\247\320\232\320\245", nullptr));
        m_PB_DrawNonCoh->setText(QCoreApplication::translate("dqtplotdialog", "\320\235\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272\320\270", nullptr));
        m_PB_DrawNonCoh_3->setText(QCoreApplication::translate("dqtplotdialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("dqtplotdialog", "\320\235\320\265\320\272\320\276\320\263\320\265\321\200\320\265\320\275\321\202\320\275\320\276\320\265 \320\270\320\267\320\273\321\203\321\207\320\265\320\275\320\270\320\265", nullptr));
        pushButtonBack->setText(QCoreApplication::translate("dqtplotdialog", "\320\222\320\262\320\265\321\201\321\202\320\270 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("dqtplotdialog", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \321\205\320\260\321\200\320\260\320\272\321\202\320\265\321\200\320\270\321\201\321\202\320\270\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dqtplotdialog: public Ui_dqtplotdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DQTPLOTDIALOG_H
