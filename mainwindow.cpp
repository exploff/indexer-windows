#include "mainwindow.h"
#include "ui_imainwindow.h"
#include "commandhandler/commandhandler.h"
#include "common/constants.h"
#include <QStandardPaths>
#include <QFileInfo>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),  receiver(ui), sender()
{
    ui->setupUi(this);

    QObject::connect(&sender, &Sender::indexingStart, &receiver, &Receiver::onIndexingStart);
    QObject::connect(&sender, &Sender::indexingEnd, &receiver, &Receiver::onIndexingEnd);
    QObject::connect(&sender, &Sender::indexingPause, &receiver, &Receiver::onIndexingPause);
    QObject::connect(&sender, &Sender::indexingResume, &receiver, &Receiver::onIndexingResume);
    QObject::connect(&sender, &Sender::addingSearchResult, &receiver, &Receiver::onAddOneSearchResult);
    QObject::connect(&sender, &Sender::actionResult, &receiver, &Receiver::onActionResult);

    QObject::connect(&sender, &Sender::sendingLogs, &receiver, &Receiver::onSendingLogs);

    QObject::connect(ui->resultSearch, &QListWidget::itemClicked, this, &MainWindow::on_resultItemClicked);
    QObject::connect(ui->tableWidget, &QTableWidget::itemClicked, this, &MainWindow::on_tableWidget_itemClicked);

    QStringList headers;
    headers << "Name" << "Size" << "Date" << "Path";

    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRootFolderToBeIndexed(QString rootFolder)
{
    qDebug() << "rootFolder" << rootFolder;
    ui->textEditRootFolder->setPlainText(rootFolder);
}

void MainWindow::on_submitButton_clicked()
{

    ui->resultSearch->clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    qDebug() << "Submit clicked !";
    QString command = ui->textEdit->toPlainText();
    ui->textEdit->clear();

    sender.sendLogs("COMMANDE : " + command);

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

void MainWindow::on_buttonRootFolder_clicked()
{
    qDebug() << "on_buttonRootFolder_clicked";
    QString rootFolderToBeIndexed = ui->textEditRootFolder->toPlainText();

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFileName = Constants::DB_FILENAME;

    DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);

    dbAdapter.open();
    dbAdapter.updateRootFolderToBeIndexed(rootFolderToBeIndexed);
    dbAdapter.close();

    ui->logs->append("Root folder to be indexed : " + rootFolderToBeIndexed);
}

void MainWindow::on_resultItemClicked(QListWidgetItem *item)
{
    if (item) {
        QString filePath = item->text();  // Obtenez le chemin du fichier sélectionné

        QFileInfo fileInfo(filePath);
        QString folderPath = fileInfo.path();

        // Ouvrez l'explorateur de fichiers
        QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
    }
}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    if (item && item->column() == 3) {
        int row = item->row();

        QString path = ui->tableWidget->item(row, 3)->text();

        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
}
