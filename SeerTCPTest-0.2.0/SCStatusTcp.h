#ifndef SCStatusTcp_H
#define SCStatusTcp_H


#include <QTcpSocket>
#include <QObject>
#include <QTime>

class SCStatusTcp : public QObject
{
    Q_OBJECT
public:
    explicit SCStatusTcp(QObject *parent = 0);

    ~SCStatusTcp();

    void releaseTcpSocket();
    QString lastError() const;

    void setLastError(const QString &lastError);

    bool writeTcpData(uint16_t sendCommand,
                      const QString &sendData,
                      uint16_t &number);

    QTcpSocket *tcpSocket() const;

    QTime time() const;

    int connectHost(const QString &ip, quint16 port);
    QString getCurrentDateTime() const;
    QString hexToQString(const QByteArray &b);
public slots:
    void receiveTcpReadyRead();
signals:
    void sigPrintInfo(QString);
    void sigChangedText(bool ,int ,QByteArray ,QByteArray ,int ,int );
private:

    QTcpSocket *_tcpSocket;
    QString _lastError;
    QString _ip; //ip
    quint16 _port; //端口号
    uint16_t _number;//序号

    QByteArray _lastMessage;//存放所有读取的数据
    QTime _time;//用来监测时间

    int _oldSendCommand;
    int _oldNumber;


};

#endif // SCStatusTcp_H
