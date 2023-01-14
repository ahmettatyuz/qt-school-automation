#ifndef NOTT_H
#define NOTT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class nott;
}

class nott : public QDialog
{
    Q_OBJECT

public:
    explicit nott(QWidget *parent = nullptr);
    ~nott();

private slots:
    void ogrencileri_yukle();

    void dersleri_yukle();

    void on_dersKayit_clicked();

    void on_tumOgrenciler_clicked(const QModelIndex &index);

    void on_tumDersler_clicked(const QModelIndex &index);

    void notlari_yukle();

private:
    Ui::nott *ui;
};

#endif // NOTT_H
