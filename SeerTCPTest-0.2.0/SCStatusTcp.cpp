#include "SCStatusTcp.h"
#include "SCHeadData.h"

#define M_TimeOut 3000 //等待时间

SCStatusTcp::SCStatusTcp(QObject *parent) : QObject(parent),
    _tcpSocket(Q_NULLPTR)
{

}
SCStatusTcp::~SCStatusTcp()
{
    releaseTcpSocket();
}
/** 释放tcpSocket
 * @brief SCStatusTcp::releaseTcpSocket
 */
void SCStatusTcp::releaseTcpSocket()
{
    if(_tcpSocket){

        if(_tcpSocket->isOpen()){
            _tcpSocket->close();
        }
    }
}
int SCStatusTcp::connectHost(const QString&ip,quint16 port)
{
    int ret = 0;
    if(!_tcpSocket){
        _tcpSocket = new QTcpSocket(this);
        connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveTcpReadyRead()));
        connect(_tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                this->parent(), SLOT(stateChanged(QAbstractSocket::SocketState)));
        connect(_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this->parent(),
                SLOT(receiveTcpError(QAbstractSocket::SocketError)));
    }
    if(_tcpSocket->isOpen()
            &&(_tcpSocket->state()==QAbstractSocket::ConnectedState
               ||_tcpSocket->state()==QAbstractSocket::ConnectingState)){
        _tcpSocket->close();
        _tcpSocket->abort();
        qDebug()<<"----close _tcpSocket----\n";
        ret = 1;
    }else{
        _tcpSocket->connectToHost(ip,port);
        _ip = ip;
        _port = port;
        ret = 0;
    }
    return ret;
}
/** TCP请求
 * @brief SCStatusTcp::writeTcpData
 * @param sendCommand 报文类型
 * @param sendData 数据区数据
 * @param number 序号
 * @return
 */
