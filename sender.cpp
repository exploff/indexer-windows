#include "sender.h"
#include <QDebug>
#include "ui_imainwindow.h"


Sender::Sender(Ui::MainWindow* mainUi) : mainUi(mainUi) {}


void Sender::startIndexing()
{
    emit indexingStart();
}

void Sender::endIndexing()
{
    emit indexingEnd();
}

void Sender::pauseIndexing()
{
    emit indexingPause();
}

void Sender::resumeIndexing()
{
    emit indexingResume();
}

void Sender::sendLogs(QString log)
{
    emit sendingLogs(log);
}
void Sender::searchResult(QList<FileInfo> &results)
{
    for (const FileInfo &fileInfo : results) {
        emit addingSearchResult(fileInfo);
    }
}
