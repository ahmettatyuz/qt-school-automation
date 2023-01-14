#include "nott.h"
#include "ui_nott.h"
#include "QMessageBox"

nott::nott(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nott)
{
    ui->setupUi(this);
    ogrencileri_yukle();
    dersleri_yukle();
    notlari_yukle();
}

nott::~nott()
{
    delete ui;
}


void nott::ogrencileri_yukle()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from ogrenci");
    query.exec();
    model->setQuery(query);
    ui->tumOgrenciler->setModel(model);
}

void nott::dersleri_yukle()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from dersler");
    query.exec();
    model->setQuery(query);
    ui->tumDersler->setModel(model);
}

void nott::on_dersKayit_clicked()
{
    QString ogr_no,ders_kodu,vize_not,final_not;
    int finall,vize;
    float gecme_notu;
    ogr_no=ui->ogr_no->text();
    ders_kodu=ui->ders_kodu->text();
    vize_not =ui->vize_not->text();
    final_not=ui->final_not->text();

    finall = final_not.toInt();
    vize = vize_not.toInt();
    gecme_notu = finall*0.6+vize*0.4;

    if(ogr_no=="" || ders_kodu=="" ||vize_not==""||final_not==""){
        QMessageBox::critical(this,"Hata!","Gerekli Alanları Doldurunuz !");
    }else{
        int kontrol=0;
        QSqlQuery query;
        query.prepare("select ogr_no,ders_kodu from notlar");
        query.exec();
        while(query.next()){
            QString no = query.value(0).toString();
            QString kod=query.value(1).toString();
            if(no==ogr_no && kod==ders_kodu){
                QMessageBox::information(this,"Hata !","Bu öğrenci üzerinde bu ders zaten tanımlı !");
                kontrol=1;
                break;
            }
        }
        if(kontrol==0){
            query.prepare("insert into notlar (ogr_no,ders_kodu,vize_not,final_not,gecme_notu) values (:ogrno,:derskod,:vize,:final,:gnot)");
            query.bindValue(":ogrno",ogr_no);
            query.bindValue(":derskod",ders_kodu);
            query.bindValue(":vize",vize_not);
            query.bindValue(":final",final_not);
            query.bindValue(":gnot",gecme_notu);
            query.exec();
        }

        notlari_yukle();
    }
}


void nott::on_tumOgrenciler_clicked(const QModelIndex &index)
{
    QString ogr_no;
    ogr_no = index.sibling(index.row(),0).data().toString();
    ui->ogr_no->setText(ogr_no);
}


void nott::on_tumDersler_clicked(const QModelIndex &index)
{
    QString ders_kodu;
    ders_kodu=index.sibling(index.row(),0).data().toString();
    ui->ders_kodu->setText(ders_kodu);
}

void nott::notlari_yukle()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from notlar");
    query.exec();
    model->setQuery(query);
    ui->tumOgrenciDers->setModel(model);
    ui->ders_kodu->clear();
    ui->ogr_no->clear();
    ui->vize_not->clear();
    ui->final_not->clear();
}