bool SCStatusTcp::writeTcpData(uint16_t sendCommand,
                               const QString&sendData,
                               uint16_t &number)
{
    //已发送
    _oldSendCommand = sendCommand;
    _oldNumber = number;
    //数据区长度
    int size = 0;
    //报文头部数据
    uint8_t* headBuf = Q_NULLPTR;
    int headSize = 0;
    //发送的全部数据
    SeerData* seerData = Q_NULLPTR;
    //开始计时
    _time.start();

    //根据数据区数据进行数据转换
    if(sendData.isEmpty()){
        headSize = sizeof(SeerHeader);
        headBuf = new uint8_t[headSize];
        seerData = (SeerData*)headBuf;
        size = seerData->setData(sendCommand,Q_NULLPTR,0,number);
    }else{
        std::string json_str = sendData.toStdString();
        headSize = sizeof(SeerHeader) + json_str.length();
        headBuf = new uint8_t[headSize];
        seerData = (SeerData*)headBuf;
        size = seerData->setData(sendCommand,
                                 (uint8_t*)json_str.data(),
                                 json_str.length(),
                                 number);
    }
    //---------------------------------------
    //发送的所有数据
    QByteArray tempA = QByteArray::fromRawData((char*)seerData,size);
    qDebug()<<"send:"<<QString(tempA)<<"  Hex:"<<tempA.toHex();
    //打印信息
    QString info = QString("\n%1--------- 请求 ---------\n"
                           "报文类型:%2 (0x%3) \n"
                           "端口: %4\n"
                           "序号: %5 (0x%6)\n"
                           "头部十六进制: %7 \n"
                           "数据区[size:%8 (0x%9)]: %10 \n"
                           "数据区十六进制: %11 ")
            .arg(getCurrentDateTime())
            .arg(sendCommand)
            .arg(QString::number(sendCommand,16))
            .arg(_port)
            .arg(number)
            .arg(QString::number(number,16))
            .arg(hexToQString(tempA.left(16).toHex()))
            .arg(sendData.size())
            .arg(QString::number(sendData.size(),16))
            .arg(sendData)
            .arg(hexToQString(sendData.toLatin1().toHex()));

    emit sigPrintInfo(info);
    //---------------------------------------
    _tcpSocket->write((char*)seerData, size);
    delete[] headBuf;
    //等待写入
    if(!_tcpSocket->waitForBytesWritten(M_TimeOut)){
        _lastError = tr("waitForBytesWritten: time out!");
        return false;
    }
    //等待读取
    if(!_tcpSocket->waitForReadyRead(M_TimeOut)){
        _lastError = tr("waitForReadyRead: time out!");
        return false;
    }
    return true;
}
void SCStatusTcp::receiveTcpReadyRead()
{
    //读取所有数据
    //返回的数据大小不定,需要使用_lastMessage成员变量存放多次触发槽读取的数据。
    QByteArray message = _tcpSocket->readAll();
    message = _lastMessage + message;
    int size = message.size();

    while(size > 0){
        char a0 = message.at(0);
        if (uint8_t(a0) == 0x5A){//检测第一位是否为0x5A
            if (size >= 16) {//返回的数据最小长度为16位,如果大小小于16则数据不完整等待再次读取
                SeerHeader* header = new SeerHeader;
                memcpy(header, message.data(), 16);

                uint32_t data_size;//返回所有数据总长值
                uint16_t revCommand;//返回报文数据类型
                uint16_t number;//返回序号
                qToBigEndian(header->m_length,(uint8_t*)&(data_size));
                qToBigEndian(header->m_type, (uint8_t*)&(revCommand));
                qToBigEndian(header->m_number, (uint8_t*)&(number));
                delete header;

                int remaining_size = size - 16;//所有数据总长度 - 头部总长度16 = 数据区长度
                //如果返回数据长度值 大于 已读取数据长度 表示数据还未读取完整，跳出循环等待再次读取.
                if (data_size > remaining_size) {
                    _lastMessage = message;

                    break;
                }else{//返回数据长度值 大于等于 已读取数据，开始解析
                    QByteArray tempMessage;
                    if(_lastMessage.isEmpty()){
                        tempMessage = message;
                    }else{
                        tempMessage = _lastMessage;
                    }
                    QByteArray headB = message.left(16);
                    //截取报头16位后面的数据区数据
                    QByteArray json_data = message.mid(16,data_size);
                    qDebug()<<"rev:"<<QString(json_data)<<"  Hex:"<<json_data.toHex();
                    //--------------------------------------
                    //输出打印信息
                    QString info = QString("%1--------- 响应 ---------\n"
                                           "报文类型:%2 (%3) \n"
                                           "序号: %4 (0x%5)\n"
                                           "头部十六进制: %6\n"
                                           "数据区[size:%7 (0x%8)]: %9 \n"
                                           "数据区十六进制: %10 \n")
                            .arg(getCurrentDateTime())
                            .arg(revCommand)
                            .arg(QString::number(revCommand,16))
                            .arg(number)
                            .arg(QString::number(number,16))
                            .arg(hexToQString(headB.toHex()))
                            .arg(json_data.size())
                            .arg(QString::number(json_data.size(),16))
                            .arg(QString(json_data))
                            .arg(hexToQString(json_data.toHex()));

                    emit sigPrintInfo(info);
                    int msTime = _time.elapsed();
                    //----------------------------------------
                    //输出返回信息
                    emit sigChangedText(true,revCommand,
                                        json_data,json_data.toHex(),
                                        number,msTime);
                    //截断message,清空_lastMessage
                    message = message.right(remaining_size - data_size);
                    size = message.size();
                    _lastMessage.clear();
                }

            } else{
                _lastMessage = message;
                break;
            }
        }else{
            //报头数据错误
            setLastError("Seer Header Error !!!");
            message = message.right(size - 1);
            size = message.size();
            int msTime = _time.elapsed();
            emit sigChangedText(false,_oldSendCommand,
                                _lastMessage,_lastMessage.toHex(),
                                0,msTime);
        }
    }
}


QTcpSocket *SCStatusTcp::tcpSocket() const
{
    return _tcpSocket;
}

QTime SCStatusTcp::time() const
{
    return _time;
}

void SCStatusTcp::setLastError(const QString &lastError)
{
    _lastError = lastError;
}

QString SCStatusTcp::lastError() const
{
    return _lastError;
}
QString SCStatusTcp::getCurrentDateTime()const
{
    return QDateTime::currentDateTime().toString("[yyyyMMdd|hh:mm:ss:zzz]:");
}
QString SCStatusTcp::hexToQString(const QByteArray &b)
{
    QString str;
    for(int i=0;i<b.size();++i){
//        //每2位空格0x
//        if((!(i%2)&&i/2)||0==i){
//            str+= QString(" 0x");
//        }
        str +=QString("%1").arg(b.at(i));
    }
    str = str.toUpper();
    return str;
}

