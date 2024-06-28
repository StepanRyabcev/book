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

    void onDataChanged(const QModelIndex&, const QModelIndex&);

    void on_load_clicked();

    void on_save_clicked();

    void on_earase_clicked(bool nowarning = false);

    void save_binary();

    void load_binary();

private:
    void on_get_out_data();
    void attemptosaveemptytable();
    bool losingdatawarning();
    QVector<Book> bookv;
    Ui::MainWindow *ui;
    int objnum = 0;
    bool changedbysubmit = false;
};
#endif // MAINWINDOW_H
