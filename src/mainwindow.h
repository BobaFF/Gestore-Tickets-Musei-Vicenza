#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include <QAction>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QApplication>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QDir>
#include "aggiungibw.h"
#include "lista.h"
#include "modificabw.h"
#include "eliminabw.h"
#include "listabiglietti.h"


class MainWindow: public QMainWindow{
        Q_OBJECT
private:
        listaBiglietti lista;

        QMenuBar* menuB;
        QMenu* fileB;

        QAction* apriA;
        QAction* salvaA;


        QPushButton* InserisciBigliettoB;
        QPushButton* RimuoviBigliettoB;
        QPushButton* ModificaBigliettoB;
        QPushButton* VisualizzaListaB;

        QLabel* vendutiL;
        QLineEdit* vendutiB;
        QLabel* guadagnoL;
        QLineEdit* guadagnoB;
        QLabel* singoloL;
        QLineEdit* singoloB;
        QLabel* cumulativoL;
        QLineEdit* cumulativoB;
        QLabel* museoL;
        QLineEdit* museoB;
        QPushButton* EsciB;
        QWidget* widget;
        QGridLayout* statistiche;
        QVBoxLayout* layout;

private slots:
        void slotAggiungiB();
        void slotVisualizzaL();
        void slotModificaB();
        void slotEliminaB();
        void slotApriFile();
        void slotSalva();
        void slotSalvaFile(QFile&);
public slots:
        void slotAggiornaStatistiche();

public:
    MainWindow(QWidget* parent = nullptr);
};

#endif // MAINWINDOW_H
