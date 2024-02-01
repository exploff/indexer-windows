#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "receiver.h"
#include "sender.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setRootFolderToBeIndexed(QString rootFolder);

private slots:
    void on_submitButton_clicked();

    void on_buttonStartIndexing_clicked();
    void on_buttonStopIndexing_clicked();
    void on_buttonPauseIndexing_clicked();
    void on_buttonResumeIndexing_clicked();
    void on_buttonRootFolder_clicked();
    void on_resultItemClicked(QListWidgetItem *item);
    void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Receiver receiver;
    Sender sender;

};
#endif // MAINWINDOW_H
