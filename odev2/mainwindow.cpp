#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Uygulamalar/Kodlar/QT/odev2/odev2.db");
    if(db.open()){
        ui->statusbar->showMessage("Veri tabanına bağlanıldı !");
    }
    else{
        ui->statusbar->showMessage("Veri tabanına bağlanılmadı !");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ogrenciIslem_clicked()
{
    ogrenci *new_ogrenci =new ogrenci;
    new_ogrenci->show();
}

void MainWindow::on_dersIslem_clicked()
{
    ders *new_ders = new ders;
    new_ders->show();
}

void MainWindow::on_notIslem_clicked()
{
    nott *new_nott = new nott;
    new_nott->show();
}

