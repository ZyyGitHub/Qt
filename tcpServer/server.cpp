#include <QtGui>
#include <QtNetwork>
#include <stdlib.h>
#include <server.h>
#include <QLabel>
#include <QVBoxLayout>

Server::Server(QWidget *parent):QDialog (parent)
{
    Label = new QLabel;
    tcpServer = new QTcpServer(this);
    if(!tcpServer ->listen()){
        close();
        return;
    }
    Label->setText(tr("The server is running on port %1.").arg(tcpServer->serverPort()));
    msg << tr("You have been leading a dog life,stay off the furniture")
        << tr("think about tomorrow")
        << tr("Y surpirse by a loud noice")
        << tr("feel hungry again in another hour")
        << tr("have mail")
        << tr("kill time without injuring eternity")
        << tr("Computers are not intelligent");
    //信号和槽链接
    connect(tcpServer,SIGNAL(newconnection),this,SLOT(sendmsg()));
    //页面布局
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(Label);
    setLayout(mainLayout);
    setWindowTitle("server");
}
void Server::sendmsg()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << msg.at(qrand()%msg.size());
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    //建立连接
    QTcpServer *clientConnection = tcpServer -> nextPendingConnection();
    connect(clientConnection,SIGNAL(disconnect()),clientConnection,SLOT(deleteLater()));
    //向客户端传输数据
    clientConnection -> write(block);
    clientConnection -> disconnectFromHost();
}
