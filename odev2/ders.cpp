#include "ders.h"
#include "ui_ders.h"
#include "QMessageBox"

ders::ders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ders)
{
    ui->setupUi(this);
    dersleri_yukle();
}

ders::~ders()
{
    delete ui;
}

void ders::on_yeni_kayit_clicked()
{
    QString ders_adi,ders_kodu;
    ders_adi=ui->ders_adi->text().trimmed();
    ders_kodu=ui->ders_kodu->text().trimmed();
    if(ders_adi=="" || ders_kodu==""){
        QMessageBox::critical(this,"Hata !","Gerekli Alanları Doldurunuz!","OK");
    }
    else{
        int kontrol=0;
        QSqlQuery query;
        query.prepare("select ders_kodu from dersler");
        query.exec();
        while(query.next()){
            if(query.value(0).toString()==ders_kodu){
                QMessageBox::information(this,"Hata !","Bu kodda başka ders vardır. Farklı kodda ders ekleyiniz !");
                kontrol=1;
                break;
            }
        }
        if(kontrol==0){
            query.prepare("insert into dersler (ders_kodu,ders_adi) values (?,?)");
            query.addBindValue(ders_kodu);
            query.addBindValue(ders_adi);

            query.exec();
        }
        dersleri_yukle();
    }

}

void ders::dersleri_yukle()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from dersler");
    query.exec();
    model->setQuery(query);
    ui->tum_dersler->setModel(model);
    ui->ders_kodu->clear();
    ui->ders_adi->clear();
}

void ders::on_sil_clicked()
{
    QString ders_kodu=ui->ders_kodu->text();
    QSqlQuery query;
    int kontrol =0;
    query.prepare("select ders_kodu from notlar");
    query.exec();
    while(query.next()){
        if(query.value(0).toString()==ders_kodu){
            QMessageBox::information(this,"Hata !","Bu ders silinemez. Bu derse kayıtlı öğrenciler vardır !");
            kontrol=1;
            break;
        }
    }
    if(kontrol==0){
        query.prepare("delete from dersler WHERE ders_kodu=:ders_kod");
        query.bindValue(":ders_kod",ders_kodu);
        query.exec();
    }

    dersleri_yukle();
}

QString selected_kod;
void ders::on_tum_dersler_clicked(const QModelIndex &index)
{
    QString ders_kodu,ders_adi;
    ders_kodu=index.sibling(index.row(),0).data().toString();
    ders_adi=index.sibling(index.row(),1).data().toString();
    ui->ders_kodu->setText(ders_kodu);
    ui->ders_adi->setText(ders_adi);
    selected_kod=ui->ders_kodu->text();

    QSqlQuery query;
    QSqlQueryModel *model= new QSqlQueryModel();
    query.prepare("select * from notlar where ders_kodu=?");
    query.addBindValue(selected_kod);
    query.exec();
    model->setQuery(query);
    ui->ogrenci_dersler->setModel(model);
}


void ders::on_guncelle_clicked()
{
    QString ders_kodu,ders_adi;
    QSqlQuery query;
    ders_kodu=ui->ders_kodu->text();
    ders_adi=ui->ders_adi->text();
    int kontrol=0;
    query.prepare("select ders_kodu from dersler where ders_kodu=?");
    query.addBindValue(ders_kodu);
    query.exec();
    query.next();
    query.prepare("select ders_kodu from notlar");
    query.exec();
    while(query.next()){
        if(query.value(0).toString()==ders_kodu){
            QMessageBox::information(this,"Hata !","Bu ders güncellenemez. Bu derse kayıtlı öğrenciler vardır !");
            kontrol=1;
            break;
        }
    }
    if(kontrol==0){
        query.prepare("update dersler set ders_kodu=?,ders_adi=? where ders_kodu=?");
        query.addBindValue(ders_kodu);
        query.addBindValue(ders_adi);
        query.addBindValue(selected_kod);
        query.exec();
    }

    dersleri_yukle();

}

