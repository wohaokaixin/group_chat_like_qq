
#include <QApplication>
#include "denglu_jiemian.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    denglu d;
//    d.show();

    Denglu_jiemian denglu_jiemian1;
    denglu_jiemian1.show();
    return a.exec();
}
