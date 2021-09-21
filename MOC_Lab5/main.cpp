#include "dqtplotdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    dqtplotdialog dialog;
    dialog.show();
    return app.exec();
}
