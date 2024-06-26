#include "book.h"

Book::Book()
{
    name = "";
    genre = "";
    numofpages = 0;
}
Book::Book(QString name1, QString genre1, int numofpages1)
{
    name = name1;
    genre = genre1;
    numofpages = numofpages1;
}
Book::Book(QString name1, int numofpages1)
{
    name = name1;
    numofpages = numofpages1;
}
Book::Book(QString name1, QString genre1)
{
    name = name1;
    genre = genre1;
}
Book::Book(QString name1)
{
    name = name1;
}
void Book::changeGenre(QString genre1)
{
    genre = genre1;
}
void Book::changeNumofpages(int a)
{
    if (a > 0)
        numofpages = a;
   // else
        //cout << "Число страниц не может быть не может быть меньше 0" << endl;
}
void Book::changeName(QString name1)
{
    name = name1;
}

