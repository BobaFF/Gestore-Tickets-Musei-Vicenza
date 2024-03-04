#ifndef RIMUOVIBW_H
#define RIMUOVIBW_H
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include "listabiglietti.h"
#include <singolo.h>
#include <cumulativo.h>

class visualizzaLW: public QDialog
{
private:
    listaBiglietti* l;
    QVBoxLayout* vlayout;
    QPlainTextEdit* listaB;
    QPushButton* IndietroB;
    void visualizzaL();
public:
    visualizzaLW(listaBiglietti*, QWidget* parent = nullptr);
};

#endif // RIMUOVIBW_H
