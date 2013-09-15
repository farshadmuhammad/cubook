#include <QtCore/QCoreApplication>
#include <QFile>
#include <QImageReader>
#include "messagetranslator.h"
#include <QByteArray>
#include "getwrapper.h"
#include "cuserver.h"
#include "database.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    CUServer *server = new CUServer();
    server->startServer();

    return a.exec();
}
