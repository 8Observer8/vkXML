#include "vkoauth.h"

#include <QNetworkRequest>
#include <QMessageBox>
#include <QDebug>

/**
 * Показываем страницу авторизации
 *
 * @param app Код зарегистрированного приложения
 * @param parent Указатель на родительский класс
 */
VkOAuth::VkOAuth(QString app, QWidget* parent) : QWebView(parent)
{

    QObject::connect(this, SIGNAL( urlChanged(QUrl)      ),
                     SLOT( slotLinkChanged(QUrl) )
                     );
    m_app = app;
    loadLoginPage();
}

/**
 * Показываем страницу авторизации
 *
 * @brief VkOAuth::loadLoginPage
 */
void VkOAuth::loadLoginPage(){
    QUrl url("https://oauth.vk.com/authorize");
    QUrlQuery query;

    query.addQueryItem("client_id", m_app);
    query.addQueryItem("layout","https://oauth.vk.com/blank.html"  );
    query.addQueryItem("display", "popup");
    query.addQueryItem("scope", "2");
    query.addQueryItem("response_type", "token");

    url.setQuery(query);

    load(url);
}

void VkOAuth::slotLinkChanged(QUrl url)
{
    if ("/blank.html" == url.path()) {
        QRegExp regexp("access_token=([^,]+)&expires_in=([^,]+)&user_id=([^,]+)");

        QString str= url.fragment();

        if( -1 != regexp.indexIn(str) ){
            m_access_token = regexp.cap(1);
            m_expires_in = regexp.cap(2);
            m_user_id = regexp.cap(3);
            hide(); //hide this window
            emit hided();
        }
    }
    else if("/api/login_failure.html" == url.path()){
        emit unsuccess();
    }
}

void VkOAuth::slotRequest(QUrl request) {
    //QUrl request(QString("https://api.vk.com/method/%1.xml?").arg("friends.get"));
    QUrlQuery query;
    query.addQueryItem("user_id", m_user_id);
    query.addQueryItem("access_token", m_access_token);
    request.setQuery(query);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    m_http = manager->get(QNetworkRequest(request));
    QObject::connect(m_http, SIGNAL(finished()), this, SLOT(slotDone()));
}

void VkOAuth::slotDone() {
    QString russian = QString::fromUtf8(m_http->readAll());

//    QDomDocument dom;
//    QByteArray aByteArray = russian.toUtf8();
//    if (!dom.setContent(aByteArray)) {
//        QMessageBox::critical(this, tr("Error"), tr("Failed to parse the file into a DOM tree"));
//        return;
//    }
    qDebug() << russian;
    emit success(russian);
    m_http->close();
}
