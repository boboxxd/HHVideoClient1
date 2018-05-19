#include "hikvisonwapper.h"
#include <QDebug>

HikvisonWapper::HikvisonWapper(QWidget *widget) : videowidget(widget)
{
    connect(this,&HikvisonWapper::error,this,&HikvisonWapper::handleerror);

}

HikvisonWapper::~HikvisonWapper()
{
    close();
    destroy();
}

void HikvisonWapper::setWindow(QWidget *widget)
{
    videowidget = widget;

}

bool HikvisonWapper::open(QString ip,int port,QString username,QString password)
{
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    lUserID = NET_DVR_Login_V30(ip.toLocal8Bit().data(), port, username.toLocal8Bit().data(), password.toLocal8Bit().data(), &struDeviceInfo);
    if (lUserID < 0)
    {
        emit error();
        return false;
    }

    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    struPlayInfo.hPlayWnd =videowidget->winId(); //需要 SDK 解码时句柄设为有效值,仅取流不解码时可设为空
    struPlayInfo.lChannel = 1;//预览通道号
    struPlayInfo.dwStreamType = 0; //0-主码流,1-子码流,2-码流 3,3-码流 4,以此类推
    struPlayInfo.dwLinkMode = 0; //0- TCP 方式,1- UDP 方式,2- 多播方式,3- RTP 方式,4-RTP/RTSP,5-RSTP/HTTP
    struPlayInfo.bBlocked = 1; //0- 非阻塞取流,1- 阻塞取流
    lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, NULL, NULL);
    if(lRealPlayHandle<0)
    {
        emit error();
        return false;
    }
    return true;
}

void HikvisonWapper::close()
{
    if(lRealPlayHandle > 0)
    {
        NET_DVR_StopRealPlay(lRealPlayHandle);
        lRealPlayHandle = -1;
    }

    if(lUserID > 0)
    {
        NET_DVR_Logout(lUserID);
        lUserID = -1;
    }
}


void HikvisonWapper::handleerror()
{
    videowidget = nullptr;
    if (lUserID < 0)
    {
        qDebug()<<"Login error"<<NET_DVR_GetLastError();
        emit errormsg(QString("").append(NET_DVR_GetLastError()));
        return;
    }

    if (lRealPlayHandle < 0)
    {
        qDebug()<<"NET_DVR_RealPlay_V40 error"<<NET_DVR_GetLastError();
        emit errormsg(QString("").append(NET_DVR_GetLastError()));
        NET_DVR_Logout(lUserID);
        return;
    }

    emit errormsg(QString("").append(NET_DVR_GetLastError()));
}



// state:
// 0--开始 1--停止
void HikvisonWapper::ptzup(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, TILT_UP,state, 3);
    if(!re)
    {
        emit error();
    }
}


void HikvisonWapper::ptzdown(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, TILT_DOWN,state, 3);
    if(!re)
    {
        emit error();
    }
}


void HikvisonWapper::ptzright(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, PAN_RIGHT,state, 3);
    if(!re)
    {
        emit error();
    }
}


void HikvisonWapper::ptzleft(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, PAN_LEFT,state, 3);
    if(!re)
    {
        emit error();
    }
}

void HikvisonWapper::ptzzoomin(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, ZOOM_IN,state, 3);
    if(!re)
    {
        emit error();
    }
}

void HikvisonWapper::ptzzoomout(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, ZOOM_OUT,state, 3);
    if(!re)
    {
        emit error();
    }
}

void HikvisonWapper::init()
{
    NET_DVR_Init();
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
}

void HikvisonWapper::destroy()
{
    NET_DVR_Cleanup();
}
