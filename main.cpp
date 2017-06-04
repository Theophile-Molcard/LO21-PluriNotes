#include "Notes.h"
#include "mainwindow.h"
#include "debug.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DebugTest::Debug();
    DebugTest::Debug_theophile();
    DebugTest::DebugRelation();
    MainWindow w;
    w.setWindowTitle("PluriNote");
    w.show();

    return a.exec();
}
