//widget.cpp
#include "widget.h"
#include "ui_widget.h"
#include "mcanbus.h"
#include "frmnum.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QString>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QList>
#include <QLineEdit>
#include <QFile>
#include <QObject>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);   
    //执行命令行配置CAN比特率
    system("ifconfig can0 down");
    system("ifconfig can1 down");
    system("ip link set can0 type can bitrate 1000000");
    system("ifconfig can0 up");
    system("ip link set can1 type can bitrate 1000000");
    system("ifconfig can1 up");

    serialRs232 = new QSerialPort(this);
    serialRs485 = new QSerialPort(this);

    mCanBus = new MCanBus;

    //初始化串口
    initSeialPort();


    mCanBus->caninit1();
    mCanBus->caninit0();




    connect(mCanBus,SIGNAL(ReadyRead(CANFRAME*)),this,SLOT(TransCantoSerial(CANFRAME*)),Qt::QueuedConnection);
    mCanBus->start();


    int index = 0;
    //运动参数
    for(int r = 1; r < 13; r++)
    {
        QSpinBox * qSpinBox = new QSpinBox();
        qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
        qSpinBox->setMinimum(0);
        qSpinBox->setMaximum(65535);
        qSpinBox->setAlignment(Qt::AlignRight);
        //qSpinBox->setAccessibleName(QString::number( index++));

        ui->gridLayout->addWidget(qSpinBox,r,1);
        qMoveingSpinBoxList.append(qSpinBox);

        for(int c = 2; c < 4; c++)
        {
             QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
             qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
             qDoubleSpinBox->setDecimals(1);
             qDoubleSpinBox->setMinimum(0);
             qDoubleSpinBox->setMaximum(65535.0);
             qDoubleSpinBox->setAlignment(Qt::AlignRight);
             //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout->addWidget(qDoubleSpinBox,r,c);

             qMoveingDoubleSpinBoxList.append(qDoubleSpinBox);
        }

        for(int c = 4; c < 10; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout->addWidget(qSpinBox,r,c);

             qMoveingSpinBoxList.append(qSpinBox);
        }

    }
    for(int r = 1; r < 13; r++)
    {
        QSpinBox * qSpinBox = new QSpinBox();
        qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
        qSpinBox->setMinimum(0);
        qSpinBox->setMaximum(65535);
        qSpinBox->setAlignment(Qt::AlignRight);
        //qSpinBox->setAccessibleName(QString::number( index++));

        ui->gridLayout_2->addWidget(qSpinBox,r,1);
        qMoveingSpinBoxList.append(qSpinBox);

        for(int c = 2; c < 4; c++)
        {
             QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
             qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
             qDoubleSpinBox->setDecimals(1);
             qDoubleSpinBox->setMinimum(0);
             qDoubleSpinBox->setMaximum(65535.0);
             qDoubleSpinBox->setAlignment(Qt::AlignRight);
             //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_2->addWidget(qDoubleSpinBox,r,c);

             qMoveingDoubleSpinBoxList.append(qDoubleSpinBox);
        }

        for(int c = 4; c < 10; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_2->addWidget(qSpinBox,r,c);

             qMoveingSpinBoxList.append(qSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        QSpinBox * qSpinBox = new QSpinBox();
        qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
        qSpinBox->setMinimum(0);
        qSpinBox->setMaximum(65535);
        qSpinBox->setAlignment(Qt::AlignRight);
        //qSpinBox->setAccessibleName(QString::number( index++));

        ui->gridLayout_3->addWidget(qSpinBox,r,1);
        qMoveingSpinBoxList.append(qSpinBox);

        for(int c = 2; c < 4; c++)
        {
             QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
             qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
             qDoubleSpinBox->setDecimals(1);
             qDoubleSpinBox->setMinimum(0);
             qDoubleSpinBox->setMaximum(65535.0);
             qDoubleSpinBox->setAlignment(Qt::AlignRight);
             //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_3->addWidget(qDoubleSpinBox,r,c);

             qMoveingDoubleSpinBoxList.append(qDoubleSpinBox);
        }

        for(int c = 4; c < 10; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_3->addWidget(qSpinBox,r,c);

             qMoveingSpinBoxList.append(qSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        QSpinBox * qSpinBox = new QSpinBox();
        qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
        qSpinBox->setMinimum(0);
        qSpinBox->setMaximum(65535);
        qSpinBox->setAlignment(Qt::AlignRight);
        //qSpinBox->setAccessibleName(QString::number( index++));

        ui->gridLayout_4->addWidget(qSpinBox,r,1);
        qMoveingSpinBoxList.append(qSpinBox);

        for(int c = 2; c < 4; c++)
        {
             QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
             qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
             qDoubleSpinBox->setDecimals(1);
             qDoubleSpinBox->setMinimum(0);
             qDoubleSpinBox->setMaximum(65535.0);
             qDoubleSpinBox->setAlignment(Qt::AlignRight);
             //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_4->addWidget(qDoubleSpinBox,r,c);

             qMoveingDoubleSpinBoxList.append(qDoubleSpinBox);
        }

        for(int c = 4; c < 10; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_4->addWidget(qSpinBox,r,c);

             qMoveingSpinBoxList.append(qSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        QSpinBox * qSpinBox = new QSpinBox();
        qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
        qSpinBox->setMinimum(0);
        qSpinBox->setMaximum(65535);
        qSpinBox->setAlignment(Qt::AlignRight);
        //qSpinBox->setAccessibleName(QString::number( index++));

        ui->gridLayout_5->addWidget(qSpinBox,r,1);
        qMoveingSpinBoxList.append(qSpinBox);

        for(int c = 2; c < 4; c++)
        {
             QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
             qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
             qDoubleSpinBox->setDecimals(1);
             qDoubleSpinBox->setMinimum(0);
             qDoubleSpinBox->setMaximum(65535.0);
             qDoubleSpinBox->setAlignment(Qt::AlignRight);
             //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_5->addWidget(qDoubleSpinBox,r,c);

             qMoveingDoubleSpinBoxList.append(qDoubleSpinBox);
        }

        for(int c = 4; c < 10; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_5->addWidget(qSpinBox,r,c);

             qMoveingSpinBoxList.append(qSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        QSpinBox * qSpinBox = new QSpinBox();
        qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
        qSpinBox->setMinimum(0);
        qSpinBox->setMaximum(65535);
        qSpinBox->setAlignment(Qt::AlignRight);
        //qSpinBox->setAccessibleName(QString::number( index++));

        ui->gridLayout_6->addWidget(qSpinBox,r,1);
        qMoveingSpinBoxList.append(qSpinBox);

        for(int c = 2; c < 4; c++)
        {
             QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
             qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
             qDoubleSpinBox->setDecimals(1);
             qDoubleSpinBox->setMinimum(0);
             qDoubleSpinBox->setMaximum(65535.0);
             qDoubleSpinBox->setAlignment(Qt::AlignRight);
             //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_6->addWidget(qDoubleSpinBox,r,c);

             qMoveingDoubleSpinBoxList.append(qDoubleSpinBox);
        }

        for(int c = 4; c < 10; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_6->addWidget(qSpinBox,r,c);

             qMoveingSpinBoxList.append(qSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        QSpinBox * qSpinBox = new QSpinBox();
        qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
        qSpinBox->setMinimum(0);
        qSpinBox->setMaximum(65535);
        qSpinBox->setAlignment(Qt::AlignRight);
        //qSpinBox->setAccessibleName(QString::number( index++));

        ui->gridLayout_7->addWidget(qSpinBox,r,1);
        qMoveingSpinBoxList.append(qSpinBox);

        for(int c = 2; c < 4; c++)
        {
             QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
             qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
             qDoubleSpinBox->setDecimals(1);
             qDoubleSpinBox->setMinimum(0);
             qDoubleSpinBox->setMaximum(65535.0);
             qDoubleSpinBox->setAlignment(Qt::AlignRight);
             //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_7->addWidget(qDoubleSpinBox,r,c);

             qMoveingDoubleSpinBoxList.append(qDoubleSpinBox);
        }

        for(int c = 4; c < 10; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_7->addWidget(qSpinBox,r,c);

             qMoveingSpinBoxList.append(qSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        QSpinBox * qSpinBox = new QSpinBox();
        qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
        qSpinBox->setMinimum(0);
        qSpinBox->setMaximum(65535);
        qSpinBox->setAlignment(Qt::AlignRight);
        //qSpinBox->setAccessibleName(QString::number( index++));

        ui->gridLayout_8->addWidget(qSpinBox,r,1);
        qMoveingSpinBoxList.append(qSpinBox);

        for(int c = 2; c < 4; c++)
        {
             QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
             qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
             qDoubleSpinBox->setDecimals(1);
             qDoubleSpinBox->setMinimum(0);
             qDoubleSpinBox->setMaximum(65535.0);
             qDoubleSpinBox->setAlignment(Qt::AlignRight);
             //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_8->addWidget(qDoubleSpinBox,r,c);

             qMoveingDoubleSpinBoxList.append(qDoubleSpinBox);
        }

        for(int c = 4; c < 10; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_8->addWidget(qSpinBox,r,c);

             qMoveingSpinBoxList.append(qSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        QSpinBox * qSpinBox = new QSpinBox();
        qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
        qSpinBox->setMinimum(0);
        qSpinBox->setMaximum(65535);
        qSpinBox->setAlignment(Qt::AlignRight);
        //qSpinBox->setAccessibleName(QString::number( index++));

        ui->gridLayout_9->addWidget(qSpinBox,r,1);
        qMoveingSpinBoxList.append(qSpinBox);

        for(int c = 2; c < 4; c++)
        {
             QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
             qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
             qDoubleSpinBox->setDecimals(1);
             qDoubleSpinBox->setMinimum(0);
             qDoubleSpinBox->setMaximum(65535.0);
             qDoubleSpinBox->setAlignment(Qt::AlignRight);
             //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_9->addWidget(qDoubleSpinBox,r,c);

             qMoveingDoubleSpinBoxList.append(qDoubleSpinBox);
        }

        for(int c = 4; c < 10; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_9->addWidget(qSpinBox,r,c);

             qMoveingSpinBoxList.append(qSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        QSpinBox * qSpinBox = new QSpinBox();
        qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
        qSpinBox->setMinimum(0);
        qSpinBox->setMaximum(65535);
        qSpinBox->setAlignment(Qt::AlignRight);
        //qSpinBox->setAccessibleName(QString::number( index++));

        ui->gridLayout_10->addWidget(qSpinBox,r,1);
        qMoveingSpinBoxList.append(qSpinBox);

        for(int c = 2; c < 4; c++)
        {
             QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
             qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
             qDoubleSpinBox->setDecimals(1);
             qDoubleSpinBox->setMinimum(0);
             qDoubleSpinBox->setMaximum(65535.0);
             qDoubleSpinBox->setAlignment(Qt::AlignRight);
             //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_10->addWidget(qDoubleSpinBox,r,c);

             qMoveingDoubleSpinBoxList.append(qDoubleSpinBox);
        }

        for(int c = 4; c < 10; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_10->addWidget(qSpinBox,r,c);

             qMoveingSpinBoxList.append(qSpinBox);
        }
    }

    //焊接参数
    for(int r = 1; r < 13; r++)
    {
        for(int c = 1; c < 3; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(0);
            qDoubleSpinBox->setMaximum(65535.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_13->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
        for (int c = 3; c < 5; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));
            ui->gridLayout_13->addWidget(qSpinBox,r,c);
            qWeldingSpinBoxList.append(qSpinBox);
        }
        for (int c = 5; c < 9; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(-3000.0);
            qDoubleSpinBox->setMaximum(3000.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_13->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
    }

    for(int r = 1; r < 13; r++)
    {
        for(int c = 1; c < 3; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(0);
            qDoubleSpinBox->setMaximum(65535.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_14->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
        for (int c = 3; c < 5; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));
            ui->gridLayout_14->addWidget(qSpinBox,r,c);
            qWeldingSpinBoxList.append(qSpinBox);
        }
        for (int c = 5; c < 9; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(-3000.0);
            qDoubleSpinBox->setMaximum(3000.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_14->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        for(int c = 1; c < 3; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(0);
            qDoubleSpinBox->setMaximum(65535.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_15->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
        for (int c = 3; c < 5; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));
            ui->gridLayout_15->addWidget(qSpinBox,r,c);
            qWeldingSpinBoxList.append(qSpinBox);
        }
        for (int c = 5; c < 9; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(-3000.0);
            qDoubleSpinBox->setMaximum(3000.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_15->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        for(int c = 1; c < 3; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(0);
            qDoubleSpinBox->setMaximum(65535.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_16->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
        for (int c = 3; c < 5; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));
            ui->gridLayout_16->addWidget(qSpinBox,r,c);
            qWeldingSpinBoxList.append(qSpinBox);
        }
        for (int c = 5; c < 9; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(-3000.0);
            qDoubleSpinBox->setMaximum(3000.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_16->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        for(int c = 1; c < 3; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(0);
            qDoubleSpinBox->setMaximum(65535.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_17->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
        for (int c = 3; c < 5; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));
            ui->gridLayout_17->addWidget(qSpinBox,r,c);
            qWeldingSpinBoxList.append(qSpinBox);
        }
        for (int c = 5; c < 9; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(-3000.0);
            qDoubleSpinBox->setMaximum(3000.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_17->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        for(int c = 1; c < 3; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(0);
            qDoubleSpinBox->setMaximum(65535.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_18->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
        for (int c = 3; c < 5; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));
            ui->gridLayout_18->addWidget(qSpinBox,r,c);
            qWeldingSpinBoxList.append(qSpinBox);
        }
        for (int c = 5; c < 9; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(-3000.0);
            qDoubleSpinBox->setMaximum(3000.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_18->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        for(int c = 1; c < 3; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(0);
            qDoubleSpinBox->setMaximum(65535.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_19->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
        for (int c = 3; c < 5; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));
            ui->gridLayout_19->addWidget(qSpinBox,r,c);
            qWeldingSpinBoxList.append(qSpinBox);
        }
        for (int c = 5; c < 9; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(-3000.0);
            qDoubleSpinBox->setMaximum(3000.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_19->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        for(int c = 1; c < 3; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(0);
            qDoubleSpinBox->setMaximum(65535.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_20->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
        for (int c = 3; c < 5; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));
            ui->gridLayout_20->addWidget(qSpinBox,r,c);
            qWeldingSpinBoxList.append(qSpinBox);
        }
        for (int c = 5; c < 9; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(-3000.0);
            qDoubleSpinBox->setMaximum(3000.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_20->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        for(int c = 1; c < 3; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(0);
            qDoubleSpinBox->setMaximum(65535.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_21->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
        for (int c = 3; c < 5; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));
            ui->gridLayout_21->addWidget(qSpinBox,r,c);
            qWeldingSpinBoxList.append(qSpinBox);
        }
        for (int c = 5; c < 9; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(-3000.0);
            qDoubleSpinBox->setMaximum(3000.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_21->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
    }
    for(int r = 1; r < 13; r++)
    {
        for(int c = 1; c < 3; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(0);
            qDoubleSpinBox->setMaximum(65535.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_22->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
        for (int c = 3; c < 5; c++)
        {
            QSpinBox * qSpinBox = new QSpinBox();
            qSpinBox->setButtonSymbols(QSpinBox::NoButtons);
            qSpinBox->setMinimum(0);
            qSpinBox->setMaximum(65535);
            qSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));
            ui->gridLayout_22->addWidget(qSpinBox,r,c);
            qWeldingSpinBoxList.append(qSpinBox);
        }
        for (int c = 5; c < 9; c++)
        {
            QDoubleSpinBox * qDoubleSpinBox = new QDoubleSpinBox();
            qDoubleSpinBox->setButtonSymbols(QDoubleSpinBox::NoButtons);
            qDoubleSpinBox->setDecimals(1);
            qDoubleSpinBox->setMinimum(-3000.0);
            qDoubleSpinBox->setMaximum(3000.0);
            qDoubleSpinBox->setAlignment(Qt::AlignRight);
            //qSpinBox->setAccessibleName(QString::number( index++));

             ui->gridLayout_22->addWidget(qDoubleSpinBox,r,c);
             qWeldingDoubleSpinBoxList.append(qDoubleSpinBox);
        }
    }


    GetWidgetValueFormBinFile();
    GetSwitchData();
    GetPublicData();

    connect(this->ui->radioButton,SIGNAL(toggled(bool)),this,SLOT(L1LeftRight()));
    connect(this->ui->radioButton_2,SIGNAL(toggled(bool)),this,SLOT(L1UpDown()));
    connect(this->ui->radioButton_3,SIGNAL(toggled(bool)),this,SLOT(L2LeftRight()));
    connect(this->ui->radioButton_4,SIGNAL(toggled(bool)),this,SLOT(L2UpDown()));
    connect(this->ui->radioButton_5,SIGNAL(toggled(bool)),this,SLOT(L3LeftRight()));
    connect(this->ui->radioButton_6,SIGNAL(toggled(bool)),this,SLOT(L3UpDown()));
    connect(this->ui->radioButton_7,SIGNAL(toggled(bool)),this,SLOT(L4LeftRight()));
    connect(this->ui->radioButton_8,SIGNAL(toggled(bool)),this,SLOT(L4UpDown()));
    connect(this->ui->radioButton_9,SIGNAL(toggled(bool)),this,SLOT(L5LeftRight()));
    connect(this->ui->radioButton_10,SIGNAL(toggled(bool)),this,SLOT(L5UpDown()));
    connect(this->ui->radioButton_11,SIGNAL(toggled(bool)),this,SLOT(L6LeftRight()));
    connect(this->ui->radioButton_12,SIGNAL(toggled(bool)),this,SLOT(L6UpDown()));
    connect(this->ui->radioButton_13,SIGNAL(toggled(bool)),this,SLOT(L7LeftRight()));
    connect(this->ui->radioButton_14,SIGNAL(toggled(bool)),this,SLOT(L7UpDown()));
    connect(this->ui->radioButton_15,SIGNAL(toggled(bool)),this,SLOT(L8LeftRight()));
    connect(this->ui->radioButton_16,SIGNAL(toggled(bool)),this,SLOT(L8UpDown()));
    connect(this->ui->radioButton_17,SIGNAL(toggled(bool)),this,SLOT(C1LeftRight()));
    connect(this->ui->radioButton_18,SIGNAL(toggled(bool)),this,SLOT(C1UpDown()));
    connect(this->ui->radioButton_19,SIGNAL(toggled(bool)),this,SLOT(C2LeftRight()));
    connect(this->ui->radioButton_20,SIGNAL(toggled(bool)),this,SLOT(C2UpDown()));

    connect(this->ui->lr20,SIGNAL(toggled(bool)),this,SLOT(L1LeftRight2()));
    connect(this->ui->ud20,SIGNAL(toggled(bool)),this,SLOT(L1UpDown2()));
    connect(this->ui->lr21,SIGNAL(toggled(bool)),this,SLOT(L2LeftRight2()));
    connect(this->ui->ud21,SIGNAL(toggled(bool)),this,SLOT(L2UpDown2()));
    connect(this->ui->lr22,SIGNAL(toggled(bool)),this,SLOT(L3LeftRight2()));
    connect(this->ui->ud22,SIGNAL(toggled(bool)),this,SLOT(L3UpDown2()));
    connect(this->ui->lr23,SIGNAL(toggled(bool)),this,SLOT(L4LeftRight2()));
    connect(this->ui->ud23,SIGNAL(toggled(bool)),this,SLOT(L4UpDown2()));
    connect(this->ui->lr24,SIGNAL(toggled(bool)),this,SLOT(L5LeftRight2()));
    connect(this->ui->ud24,SIGNAL(toggled(bool)),this,SLOT(L5UpDown2()));
    connect(this->ui->lr25,SIGNAL(toggled(bool)),this,SLOT(L6LeftRight2()));
    connect(this->ui->ud25,SIGNAL(toggled(bool)),this,SLOT(L6UpDown2()));
    connect(this->ui->lr26,SIGNAL(toggled(bool)),this,SLOT(L7LeftRight2()));
    connect(this->ui->ud26,SIGNAL(toggled(bool)),this,SLOT(L7UpDown2()));
    connect(this->ui->lr27,SIGNAL(toggled(bool)),this,SLOT(L8LeftRight2()));
    connect(this->ui->ud27,SIGNAL(toggled(bool)),this,SLOT(L8UpDown2()));
    connect(this->ui->lr28,SIGNAL(toggled(bool)),this,SLOT(C1LeftRight2()));
    connect(this->ui->ud28,SIGNAL(toggled(bool)),this,SLOT(C1UpDown2()));
    connect(this->ui->lr29,SIGNAL(toggled(bool)),this,SLOT(C2LeftRight2()));
    connect(this->ui->ud29,SIGNAL(toggled(bool)),this,SLOT(C2UpDown2()));

    connect(this->ui->pushButton,SIGNAL(clicked()),this,SLOT(send()));
    //connect(this,SIGNAL(CanSendData(QByteArray)),mCanBus,SLOT(send(QByteArray)));
    angle = 0;
    Layer = 0;

}

Widget::~Widget()
{
    serialRs232->close();
    serialRs485->close();

    //mCanBus->stop();
    mCanBus->quit();
    mCanBus->wait();
    delete mCanBus;

    delete ui;


}

//各层方向开关处理事件
void Widget::L1LeftRight()
{
    if (ui->radioButton->isChecked())
        {
            Leftright[0] = 0x01;

        }
        else
        {
            Leftright[0] = 0x00;
        }

}
void Widget::L1LeftRight2()
{
    if (ui->lr20->isChecked())
        {
            Leftright[1] = 0x01;

        }
        else
        {
            Leftright[1] = 0x00;
        }

}
void Widget::L1UpDown()
{
    if (ui->radioButton_2->isChecked())
        {
            Updown[0] = 0x01;
        }
        else
        {
            Updown[0] = 0x00;
        }

}
void Widget::L1UpDown2()
{
    if (ui->ud20->isChecked())
        {
            Updown[1] = 0x01;
        }
        else
        {
            Updown[1] = 0x00;
        }

}
void Widget::L2LeftRight()
{
    if (ui->radioButton_3->isChecked())
        {
            Leftright[2] = 0x01;
        }
        else
        {
            Leftright[2] = 0x00;
        }

}
void Widget::L2LeftRight2()
{
    if (ui->lr21->isChecked())
        {
            Leftright[3] = 0x01;
        }
        else
        {
            Leftright[3] = 0x00;
        }

}
void Widget::L2UpDown()
{
    if (ui->radioButton_4->isChecked())
        {
            Updown[2] = 0x01;
        }
        else
        {
            Updown[2] = 0x00;
        }

}
void Widget::L2UpDown2()
{
    if (ui->ud21->isChecked())
        {
            Updown[3] = 0x01;
        }
        else
        {
            Updown[3] = 0x00;
        }

}
void Widget::L3LeftRight()
{
    if (ui->radioButton_5->isChecked())
        {
            Leftright[4] = 0x01;
        }
        else
        {
            Leftright[4] = 0x00;
        }

}
void Widget::L3LeftRight2()
{
    if (ui->lr22->isChecked())
        {
            Leftright[5] = 0x01;
        }
        else
        {
            Leftright[5] = 0x00;
        }

}
void Widget::L3UpDown()
{
    if (ui->radioButton_6->isChecked())
        {
            Updown[4] = 0x01;
        }
        else
        {
            Updown[4] = 0x00;
        }

}
void Widget::L3UpDown2()
{
    if (ui->ud22->isChecked())
        {
            Updown[5] = 0x01;
        }
        else
        {
            Updown[5] = 0x00;
        }

}
void Widget::L4LeftRight()
{
    if (ui->radioButton_7->isChecked())
        {
            Leftright[6] = 0x01;
        }
        else
        {
            Leftright[6] = 0x00;
        }

}
void Widget::L4LeftRight2()
{
    if (ui->ud23->isChecked())
        {
            Leftright[7] = 0x01;
        }
        else
        {
            Leftright[7] = 0x00;
        }

}
void Widget::L4UpDown()
{
    if (ui->radioButton_8->isChecked())
        {
            Updown[6] = 0x01;
        }
        else
        {
            Updown[6] = 0x00;
        }

}
void Widget::L4UpDown2()
{
    if (ui->ud23->isChecked())
        {
            Updown[7] = 0x01;
        }
        else
        {
            Updown[7] = 0x00;
        }

}
void Widget::L5LeftRight()
{
    if (ui->radioButton_9->isChecked())
        {
            Leftright[8] = 0x01;
        }
        else
        {
            Leftright[8] = 0x00;
        }

}
void Widget::L5LeftRight2()
{
    if (ui->lr24->isChecked())
        {
            Leftright[9] = 0x01;
        }
        else
        {
            Leftright[9] = 0x00;
        }

}
void Widget::L5UpDown()
{
    if (ui->radioButton_10->isChecked())
        {
            Updown[8] = 0x01;
        }
        else
        {
            Updown[8] = 0x00;
        }

}
void Widget::L5UpDown2()
{
    if (ui->ud24->isChecked())
        {
            Updown[9] = 0x01;
        }
        else
        {
            Updown[9] = 0x00;
        }

}
void Widget::L6LeftRight()
{
    if (ui->radioButton_11->isChecked())
        {
            Leftright[10] = 0x01;
        }
        else
        {
            Leftright[10] = 0x00;
        }

}
void Widget::L6LeftRight2()
{
    if (ui->lr25->isChecked())
        {
            Leftright[11] = 0x01;
        }
        else
        {
            Leftright[11] = 0x00;
        }

}
void Widget::L6UpDown()
{
    if (ui->radioButton_12->isChecked())
        {
            Updown[10] = 0x01;
        }
        else
        {
            Updown[10] = 0x00;
        }

}
void Widget::L6UpDown2()
{
    if (ui->ud25->isChecked())
        {
            Updown[11] = 0x01;
        }
        else
        {
            Updown[11] = 0x00;
        }

}
void Widget::L7LeftRight()
{
    if (ui->radioButton_13->isChecked())
        {
            Leftright[12] = 0x01;
        }
        else
        {
            Leftright[12] = 0x00;
        }

}
void Widget::L7LeftRight2()
{
    if (ui->lr26->isChecked())
        {
            Leftright[13] = 0x01;
        }
        else
        {
            Leftright[13] = 0x00;
        }

}
void Widget::L7UpDown()
{
    if (ui->radioButton_14->isChecked())
        {
            Updown[12] = 0x01;
        }
        else
        {
            Updown[12] = 0x00;
        }

}
void Widget::L7UpDown2()
{
    if (ui->ud26->isChecked())
        {
            Updown[13] = 0x01;
        }
        else
        {
            Updown[13] = 0x00;
        }

}
void Widget::L8LeftRight()
{
    if (ui->radioButton_15->isChecked())
        {
            Leftright[14] = 0x01;
        }
        else
        {
            Leftright[14] = 0x00;
        }

}
void Widget::L8LeftRight2()
{
    if (ui->lr27->isChecked())
        {
            Leftright[15] = 0x01;
        }
        else
        {
            Leftright[15] = 0x00;
        }

}
void Widget::L8UpDown()
{
    if (ui->radioButton_16->isChecked())
        {
            Updown[14] = 0x01;
        }
        else
        {
            Updown[14] = 0x00;
        }

}
void Widget::L8UpDown2()
{
    if (ui->ud27->isChecked())
        {
            Updown[15] = 0x01;
        }
        else
        {
            Updown[15] = 0x00;
        }

}
void Widget::C1LeftRight()
{
    if (ui->radioButton_17->isChecked())
        {
            Leftright[16] = 0x01;
        }
        else
        {
            Leftright[16] = 0x00;
        }

}
void Widget::C1LeftRight2()
{
    if (ui->lr28->isChecked())
        {
            Leftright[17] = 0x01;
        }
        else
        {
            Leftright[17] = 0x00;
        }

}
void Widget::C1UpDown()
{
    if (ui->radioButton_18->isChecked())
        {
            Updown[16] = 0x01;
        }
        else
        {
            Updown[16] = 0x00;
        }

}
void Widget::C1UpDown2()
{
    if (ui->ud28->isChecked())
        {
            Updown[17] = 0x01;
        }
        else
        {
            Updown[17] = 0x00;
        }

}
void Widget::C2LeftRight()
{
    if (ui->radioButton_19->isChecked())
        {
            Leftright[18] = 0x01;
        }
        else
        {
            Leftright[18] = 0x00;
        }

}
void Widget::C2LeftRight2()
{
    if (ui->lr29->isChecked())
        {
            Leftright[19] = 0x01;
        }
        else
        {
            Leftright[19] = 0x00;
        }

}
void Widget::C2UpDown()
{
    if (ui->radioButton_20->isChecked())
        {
            Updown[18] = 0x01;
        }
        else
        {
            Updown[18] = 0x00;
        }

}
void Widget::C2UpDown2()
{
    if (ui->ud29->isChecked())
        {
            Updown[19] = 0x01;
        }
        else
        {
            Updown[19] = 0x00;
        }

}
//串口初始化
void Widget::initSeialPort(){

    //设置串口名
    serialRs232->setPortName("ttyS3");
    //设置波特率
    serialRs232->setBaudRate(QSerialPort::Baud115200);
    //设置数据位数
    serialRs232->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serialRs232->setParity(QSerialPort::NoParity);
    //设置停止位
    serialRs232->setStopBits(QSerialPort::OneStop);
    //设置流控制
    serialRs232->setFlowControl(QSerialPort::NoFlowControl);
    //打开串口
    serialRs232->open(QIODevice::ReadWrite);
    connect(serialRs232,SIGNAL(readyRead()),this,SLOT(receiveinfo()));

    //设置串口名
    serialRs485->setPortName("ttyS4");
    //设置波特率
    serialRs485->setBaudRate(QSerialPort::Baud115200);
    //设置数据位数
    serialRs485->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serialRs485->setParity(QSerialPort::NoParity);
    //设置停止位
    serialRs485->setStopBits(QSerialPort::OneStop);
    //设置流控制
    serialRs485->setFlowControl(QSerialPort::NoFlowControl);
    //打开串口
    serialRs485->open(QIODevice::ReadWrite);



}
//保存表格数据
void Widget::GetDataFormWidget()
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    MovingData.resize(840*2);
    MovingFloatData.resize(240*2);
    WeldingData.resize(240*2);
    WeldingFloatData.resize(720*2);

    foreach(QSpinBox * qspinbox ,qMoveingSpinBoxList )
    {
        int v = qspinbox->value();
        MovingData[a++] =  (uchar)(0x000000ff & v);
        MovingData[a++] =  (uchar)((0x0000ff00&v)>>8);
    }
    foreach(QDoubleSpinBox * qdoublespinbox ,qMoveingDoubleSpinBoxList )
    {

        float f = qdoublespinbox->value();
        int v = f*10;
        MovingFloatData[b++] =  (uchar)(0x000000ff & v);
        MovingFloatData[b++] =  (uchar)((0x0000ff00&v)>>8);
    }

    foreach(QSpinBox * qspinbox ,qWeldingSpinBoxList )
    {
        int v = qspinbox->value();
        WeldingData[c++] =  (uchar)(0x000000ff & v);
        WeldingData[c++] =  (uchar)((0x0000ff00&v)>>8);
    }
    foreach(QDoubleSpinBox * qdoublespinbox ,qWeldingDoubleSpinBoxList )
    {

        float f = qdoublespinbox->value();
        int v = f*10;
        WeldingFloatData[d++] =  (uchar)(0x000000ff & v);
        WeldingFloatData[d++] =  (uchar)((0x0000ff00&v)>>8);
    }

    //保存为二维数组
    for (int i = 0; i < 120 ; i++)
    {
        for (int j = 0; j < 7*2; j++)
        {
            mData[i][j] = MovingData[i*7*2 + j];
        }
    }
    for (int i = 0; i < 120 ; i++)
    {
        for (int j = 0; j < 2*2; j++)
        {
            mFloatData[i][j] = MovingFloatData[i*2*2 + j];
        }
    }

    for (int i = 0; i < 120 ; i++)
    {   for (int j = 0; j < 2*2; j++)
        {
            wData[i][j] = WeldingData[i*2*2 + j];
        }
    }

    for (int i = 0; i < 120 ; i++)
    {   for (int j = 0; j < 6*2; j++)
        {
            wFloatData[i][j] = WeldingFloatData[i*6*2 + j];
        }
    }


    //保存数组到二进制文件
    QFile movingdataf("/home/root/savefile/movingdata.txt");      //定义一个文件
    movingdataf.open(QIODevice::WriteOnly);   //打开文件
    movingdataf.write(MovingData);
    movingdataf.close();
    QFile movingfloatdataf("/home/root/savefile/movingfloatdata.txt");      //定义一个文件
    movingfloatdataf.open(QIODevice::WriteOnly);   //打开文件
    movingfloatdataf.write(MovingFloatData);
    movingfloatdataf.close();
    QFile weldingdataf("/home/root/savefile/weldingdata.txt");      //定义一个文件
    weldingdataf.open(QIODevice::WriteOnly);   //打开文件
    weldingdataf.write(WeldingData);
    weldingdataf.close();
    QFile weldingfloatdataf("/home/root/savefile/weldingfloatdata.txt");      //定义一个文件
    weldingfloatdataf.open(QIODevice::WriteOnly);   //打开文件
    weldingfloatdataf.write(WeldingFloatData);
    weldingfloatdataf.close();
}

void Widget::GetWidgetValueFormBinFile()
{
    QFile movingdataf("/home/root/savefile/movingdata.txt");      //定义一个文件
    movingdataf.open(QIODevice::ReadOnly);   //打开文件
    MovingData = movingdataf.readAll();
    movingdataf.close();
    QFile movingfloatdataf("/home/root/savefile/movingfloatdata.txt");      //定义一个文件
    movingfloatdataf.open(QIODevice::ReadOnly);   //打开文件
    MovingFloatData = movingfloatdataf.readAll();
    movingfloatdataf.close();
    QFile weldingdataf("/home/root/savefile/weldingdata.txt");      //定义一个文件
    weldingdataf.open(QIODevice::ReadOnly);   //打开文件
    WeldingData = weldingdataf.readAll();
    weldingdataf.close();
    QFile weldingfloatdataf("/home/root/savefile/weldingfloatdata.txt");      //定义一个文件
    weldingfloatdataf.open(QIODevice::ReadOnly);   //打开文件
    WeldingFloatData = weldingfloatdataf.readAll();
    weldingfloatdataf.close();

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    for(int i=0;i<840;i++)  //读取数据
    {
        qMoveingSpinBoxList[i]->setValue(MovingData[a++] + MovingData[a++] * 256 );
    }

    for(int i=0;i<240;i++)  //读取数据
    {
        short result[240];
        float tr[240];
        float value[240];
        result[i] = (short)( (0x00ff & MovingFloatData[b++]) | ((0x00ff & MovingFloatData[b++])<<8) );
        tr[i] = (float)result[i];
        value[i] = tr[i]/10;
        qMoveingDoubleSpinBoxList[i]->setValue(value[i]);
    }
    for(int i=0;i<240;i++)  //读取数据
    {
        qWeldingSpinBoxList[i]->setValue(WeldingData[c++] + WeldingData[c++] * 256 );
    }

    for(int i=0;i<720;i++)  //读取数据
    {
        short result[720];
        float tr[720];
        float value[720];
        result[i] = (short)( (0x00ff & WeldingFloatData[d++]) | ((0x00ff & WeldingFloatData[d++])<<8) );
        tr[i] = (float)result[i];
        value[i] = tr[i]/10;
        qWeldingDoubleSpinBoxList[i]->setValue(value[i]);
    }
}

void Widget::TransCantoSerial(CANFRAME* frame)
{
    if (frame->can_id == 0x40)
    {
        //起弧
        if(frame->data[0] == 0x15){
            welding(angle);
            ui->statusline->setText("welding");
            QByteArray sfire;
            sfire[0] = HEAD_1;
            sfire[1] = HEAD_2;
            sfire[2] = SINGLEWELDING;
            sfire.append(0X0D);
            sfire.append(0x0A);
            serialRs485->write(sfire);
        }
        else if(frame->data[0] == 0x16){
            QByteArray dfire;
            dfire[0] = HEAD_1;
            dfire[1] = HEAD_2;
            dfire[2] = DOUBLEWELDING;
            dfire.append(0X0D);
            dfire.append(0x0A);
            serialRs485->write(dfire);
        }
        else if(frame->data[0] == 0x17){
            QByteArray stop;
            ui->statusline->setText("stop");
            stop[0] = HEAD_1;
            stop[1] = HEAD_2;
            stop[2] = STOP;
            stop.append(0X0D);
            stop.append(0x0A);
            serialRs485->write(stop);

        }
    }
    else
    {
        QByteArray package;
        package[0] = HEAD_1;
        package[1] = HEAD_2;
        package[2] = frame->data[0];
        package.append(0x0D);
        package.append(0x0A);
        serialRs485->write(package);
    }

    /*//置位
    if(frame->data[0] == 0x00 && frame->can_id != 0x40){
        qDebug("def");
        QByteArray def;
        def[0] = HEAD_1;
        def[1] = HEAD_2;
        def[2] = DEFAULT;
        def.append(0X0D);
        def.append(0x0A);
        serialRs232->write(def);
    }
    //1#方向控制
    if(frame->data[0] == 0x01){
        QByteArray up;
        up[0] = HEAD_1;
        up[1] = HEAD_2;
        up[2] = UP_1;
        up.append(0X0D);
        up.append(0x0A);
        serialRs232->write(up);
        qDebug()<<"up";
    }

    if(frame->data[0] == 0x02){
        QByteArray down;
        down[0] = HEAD_1;
        down[1] = HEAD_2;
        down[2] = DOWN_1;
        down.append(0X0D);
        down.append(0x0A);
        serialRs232->write(down);
        qDebug("down");
    }

    if(frame->data[0] == 0x03){
        QByteArray left;
        left[0] = HEAD_1;
        left[1] = HEAD_2;
        left[2] = LEFT_1;
        left.append(0X0D);
        left.append(0x0A);
        serialRs232->write(left);
        qDebug("left");

    }

    if(frame->data[0] == 0x04){
        QByteArray right;
        right[0] = HEAD_1;
        right[1] = HEAD_2;
        right[2] = RIGHT_1;
        right.append(0X0D);
        right.append(0x0A);
        serialRs232->write(right);
        qDebug("right");

    }


    //增减幅
    if(frame->data[0] == 0x05){
        QByteArray rise;
        rise[0] = HEAD_1;
        rise[1] = HEAD_2;
        rise[2] = RISE_1;
        rise.append(0X0D);
        rise.append(0x0A);
        serialRs232->write(rise);

    }

    if(frame->data[0] == 0x06){
        QByteArray fall;
        fall[0] = HEAD_1;
        fall[1] = HEAD_2;
        fall[2] = FALL_1;
        fall.append(0X0D);
        fall.append(0x0A);
        serialRs232->write(fall);

    }

    //2#方向控制
    if(frame->data[0] == 0x09){
        QByteArray up;
        up[0] = HEAD_1;
        up[1] = HEAD_2;
        up[2] = UP_2;
        up.append(0X0D);
        up.append(0x0A);
        serialRs485->write(up);
        qDebug()<<"up";
    }

    if(frame->data[0] == 0x0A){
        QByteArray down;
        down[0] = HEAD_1;
        down[1] = HEAD_2;
        down[2] = DOWN_2;
        down.append(0X0D);
        down.append(0x0A);
        serialRs485->write(down);
        qDebug("down");
    }

    if(frame->data[0] == 0x0B){
        QByteArray left;
        left[0] = HEAD_1;
        left[1] = HEAD_2;
        left[2] = LEFT_2;
        left.append(0X0D);
        left.append(0x0A);
        serialRs485->write(left);
        qDebug("left");

    }

    if(frame->data[0] == 0x0C){
        QByteArray right;
        right[0] = HEAD_1;
        right[1] = HEAD_2;
        right[2] = RIGHT_2;
        right.append(0X0D);
        right.append(0x0A);
        serialRs485->write(right);
        qDebug("right");

    }


    //增减幅
    if(frame->data[0] == 0x0D){
        QByteArray rise;
        rise[0] = HEAD_1;
        rise[1] = HEAD_2;
        rise[2] = RISE_2;
        rise.append(0X0D);
        rise.append(0x0A);
        serialRs485->write(rise);

    }

    if(frame->data[0] == 0x0E){
        QByteArray fall;
        fall[0] = HEAD_1;
        fall[1] = HEAD_2;
        fall[2] = FALL_2;
        fall.append(0X0D);
        fall.append(0x0A);
        serialRs485->write(fall);

    }

    if(frame->data[0] == 0x17){
        QByteArray stop;
        stop[0] = HEAD_1;
        stop[1] = HEAD_2;
        stop[2] = STOP;
        stop.append(0X0D);
        stop.append(0x0A);
        serialRs232->write(stop);

    }

    //前进
    if(frame->data[0] == 0x11){
        QByteArray moveF;
        moveF[0] = HEAD_1;
        moveF[1] = HEAD_2;
        moveF[2] = MOVEFORWARD;
        moveF.append(0X0D);
        moveF.append(0x0A);
        serialRs232->write(moveF);

    }
    //后退
    if(frame->data[0] == 0x12){
        QByteArray moveB;
        moveB[0] = HEAD_1;
        moveB[1] = HEAD_2;
        moveB[2] = MOVEBACK;
        moveB.append(0X0D);
        moveB.append(0x0A);
        serialRs232->write(moveB);

    }


    //起弧
    if(frame->data[0] == 0x15){
        welding(0);
        QByteArray sfire;
        sfire[0] = HEAD_1;
        sfire[1] = HEAD_2;
        sfire[2] = SINGLEWELDING;
        sfire.append(0X0D);
        sfire.append(0x0A);
        serialRs232->write(sfire);
    }
    if(frame->data[0] == 0x16){
        QByteArray dfire;
        dfire[0] = HEAD_1;
        dfire[1] = HEAD_2;
        dfire[2] = DOUBLEWELDING;
        dfire.append(0X0D);
        dfire.append(0x0A);
        serialRs485->write(dfire);
    }*/

    //
    /*
    if(frame->data[0] == 0x80)
    {
        Layer = 0;
    }
    if(frame->data[0] == 0x81)
    {
        Layer = 1;
    }
    if(frame->data[0] == 0x82)
    {
        Layer = 2;
    }
    if(frame->data[0] == 0x83)
    {
        Layer = 3;
    }
    if(frame->data[0] == 0x84)
    {
        Layer = 4;
    }
    if(frame->data[0] == 0x85)
    {
        Layer = 5;
    }
    if(frame->data[0] == 0x86)
    {
        Layer = 6;
    }
    if(frame->data[0] == 0x87)
    {
        Layer = 7;
    }
    if(frame->data[0] == 0x88)
    {
        Layer = 8;
    }
    if(frame->data[0] == 0x89)
    {
        Layer = 9;
    }*/


}

int Widget::welding(float a)
{
    int positionnum;
    if(((a >= clock0P) & (a < clock0p5P)) || ((a >= clock11p5P) & (a < clock12P)))
    {
        positionnum = 0;
        ui->lineEdit_7->setText("positionnum = 0");
        QByteArray data;
        int value_A = (wFloatData[0][0] + wFloatData[0][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[0][0] + wData[0][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if(((a >= clock0p5P) & (a < clock1P)) || ((a >= clock11P) & (a < clock11p5P)))
    {
        qDebug("positionnum = 1");
        ui->lineEdit_7->setText("positionnum = 1");
        positionnum = 1;
        QByteArray data;
        int value_A = (wFloatData[1][0] + wFloatData[1][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[1][0] + wData[1][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if(((a >= clock1P) & (a < clock1p5P)) || ((a >= clock10p5P) & (a < clock11P)))
    {
        qDebug("positionnum = 2");
        ui->lineEdit_7->setText("positionnum = 2");
        positionnum = 2;
        QByteArray data;
        int value_A = (wFloatData[2][0] + wFloatData[2][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[2][0] + wData[2][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if(((a >= clock1p5P) & (a < clock2P)) || ((a >= clock10P) & (a < clock10p5P)))
    {
        positionnum = 3;
        ui->lineEdit_7->setText("positionnum = 3");
        QByteArray data;
        int value_A = (wFloatData[3][0] + wFloatData[3][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[3][0] + wData[3][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if(((a >= clock2P) & (a < clock2p5P)) || ((a >= clock9p5P) & (a < clock10P)))
    {
        positionnum = 4;
        ui->lineEdit_7->setText("positionnum = 4");
        QByteArray data;
        int value_A = (wFloatData[4][0] + wFloatData[4][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[4][0] + wData[4][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if(((a >= clock2p5P) & (a < clock3P)) || ((a >= clock9P) & (a < clock9p5P)))
    {
        positionnum = 5;
        ui->lineEdit_7->setText("positionnum = 5");
        QByteArray data;
        int value_A = (wFloatData[5][0] + wFloatData[5][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[5][0] + wData[5][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if(((a >= clock3P) & (a < clock3p5P)) || ((a >= clock8p5P) & (a < clock9P)))
    {
        positionnum = 6;
        ui->lineEdit_7->setText("positionnum = 6");
        QByteArray data;
        int value_A = (wFloatData[6][0] + wFloatData[6][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[6][0] + wData[6][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if(((a >= clock3p5P) & (a < clock4P)) || ((a >= clock8P) & (a < clock8p5P)))
    {
        positionnum = 7;
        ui->lineEdit_7->setText("positionnum = 7");
        QByteArray data;
        int value_A = (wFloatData[7][0] + wFloatData[7][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[7][0] + wData[7][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if(((a >= clock4P) & (a < clock4p5P)) || ((a >= clock7p5P) & (a < clock8P)))
    {
        positionnum = 8;
        ui->lineEdit_7->setText("positionnum = 8");
        QByteArray data;
        int value_A = (wFloatData[8][0] + wFloatData[8][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[8][0] + wData[8][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if(((a >= clock4p5P) & (a < clock5P)) || ((a >= clock7P) & (a < clock7p5P)))
    {
        positionnum = 9;
        ui->lineEdit_7->setText("positionnum = 9");
        QByteArray data;
        int value_A = (wFloatData[9][0] + wFloatData[9][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[9][0] + wData[9][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if(((a >= clock5P) & (a < clock5p5P)) ||((a >= clock6p5P) & (a < clock7P)))
    {
        positionnum = 10;
        ui->lineEdit_7->setText("positionnum = 10");
        QByteArray data;
        int value_A = (wFloatData[10][0] + wFloatData[10][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[10][0] + wData[10][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else if((a >= clock5p5P) & (a < clock6p5P))
    {
        positionnum = 11;
        ui->lineEdit_7->setText("positionnum = 11");
        QByteArray data;
        int value_A = (wFloatData[11][0] + wFloatData[11][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[11][0] + wData[11][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    else
    {
        positionnum = 11;
        QByteArray data;
        int value_A = (wFloatData[11][0] + wFloatData[11][1] * 256);
        int result_A = value_A*(65535/220);
        data[0] =  (uchar)(0x000000ff & result_A);
        data[1] =  (uchar)((0x0000ff00&result_A)>>8);

        int value_V = (wData[11][0] + wData[11][1] * 256);
        int result_V = value_V*(65535/50);
        data[2] =  (uchar)(0x000000ff & result_V);
        data[3] =  (uchar)((0x0000ff00&result_V)>>8);

        mCanBus->send(data);
    }
    return positionnum;

}

//保存跟踪开关数据
void Widget::SaveSwitchData()
{
    QFile f("/home/root/savefile/Switchlr.txt");      //定义一个文件
    f.open(QIODevice::WriteOnly);   //打开文件
    f.write(Leftright);
    f.close();

    QFile w("/home/root/savefile/Switchud.txt");
    w.open(QIODevice::WriteOnly);   //打开文件
    w.write(Updown);
    w.close();
}
//界面跟踪开关响应
void Widget::GetSwitchData()
{
    QFile f("/home/root/savefile/Switchlr.txt");      //定义一个文件
    f.open(QIODevice::ReadOnly);   //打开文件
    Leftright = f.readAll();
    f.close();

    QFile w("/home/root/savefile/Switchud.txt");
    w.open(QIODevice::ReadOnly);   //打开文件
    Updown = w.readAll();
    w.close();

    if (Leftright[0] == 01){
        this->ui->radioButton->setChecked(true);
    }
    if (Leftright[1] == 01){
        this->ui->lr20->setChecked(true);
    }
    if (Leftright[2] == 01){
        this->ui->radioButton_3->setChecked(true);
    }
    if (Leftright[3] == 01){
        this->ui->lr21->setChecked(true);
    }
    if (Leftright[4] == 01){
        this->ui->radioButton_5->setChecked(true);
    }
    if (Leftright[5] == 01){
        this->ui->lr22->setChecked(true);
    }
    if (Leftright[6] == 01){
        this->ui->radioButton_7->setChecked(true);
    }
    if (Leftright[7] == 01){
        this->ui->lr23->setChecked(true);
    }
    if (Leftright[8] == 01){
        this->ui->radioButton_9->setChecked(true);
    }
    if (Leftright[9] == 01){
        this->ui->lr24->setChecked(true);
    }
    if (Leftright[10] == 01){
        this->ui->radioButton_11->setChecked(true);
    }
    if (Leftright[11] == 01){
        this->ui->lr25->setChecked(true);
    }
    if (Leftright[12] == 01){
        this->ui->radioButton_13->setChecked(true);
    }
    if (Leftright[13] == 01){
        this->ui->lr26->setChecked(true);
    }
    if (Leftright[14] == 01){
        this->ui->radioButton_15->setChecked(true);
    }
    if (Leftright[15] == 01){
        this->ui->lr27->setChecked(true);
    }
    if (Leftright[16] == 01){
        this->ui->radioButton_17->setChecked(true);
    }
    if (Leftright[17] == 01){
        this->ui->lr28->setChecked(true);
    }
    if (Leftright[18] == 01){
        this->ui->radioButton_19->setChecked(true);
    }
    if (Leftright[19] == 01){
        this->ui->lr29->setChecked(true);
    }

    if (Leftright[0] == 00){
        this->ui->radioButton->setChecked(false);
    }
    if (Leftright[1] == 00){
        this->ui->lr20->setChecked(false);
    }
    if (Leftright[2] == 00){
        this->ui->radioButton_3->setChecked(false);
    }
    if (Leftright[3] == 00){
        this->ui->lr21->setChecked(false);
    }
    if (Leftright[4] == 00){
        this->ui->radioButton_5->setChecked(false);
    }
    if (Leftright[5] == 00){
        this->ui->lr22->setChecked(false);
    }
    if (Leftright[6] == 00){
        this->ui->radioButton_7->setChecked(false);
    }
    if (Leftright[7] == 00){
        this->ui->lr23->setChecked(false);
    }
    if (Leftright[8] == 00){
        this->ui->radioButton_9->setChecked(false);
    }
    if (Leftright[9] == 00){
        this->ui->lr24->setChecked(false);
    }
    if (Leftright[10] == 00){
        this->ui->radioButton_11->setChecked(false);
    }
    if (Leftright[11] == 00){
        this->ui->lr25->setChecked(false);
    }
    if (Leftright[12] == 00){
        this->ui->radioButton_13->setChecked(false);
    }
    if (Leftright[13] == 00){
        this->ui->lr26->setChecked(false);
    }
    if (Leftright[14] == 00){
        this->ui->radioButton_15->setChecked(false);
    }
    if (Leftright[15] == 00){
        this->ui->lr27->setChecked(false);
    }
    if (Leftright[16] == 00){
        this->ui->radioButton_17->setChecked(false);
    }
    if (Leftright[17] == 00){
        this->ui->lr28->setChecked(false);
    }
    if (Leftright[18] == 00){
        this->ui->radioButton_19->setChecked(false);
    }
    if (Leftright[19] == 00){
        this->ui->lr29->setChecked(false);
    }

    if (Updown[0] == 01){
        this->ui->radioButton_2->setChecked(true);
    }
    if (Updown[1] == 01){
        this->ui->ud20->setChecked(true);
    }
    if (Updown[2] == 01){
        this->ui->radioButton_4->setChecked(true);
    }
    if (Updown[3] == 01){
        this->ui->ud21->setChecked(true);
    }
    if (Updown[4] == 01){
        this->ui->radioButton_6->setChecked(true);
    }
    if (Updown[5] == 01){
        this->ui->ud22->setChecked(true);
    }
    if (Updown[6] == 01){
        this->ui->radioButton_8->setChecked(true);
    }
    if (Updown[7] == 01){
        this->ui->ud23->setChecked(true);
    }
    if (Updown[8] == 01){
        this->ui->radioButton_10->setChecked(true);
    }
    if (Updown[9] == 01){
        this->ui->ud24->setChecked(true);
    }
    if (Updown[10] == 01){
        this->ui->radioButton_12->setChecked(true);
    }
    if (Updown[11] == 01){
        this->ui->ud25->setChecked(true);
    }
    if (Updown[12] == 01){
        this->ui->radioButton_14->setChecked(true);
    }
    if (Updown[13] == 01){
        this->ui->ud26->setChecked(true);
    }
    if (Updown[14] == 01){
        this->ui->radioButton_16->setChecked(true);
    }
    if (Updown[15] == 01){
        this->ui->ud27->setChecked(true);
    }
    if (Updown[16] == 01){
        this->ui->radioButton_18->setChecked(true);
    }
    if (Updown[17] == 01){
        this->ui->ud28->setChecked(true);
    }
    if (Updown[18] == 01){
        this->ui->radioButton_20->setChecked(true);
    }
    if (Updown[19] == 01){
        this->ui->ud29->setChecked(true);
    }

    if (Updown[0] == 00){
        this->ui->radioButton_2->setChecked(false);
    }
    if (Updown[1] == 00){
        this->ui->ud20->setChecked(false);
    }
    if (Updown[2] == 00){
        this->ui->radioButton_4->setChecked(false);
    }
    if (Updown[3] == 00){
        this->ui->ud21->setChecked(false);
    }
    if (Updown[4] == 00){
        this->ui->radioButton_6->setChecked(false);
    }
    if (Updown[5] == 00){
        this->ui->ud22->setChecked(false);
    }
    if (Updown[6] == 00){
        this->ui->radioButton_8->setChecked(false);
    }
    if (Updown[7] == 00){
        this->ui->ud23->setChecked(false);
    }
    if (Updown[8] == 00){
        this->ui->radioButton_10->setChecked(false);
    }
    if (Updown[9] == 00){
        this->ui->ud24->setChecked(false);
    }
    if (Updown[10] == 00){
        this->ui->radioButton_12->setChecked(false);
    }
    if (Updown[11] == 00){
        this->ui->ud25->setChecked(false);
    }
    if (Updown[12] == 00){
        this->ui->radioButton_14->setChecked(false);
    }
    if (Updown[13] == 00){
        this->ui->ud26->setChecked(false);
    }
    if (Updown[14] == 00){
        this->ui->radioButton_16->setChecked(false);
    }
    if (Updown[15] == 00){
        this->ui->ud27->setChecked(false);
    }
    if (Updown[16] == 00){
        this->ui->radioButton_18->setChecked(false);
    }
    if (Updown[17] == 00){
        this->ui->ud28->setChecked(false);
    }
    if (Updown[18] == 00){
        this->ui->radioButton_20->setChecked(false);
    }
    if (Updown[19] == 00){
        this->ui->ud29->setChecked(false);
    }

}

void Widget::SavePublicData()
{

    Public.resize(6*2);
    int v[2];
    float fl[4];
    int f = 0;

    fl[0] = this->ui->doubleSpinBox->value();
    fl[1] = this->ui->doubleSpinBox_2->value();
    fl[2] = this->ui->doubleSpinBox_3->value();
    fl[3] = this->ui->doubleSpinBox_6->value();

    v[1] = this->ui->spinBox_4->value();
    v[2] = this->ui->spinBox_5->value();

    int value[4];
    for (int i = 0; i < 4;i++)
    {

        float tr[4];
        tr[i] = fl[i]*10;
        value[i] = (int)(tr[i]);
        Public[f++] =  (uchar)(0x000000ff & value[i]);
        Public[f++] =  (uchar)((0x0000ff00& value[i])>>8);
    }
    for (int i = 0; i < 2;i++)
    {

        Public[f++] =  (uchar)(0x000000ff & v[i]);
        Public[f++] =  (uchar)((0x0000ff00&v[i])>>8);
    }

    QFile Publicf("/home/root/savefile/Public.txt");      //定义一个文件
    Publicf.open(QIODevice::WriteOnly);   //打开文件
    Publicf.write(Public);
    Publicf.close();
}

void Widget::GetPublicData()
{
    QFile Publicf("/home/root/savefile/Public.txt");      //定义一个文件
    Publicf.open(QIODevice::ReadOnly);   //打开文件
    Public = Publicf.readAll();
    Publicf.close();
    int index = 0;

    float value[4];
    for (int i =0;i < 4;i++)
    {
        short result[4];
        float tr[4];
        result[i] = (short)( (0x00ff & Public[index++]) | ((0x00ff & Public[index++])<<8) );
        tr[i] = (float)result[i];
        value[i] = tr[i]/10;
    }
    this->ui->doubleSpinBox->setValue(value[0]);
    this->ui->doubleSpinBox_2->setValue(value[1]);
    this->ui->doubleSpinBox_3->setValue(value[2]);
    this->ui->doubleSpinBox_6->setValue(value[3]);
    this->ui->spinBox_4->setValue(Public[8] + Public[9]*256);
    this->ui->spinBox_5->setValue(Public[10] + Public[11]*256);
}


QString ByteArrayToHexString(QByteArray &ba)
{
    QDataStream out(&ba,QIODevice::ReadWrite);   //将str的数据 读到out里面去
    QString buf;
    while(!out.atEnd())
    {
        qint8 outChar = 0;
        out >> outChar;   //每次一个字节的填充到 outchar
        QString str = QString("0x")+QString("%1").arg(outChar&0xFF,2,16,QLatin1Char('0')).toUpper() + QString(" ");   //2 字符宽度
        buf += str;
    }
    return buf;
}

//参数发送
void Widget::send()
{

    //获取表格数据
    GetDataFormWidget();
    //获取开关数据
    SaveSwitchData();
    //保存公共参数
    SavePublicData();

    //生成运动参数协议
    for (int i = 0; i < 12; i++)
    {
        QByteArray Layer1;
        Layer1[0] = HEAD_1;
        Layer1[1] = HEAD_2;
        Layer1[2] = MOTION;
        Layer1[3] = 0x00;
        Layer1.append(i).toHex();
        for(int j = 0; j < 1*2; j++)
        {
            Layer1.append(mData[i][j]);
        }
        for(int j = 0; j < 2*2; j++)
        {
            Layer1.append(mFloatData[i][j]);
        }
        for(int j = 2; j < 7*2; j++)
        {
            Layer1.append(mData[i][j]);
        }
        Layer1.append(0X0D);
        Layer1.append(0X0A);
        serialRs485->write(Layer1);
        qDebug()<<ByteArrayToHexString(Layer1)<<i<<endl;
    }


    for (int i = 0; i < 12; i++)
    {
        QByteArray Layer2;
        Layer2[0] = HEAD_1;
        Layer2[1] = HEAD_2;
        Layer2[2] = MOTION;
        Layer2[3] = 0x01;
        Layer2.append(i).toHex();
        for(int j = 0; j < 1*2; j++)
        {
            Layer2.append(mData[i][j]);
        }
        for(int j = 0; j < 2*2; j++)
        {
            Layer2.append(mFloatData[i][j]);
        }
        for(int j = 2; j < 7*2; j++)
        {
            Layer2.append(mData[i][j]);
        }
        Layer2.append(0X0D);
        Layer2.append(0X0A);
        serialRs485->write(Layer2);
        qDebug()<<ByteArrayToHexString(Layer2)<<i<<endl;
    }


    for (int i = 0; i < 12; i++)
    {
        QByteArray Layer3;
        Layer3[0] = HEAD_1;
        Layer3[1] = HEAD_2;
        Layer3[2] = MOTION;
        Layer3[3] = 0x02;
        Layer3.append(i).toHex();
        for(int j = 0; j < 1*2; j++)
        {
            Layer3.append(mData[i][j]);
        }
        for(int j = 0; j < 2*2; j++)
        {
            Layer3.append(mFloatData[i][j]);
        }
        for(int j = 2; j < 7*2; j++)
        {
            Layer3.append(mData[i][j]);
        }
        Layer3.append(0X0D);
        Layer3.append(0X0A);
        serialRs485->write(Layer3);
        qDebug()<<ByteArrayToHexString(Layer3)<<i<<endl;
    }


    for (int i = 0; i < 12; i++)
    {
        QByteArray Layer4;
        Layer4[0] = HEAD_1;
        Layer4[1] = HEAD_2;
        Layer4[2] = MOTION;
        Layer4[3] = 0x03;
        Layer4.append(i).toHex();
        for(int j = 0; j < 1*2; j++)
        {
            Layer4.append(mData[i][j]);
        }
        for(int j = 0; j < 2*2; j++)
        {
            Layer4.append(mFloatData[i][j]);
        }
        for(int j = 2; j < 7*2; j++)
        {
            Layer4.append(mData[i][j]);
        }
        Layer4.append(0X0D);
        Layer4.append(0X0A);
        serialRs485->write(Layer4);
        qDebug()<<ByteArrayToHexString(Layer4)<<i<<endl;
    }


    for (int i = 0; i < 12; i++)
    {
        QByteArray Layer5;
        Layer5[0] = HEAD_1;
        Layer5[1] = HEAD_2;
        Layer5[2] = MOTION;
        Layer5[3] = 0x04;
        Layer5.append(i).toHex();
        for(int j = 0; j < 1*2; j++)
        {
            Layer5.append(mData[i][j]);
        }
        for(int j = 0; j < 2*2; j++)
        {
            Layer5.append(mFloatData[i][j]);
        }
        for(int j = 2; j < 7*2; j++)
        {
            Layer5.append(mData[i][j]);
        }
        Layer5.append(0X0D);
        Layer5.append(0X0A);
        serialRs485->write(Layer5);
        qDebug()<<ByteArrayToHexString(Layer5)<<i<<endl;
    }


    for (int i = 0; i < 12; i++)
    {
        QByteArray Layer6;
        Layer6[0] = HEAD_1;
        Layer6[1] = HEAD_2;
        Layer6[2] = MOTION;
        Layer6[3] = 0x05;
        Layer6.append(i).toHex();
        for(int j = 0; j < 1*2; j++)
        {
            Layer6.append(mData[i][j]);
        }
        for(int j = 0; j < 2*2; j++)
        {
            Layer6.append(mFloatData[i][j]);
        }
        for(int j = 2; j < 7*2; j++)
        {
            Layer6.append(mData[i][j]);
        }
        Layer6.append(0X0D);
        Layer6.append(0X0A);
        serialRs485->write(Layer6);
        qDebug()<<ByteArrayToHexString(Layer6)<<i<<endl;
    }


    for (int i = 0; i < 12; i++)
    {
        QByteArray Layer7;
        Layer7[0] = HEAD_1;
        Layer7[1] = HEAD_2;
        Layer7[2] = MOTION;
        Layer7[3] = 0x06;
        Layer7.append(i).toHex();
        for(int j = 0; j < 1*2; j++)
        {
            Layer7.append(mData[i][j]);
        }
        for(int j = 0; j < 2*2; j++)
        {
            Layer7.append(mFloatData[i][j]);
        }
        for(int j = 2; j < 7*2; j++)
        {
            Layer7.append(mData[i][j]);
        }
        Layer7.append(0X0D);
        Layer7.append(0X0A);
        serialRs485->write(Layer7);
        qDebug()<<ByteArrayToHexString(Layer7)<<i<<endl;
    }


    for (int i = 0; i < 12; i++)
    {
        QByteArray Layer8;
        Layer8[0] = HEAD_1;
        Layer8[1] = HEAD_2;
        Layer8[2] = MOTION;
        Layer8[3] = 0x07;
        Layer8.append(i).toHex();
        for(int j = 0; j < 1*2; j++)
        {
            Layer8.append(mData[i][j]);
        }
        for(int j = 0; j < 2*2; j++)
        {
            Layer8.append(mFloatData[i][j]);
        }
        for(int j = 2; j < 7*2; j++)
        {
            Layer8.append(mData[i][j]);
        }
        Layer8.append(0X0D);
        Layer8.append(0X0A);
        serialRs485->write(Layer8);
        qDebug()<<ByteArrayToHexString(Layer8)<<i<<endl;
    }


    for (int i = 0; i < 12; i++)
    {
        QByteArray Layer9;
        Layer9[0] = HEAD_1;
        Layer9[1] = HEAD_2;
        Layer9[2] = MOTION;
        Layer9[3] = 0x08;
        Layer9.append(i).toHex();
        for(int j = 0; j < 1*2; j++)
        {
            Layer9.append(mData[i][j]);
        }
        for(int j = 0; j < 2*2; j++)
        {
            Layer9.append(mFloatData[i][j]);
        }
        for(int j = 2; j < 7*2; j++)
        {
            Layer9.append(mData[i][j]);
        }
        Layer9.append(0X0D);
        Layer9.append(0X0A);
        serialRs485->write(Layer9);
        qDebug()<<ByteArrayToHexString(Layer9)<<i<<endl;
    }


    for (int i = 0; i < 12; i++)
    {
        QByteArray Layer10;
        Layer10[0] = HEAD_1;
        Layer10[1] = HEAD_2;
        Layer10[2] = MOTION;
        Layer10[3] = 0x09;
        Layer10.append(i).toHex();
        for(int j = 0; j < 1*2; j++)
        {
            Layer10.append(mData[i][j]);
        }
        for(int j = 0; j < 2*2; j++)
        {
            Layer10.append(mFloatData[i][j]);
        }
        for(int j = 2; j < 7*2; j++)
        {
            Layer10.append(mData[i][j]);
        }
        Layer10.append(0X0D);
        Layer10.append(0X0A);
        serialRs485->write(Layer10);
        qDebug()<<ByteArrayToHexString(Layer10)<<i<<endl;
    }


    //生成左右开关协议
    for (int i = 0; i < 10; i++)
    {
        QByteArray Switchlr;
        Switchlr[0] = HEAD_1;
        Switchlr[1] = HEAD_2;
        Switchlr[2] = LEFTRIGHTTRACKING;
        Switchlr.append(i).toHex();

        Switchlr[4] = 0x00;
        Switchlr.append(Leftright[i*2]);
        Switchlr.append(0x0D);
        Switchlr.append(0x0A);
        serialRs485->write(Switchlr);
        qDebug()<<ByteArrayToHexString(Switchlr)<<i<<endl;

    }
    for (int i = 0; i < 10; i++)
    {
        QByteArray Switchlr;
        Switchlr[0] = HEAD_1;
        Switchlr[1] = HEAD_2;
        Switchlr[2] = LEFTRIGHTTRACKING;
        Switchlr.append(i).toHex();

        Switchlr[4] = 0x01;
        Switchlr.append(Leftright[i*2+1]);
        Switchlr.append(0x0D);
        Switchlr.append(0x0A);
        serialRs485->write(Switchlr);
        qDebug()<<ByteArrayToHexString(Switchlr)<<i<<endl;

    }

    //生成上下开关协议
    for (int i = 0; i < 10; i++)
    {
        QByteArray Switchud;
        Switchud[0] = HEAD_1;
        Switchud[1] = HEAD_2;
        Switchud[2] = UPDOWNTRACKING;
        Switchud.append(i).toHex();

        Switchud[4] = 0x00;
        Switchud.append(Updown[i*2]);
        Switchud.append(0x0D);
        Switchud.append(0x0A);
        serialRs485->write(Switchud);
        qDebug()<<ByteArrayToHexString(Switchud)<<i<<endl;
    }
    for (int i = 0; i < 10; i++)
    {
        QByteArray Switchud;
        Switchud[0] = HEAD_1;
        Switchud[1] = HEAD_2;
        Switchud[2] = UPDOWNTRACKING;
        Switchud.append(i).toHex();

        Switchud[4] = 0x01;
        Switchud.append(Updown[i*2+1]);
        Switchud.append(0x0D);
        Switchud.append(0x0A);
        serialRs485->write(Switchud);
        qDebug()<<ByteArrayToHexString(Switchud)<<i<<endl;
    }

    //公共参数
    QByteArray PublicParameter;
    PublicParameter[0] = HEAD_1;
    PublicParameter[1] = HEAD_2;
    PublicParameter[2] = PUBLIC;
    for (int i = 0; i < 4; i++)
    {
        PublicParameter.append(Public[i]);
    }
    for (int i = 6; i < 12; i++)
    {
        PublicParameter.append(Public[i]);
    }
    for (int i = 4; i < 6; i++)
    {
        PublicParameter.append(Public[i]);
    }
    PublicParameter.append(0X0D);
    PublicParameter.append(0X0A);
    serialRs485->write(PublicParameter);
    QMessageBox::information(NULL,"发送","发送完毕");

}


//串口接收
void Widget::receiveinfo()
{
    QString buf;

    QByteArray buffer = serialRs232->readAll();
    buf = buffer.toHex();
    qDebug()<<buf;

    if (buf.startsWith("55aa60"))
    {
        qDebug()<<"angle";
        //float angle;
        int value;
        value = (buf.mid(8,2)+buf.mid(6,2)).toInt(NULL,16);
        float f = (float)value;

        angle = f/10;

        QString str = QString("%1").arg(angle);

        welding(angle);

        ui->lineEdit->setText(str);
        buffer.clear();
    }
    else if (buf.startsWith("55aa61"))
    {
        qDebug()<<"temp";

        int value;
        float temp;
        value = (buf.mid(6,2)+buf.mid(8,2)).toInt(NULL,16);
        float f = (float)value;
        temp = f/10;

        QString str = QString("%1").arg(temp);
        ui->lineEdit_2->setText(str);
        buffer.clear();
    }
    else if (buf.startsWith("55aa62"))
    {
        qDebug()<<"1v";
        int value;
        float temp;
        value = (buf.mid(6,2)+buf.mid(8,2)).toInt(NULL,16);
        float f = (float)value;
        temp = f/10;

        QString str = QString("%1").arg(temp);
        ui->lineEdit_3->setText(str);
        buffer.clear();
    }
    else if (buf.startsWith("55aa63"))
    {
        qDebug()<<"1a";
        int value;
        float temp;
        value = (buf.mid(6,2)+buf.mid(8,2)).toInt(NULL,16);
        float f = (float)value;
        temp = f/10;

        QString str = QString("%1").arg(temp);
        ui->lineEdit_4->setText(str);
        buffer.clear();
    }
    else if (buf.startsWith("55aa64"))
    {
        qDebug()<<"2v";
        int value;
        float temp;
        value = (buf.mid(6,2)+buf.mid(8,2)).toInt(NULL,16);
        float f = (float)value;
        temp = f/10;
        QString str = QString("%1").arg(temp);

        ui->lineEdit_5->setText(str);
        buffer.clear();
    }
    else if (buf.startsWith("55aa65"))
    {
        qDebug()<<"2a";
        int value;
        float temp;
        value = (buf.mid(6,2)+buf.mid(8,2)).toInt(NULL,16);
        float f = (float)value;
        temp = f/10;
        QString str = QString("%1").arg(temp);

        ui->lineEdit_6->setText(str);
        buffer.clear();
    }

    else{
        buffer.clear();
    }

}





