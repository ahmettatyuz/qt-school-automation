#ifndef OGRENCI_H
#define OGRENCI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class ogrenci;
}

class ogrenci : public QDialog
{
    Q_OBJECT

public:
    explicit ogrenci(QWidget *parent = nullptr);
    ~ogrenci();

private slots:

    void on_yeni_kayit_clicked();

    void ogrencileri_yukle();

    void on_ogrenciler_clicked(const QModelIndex &index);

    void on_guncelle_clicked();

    void on_sil_clicked();

private:
    Ui::ogrenci *ui;
};

#endif // OGRENCI_H
