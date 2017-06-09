#include "iucalmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IUCalMain w;
    w.show();

    return a.exec();
}
