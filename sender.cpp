#include "sender.h"
#include <QDebug>
#include "ui_imainwindow.h"


Sender::Sender() {}


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
    if (results.isEmpty()) {
        emit sendingLogs("Aucun résultat");
        return;
    }
    for (const FileInfo &fileInfo : results) {
        emit addingSearchResult(fileInfo);
    }
}

void Sender::sendActionResult(QList<QString> results)
{
    if (results.isEmpty()) {
        emit sendingLogs("Aucun résultat");
        return;
    }
    for (const QString& result : results) {
        emit actionResult(result);
    }
}
