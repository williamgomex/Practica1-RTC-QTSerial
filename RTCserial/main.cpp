#include "lampara.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lampara w;
    w.show();

    return a.exec();
}
