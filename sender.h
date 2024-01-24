#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include "ui_imainwindow.h"
#include "common/fileinfo/fileinfo.h"

class Sender : public QObject
{
    Q_OBJECT
    int _value = 0;
    Ui::MainWindow* mainUi;

public:
    //explicit Sender(QObject *parent = nullptr);
    Sender(Ui::MainWindow* mainUi);

    void setValue(int newValue);
    void startIndexing();
    void sendLogs(QString log);
    void endIndexing();
    void pauseIndexing();
    void resumeIndexing();

    void searchResult(QList<FileInfo> &results);

signals:
    void indexingStart();
    void indexingEnd();
    void indexingPause();
    void indexingResume();
    void addingSearchResult(FileInfo result);
    void sendingLogs(QString log);
};

#endif // SENDER_H
