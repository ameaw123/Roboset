#include "SCTcpToolWidget.h"
#include "ui_SCTcpToolWidget.h"
#include <QDateTime>
#include <QDebug>
#include "Windows.h"
#include <time.h>
#include <QFile>
#include <QTime>

SCTcpToolWidget::SCTcpToolWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SCTcpToolWidget)
{
    ui->setupUi(this);
    //*****************摄像头初始化*******************
    bool isok = NET_DVR_Init();
    if(isok == false)
    {
        QString errorstring="摄像头初始化失败 " +QString::number(NET_DVR_GetLastError());
        ui->textEdit_info->append(errorstring);
        return;
    }
    if(isok==true)
    {
        ui->textEdit_info->append("摄像头初始化完成");
    }
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(1000, 1);
    NET_DVR_SetReconnect(5000, true);

    //*****************机器人原始代码*******************
    //自动滚动
    connect(ui->textEdit_info,SIGNAL(textChanged()),this,SLOT(slotAutomaticallyScroll()));
    //tcp
    pSCStatusTcp = new SCStatusTcp(this);
    connect(pSCStatusTcp,SIGNAL(sigPrintInfo(QString)),this,SLOT(slotPrintInfo(QString)));
    connect(pSCStatusTcp,SIGNAL(sigChangedText(bool,int,QByteArray,QByteArray,int,int)),
            this,SLOT(slotChangedText(bool,int,QByteArray,QByteArray,int,int)));
    //ip正则
    QRegExp regExp("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    QRegExpValidator *ev = new QRegExpValidator(regExp);
    ui->lineEdit_ip->setValidator(ev);
    //0-65535
    QIntValidator *intV = new QIntValidator(0,65535);
    ui->lineEdit_number->setValidator(intV);
    ui->lineEdit_sendCommand->setValidator(intV);
}

SCTcpToolWidget::~SCTcpToolWidget()
{
    //摄像头注销登录及SDK释放
    NET_DVR_Logout(lUserID);
    NET_DVR_Cleanup();
    //pSCStatusTcp类不用手动释放，qt会自动释放它的子类.
    delete ui;
}
//*******************************机器人原始代码*********************************
/** socket连接/断开
 * @brief SCTcpToolWidget::on_pushButton_connect_clicked
 * @param checked
 */
void SCTcpToolWidget::on_pushButton_connect_clicked(bool checked)
{
    switch (pSCStatusTcp->connectHost(ui->lineEdit_ip->text(),ui->comboBox_port->currentText().toInt())) {
    case 1:
        ui->pushButton_connect->setText(tr("开始连接"));
        break;

    default:
        break;
    }
}
/** tcp槽实时监测tcp状态
 * @brief SCTcpToolWidget::stateChanged
 * @param state
 */
void SCTcpToolWidget::stateChanged(QAbstractSocket::SocketState state)
{
    QString info;
    switch (state) {
    case QAbstractSocket::UnconnectedState:
        info = "QAbstractSocket::UnconnectedState";
        ui->comboBox_port->setEnabled(true);
        ui->pushButton_connect->setText(tr("开始连接"));
        break;
    case QAbstractSocket::HostLookupState:
        info = "QAbstractSocket::HostLookupState";
        break;

    case QAbstractSocket::ConnectingState:
        info = "QAbstractSocket::ConnectingState";
        ui->pushButton_connect->setText(tr("正在连接..."));
        ui->comboBox_port->setEnabled(false);
        break;
    case QAbstractSocket::ConnectedState:
    {
        info = "QAbstractSocket::ConnectedState \n";
        ui->pushButton_connect->setText(tr("断开连接"));
    }
        break;
    case QAbstractSocket::BoundState:
        info = "QAbstractSocket::BoundState";
        break;
    case QAbstractSocket::ListeningState:
        info = "QAbstractSocket::ListeningState";
        break;
    case QAbstractSocket::ClosingState:
        info = "QAbstractSocket::ClosingState";
        ui->comboBox_port->setEnabled(true);
        ui->pushButton_connect->setText(tr("开始连接"));
        break;
    }
    ui->textEdit_info->append(QString("%1 IP:%2:%3 %4")
                              .arg(pSCStatusTcp->getCurrentDateTime())
                              .arg(ui->lineEdit_ip->text())
                              .arg(ui->comboBox_port->currentText())
                              .arg(info));
}
/** tcp槽 返回tcp错误
 * @brief SCTcpToolWidget::receiveTcpError
 * @param error
 */
void SCTcpToolWidget::receiveTcpError(QAbstractSocket::SocketError error)
{
    ui->textEdit_info->append(QString("%1  connect error[%2]: IP:%3:%4")
                              .arg(pSCStatusTcp->getCurrentDateTime())
                              .arg(error)
                              .arg(ui->lineEdit_ip->text())
                              .arg(ui->comboBox_port->currentText()));
    ui->comboBox_port->setEnabled(true);
    ui->pushButton_connect->setText(tr("开始连接"));
}

/** 发送
 * @brief SCTcpToolWidget::on_pushButton_send_clicked
 */
void SCTcpToolWidget::on_pushButton_send_clicked()
{
    if(pSCStatusTcp->tcpSocket()
            &&pSCStatusTcp->tcpSocket()->state()==QAbstractSocket::ConnectedState)
    {
        //报头数据类型
        uint16_t sendCommand = ui->lineEdit_sendCommand->text().toInt();
        //数据区数据
        QString sendData = ui->textEdit_sendData->toPlainText();
        //序号
        uint16_t number = ui->lineEdit_number->text().toInt();
        //清理接收数据区域
        ui->textEdit_revData->clear();
        //发送数据
        if(!pSCStatusTcp->writeTcpData(sendCommand,sendData,number))
        {
            slotPrintInfo(tr("<font color=\"red\">"
                             "%1--------- 发送错误----------\n"
                             "发送的报文类型:%2  \n"
                             "错误: %3"
                             "</font>")
                          .arg(pSCStatusTcp->getCurrentDateTime())
                          .arg(sendCommand)
                          .arg(pSCStatusTcp->lastError()));
        }
    }else{
        ui->textEdit_info->append(QString("UnconnectedState"));
    }
}
/** 发送后，响应
 * @brief SCTcpToolWidget::slotChangedText
 * @param isOk
 * @param revCommand
 * @param revData
 * @param revHex
 * @param number
 * @param msTime
 */
void SCTcpToolWidget::slotChangedText(bool isOk,int revCommand,
                                      QByteArray revData,QByteArray revHex,
                                      int number,int msTime)
{
    if(isOk){

        int dataSize = 0;
        if(ui->checkBox_revHex->isChecked()){//16进制显示
            dataSize = revHex.size();
            ui->textEdit_revData->setText(pSCStatusTcp->hexToQString(revHex));
        }else{//文本显示
            dataSize = revData.size();
            ui->textEdit_revData->setText(QString(revData));
        }
        ui->label_revText->setText(QString("响应的报文类型: %1 (0x%2) \t\n\n"
                                           "序号: %4 (0x%5)\t\n\n"
                                           "响应时间: %6 ms \t\n\n"
                                           "响应数据区字节数: %7")
                                   .arg(revCommand)
                                   .arg(QString::number(revCommand,16))
                                   .arg(number)
                                   .arg(QString::number(number,16))
                                   .arg(msTime)
                                   .arg(dataSize));

    }else{

        slotPrintInfo(tr("<font color=\"red\">"
                         "%1--------- 返回错误----------\n"
                         "报文类型:%2  \n"
                         "错误: %3"
                         "</font>")
                      .arg(pSCStatusTcp->getCurrentDateTime())
                      .arg(revCommand)
                      .arg(pSCStatusTcp->lastError()));

        ui->textEdit_revData->setText(QString(revData));
        ui->label_revText->setText(QString("响应的错误: %1 \t\n")
                                   .arg(pSCStatusTcp->lastError()));
    }
}
/** 打印信息
 * @brief SCTcpToolWidget::slotPrintInfo
 * @param info
 */
void SCTcpToolWidget::slotPrintInfo(QString info)
{
    ui->textEdit_info->append(info);
}
/** 清空textEdit_info数据
 * @brief SCTcpToolWidget::on_pushButton_clearInfo_clicked
 */
void SCTcpToolWidget::on_pushButton_clearInfo_clicked()
{
    ui->textEdit_info->clear();
}
/** 自动滚动
 * @brief SCTcpToolWidget::slotAutomaticallyScroll
 */
void SCTcpToolWidget::slotAutomaticallyScroll()
{
    if(ui->checkBox_automatically->isChecked()){
        QTextEdit *textedit = (QTextEdit*)sender();
        if(textedit){
            QTextCursor cursor = textedit->textCursor();
            cursor.movePosition(QTextCursor::End);
            textedit->setTextCursor(cursor);
        }
    }
}



//*******************************新代码*********************************

//获取机器人设定点信息
void SCTcpToolWidget::on_pushButton_getrobo_clicked()
{
    QString revDataCheck=ui->textEdit_revData->toPlainText();
    if(revDataCheck.isEmpty()){
        ui->textEdit_setinfo->append("请先查询机器人站点信息");
        qDebug()<<"请先查询机器人站点信息"<<endl;
        return;
    }
    if(revDataCheck.startsWith("{\"stations\":[")){
       revDataCheck=revDataCheck.replace("{\"stations\":[{","");
       revDataCheck=revDataCheck.replace("{","");
       revDataCheck=revDataCheck.replace("}","");
       revDataCheck=revDataCheck.replace("]","");
       revDataCheck=revDataCheck.replace("\"desc\":\"","");  //是1
       revDataCheck=revDataCheck.replace("\"id\":\"","");    //是0
       revDataCheck=revDataCheck.replace("\"r\":","");       //是2
       revDataCheck=revDataCheck.replace("\"type\":\"","");  //是3
       revDataCheck=revDataCheck.replace("\"x\":","");       //是4
       revDataCheck=revDataCheck.replace("\"y\":","");       //是5
       revDataCheck=revDataCheck.replace("\"","");
       QStringList revDataChecklist=revDataCheck.split(",");
       int length_RobostationNamelist;
       for(int i=0;i<revDataChecklist.length();i+=6)
       {
           QList<QString> templist;
           templist<<revDataChecklist.at(i+1)<<revDataChecklist.at(i)<<revDataChecklist.at(i+2)<<revDataChecklist.at(i+4)<<revDataChecklist.at(i+5)<<revDataChecklist.at(i+3);
           length_RobostationNamelist=RobostationNamelist.count();
           QMapIterator<int,QList<QString> > findit(RobostationNamelist);
           int flag_addmode=1;// 0:不增加；1：代替
           while(findit.hasNext()) {
                findit.next();
                QList<QString> temp_value=findit.value();
                if(temp_value.at(0)==templist.at(0))
                {
                    flag_addmode=0;
                }
           }
           if(flag_addmode==1)
           {
               RobostationNamelist[length_RobostationNamelist]=templist;
           }
       }
       QMapIterator<int,QList<QString> > findit(RobostationNamelist);
       while(findit.hasNext()) {
            findit.next();
            QList<QString> templist=findit.value();
            ui->comboBox_robo->addItem(templist.at(0));
            qDebug()<<templist.at(0);
       }
        return;
    }
    else{
        qDebug()<<"请先查询机器人站点信息，端口号19204，报文类型1301"<<endl;
        ui->textEdit_info->append("请先查询机器人站点信息，端口号19204，报文类型1301");
        return;
    }
}
//连接摄像头
void SCTcpToolWidget::on_pushButton_connect_cam_clicked()
{
    ui->pushButton_connect_cam->setEnabled(false);
    ui->pushButton_close->setEnabled(true);
    bool ok;
    //接收传回来的字符串QString类型
    devip1 = ui->lineEdit_ip_cam->text();
    user1 = ui->lineEdit_username->text();
    password1 = ui->lineEdit_password->text();
    port1 = "8000";
    //QString转QByteArray类型
    devip2 = devip1.toLatin1();
    user2 = user1.toLatin1();
    password2 = password1.toLatin1();
    //QByteArray转char*类型
    devip = devip2.data();
    user = user2.data();
    password = password2.data();
    port = port1.toInt(&ok,10);

    struLoginInfo = {0};
    struLoginInfo.bUseAsynLogin = 0; //同步登录方式
    strcpy(struLoginInfo.sDeviceAddress,devip); //设备IP地址
    struLoginInfo.wPort = 8000; //设备服务端口
    strcpy(struLoginInfo.sUserName, user); //设备登录用户名
    strcpy(struLoginInfo.sPassword, password); //设备登录密码
    struDeviceInfoV40={0};
    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    if (lUserID < 0)
     {
        ui->textEdit_info->append("连接失败，错误代码：");
        ui->textEdit_info->append(QString::number(NET_DVR_GetLastError()));
        ui->textEdit_info->append(QString::number(lUserID));
        NET_DVR_Logout(lUserID);
     }
    else{

         ui->textEdit_info->append("连接成功，lUserID：");
         ui->textEdit_info->append(QString::number(lUserID));
         ui->textEdit_info->append(QString::number(struDeviceInfoV40.struDeviceV30.byStartChan));
    }
    return;
}
//断开与摄像头的连接
void SCTcpToolWidget::on_pushButton_close_clicked()
{
    ui->pushButton_connect_cam->setEnabled(true);
    ui->pushButton_close->setEnabled(false);
    NET_DVR_Logout(lUserID);
}
//获取摄像头预置点信息
void SCTcpToolWidget::on_pushButton_getcam_clicked()
{
    if(lUserID<0){
        ui->textEdit_info->append("请先连接摄像头");
        NET_DVR_Logout(lUserID);
        return;
    }
    else{
          bool iRet=0;
          DWORD dwReturnLen;
          for(int i=0;i<PRESET_NUM;i++)
          {
              struParams[i]={0};
          }
          iRet = NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_PRESET_NAME, 1, &struParams, sizeof(NET_DVR_PRESET_NAME)*PRESET_NUM,&dwReturnLen);
          if (!iRet)
           {
              ui->textEdit_info->append("获取预置点失败");
              ui->textEdit_info->append(QString::number(NET_DVR_GetLastError()));
              return;
           }
          else{
                ui->textEdit_info->append("获取预置点成功");
                for(int i=0;i<PRESET_NUM;i++)
                {
                    ui->comboBox_cam->addItem(struParams[i].byName);
                }

              }
          }
}
//设置关联
void SCTcpToolWidget::on_pushButton_taskset_clicked()
{
    QString temp1=ui->comboBox_robo->currentText();
    if(temp1==NULL)
    {
        ui->textEdit_setinfo->append("请先获取机器人位置点");
        return;
    }
    QString temp2=ui->comboBox_cam->currentText();
    if(temp2==NULL)
    {
        ui->textEdit_setinfo->append("请先获取摄像头预置点");
        return;
    }
    QList<QString> temp1list=temp1.split(",");
    temp1=temp1list.at(0);
    int i=0;
    while(QString::compare(temp1,RobostationNamelist.value(i).at(0))!=0)
    {
        i++;
        qDebug()<<i<<"i";
    }

    int j=0;
    while(QString::compare(temp2,QString(struParams[j].byName))!=0)
    {
        j++;
        qDebug()<<j<<"j";
    }
    QList<QString> temp3=RobostationNamelist.value(i);
    QString taskname=ui->lineEdit_taskname->text();
    if(taskname==NULL)
    {
        taskname=QString(struParams[j].byName);
        qDebug()<<taskname;
    }
    if(temp3.length()>numRobostationName) //如果已经设置过关联了，就替换
    {
        temp3.replace(numRobostationName,QString(struParams[j].byName));
        temp3.replace(numRobostationName+1,QString::number(struParams[j].wPresetNum));
        temp3.replace(numRobostationName+2,taskname);
    }
    else
    {                                     //如果没有设置过关联，就增加
        temp3.append(QString(struParams[j].byName));
        temp3.append(QString::number(struParams[j].wPresetNum));
        temp3.append(taskname);
    }
    RobostationNamelist[i]=temp3;
    QString temp11=temp1;
    temp11=temp1+","+QString(struParams[j].byName)+","+temp3.at(numRobostationName+2);
    ui->comboBox_robo->setItemText(ui->comboBox_robo->currentIndex(),temp11);
    for(int k=0;k<temp3.size();k++)
    {
    ui->textEdit_setinfo->append(RobostationNamelist.value(i).at(k));
    }
}

