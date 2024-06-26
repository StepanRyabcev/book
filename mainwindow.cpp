#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->get_out->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submit_clicked()
{
    QString name = ui->b_name->toPlainText();
    QString genre = ui->b_genre->toPlainText();
    int str = ui->b_str->value();
    book = new Book(name, genre, str);
    ui->get_out->setEnabled(true);
}


void MainWindow::on_get_out_clicked()
{
    ui->b_name_out->setText(book->getname());
    ui->b_genre_out->setText(book->getgenre());
    ui->b_str_out->setText(QString::number(book->getstr()));
}

