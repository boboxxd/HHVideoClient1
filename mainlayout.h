#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H
#include <QMap>
#include <QStackedWidget>
#include "videowidget.h"
class MainLayout : public QStackedWidget
{
    Q_OBJECT
public:
    enum State {ONE,FOUR,MUTI};
    MainLayout(QWidget *parent = nullptr);
    ~MainLayout();
    VideoWidget *GetVideoWidget(int page,int index);
    VideoWidget * videowidget();

signals:
    void currentScreenIndex(int);
public slots:
    void setScreenCount(int );
    void setCurrentScreen(WId);
private:
    void addPage(State state);
    void initpage1();
    void initpage2();
    void initpage3();
    void closeAllPlayer();
    void destory();
private:
    QWidget *page1;//页面１
    QWidget *page2;//页面２
    QWidget *page3;//页面３
    VideoWidget *videowidgets[14];
    VideoWidget *checkedwidget;
    QMap<WId,int> map;
};

#endif // MAINLAYOUT_H
