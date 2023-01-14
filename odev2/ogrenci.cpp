#include "ogrenci.h"
#include "ui_ogrenci.h"
#include "QMessageBox.h"

ogrenci::ogrenci(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ogrenci)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Uygulamalar/Kodlar/QT/odev2/odev2.db");
    db.open();
    ogrencileri_yukle();

}

ogrenci::~ogrenci()
{
    delete ui;
}

void ogrenci::on_yeni_kayit_clicked()
{
    QString ad,soyad;
    ad=ui->ad->text().trimmed();
    soyad = ui->soyad->text().trimmed();
    if(ad=="" || soyad==""){
        QMessageBox::critical(this,"Hata !","Gerekli Alanları Doldurunuz!","OK");
    }else{
        QSqlQuery query;
        query.prepare("insert into ogrenci (ogr_ad,ogr_soyad) values (:ad,:soyad)");
        query.bindValue(":ad",ad);
        query.bindValue(":soyad",soyad);
        query.exec();
        ogrencileri_yukle();
    }
}

void ogrenci::ogrencileri_yukle()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from ogrenci");
    query.exec();
    model->setQuery(query);
    ui->ogrenciler->setModel(model);
    ui->ad->clear();
    ui->no->clear();
    ui->soyad->clear();
}


void ogrenci::on_ogrenciler_clicked(const QModelIndex &index)
{
    QString ogr_no,ogr_ad,ogr_soyad;
    ogr_no=index.sibling(index.row(),0).data().toString();
    ogr_ad=index.sibling(index.row(),1).data().toString();
    ogr_soyad=index.sibling(index.row(),2).data().toString();
    ui->ad->setText(ogr_ad);
    ui->no->setText(ogr_no);
    ui->soyad->setText(ogr_soyad);
}


void ogrenci::on_guncelle_clicked()
{
    QString ad,soyad,no;
    no=ui->no->text();
    ad=ui->ad->text();
    soyad=ui->soyad->text();
    QSqlQuery query;
    query.prepare("update ogrenci set ogr_ad=:ad,ogr_soyad=:soyad where ogr_no=:no");
    query.bindValue(":ad",ad);
    query.bindValue(":soyad",soyad);
    query.bindValue(":no",no);
    query.exec();
    ogrencileri_yukle();
}


void ogrenci::on_sil_clicked()
{
    QString no=ui->no->text();
    int kontrol =0;
    QSqlQuery query;
    query.prepare("SELECT ogr_no from notlar");
    query.exec();
    while(query.next()){
        if(query.value(0).toString() == no){
            QMessageBox::information(this,"Hata !","Bu öğrenci silinemez. Bu öğrencinin üstüne tanımlanmış dersler vardır !");
            kontrol =1;
            break;
        }
    }
    if(kontrol==0){
        query.prepare("delete from ogrenci WHERE ogr_no=:no");
        query.bindValue(":no",no);
        query.exec();
    }

    ogrencileri_yukle();
}

