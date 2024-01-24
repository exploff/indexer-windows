#include "mainwindow.h"
#include "ui_imainwindow.h"
#include "commandhandler/commandhandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),  receiver(ui), sender(ui)
{
    ui->setupUi(this);

    QObject::connect(&sender, &Sender::indexingStart, &receiver, &Receiver::onIndexingStart);
    QObject::connect(&sender, &Sender::indexingEnd, &receiver, &Receiver::onIndexingEnd);
    QObject::connect(&sender, &Sender::indexingPause, &receiver, &Receiver::onIndexingPause);
    QObject::connect(&sender, &Sender::indexingResume, &receiver, &Receiver::onIndexingResume);
    QObject::connect(&sender, &Sender::addingSearchResult, &receiver, &Receiver::onAddOneSearchResult);

    QObject::connect(&sender, &Sender::sendingLogs, &receiver, &Receiver::onSendingLogs);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_submitButton_clicked()
{

    ui->resultSearch->clear();

    qDebug() << "Submit clicked !";
    QString command = ui->textEdit->toPlainText();
    ui->textEdit->clear();

    ui->resultSearch->addItem("COMMANDE : " + command);

    qDebug() << "Commande : " << command;
    CommandHandler commandHandler(&sender);

    commandHandler.processCommand(command);
}



void MainWindow::on_buttonStartIndexing_clicked()
{
    qDebug() << "Start indexing clicked";

    CommandHandler commandHandler(&sender);

    commandHandler.processCommand("INDEXER START");
}

void MainWindow::on_buttonStopIndexing_clicked()
{
    qDebug() << "Stop indexing clicked";

    CommandHandler commandHandler(&sender);

    commandHandler.processCommand("INDEXER STOP");
}

void MainWindow::on_buttonPauseIndexing_clicked()
{
    qDebug() << "Pause indexing clicked";

    CommandHandler commandHandler(&sender);

    commandHandler.processCommand("INDEXER PAUSE");
}

void MainWindow::on_buttonResumeIndexing_clicked()
{
    qDebug() << "Resume indexing clicked";

    CommandHandler commandHandler(&sender);

    commandHandler.processCommand("INDEXER RESUME");
}
