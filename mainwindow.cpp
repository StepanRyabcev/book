#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QStandardItemModel>
#include <QTableView>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Book");
    QObject::connect(ui->load_2, &QAction::triggered, this, MainWindow::on_load_clicked);
    QObject::connect(ui->save_2, &QAction::triggered, this, MainWindow::on_save_clicked);
    QObject::connect(ui->clear, &QAction::triggered, this, MainWindow::on_earase_clicked);
    QObject::connect(ui->save_binary, &QAction::triggered, this, MainWindow::save_binary);
    QObject::connect(ui->load_binary, &QAction::triggered, this, MainWindow::load_binary);
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
    if (name != "")
    {
        bookv.push_back(Book(name, genre, str));
        on_get_out_data();
        ui->b_name->clear();
        ui->b_genre->clear();
        ui->b_str->setValue(0);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Название книги не может быть пустым");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    changedbysubmit = false;
}

void MainWindow::on_get_out_data()
{
    delete model;
    model= new QStandardItemModel(bookv.size(), 3);
    connect(model, &QStandardItemModel::dataChanged, this, &MainWindow::onDataChanged);
    for (int i = 0; i < bookv.size(); i++)
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
            else
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Предупреждение");
                msgBox.setText("Вы действительно хотите удалить данную строку");
                msgBox.setInformativeText("Вы хотите продолжить?");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::No);
                QPushButton *buttonY = qobject_cast<QPushButton *>(msgBox.button(QMessageBox::Yes));
                buttonY->setText("Да");
                QPushButton *buttonN = qobject_cast<QPushButton *>(msgBox.button(QMessageBox::No));
                buttonN->setText("Нет");
                msgBox.setIcon(QMessageBox::Question);
                if (msgBox.exec() == QMessageBox::Yes)
                {
                    bookv.remove(bottomRight.row());
                    if (bookv.empty())
                        on_earase_clicked();
                }
                else
                on_get_out_data();
            }
        }
        if (topLeft.column() == 1)
            bookv[bottomRight.row()].changeGenre(topLeft.data().toString());
        if (topLeft.column() == 2)
            bookv[bottomRight.row()].changeNumofpages(topLeft.data().toInt());
    }
}

void MainWindow::on_load_clicked()
{
    bool cont = true;
    if (!bookv.isEmpty())
        cont = losingdatawarning();
    if (cont)
    {
        QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("csv File(*.csv)"));
        QFile file(fileName);
        QString data;
        QStringList rowOfData;
        QStringList rowData;

    if (file.open(QFile::ReadOnly))
    {
        on_earase_clicked(true);
        data = file.readAll();
        rowOfData = data.split("\n");
        file.close();
    for (int x = 0; x < rowOfData.size(); x++)
    {
        Book a;
        rowData = rowOfData.at(x).split(";");
        if (rowData.size() >= 3)
        {
        a.changeName(rowData[0]);
        a.changeGenre(rowData[1]);
        a.changeNumofpages(rowData[2].toInt());
        bookv.push_back(a);
        }
    }
    if (bookv.empty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Возникла ошибка при загрузке файла");
        msgBox.setInformativeText("Вы уверены что это корректный файл списка книг?");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else
    on_get_out_data();
    }
    }
}

void MainWindow::on_save_clicked()
{
    if (!bookv.empty())
    {
    QString fileName = QFileDialog::getSaveFileName(this, ("Open File"), "/home", ("csv File(*.csv)"));
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream write(&file);
        for (int i = 0; i < bookv.size(); i++)
        {
            write << bookv[i].getname() << ";" << bookv[i].getgenre() << ";" << QString::number(bookv[i].getstr());
            if (i + 1 != bookv.size())
                write << "\n";
        }
        file.close();
    }
    }
    else
        attemptosaveemptytable();
}

void MainWindow::on_earase_clicked(bool nowarning)
{
    if (bookv.size() != 0)
    {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Предупреждение");
    msgBox.setText("Очистка таблицы приведёт к потере существующих данных");
    msgBox.setInformativeText("Вы хотите продолжить?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    QPushButton *buttonY = qobject_cast<QPushButton *>(msgBox.button(QMessageBox::Yes));
    buttonY->setText("Да");
    QPushButton *buttonN = qobject_cast<QPushButton *>(msgBox.button(QMessageBox::No));
    buttonN->setText("Нет");
    msgBox.setIcon(QMessageBox::Question);
    if (nowarning or (msgBox.exec() == QMessageBox::Yes))
    {
        bookv.clear();
        delete model;
        ui->tableView->setModel(nullptr);
    }
    }
    else
    {
        delete model;
        ui->tableView->setModel(nullptr);
    }
}

void MainWindow::save_binary()
{
    if (!bookv.empty())
    {
    QString fileName = QFileDialog::getSaveFileName(this, ("Open File"), "/home", ("Binary File(*.bin)"));
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        for (int i = 0; i < bookv.size(); i++)
        {
            stream << bookv[i].getname() << bookv[i].getgenre() << bookv[i].getstr();
        }
        file.close();
    }
    }
    else
        attemptosaveemptytable();
}

void MainWindow::load_binary()
{
    bool cont = true;
    if (!bookv.isEmpty())
        cont = losingdatawarning();
    if (cont)
    {
        QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("Binary File(*.bin)"));
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly))
        {
            on_earase_clicked(true);
            QDataStream stream(&file);
            QString name, genre;
            int str;
            while(!stream.atEnd())
            {
                stream >> name >> genre >> str;
                Book a(name, genre, str);
                bookv.push_back(a);
            }
            file.close();
            on_get_out_data();
        }
    }
}

void MainWindow::attemptosaveemptytable()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Внимание");
    msgBox.setText("Таблица пуста");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
}

bool MainWindow::losingdatawarning()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Предупреждение");
    msgBox.setText("Загрузка таблицы приведёт к потере существующих данных");
    msgBox.setInformativeText("Вы хотите продолжить?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    QPushButton *buttonY = qobject_cast<QPushButton *>(msgBox.button(QMessageBox::Yes));
    buttonY->setText("Да");
    QPushButton *buttonN = qobject_cast<QPushButton *>(msgBox.button(QMessageBox::No));
    buttonN->setText("Нет");
    msgBox.setIcon(QMessageBox::Question);
    if (msgBox.exec() == QMessageBox::No)
        return false;
    return true;
}
