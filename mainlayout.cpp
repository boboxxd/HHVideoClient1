#include "mainlayout.h"
#include <QGridLayout>
#include <QDebug>
MainLayout::MainLayout(QWidget *parent) : QStackedWidget(parent)
{
    resize(1000,680);
    checkedwidget = nullptr;
    for(int i=0;i<14;i++)
        videowidgets[i]=nullptr;
    addPage(ONE);
    addPage(FOUR);
    addPage(MUTI);

    for(int i=0;i<14;i++)
    {
        map[videowidgets[i]->winId()]=i;
        connect(videowidgets[i],&VideoWidget::sendWId,this,&MainLayout::setCurrentScreen);
    }
}

MainLayout::~MainLayout()
{

}

VideoWidget *MainLayout::GetVideoWidget(int page, int index)
{
    setCurrentIndex(page);
    switch(page)
    {
    case 0:
        if(index == 0)
            return videowidgets[0];
    case 1:
        if(index >=0 && index<4)
            return videowidgets[index+1];
    case 2:
        if(index >=0 && index <9)
            return videowidgets[index+5];
        break;
    }
    return nullptr;
}

VideoWidget *MainLayout::videowidget()
{

}

void MainLayout::setScreenCount(int num)
{
    switch(num)
    {
    case 1:
        setCurrentIndex(0);

        break;
    case 4:
        setCurrentIndex(1);

        break;
    case 9:
        setCurrentIndex(2);

        break;
    }
}

void MainLayout::setCurrentScreen(WId wid)
{
    if(currentWidget()==page1)
    {
        emit currentScreenIndex(map[wid]);
    }
    if(currentWidget()==page2)
    {
        emit currentScreenIndex(map[wid]-1);
    }
    if(currentWidget()==page3)
    {
        emit currentScreenIndex(map[wid]-5);
    }

}

void MainLayout::addPage(State state)
{
    switch (state)
    {
    case ONE:
        page1= new QWidget(this);
        page1->setStyleSheet("background-color:rgb(199,237,204)");
        addWidget(page1);
        initpage1();
        break;
    case FOUR:
        page2= new QWidget(this);
        page2->setStyleSheet("background-color:rgb(237,199,204)");
        addWidget(page2);
        initpage2();
        break;
    case MUTI:
        page3= new QWidget(this);
        page3->setStyleSheet("background-color:rgb(204,237,199)");
        addWidget(page3);
        initpage3();
        break;
    }
}

void MainLayout::initpage1()
{
    videowidgets[0]=new VideoWidget(page1);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(videowidgets[0]);
    layout->setSpacing(1);
    layout->setContentsMargins(0,0,0,0);
    page1->setLayout(layout);
}

void MainLayout::initpage2()
{
    for(int i =1;i<=4;i++)
        videowidgets[i]=new VideoWidget(page2);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(videowidgets[1],0,0,1,1);
    layout->addWidget(videowidgets[2],0,1,1,1);
    layout->addWidget(videowidgets[3],1,0,1,1);
    layout->addWidget(videowidgets[4],1,1,1,1);
    layout->setSpacing(1);
    layout->setContentsMargins(0,0,0,0);
    page2->setLayout(layout);

}

void MainLayout::initpage3()
{
    for(int i=5;i<14;i++)
        videowidgets[i]=new VideoWidget(page3);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(videowidgets[5],0,0,1,1);
    layout->addWidget(videowidgets[6],0,1,1,1);
    layout->addWidget(videowidgets[7],0,2,1,1);
    layout->addWidget(videowidgets[8],1,0,1,1);
    layout->addWidget(videowidgets[9],1,1,1,1);
    layout->addWidget(videowidgets[10],1,2,1,1);
    layout->addWidget(videowidgets[11],2,0,1,1);
    layout->addWidget(videowidgets[12],2,1,1,1);
    layout->addWidget(videowidgets[13],2,2,1,1);
    layout->setSpacing(1);
    layout->setContentsMargins(0,0,0,0);
    page3->setLayout(layout);
}

void MainLayout::destory()
{
    checkedwidget = nullptr;
    for(int i=0;i<14;i++)
        videowidgets[i]=nullptr;
}
