#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
    QString name, genre;
    int numofpages = 0;
public:
    Book();
    Book(QString, QString, int);
    Book(QString, int);
    Book(QString, QString);
    Book(QString);
    void changeGenre(QString);
    void changeNumofpages(int);
    void changeName(QString);
    void getFromKeyboard();
    QString getname()
    {
        return name;
    }
    QString getgenre()
    {
        return genre;
    }
    int getstr()
    {
        return numofpages;
    }

};

#endif // BOOK_H
