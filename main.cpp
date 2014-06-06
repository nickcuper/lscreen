#include <QApplication>
#include "lscreen.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    LScreen lscreen;
    lscreen.show();
    
    return a.exec();
}