//取消设置关联
void SCTcpToolWidget::on_pushButton_unset_clicked()
{
    QString temp1=ui->comboBox_robo->currentText();
    if(temp1==NULL)
    {
        ui->textEdit_setinfo->append("请先获取机器人位置点");
        return;
    }
    QList<QString> temp1list=temp1.split(",");
    temp1=temp1list.at(0);
    int seeker=0;
    while(QString::compare(temp1,RobostationNamelist.value(seeker).at(0))!=0)
    {
        seeker++;
        qDebug()<<seeker<<"seeker";
    }
    QList<QString> temp3=RobostationNamelist.value(seeker);
    QList<QString> temp4;
    for(int k=0;k<numRobostationName;k++)
    {
        temp4<<temp3.at(k);
    }
    RobostationNamelist[seeker]=temp4;
    ui->comboBox_robo->setItemText(ui->comboBox_robo->currentIndex(),temp4.at(0));
    for(int h=0;h<temp4.size();h++)
    {
    ui->textEdit_setinfo->append(RobostationNamelist.value(seeker).at(h));
    }
}

//任务循环的定时器
void SCTcpToolWidget::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == _queryTimeID){
      ui->textEdit_info->append("进入定时");//*******check point***********
        //获取速度
      float loca_vr=20000; float loca_vx=20000; float loca_vy=20000;
       if(pSCStatusTcp->tcpSocket()
             &&pSCStatusTcp->tcpSocket()->state()==QAbstractSocket::ConnectedState)
       {
         uint16_t sendCommand = 1005;
         QString sendData = ui->textEdit_sendData->toPlainText();
         uint16_t number = ui->lineEdit_number->text().toInt();
         ui->textEdit_revData->clear();
         if(!pSCStatusTcp->writeTcpData(sendCommand,sendData,number))
         {
             slotPrintInfo(tr("<font color=\"red\">"
                              "%1--------- 发送错误----------\n"
                              "发送的报文类型:%2  \n"
                              "错误: %3"
                              "</font>")
                           .arg(pSCStatusTcp->getCurrentDateTime())
                           .arg(sendCommand)
                           .arg(pSCStatusTcp->lastError()));
         }
         QString speedinfo=ui->textEdit_revData->toPlainText();
         if(speedinfo.startsWith("{\"r_spin\":")){
            speedinfo=speedinfo.replace("{","");
            speedinfo=speedinfo.replace("}","");
            speedinfo=speedinfo.replace("\"vx\":","");
            speedinfo=speedinfo.replace("\"vy\":","");
            speedinfo=speedinfo.replace("\"w\":","");
         }
            QStringList speedinfolist=speedinfo.split(",");
            loca_vr=speedinfolist.at(7).toFloat();
            loca_vx=speedinfolist.at(8).toFloat();
            loca_vy=speedinfolist.at(9).toFloat();
     }else{
         ui->textEdit_info->append(QString("UnconnectedState"));
          }
       //获取速度
       //获取充电信息
       if(pSCStatusTcp->tcpSocket()
             &&pSCStatusTcp->tcpSocket()->state()==QAbstractSocket::ConnectedState)
       {
         uint16_t sendCommand = 1007;
         QString sendData = ui->textEdit_sendData->toPlainText();
         uint16_t number = ui->lineEdit_number->text().toInt();
         ui->textEdit_revData->clear();
         if(!pSCStatusTcp->writeTcpData(sendCommand,sendData,number))
         {
             slotPrintInfo(tr("<font color=\"red\">"
                              "%1--------- 发送错误----------\n"
                              "发送的报文类型:%2  \n"
                              "错误: %3"
                              "</font>")
                           .arg(pSCStatusTcp->getCurrentDateTime())
                           .arg(sendCommand)
                           .arg(pSCStatusTcp->lastError()));
         }
         QString chargeinfo=ui->textEdit_revData->toPlainText();
         if(chargeinfo.startsWith("{\"auto_charge\"")){
            chargeinfo=chargeinfo.replace("{\"auto_charge\":",""); //0
            chargeinfo=chargeinfo.replace("\"battery_cycle\":","");//1
            chargeinfo=chargeinfo.replace("\"battery_level\":","");//2
            chargeinfo=chargeinfo.replace("\"battery_temp\":","");//3
            chargeinfo=chargeinfo.replace("\"charging\":","");//4
            chargeinfo=chargeinfo.replace("\"current\":","");//5
            chargeinfo=chargeinfo.replace("\"manual_charge\":","");//6
            chargeinfo=chargeinfo.replace("\"voltage\":","");//7
            chargeinfo=chargeinfo.replace("}","");
         }
            QStringList chargeinfolist=chargeinfo.split(",");
            QString charge_true="true";
            QString charge_false="false";
            if(chargeinfolist.at(4)==charge_true)
            {
                count_id="0";
                return;
            }
            if(chargeinfolist.at(4)==charge_false)
            {
                //获取导航状态
                sendCommand = 1020;
                sendData = ui->textEdit_sendData->toPlainText();
                number = ui->lineEdit_number->text().toInt();
                ui->textEdit_revData->clear();
                if(!pSCStatusTcp->writeTcpData(sendCommand,sendData,number))
                {
                    slotPrintInfo(tr("<font color=\"red\">"
                                     "%1--------- 发送错误----------\n"
                                     "发送的报文类型:%2  \n"
                                     "错误: %3"
                                     "</font>")
                                  .arg(pSCStatusTcp->getCurrentDateTime())
                                  .arg(sendCommand)
                                  .arg(pSCStatusTcp->lastError()));
                }
                QString guideinfo=ui->textEdit_revData->toPlainText();
                if(guideinfo.startsWith("{\"finished_path\":")){//0
                   guideinfo=guideinfo.replace("{\"finished_path\":",""); //1
                   guideinfo=guideinfo.replace("\"running_status\":",""); //2
                   guideinfo=guideinfo.replace("\"target_id\"",""); //3
                   guideinfo=guideinfo.replace("\"task_status\"",""); //4
                   guideinfo=guideinfo.replace("\"task_type\":",""); //5
                   guideinfo=guideinfo.replace("\"unfinished_path\":",""); //6
                   guideinfo=guideinfo.replace("}","");
                   guideinfo=guideinfo.replace("\"","");
                }
                QStringList  guideinfolisttemp1= guideinfo.split(":");
                QString target_id=guideinfolisttemp1.at(1);
                target_id=target_id.replace(",","");
                QStringList guideinfolisttemp11=guideinfolisttemp1.at(2).split(",");
                QString task_status=guideinfolisttemp11.at(0); //0 = NONE, 1 = WAITING, 2 = RUNNING, 3 = SUSPENDED, 4 = COMPLETED, 5 = FAILED, 6 = CANCELED
                if(task_status=="0"||task_status=="1"||task_status=="5"||task_status=="6")
                {
                    return;
                }
                int seeker=0;
                qDebug()<<"进入while seeker前";
                while(QString::compare(target_id,RobostationNamelist.value(seeker).at(0))!=0)
                {
                    seeker++;
                }
                qDebug()<<"进入while seeker后";
                ui->textEdit_info->append(QString::number(seeker));//*******check point***********
                if(RobostationNamelist.value(seeker).length()==numRobostationName)
                {
                    return;
                }
                if(RobostationNamelist.value(seeker).length()==numRobostationName+3)
                {
                    //转摄像头部分
                    if(lUserID<0){
                        ui->textEdit_info->append("摄像头未连接");
                        return;
                    }
                    else{
                        bool iRet=0;
                        DWORD PRESETNAME=RobostationNamelist.value(seeker).at(7).toInt();
                        iRet = NET_DVR_PTZPreset_Other(lUserID,1,GOTO_PRESET,PRESETNAME);
                        if (!iRet)
                          {
                              ui->textEdit_info->append("转到预置点失败");
                              ui->textEdit_info->append(QString::number(NET_DVR_GetLastError()));
                              return;
                          }
                        else
                        {
                            ui->textEdit_info->append("转到预置点成功");//*******check point***********
                        }
                    }
                    QString task_status_4="4";
                    qDebug()<<"进入速度判别的之前";
                    qDebug()<<task_status;
                    if((task_status==task_status_4)&&(loca_vr<=0.001)&&(loca_vx<=0.001)&&(loca_vy<=0.001))
                    {
                        qDebug()<<"进入速度判别的for";
                        if (count_id!=target_id)
                        {
                            qDebug()<<"进入要延时的if了";
                            QTime dieTime = QTime::currentTime().addMSecs(1000);
                            while( QTime::currentTime() < dieTime )
                            {
                                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                            }
                            qDebug()<<"进入要拍照了";
                            //抓图部分
                            if(lUserID<0){
                                ui->textEdit_info->append("摄像头未连接");
                                return;
                            }
                            else{
                                NET_DVR_JPEGPARA lpJpegPara={0};
                                lpJpegPara.wPicQuality=0;
                                lpJpegPara.wPicSize=0xff;
                                QString sPicFileNam;
                                QString sPicFileNamone=ui->lineEdit_save->text();
                                QString sPicFileNamtwo=RobostationNamelist.value(seeker).at(numRobostationName+2);
                                if(sPicFileNamtwo.length()==0)
                                {
                                    sPicFileNamtwo=sPicFileNamtwo.append("默认");
                                }
                                sPicFileNam=sPicFileNam.append(sPicFileNamone);
                                sPicFileNam=sPicFileNam.append("\\\\");
                                sPicFileNam=sPicFileNam.append(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
                                sPicFileNam=sPicFileNam.append(sPicFileNamtwo);
                                sPicFileNam=sPicFileNam.append(".jpg");
                                QByteArray sPicFileNam1;
                                char* sPicFileNam2;
                                sPicFileNam1=sPicFileNam.toLatin1();
                                sPicFileNam2=sPicFileNam1.data();
                                int iRet;
                                iRet=NET_DVR_CaptureJPEGPicture(lUserID,1,&lpJpegPara,sPicFileNam2);
                                if(!iRet){
                                    ui->textEdit_setinfo->append(sPicFileNam);
                                    qDebug()<<"抓图失败";
                                    ui->textEdit_setinfo->append("抓图失败");
                                    ui->textEdit_setinfo->append(QString::number(NET_DVR_GetLastError()));
                                    return;
                                }
                                count_id.clear();
                                count_id.append(target_id);
                            }
                        }
                    }
                }
            }
       }else{
           ui->textEdit_info->append(QString("UnconnectedState"));
            }

        //todo   0、判断机器人是否在充电，是的话count=-1，count_id清空
         //count为全局变量初始化为-1，count_id_length()为全局变量，
         // 1、分离出导航信息数据，并做判断，在导航时才动作（target_id 与Robonamelist配置中的id对比，判断存在，且判断有关联点才要动作（），保留存在id对应i，摄像头转到预置点，下一步；
         //2、finished_path列表中最后一个为target_id时,下一步；3、速度为0时，if count_id!=target_id，然后延时100毫秒，抓图，存图，图名=时间+Robonamelist[i].任务名，设count_id=target_id
         /*****延时方法*******
          * QTime dieTime = QTime::currentTime().addMSecs(msec);
          *  while( QTime::currentTime() < dieTime ) {
          * QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
          * }
          */

    }
}
//任务循环断开
void SCTcpToolWidget::myKillTimer(int id)
{
    killTimer(id);
    id = -1;
}
//开始或停止任务
void SCTcpToolWidget::on_pushButton_start_clicked(bool checked)
{
    if(checked)
    {
        ui->pushButton_start->setText("stop");
        _queryTimeID = this->startTimer(1000);

    }
    else{
        ui->pushButton_start->setText("start");
         if (_queryTimeID > 0) {
            myKillTimer(_queryTimeID);
         }
    }
}
//转到预置点
void SCTcpToolWidget::on_pushButton_clicked()
{
    if(lUserID<0){
        ui->textEdit_info->append("请先连接摄像头");
        NET_DVR_Logout(lUserID);
        return;
    }
    else{
        bool iRet=0;
        QString temp_cam=ui->comboBox_cam->currentText();
        int j=0;
        while(QString::compare(temp_cam,QString(struParams[j].byName))!=0)
        {
            j++;
        }
        j=j;


        DWORD PRESETNAME=struParams[j].wPresetNum;
        iRet = NET_DVR_PTZPreset_Other(lUserID,1,GOTO_PRESET,PRESETNAME);


        if (!iRet)
          {
              ui->textEdit_info->append("转到预置点失败");
              ui->textEdit_info->append(QString::number(NET_DVR_GetLastError()));
              ui->textEdit_info->append(QString::number(lUserID));
              return;
          }
        else{
              ui->textEdit_info->append("转到预置点成功，预置点名称：");
              ui->textEdit_info->append(QString::number(struParams[j].wPresetNum));
            return;
        }
    }
}
//抓图
void SCTcpToolWidget::on_pushButton_catch_clicked()
{
    NET_DVR_JPEGPARA lpJpegPara={0};
    lpJpegPara.wPicQuality=0;
    lpJpegPara.wPicSize=0xff;
    QString sPicFileNam;
    QString sPicFileNamone=ui->lineEdit_save->text();
    QString sPicFileNamtwo=ui->lineEdit_taskname->text();
    /*if(sPicFileNamtwo.length()==0)
    {
        sPicFileNamtwo=sPicFileNamtwo.append("默认");
    }*/
    sPicFileNam=sPicFileNam.append(sPicFileNamone);
    sPicFileNam=sPicFileNam.append("\\\\");
    //sPicFileNam=sPicFileNam.append(QTime::currentTime().toString());
    sPicFileNam=sPicFileNam.append(sPicFileNamtwo);
    sPicFileNam=sPicFileNam.append(".jpg");
    QByteArray sPicFileNam1;
    char* sPicFileNam2;
    sPicFileNam1=sPicFileNam.toLatin1();
    sPicFileNam2=sPicFileNam1.data();
    int iRet;
    iRet=NET_DVR_CaptureJPEGPicture(lUserID,1,&lpJpegPara,sPicFileNam2);
    if(!iRet){
        ui->textEdit_setinfo->append(sPicFileNam);
        ui->textEdit_setinfo->append("抓图失败");
        ui->textEdit_setinfo->append(QString::number(NET_DVR_GetLastError()));
        return;
    }
  else{
        ui->textEdit_setinfo->append("抓图成功");
      return;
      }
}

