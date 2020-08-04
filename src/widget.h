#ifndef WIDGET_H
#define WIDGET_H

#include "mcanbus.h"
#include "frmnum.h"
#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QList>
#include <QMessageBox>


#define HEAD_1               0x55
#define HEAD_2               0xAA

#define DEFAULT              0x00

#define UP_1                 0x01
#define DOWN_1               0x02
#define LEFT_1               0x03
#define RIGHT_1              0x04
#define RISE_1               0x05
#define FALL_1               0x06

#define UP_2                 0x09
#define DOWN_2               0x0A
#define LEFT_2               0x0B
#define RIGHT_2              0x0C
#define RISE_2               0x0D
#define FALL_2                0x0E

#define MOVEFORWARD          0x11
#define MOVEBACK             0x12
#define SPEEDUP              0x13
#define SLOWDOWN             0x14
#define SINGLEWELDING        0x15
#define DOUBLEWELDING        0x16
#define STOP                 0x17

#define PUBLIC               0x40
#define UPDOWNTRACKING       0x41
#define LEFTRIGHTTRACKING    0x42
#define MOTION               0x43

#define ROOT                 0x80
#define HOT                  0x81
#define FILLING_1            0x82
#define FILLING_2            0x83
#define FILLING_3            0x84
#define FILLING_4            0x85
#define FILLING_5            0x86
#define FILLING_6            0x87
#define FILLING_7            0x88
#define FILLING_8            0x89
#define FILLING_9            0x8A
#define FILLING_10           0x8B
#define COVER_1              0x8C
#define COVER_2              0x8D
#define COVER_3              0x8E
#define COVER_4              0x8F

#define clock0P              0//
#define clock0p5P            15//0
#define clock1P              30//1
#define clock1p5P            45//2
#define clock2P              60//3
#define clock2p5P            75//4
#define clock3P              90//5
#define clock3p5P            105//6
#define clock4P              120//7
#define clock4p5P            135//8
#define clock5P              150//9
#define clock5p5P            165//10
#define clock6P              180//11
#define clock6p5P            195//5.5//11
#define clock7P              210//5//10
#define clock7p5P            225//4.5//9
#define clock8P              240//4//8
#define clock8p5P            255//3.5//7
#define clock9P              270//3//6
#define clock9p5P            285//2.5//5
#define clock10P             300//2//4
#define clock10p5P           315//1.5//3
#define clock11P             330//1//2
#define clock11p5P           345//0.5//1
#define clock12P             360//0//0


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();



private slots:
    void L1UpDown();
    void L1LeftRight();
    void L2UpDown();
    void L2LeftRight();
    void L3UpDown();
    void L3LeftRight();
    void L4UpDown();
    void L4LeftRight();
    void L5UpDown();
    void L5LeftRight();
    void L6UpDown();
    void L6LeftRight();
    void L7UpDown();
    void L7LeftRight();
    void L8UpDown();
    void L8LeftRight();
    void C1UpDown();
    void C1LeftRight();
    void C2UpDown();
    void C2LeftRight();

    void L1UpDown2();
    void L1LeftRight2();
    void L2UpDown2();
    void L2LeftRight2();
    void L3UpDown2();
    void L3LeftRight2();
    void L4UpDown2();
    void L4LeftRight2();
    void L5UpDown2();
    void L5LeftRight2();
    void L6UpDown2();
    void L6LeftRight2();
    void L7UpDown2();
    void L7LeftRight2();
    void L8UpDown2();
    void L8LeftRight2();
    void C1UpDown2();
    void C1LeftRight2();
    void C2UpDown2();
    void C2LeftRight2();

    void TransCantoSerial(CANFRAME*);


    void send();
    void receiveinfo();


signals:

    //void ANGEL(float a);
    void CanSendData(QByteArray data);
private:
    Ui::Widget *ui;

    QSerialPort* serialRs232;
    QSerialPort* serialRs485;

    MCanBus *mCanBus;


    //跟踪开关数组
    QByteArray Leftright;
    QByteArray Updown;


    //字节数组
    QByteArray MovingData;
    QByteArray MovingFloatData;

    QByteArray WeldingData;
    QByteArray WeldingFloatData;
    //二维字节数组
    QByteArray mData[120];
    QByteArray mFloatData[120];

    QByteArray wData[120];
    QByteArray wFloatData[120];
    //公共参数数组
    QByteArray Public;

    //接收数组
    QByteArray Recv_MovingData;
    QByteArray Recv_MovingFloatData;
    QByteArray Recv_WeldingData;
    QByteArray Recv_WeldingFloatData;
    QByteArray Recv_Public;
    QByteArray Recv_Leftright_1;
    QByteArray Recv_Updown_1;
    QByteArray Recv_Leftright_2;
    QByteArray Recv_Updown_2;


    //保存文件路径
    QString BinFile;
    float angle;
    int Layer;

    void initSeialPort();

    //数值控件列表
    QList<QSpinBox*>  qMoveingSpinBoxList;
    QList<QDoubleSpinBox*>  qMoveingDoubleSpinBoxList;
    QList<QSpinBox*>  qWeldingSpinBoxList;
    QList<QDoubleSpinBox*>  qWeldingDoubleSpinBoxList;

    void GetDataFormWidget();
    void GetWidgetValueFormBinFile();
    void SaveSwitchData();
    void GetSwitchData();
    void SavePublicData();
    void GetPublicData();
    int welding(float a);


};

#endif // WIDGET_H
