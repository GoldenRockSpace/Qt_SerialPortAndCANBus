#include "mcanbus.h"
#include <QString>
#include <QThread>
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
#include <QEventLoop>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>


MCanBus::MCanBus(QObject *parent) : QThread(parent)
{
    Fire = false;
}

MCanBus::~MCanBus()
{
    close(fb0);
    close(fb1);
}


void MCanBus::run()
{
    connect(this,SIGNAL(ReadyRead(CANFRAME*)),this,SLOT(sendData(CANFRAME*)),Qt::QueuedConnection);
    while (1)
    {
        recvData();
    }

}

void MCanBus::send(QByteArray data)
{
    struct can_frame frame;
    int nbytes = -1;
    frame.can_id = 0x00200088 | CAN_EFF_FLAG;
    frame.can_dlc = 4;


    for(int i=0;i < 4;i++)
    {
        frame.data[i] = data[i];
    }

    nbytes = write(fb0,&frame,sizeof(frame));
        if(nbytes > 0)
        {
            qDebug("Send ID:0x%08x > [%d] >> : ",frame.can_id & CAN_EFF_MASK);
            for(int dlc=0;dlc<frame.can_dlc;dlc++)
                qDebug("0x%02x ",frame.data[dlc]);
        }
        else
        {
            qDebug("CAN write error");
        }

}


void MCanBus::sendData(CANFRAME *frame)
{

    if(frame->data[0] == 0x00 && frame->can_id == 0x40){
        if(Fire == true)
        {
             qDebug("fired");
             Fire = false;
        }
        else
        {
            int nbytes;
            struct can_frame frame;
            /*frame[0].can_id = 0x00200002 | CAN_EFF_FLAG;//扩展帧ID
            frame[0].can_dlc = 1;
            frame[0].data[0] = 0x2F;*/
            frame.can_id = 0x00200022 | CAN_EFF_FLAG;
            frame.can_dlc = 1;
            frame.data[0] = 0x00;


            nbytes = write(fb0,&frame,sizeof(frame));
            if(nbytes != sizeof(frame))
            {
                    qDebug("CAN write error");

            }
            else
            {
                    qDebug("Send ID:0x%00x > [%d] >> : ",frame.can_id,frame.can_dlc);
                                for(int dlc=0;dlc<frame.can_dlc;dlc++)
                                    qDebug("0x%02x ",frame.data[dlc]);
            }
        }


    }
     if(frame->data[0] == 0x15){
        Fire = true;
        int nbytes;
        struct can_frame frame ;
        frame.can_id = 0x00200002 | CAN_EFF_FLAG;//扩展帧ID
        frame.can_dlc = 1;
        frame.data[0] = 0x03;

        nbytes = write(fb0, &frame, sizeof(frame));
        if(nbytes != sizeof(frame))
        {
                printf("Send Error frame[0]\n");
        }
        else
        {
            qDebug()<<frame.data[0]<<endl;
        }
    }
     if(frame->data[0] == 0x07){

        int nbytes;
        struct can_frame frame ;
        frame.can_id = 0x00200022 | CAN_EFF_FLAG;
        frame.can_dlc = 1;
        frame.data[0] = 0x02;

        nbytes = write(fb0, &frame, sizeof(frame));
        if(nbytes != sizeof(frame))
        {
                printf("Send Error frame[0]\n");
        }
        else
        {
            qDebug()<<frame.data[0]<<endl;
        }
    }
     if(frame->data[0] == 0x08){

         int nbytes;
         struct can_frame frame ;
         frame.can_id = 0x00200022 | CAN_EFF_FLAG;
         frame.can_dlc = 1;
         frame.data[0] = 0x01;


         nbytes = write(fb0, &frame, sizeof(frame));
         if(nbytes != sizeof(frame))
         {
                 printf("Send Error frame[0]\n");
         }
         else
         {
             qDebug()<<frame.data[0]<<endl;
         }
    }
     if(frame->data[0] == 0x17){

         int nbytes;
         struct can_frame frame;
         frame.can_id = 0x00200002 | CAN_EFF_FLAG;//扩展帧ID
         frame.can_dlc = 1;
         frame.data[0] = 0x00;

         nbytes = write(fb0,&frame,sizeof(frame));
         if(nbytes != sizeof(frame))
         {
                 qDebug("CAN write error");

         }
         else
         {
                 qDebug("Send ID:0x%00x > [%d] >> : ",frame.can_id,frame.can_dlc);
                             for(int dlc=0;dlc<frame.can_dlc;dlc++)
                                 qDebug("0x%02x ",frame.data[dlc]);
         }

    }



}

void MCanBus::caninit1()
{
    struct sockaddr_can addr_1;
    struct ifreq ifr_1;

    fb1 = socket(PF_CAN, SOCK_RAW, CAN_RAW);//创建套接字
    strcpy(ifr_1.ifr_name, "can1" );
    ioctl(fb1, SIOCGIFINDEX, &ifr_1); //指定 can0 设备

    addr_1.can_family = AF_CAN;
    addr_1.can_ifindex = ifr_1.ifr_ifindex;
    bind(fb1, (struct sockaddr *)&addr_1, sizeof(addr_1));//将套接字与 can0 绑定
    qDebug("1");
}

/*void MCanBus::stop()
{
    m_stopped = true;
}*/

void MCanBus::recvData()
{

    int nbytes = -1;
    struct can_frame frame;
    nbytes = read(fb0,&frame,sizeof(can_frame));
    if((nbytes) > 0)
    {

        emit ReadyRead(&frame);
        emit ReadyRead(frame.data,frame.can_dlc);
        qDebug("ID:0x%08x > [%d] <<: \n",frame.can_id ,frame.can_dlc);
        for(int i=0;i<frame.can_dlc;i++)
            qDebug("0x%02x",frame.data[i]);

    }
   else
    {
        qDebug()<<"can receive error.\n";
        exit(-1);
    }

}

void MCanBus::caninit0()
{
    struct sockaddr_can addr_0;
    struct ifreq ifr_0;

    fb0 = socket(PF_CAN, SOCK_RAW, CAN_RAW);//创建套接字
    strcpy(ifr_0.ifr_name, "can0");
    ioctl(fb0, SIOCGIFINDEX, &ifr_0); //指定 can0 设备

    addr_0.can_family = AF_CAN;
    addr_0.can_ifindex = ifr_0.ifr_ifindex;
    bind(fb0, (struct sockaddr *)&addr_0, sizeof(addr_0));//将套接字与 can0 绑定
    qDebug("0");
}

























