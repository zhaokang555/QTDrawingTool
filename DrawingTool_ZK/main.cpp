#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle(QObject::tr("DrawingTool_ZK"));
    w.resize(800, 600);
    w.show();
    return app.exec();
}
