#include <QtGui>
#include <QtNetwork>
#include <stdlib.h>
#include <server.h>

Server::Server(QWidget *parent):QDialog (parent)
{
    Label = new QLabel;
    tcpServer = new QTcpServer(this);
    if(!tcpServer ->listen()){
        close();
        return;
    }
    Label->setText(tr("The server is running on port %1.")).arg(tcpServer->serverPort())
}
