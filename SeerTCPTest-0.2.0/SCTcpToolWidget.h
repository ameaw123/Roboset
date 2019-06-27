#ifndef SCTCPTOOLWIDGET_H
#define SCTCPTOOLWIDGET_H
#include <QWidget>
#include "SCStatusTcp.h"
#include <QDebug>
#include <QString>
#include "HCNetSDK.h"
#include <Windows.h>
#include <QTime>

namespace Ui {
class SCTcpToolWidget;
}

class SCTcpToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SCTcpToolWidget(QWidget *parent = 0);
    ~SCTcpToolWidget();
    QMap<int,QList<QString> > RobostationNamelist;
    int numRobostationName=6;
    long lUserID;
    //long IRealPlayHandle;
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40;
    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    NET_DVR_USER_LOGIN_INFO struLoginInfo;
    int PRESET_NUM=40;
    NET_DVR_PRESET_NAME struParams[40];
    void timerEvent(QTimerEvent *event);
    void myKillTimer(int id);
    QString count_id="0";



public slots:
    void stateChanged(QAbstractSocket::SocketState state);
    void receiveTcpError(QAbstractSocket::SocketError error);
    void slotPrintInfo(QString info);


    void slotChangedText(bool isOk, int revCommand, QByteArray revData, QByteArray revHex, int number, int msTime);
    void slotAutomaticallyScroll();
private slots:
    void on_pushButton_connect_clicked(bool checked);
    void on_pushButton_send_clicked();

    void on_pushButton_clearInfo_clicked();

    void on_pushButton_getrobo_clicked();

    void on_pushButton_connect_cam_clicked();

    void on_pushButton_getcam_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_taskset_clicked();

    void on_pushButton_clicked();

    void on_pushButton_catch_clicked();

    void on_pushButton_start_clicked(bool checked);

    void on_save_set_clicked();

    void on_read_set_clicked();



    void on_pushButton_unset_clicked();

private:
    Ui::SCTcpToolWidget *ui;
    SCStatusTcp *pSCStatusTcp;
    NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
    int _queryTimeID = -1;

    QString devip1;       //摄像头ip
    QString user1;        //用户名
    QString password1;    //密码
    QString port1;
    QByteArray devip2;
    QByteArray user2;
    QByteArray password2;
    char* devip;
    char* user;
    char* password;
    unsigned int port;
};

#endif // SCTCPTOOLWIDGET_H
