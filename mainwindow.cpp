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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submit_clicked()
{
    changedbysubmit = true;
    QString name = ui->b_name->toPlainText();
    QString genre = ui->b_genre->toPlainText();
    int str = ui->b_str->value();
    ui->b_name->clear();
    ui->b_genre->clear();
    ui->b_str->setValue(0);
    if (name != "")
    {
        bookv.push_back(Book(name, genre, str));
        objnum++;
        on_get_out_data();
    }
    changedbysubmit = false;
}


void MainWindow::on_get_out_data()
{
    QStandardItemModel* model=  new QStandardItemModel(objnum, 3);
    connect(model, &QStandardItemModel::dataChanged, this, &MainWindow::onDataChanged);
    for (int i = 0; i < objnum; i++)
    {
        model->setItem(i, 0, new QStandardItem(bookv[i].getname()));
        model->setItem(i, 1, new QStandardItem(bookv[i].getgenre()));
        if (bookv[i].getstr() != 0)
            model->setItem(i, 2, new QStandardItem(QString::number(bookv[i].getstr())));
    }
    model->setHeaderData(0, Qt::Horizontal, "Название");
        model->setHeaderData(1, Qt::Horizontal, "Жанр");
        model->setHeaderData(2, Qt::Horizontal, "Страницы");
        ui->tableView->setModel(model);
}

void MainWindow::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    if (changedbysubmit == false)
    {
        if (topLeft.column() == 0)
        {
            QString name = topLeft.data().toString();
            if (name != "")
                bookv[bottomRight.row()].changeName(name);
        }
        if (topLeft.column() == 1)
            bookv[bottomRight.row()].changeGenre(topLeft.data().toString());
        if (topLeft.column() == 2)
            bookv[bottomRight.row()].changeNumofpages(topLeft.data().toInt());
    }
}
