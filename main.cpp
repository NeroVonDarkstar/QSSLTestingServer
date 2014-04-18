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

    //After this is the new code!
        QSslSocket Socket;
        Socket.setProtocol(QSsl::SslV3);

       QByteArray  key;
       QByteArray  cert;

       QFile  fileKey("C:\Qt\Tools\QtCreator\bin\QTTestingSSLServer\www.nerovon.com.key");
       if(fileKey.open(QIODevice ::ReadOnly))
       {
           key = fileKey.readAll();
           fileKey.close();
       }
       else
       {
           qDebug() << fileKey.errorString();
       }

       QFile  fileCert("C:\Qt\Tools\QtCreator\bin\QTTestingSSLServer\www.nerovon.com.csr");
       if(fileCert.open(QIODevice ::ReadOnly))
       {
           cert = fileCert.readAll();
           fileCert.close();
       }
       else
       {
           qDebug() << fileCert.errorString();
       }

       qDebug() << key + "\n" + cert;

       QSslKey sslKey(key, QSsl::Rsa);
       QSslCertificate sslCert(cert);

       Socket.setPrivateKey(sslKey);
       Socket.setLocalCertificate(sslCert);

       if (!Socket.setSocketDescriptor(SocketDescriptor)) {
          return 0;
       }

       Socket.startServerEncryption();
       cout << "Server successfully created" << endl;

       if(!Socket.waitForEncrypted()) {
          return 0;
       }

    return a.exec();
}
