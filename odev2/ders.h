#ifndef DERS_H
#define DERS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class ders;
}

class ders : public QDialog
{
    Q_OBJECT

public:
    explicit ders(QWidget *parent = nullptr);
    ~ders();

private slots:
    void on_yeni_kayit_clicked();
    void dersleri_yukle();

    void on_sil_clicked();

    void on_tum_dersler_clicked(const QModelIndex &index);

    void on_guncelle_clicked();

private:
    Ui::ders *ui;
};

#endif // DERS_H
