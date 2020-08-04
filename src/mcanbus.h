#ifndef MCANBUS_H
#define MCANBUS_H

#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <QDebug>
#include <QApplication>
#include <QObject>
#include <QThread>

typedef can_frame   CANFRAME;
typedef canid_t         CAN_ID;

class MCanBus : public QThread
{
    Q_OBJECT

public:
    explicit MCanBus(QObject *parent = 0);
    ~MCanBus();

    bool Fire;
    bool Gas;
    bool Wire;

    void caninit0();
    void caninit1();
    void stop();
    void recvData();
    void send();

private:
   int fb0;
   int fb1;


signals:
   void ReadyRead(CANFRAME *frame);      // 参数必须是结构体指针的形式
   void ReadyRead(uchar* p_data,int len);     //

protected:
   void run();
   volatile bool m_stopped;

private slots:


public slots:
   void send(QByteArray data);
   void sendData(CANFRAME *frame);

};

#endif // MCANBUS_H
