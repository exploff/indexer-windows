#include "receiver.h"
#include <QDebug>
#include "ui_imainwindow.h"

//Receiver::Receiver(QObject *parent)
//    : QObject{parent}
//{

//}

Receiver::Receiver(Ui::MainWindow* mainUi) : mainUi(mainUi) {}



void Receiver::onIndexingStart()
{
    mainUi->buttonStartIndexing->setEnabled(false);
    mainUi->buttonStopIndexing->setEnabled(true);
    mainUi->buttonPauseIndexing->setEnabled(true);
    mainUi->buttonResumeIndexing->setEnabled(true);
}


void Receiver::onIndexingEnd()
{
    mainUi->buttonStartIndexing->setEnabled(true);
    mainUi->buttonStopIndexing->setEnabled(false);
    mainUi->buttonPauseIndexing->setEnabled(false);
    mainUi->buttonResumeIndexing->setEnabled(false);
}

void Receiver::onIndexingPause()
{
    mainUi->buttonPauseIndexing->setEnabled(false);
    mainUi->buttonResumeIndexing->setEnabled(true);
}

void Receiver::onIndexingResume()
{
    mainUi->buttonResumeIndexing->setEnabled(false);
    mainUi->buttonPauseIndexing->setEnabled(true);
}

void Receiver::onSendingLogs(QString log)
{
    mainUi->logs->append(log);
}

void Receiver::onAddOneSearchResult(FileInfo result)
{
    mainUi->resultSearch->addItem(result.getPath() + "/" + result.getFileName());

    int row = mainUi->tableWidget->rowCount();  // Ajouter une nouvelle ligne
    mainUi->tableWidget->insertRow(row);

    mainUi->tableWidget->setItem(row, 0, new QTableWidgetItem(result.getFileName()));
    mainUi->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(result.getSize())));
    mainUi->tableWidget->setItem(row, 2, new QTableWidgetItem(result.getCreatedDate().toString("dd/MM/yyyy")));
    mainUi->tableWidget->setItem(row, 3, new QTableWidgetItem(result.getPath()));
}

void Receiver::onActionResult(QString result)
{
    mainUi->logs->append(result);
}
