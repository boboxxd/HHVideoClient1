#include "widget.h"
#include <QApplication>
#include <QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("江苏濠汉智能监控播放器");
    w.setWindowIcon(QIcon(":/icon/hh.ico"));
    w.showMaximized();
    return a.exec();
}
