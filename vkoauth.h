#ifndef VKOAUTH_H
#define VKOAUTH_H

#include <QWebView>
#include <QNetworkReply>
#include <QtXml>

class VkOAuth : public QWebView
{
    Q_OBJECT

protected:
    QString m_app;
    QNetworkReply* m_http;
    void loadLoginPage();

public:
    VkOAuth(QString app, QWidget* parent=0);

signals:
    void success(QString);
    void unsuccess();
    void hided();

public slots:
    void slotLinkChanged(QUrl url);
    void slotDone();
    void slotRequest(QUrl request);

private:
    QString m_access_token;
    QString m_expires_in;
    QString m_user_id;
};

#endif // VKOAUTH_H
