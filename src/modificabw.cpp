#include "modificabw.h"

modificaBW::modificaBW(listaBiglietti* lista, QWidget *parent)
    : QDialog(parent), l(lista)
{
    setWindowTitle("Modifica biglietto");
    resize(400, 500);
    setMinimumWidth(400);
    setModal(true);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(50, 25, 50, 25);

    tipi = new QGridLayout();
    tipi->setContentsMargins(1, 0, 1, 0);

    erL = new QGridLayout();
    erL->setContentsMargins(1, 0, 1, 0);

    museiL = new QGridLayout();

    idL = new QLabel("ID");
    idL->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    idB = new QLineEdit();
    idB->setAlignment(Qt::AlignHCenter);

    etaL = new QLabel("Età");
    erL->addWidget(etaL, 1, 1, Qt::AlignBottom | Qt::AlignHCenter);

    etaB = new QSpinBox();
    erL->addWidget(etaB, 2, 1, Qt::AlignCenter | Qt::AlignHCenter);

    residenzaL = new QLabel("Residenza");
    erL->addWidget(residenzaL, 1, 2, Qt::AlignBottom | Qt::AlignHCenter);

    residenzaB = new QLineEdit();
    erL->addWidget(residenzaB, 2, 2, Qt::AlignCenter | Qt::AlignHCenter);

    dataL = new QLabel ("Data", this);
    erL->addWidget(dataL, 1, 3, Qt::AlignBottom|Qt::AlignHCenter);

    dataB = new QDateEdit(this);
    erL->addWidget(dataB, 2, 3, Qt::AlignHCenter|Qt::AlignCenter);

    prezzoL = new QLabel("Costo");
    tipi->addWidget(prezzoL, 1, 1, Qt::AlignBottom | Qt::AlignHCenter);

    prezzoB = new QLineEdit();
    tipi->addWidget(prezzoB, 2, 1, Qt::AlignHCenter|Qt::AlignCenter);
    prezzoB->setAlignment(Qt::AlignHCenter);
    prezzoB->setReadOnly(true);
    prezzoB->setText("0€");

    nMusei = new QLabel("Musei:");

    museo1 = new QCheckBox("Basilica Palladiana");
    museiL->addWidget(museo1, 1, 1, Qt::AlignLeft);

    museo2 = new QCheckBox("Palazzo Chiericati");
    museiL->addWidget(museo2, 1, 2, Qt::AlignLeft);

    museo3 = new QCheckBox("Museo Naturalistico");
    museiL->addWidget(museo3, 2, 1, Qt::AlignLeft);

    museo4 = new QCheckBox("Teatro Olimpico");
    museiL->addWidget(museo4, 2, 2, Qt::AlignLeft);

    museo5 = new QCheckBox("Santa Corona");
    museiL->addWidget(museo5, 3, 1, Qt::AlignLeft);

    museo6 = new QCheckBox("Palazzo Thiene");
    museiL->addWidget(museo6, 3, 2, Qt::AlignLeft);

    cumulativoW = new QWidget();
    cumulativoW->setLayout(museiL);
    cumulativoW->hide();

    singoloW = new QComboBox ();
    singoloW->addItem("Basilica Palladiana");
    singoloW->addItem("Palazzo Chiericati");
    singoloW->addItem("Museo Naturalistico");
    singoloW->addItem("Teatro Olimpico");
    singoloW->addItem("Santa Corona");
    singoloW->addItem("Palazzo Thiene");
    singoloW->setDisabled(true);

    modificaB = new QPushButton("Modifica dati biglietto");

    IndietroB = new QPushButton ("Indietro", this);

    layout->addWidget(idL);
    layout->addWidget(idB);
    layout->addLayout(erL);
    layout->addWidget(nMusei, 0,  Qt::AlignHCenter | Qt::AlignBottom);
    layout->addWidget(cumulativoW);
    layout->addWidget(singoloW);
    layout->addLayout(tipi);
    layout->addWidget(modificaB);
    layout->addWidget(IndietroB);

    connect(idB, SIGNAL(editingFinished()), this, SLOT(slotAggiornaDati()));
    connect(modificaB, SIGNAL(clicked(bool)), this, SLOT(slotModificaDati()));
    connect(IndietroB, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void modificaBW::slotAggiornaDati() {
    biglietto* b = l->trovaBiglietto(idB->text());
    singoloW->show();
    singoloW->setDisabled(true);
    cumulativoW->hide();
    if (b) {
        museo1->setChecked(false);
        museo2->setChecked(false);
        museo3->setChecked(false);
        museo4->setChecked(false);
        museo5->setChecked(false);
        museo6->setChecked(false);

        etaB->setValue(b->getEtà());
        residenzaB->setText(b->getResidenza());
        dataB->setDate(b->getData());
        prezzoB->setText(QString::number(b->calcolaPrezzo()) + "€");
        singolo* bo = dynamic_cast<singolo*>(b);
        if (bo) {
            singoloW->setCurrentIndex(0);
            singoloW->setDisabled(false);
            Museo museo = bo->getMuseo();
            switch(museo){
                case Basilica_Palladiana:
                singoloW->setCurrentIndex(0);
                break;
            case Palazzo_Chiericati:
                singoloW->setCurrentIndex(1);
                break;
            case Museo_Naturalistico:
                singoloW->setCurrentIndex(2);
                break;
            case Teatro_Olimpico:
                singoloW->setCurrentIndex(3);
                break;
            case Santa_Corona:
                singoloW->setCurrentIndex(4);
                break;
            default:
                singoloW->setCurrentIndex(5);
                break;
            }
        }
        else {
            singoloW->hide();
            cumulativoW->show();
            cumulativo* bc = dynamic_cast<cumulativo*> (b);
            if (bc->presenzaMuseo(Basilica_Palladiana))
                museo1->setChecked(true);
            if (bc->presenzaMuseo(Palazzo_Chiericati))
                museo2->setChecked(true);
            if (bc->presenzaMuseo(Museo_Naturalistico))
                museo3->setChecked(true);
            if (bc->presenzaMuseo(Teatro_Olimpico))
                museo4->setChecked(true);
            if (bc->presenzaMuseo(Santa_Corona))
                museo5->setChecked(true);
            if (bc->presenzaMuseo(Palazzo_Thiene))
                museo6->setChecked(true);
        }
    }
}

void modificaBW::slotModificaDati() {
    biglietto* b = l->trovaBiglietto(idB->text());
    if (b) {
        b->setEtà(etaB->value());
        b->setData(dataB->date());
        b->setResidenza(residenzaB->text());
        modificaMusei(b);
        prezzoB->setText(QString::number(b->calcolaPrezzo()) + "€");
        emit sigModifica();
    }
    else
        QMessageBox::critical(this, "Modifica Biglietto", "Biglietto non trovato");
}

void modificaBW::modificaMusei(biglietto* b) {
    singolo* bs = dynamic_cast<singolo*> (b);
    cumulativo* bc = dynamic_cast<cumulativo*> (b);
    if(bs) {
        Museo m;
        if (singoloW->currentIndex() == 0)
            m = Basilica_Palladiana;
        else if (singoloW->currentIndex() == 1)
            m = Palazzo_Chiericati;
        else if (singoloW->currentIndex() == 2)
            m = Museo_Naturalistico;
        else if (singoloW->currentIndex() == 3)
            m = Teatro_Olimpico;
        else if (singoloW->currentIndex() == 4)
            m = Santa_Corona;
        else
            m = Palazzo_Thiene;
        bs->setMuseo(m);
        QMessageBox::information(this, "Modifica Biglietto", "Biglietto modificato con successo");
    }
    else if (bc) {
        Museo musei[6] = {null, null, null, null, null, null};
        if (museo1->isChecked())
            musei[0] = Basilica_Palladiana;
        if (museo2->isChecked())
            musei[1] = Palazzo_Chiericati;
        if (museo3->isChecked())
            musei[2] = Museo_Naturalistico;
        if (museo4->isChecked())
            musei[3] = Teatro_Olimpico;
        if (museo5->isChecked())
            musei[4] = Santa_Corona;
        if (museo6->isChecked())
            musei[5] = Palazzo_Thiene;
        int i = countMusei(musei);
        if (i <= 1) {
            QMessageBox::critical(this, "Errore", "Biglietto cumulativo: selezionare almeno due musei");
            return;
        }
        else
            bc->setMusei(musei);
        QMessageBox::information(this, "Modifica Biglietto", "Biglietto modificato con successo");
    }

}
