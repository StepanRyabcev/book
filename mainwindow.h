#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "book.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_submit_clicked();

    void on_get_out_clicked();

    void on_change_clicked();

private:
    QVector<Book> bookv;
    Ui::MainWindow *ui;
    int objnum = 0;
};
#endif // MAINWINDOW_H
