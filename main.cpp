#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QSsl>
#include <QSslCertificate>
#include <QByteArray>
#include <QSslSocket>
#include <QFile>
#include <QIODevice>
#include <QtNetwork/QSslKey>

using namespace std;


int main(int argc, char *argv[])
{

    //After this is the new code!
        QSslSocket Socket;
        Socket.setProtocol(QSsl::SslV3);

       QByteArray  key;
       QByteArray  cert;

       QFile fileKey("C:/Qt/Tools/QtCreator/bin/QTTestingSSLServer/Keys/NeroVon.key");
       if(fileKey.open(QIODevice ::ReadOnly))
       {
           key = fileKey.readAll();
           fileKey.close();
           cout << "Key added" << endl;
       }
       else
       {
           qDebug() << fileKey.errorString();
       }

       QFile fileCert("C:/Qt/Tools/QtCreator/bin/QTTestingSSLServer/Keys/NeroVon.csr");
       if(fileCert.open(QIODevice ::ReadOnly))
       {
           cert = fileCert.readAll();
           fileCert.close();
           cout << "Certificate added" << endl;
       }
       else
       {
           qDebug() << fileCert.errorString();
       }

       qDebug() << key + "\n" + cert;


       cout << "Adding key to key object" << endl;
       QSslKey sslKey(key, QSsl::Rsa);
       cout << "Adding certificate to certificate object" << endl;
       QSslCertificate sslCert(cert);

       cout << "Setting private key" << endl;
       Socket.setPrivateKey(sslKey);
       cout << "Setting local certificate" << endl;
       Socket.setLocalCertificate(sslCert);

       //if (!Socket.setSocketDescriptor(SocketDescriptor)) {
       //   return 0;
       //}

       cout << "Starting server" << endl;
       Socket.startServerEncryption();
       cout << "Server successfully created" << endl;

       if(!Socket.waitForEncrypted()) {
          return 0;
       }

    return 0;
}
