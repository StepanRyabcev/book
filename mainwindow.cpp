#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QStandardItemModel>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->get_out->setEnabled(false);
    ui->change->setEnabled(false);
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
    ui->change->setEnabled(true);
}


void MainWindow::on_get_out_clicked()
{
    QStandardItemModel* model=  new QStandardItemModel(1, 3);
    model->setItem(0, 0, new QStandardItem(book->getname()));
    model->setItem(0, 1, new QStandardItem(book->getgenre()));
    model->setItem(0, 2, new QStandardItem(QString::number(book->getstr())));
    ui->b_name_out->setText(book->getname());
    ui->b_genre_out->setText(book->getgenre());
    ui->b_str_out->setText(QString::number(book->getstr()));
    ui->tableView->setModel(model);
}


void MainWindow::on_change_clicked()
{
    QString name = ui->b_name->toPlainText();
    QString genre = ui->b_genre->toPlainText();
    int str = ui->b_str->value();
    if (name != "")
        book->changeName(name);
    if (genre != "")
        book->changeGenre(genre);
    if (str != 0)
        book->changeNumofpages(str);
}

