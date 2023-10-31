#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();
};
#endif // SERVER_H
