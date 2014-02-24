#include "mainwindow.h"
#include "vkoauth.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    //w.show();

    VkOAuth vkOAuth("3936584");

    QObject::connect(&vkOAuth, SIGNAL( unsuccess() ),
                     &app   , SLOT( quit() )
                     );
//    QObject::connect(&vkOAuth, SIGNAL( success(QString) ),
//                     &window, SLOT( slotSuccess(QString) )
//                     );
//    QObject::connect(&window, SIGNAL( sendRequest(QUrl) ),
//                     &vkOAuth, SLOT( slotRequest(QUrl) )
//                     );
//    QObject::connect(&vkOAuth, SIGNAL( hided() ),
//                     &window, SLOT( show() )
//                     );
    vkOAuth.show();

    return app.exec();
}