void SCTcpToolWidget::on_save_set_clicked()
{

    QFile csvFile("../set.csv");
    if (csvFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMapIterator<int,QList<QString> > findit(RobostationNamelist);
        if(!findit.hasNext())
        {
            ui->textEdit_setinfo->append("请先获取机器人位置点");
            return;
        }
     QTextStream out(&csvFile);
     while(findit.hasNext()) {
         findit.next();
         QList<QString> templist=findit.value();
         out<<templist.at(0);
         for(int i=1;i<templist.length();i++)
         {
             out<<","<<templist.at(i);
         }
         out<<"\n";
         }
     csvFile.close();
     ui->textEdit_setinfo->append("成功保存配置文件！");
     return;
     }
     else
     {
        ui->textEdit_setinfo->append("文件已被其他应用打开，请关闭后重试");
        return;
     }
}

void SCTcpToolWidget::on_read_set_clicked()
{
    QString temp1=ui->comboBox_robo->currentText();
    if(temp1==NULL)
    {
        ui->textEdit_setinfo->append("请先获取机器人位置点");
        return;
    }
    QFile csvFile("../set.csv");
     if (!csvFile.open(QIODevice::ReadOnly | QIODevice::Text))
         {
         ui->textEdit_setinfo->append("未找到文件！");
         return;
         }
     QTextStream in(&csvFile);
     if(!in.atEnd())
     {

         while(!in.atEnd()) {
             QString line = in.readLine();
             QList<QString> strlist=line.split(",");
             QMapIterator<int,QList<QString> > findit(RobostationNamelist);
             int flag_addmode=0;// 0:不增加；1：代替
             int flag_add_key=-1;
             while(findit.hasNext()) {
                 findit.next();
                 QList<QString> templist=findit.value();
                 int temp_key=findit.key();
                 if((templist.at(0)==strlist.at(0))&&(templist.length()<=strlist.length()))
                 {
                     flag_addmode=1;
                     flag_add_key=temp_key;
                 }
             }
             if(flag_addmode==1)
             {
                 RobostationNamelist[flag_add_key]=strlist;
             }
         }
     }
     else
     {
         ui->textEdit_setinfo->append("文件中无信息,保留原配置");
         return;
     }

     ui->comboBox_robo->clear();
     QMapIterator<int,QList<QString> > findit(RobostationNamelist);
     while(findit.hasNext()) {
         findit.next();
         QList<QString> templist=findit.value();
         for(int i=0;i<templist.length();i++)
         {
             qDebug()<<templist.at(i);
         }
         qDebug()<<"-------";
         if(templist.length()==numRobostationName)
         {
             ui->comboBox_robo->addItem(templist.at(0));
         }

         if(templist.length()==numRobostationName+3)
         {
             QString temp11=templist.at(0)+","+templist.at(6)+","+templist.at(8);
             ui->comboBox_robo->addItem(temp11);
         }
     }
}





