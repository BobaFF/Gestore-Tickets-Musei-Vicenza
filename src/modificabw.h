#ifndef MODIFICABW_H
#define MODIFICABW_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QComboBox>
#include "listabiglietti.h"
#include "singoloordinario.h"
#include "singoloridotto.h"
#include "cumulativoordinario.h"
#include "cumulativoridotto.h"

class modificaBW : public QDialog
{
    Q_OBJECT
private:
   QVBoxLayout* layout;
   QGridLayout* tipi;
   QGridLayout* erL;
   QGridLayout* museiL;

   QLabel* idL;
   QLineEdit* idB;
   QLabel* etaL;
   QSpinBox* etaB;
   QLabel* residenzaL;
   QLineEdit* residenzaB;
   QLabel* dataL;
   QDateEdit* dataB;
   QLabel* tipoBL;
   QLineEdit* tipoB;
   QLabel* prezzoL;
   QLineEdit* prezzoB;
   QLabel* nMusei;
   QCheckBox* museo1;
   QCheckBox* museo2;
   QCheckBox* museo3;
   QCheckBox* museo4;
   QCheckBox* museo5;
   QCheckBox* museo6;
   QWidget* cumulativoW;
   QComboBox* singoloW;
   QPushButton* inserisciB;
   QLabel* costoL;
   QLineEdit* costoB;
   QPushButton* modificaB;
   QPushButton* eliminaB;
   QPushButton* IndietroB;
   listaBiglietti* l;
   void modificaMusei(biglietto*);
public:
    explicit modificaBW(listaBiglietti*, QWidget *parent = nullptr);

public slots:
    void slotAggiornaDati();
    void slotModificaDati();

signals:
    void sigModifica();
};

#endif // MODIFICABW_H

