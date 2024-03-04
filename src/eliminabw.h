#ifndef ELIMINABW_H
#define ELIMINABW_H
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDateEdit>
#include <QLineEdit>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QComboBox>
#include "QPlainTextEdit"
#include "listabiglietti.h"
#include "singolo.h"
#include "cumulativo.h"
class eliminaBW : public QDialog
{
    Q_OBJECT
private:
   QVBoxLayout* layout;
   QGridLayout* tipi;
   QGridLayout* erL;
   QHBoxLayout* tcB;

   QLabel* idL;
   QLineEdit* idB;
   QRadioButton* testa;
   QRadioButton* coda;
   QPushButton* eliminaTCB;
   QLabel* etaL;
   QSpinBox* etaB;
   QLabel* residenzaL;
   QLineEdit* residenzaB;
   QLabel* dataL;
   QDateEdit* dataB;
   QLabel* ultimoBL;
   QLabel* prezzoL;
   QLineEdit* prezzoB;
   QLabel* nMusei;
   QLineEdit* singoloW;
   QPlainTextEdit* cumulativoW;

   QPushButton* inserisciB;
   QLabel* costoL;
   QLineEdit* costoB;
   QPushButton* modificaB;
   QPushButton* eliminaB;
   QPushButton* svuotaB;
   QPushButton* IndietroB;
   listaBiglietti* l;

   void aggiornaUltimo(biglietto*);
public:
    explicit eliminaBW(listaBiglietti*, QWidget *parent = nullptr);

private slots:
    void slotEliminaB();
    void slotEliminaTC();
    void slotSvuotaL();
signals:
    void sigModifica();
};

#endif // ELIMINABW_H
