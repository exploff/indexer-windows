#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include "ui_imainwindow.h"
#include "common/fileinfo/fileinfo.h"

class Receiver : public QObject
{
    Q_OBJECT
    Ui::MainWindow* mainUi;

public:
    //explicit Receiver(QObject *parent = nullptr);
    Receiver(Ui::MainWindow* mainUi);


public slots:
    void onIndexingStart();
    void onIndexingEnd();
    void onIndexingPause();
    void onIndexingResume();
    void onSendingLogs(QString log);

    void onAddOneSearchResult(FileInfo result);
    void onActionResult(QString result);

signals:

};

#endif // RECEIVER_H
