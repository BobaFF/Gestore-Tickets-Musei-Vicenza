#ifndef AGGIUNGIBW_H
#define AGGIUNGIBW_H
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include "listabiglietti.h"
#include "singoloordinario.h"
#include "singoloridotto.h"
#include "cumulativoordinario.h"
#include "cumulativoridotto.h"
class aggiungiBW : public QDialog
{
    Q_OBJECT
private:
   QVBoxLayout* layout;
   QGridLayout* gridER;
   QHBoxLayout* tipi;
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
   QRadioButton* ordinarioB;
   QRadioButton* ridottoB;
   QRadioButton* gratuitoB;
   QLabel* nMusei;
   QCheckBox* museo1;
   QCheckBox* museo2;
   QCheckBox* museo3;
   QCheckBox* museo4;
   QCheckBox* museo5;
   QCheckBox* museo6;
   QPushButton* inserisciB;
   QLabel* costoL;
   QLineEdit* costoB;
   QPushButton* IndietroB;
   listaBiglietti* l;
public:
    explicit aggiungiBW(listaBiglietti*, QWidget *parent = nullptr);

private slots:
    void aggiungiBiglietto();
signals:
    void sigAggiorna();
};

#endif // AGGIUNGIBW_H
