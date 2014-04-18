#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QSsl>
#include <QSslCertificate>
#include <QByteArray>
#include <QSslSocket>
#include <QFile>
#include <QIODevice>

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSslSocket serversocket;
    serversocket.setProtocol(QSsl::SslV3);
    QByteArray key;
    QByteArray cert;
    QFile file_key("www.nerovon.com.key");
    if(file_key.open(QIODevice::ReadOnly))
    {
        key = file_key.readAll();
        file_key.close();
    }
    else
    {
        qDebug()<<file_key.errorString();
    }

    QSslKey ssl_key(key, QSsl::Rsa);

    QSslCertificate ssl_cert(cert);

    serversocket.setPrivateKey(ssl_key);
    serversocket.setLocalCertificate(ssl_cert);
    cout << "Starting the server encryption" << endl;
    serversocket.startServerEncryption();
    cout << "Encrypted server successful" << endl;

    return a.exec();
}
