#ifndef SERVER_H
#define SERVER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QTcpServer;
QT_END_NAMESPACE

class Server:public QDialog
{
    Q_OBJECT
public:
    Server(QWidget *parent = 0);
private slots:
    void sendmsg();
private:
    QLabel *Label;
    QTcpServer *tcpServer;
    QStringList msg;
};


#endif // SERVER_H
