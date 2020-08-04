#include "widget.h"
#include <QApplication>
#include <QThread>
#include <QFont>
#include <QFontDatabase>
#include "mcanbus.h"
#include "frmnum.h"

int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);

    //加载字体文件
    int nlndex = QFontDatabase::addApplicationFont("/usr/lib/fonts/wenquanyi_9pt.pcf");

    QStringList strlist(QFontDatabase::applicationFontFamilies(nlndex));

    if (strlist.count() > 0) {

    QFont fontthis(strlist.at(0));

    a.setFont(fontthis);
    }

    //a.processEvents();
    //a.setOverrideCursor(Qt::BlankCursor);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    //QT5版本以上默认就是采用UTF-8编码
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif

    //qApp->setFont(QFont("Microsoft YaHei", 10));
    //qApp->setFont(QFont("WenQuanYi Micro Hei", 15));


    frmNum::Instance()->Init("brown",10);//set brown--灰黑色


    Widget w;
    w.show();



    return a.exec();
}
