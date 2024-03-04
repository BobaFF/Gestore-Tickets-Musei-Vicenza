#include "eliminabw.h"

eliminaBW::eliminaBW(listaBiglietti* lista, QWidget *parent)
    : QDialog(parent), l(lista)
{
    setWindowTitle("Elimina biglietti");
    resize(400, 500);
    setMinimumSize(400,500);
    setModal(true);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(50, 25, 50, 25);

    tipi = new QGridLayout();
    tipi->setContentsMargins(1, 0, 1, 0);

    erL = new QGridLayout();
    erL->setContentsMargins(1, 0, 1, 0);

    tcB = new QHBoxLayout();
    tcB->setContentsMargins(1,15,1,0);

    idL = new QLabel("ID");
    idL->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    idB = new QLineEdit();
    idB->setAlignment(Qt::AlignHCenter);

    testa = new QRadioButton("testa");
    testa->setChecked(true);
    tcB->addWidget(testa, 0, Qt::AlignCenter);

    coda = new QRadioButton("coda");
    tcB->addWidget(coda, 0, Qt::AlignCenter);

    eliminaTCB = new QPushButton("Elimina da testa/coda");
    eliminaTCB->setContentsMargins(0,0,0,20);

    ultimoBL = new QLabel("Ultimo biglietto rimosso:");
    ultimoBL->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    etaL = new QLabel("Età");
    erL->addWidget(etaL, 1, 1, Qt::AlignBottom | Qt::AlignHCenter);

    etaB = new QSpinBox();
    etaB->setReadOnly(true);
    erL->addWidget(etaB, 2, 1, Qt::AlignCenter | Qt::AlignHCenter);

    residenzaL = new QLabel("Residenza");
    erL->addWidget(residenzaL, 1, 2, Qt::AlignBottom | Qt::AlignHCenter);

    residenzaB = new QLineEdit();
    residenzaB->setReadOnly(true);
    erL->addWidget(residenzaB, 2, 2, Qt::AlignCenter | Qt::AlignHCenter);

    dataL = new QLabel ("Data", this);
    erL->addWidget(dataL, 1, 3, Qt::AlignBottom|Qt::AlignHCenter);

    dataB = new QDateEdit(this);
    dataB->setReadOnly(true);
    erL->addWidget(dataB, 2, 3, Qt::AlignHCenter|Qt::AlignCenter);

    prezzoL = new QLabel("Costo");
    tipi->addWidget(prezzoL, 1, 1, Qt::AlignBottom | Qt::AlignHCenter);

    prezzoB = new QLineEdit();
    prezzoB->setReadOnly(true);
    tipi->addWidget(prezzoB, 2, 1, Qt::AlignHCenter|Qt::AlignCenter);
    prezzoB->setAlignment(Qt::AlignHCenter);
    prezzoB->setReadOnly(true);
    prezzoB->setText("0€");

    nMusei = new QLabel("Musei:");

    singoloW = new QLineEdit();
    singoloW->setAlignment(Qt::AlignCenter);
    singoloW->setReadOnly(true);
    singoloW->setFixedWidth(140);
    cumulativoW = new QPlainTextEdit();
    cumulativoW->setReadOnly(true);
    cumulativoW->hide();
    cumulativoW->setFixedWidth(150);

    eliminaB = new QPushButton("Elimina biglietto da id");

    svuotaB = new QPushButton("Svuota lista");

    IndietroB = new QPushButton ("Indietro", this);

    layout->addWidget(idL);
    layout->addWidget(idB);
    layout->addWidget(eliminaB);
    layout->addLayout(tcB);
    layout->addWidget(eliminaTCB);
    layout->addWidget(ultimoBL);
    layout->addLayout(erL);
    layout->addWidget(nMusei, 0, Qt::AlignBottom | Qt::AlignHCenter);

    layout->addWidget(singoloW, 0 , Qt::AlignHCenter);
    layout->addWidget(cumulativoW, 0 , Qt::AlignHCenter);
    layout->addLayout(tipi);
    layout->addWidget(svuotaB);
    layout->addWidget(IndietroB);

    connect(eliminaB, SIGNAL(clicked(bool)), this, SLOT(slotEliminaB()));
    connect(IndietroB, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(eliminaTCB, SIGNAL(clicked(bool)), this, SLOT(slotEliminaTC()));
    connect(svuotaB, SIGNAL(clicked(bool)), this, SLOT(slotSvuotaL()));
}

void eliminaBW::slotEliminaB() {
    biglietto* b = l->trovaBiglietto(idB->text());
    if (b) {
        biglietto* bo = l->rimuoviBiglietto(idB->text());
        aggiornaUltimo(bo);

        QMessageBox::information(this, "Elimina Biglietto", "Biglietto con ID:" + bo->getID() + " eliminato");
        emit sigModifica();
    }
    else QMessageBox::critical(this, "Modifica Biglietto", "Biglietto non trovato");
}

void eliminaBW::slotEliminaTC() {
    if (!l->isEmpty()) {
        biglietto* b;
        if (testa->isChecked())
            b = l->RimuoviDaTesta();
        else
            b = l->RimuoviDaCoda();
        aggiornaUltimo(b);
        QMessageBox::information(this, "Elimina Biglietto", "Biglietto con ID:" + b->getID() + " eliminato");
        emit sigModifica();
    }
    else
        QMessageBox::critical(this, "Modifica Biglietto", "Impossibile eliminare: lista vuota!");
}

void eliminaBW::aggiornaUltimo(biglietto* b) {
    etaB->setValue(b->getEtà());
    residenzaB->setText(b->getResidenza());
    dataB->setDate(b->getData());
    prezzoB->setText(QString::number(b->calcolaPrezzo()) + "€");

    singolo* bs = dynamic_cast<singolo*> (b);
    if (bs) {
        cumulativoW->hide();
        singoloW->show();
        singoloW->setText(MuseoToString(bs->getMuseo()));
    }
    else {
        singoloW->hide();
        cumulativoW->show();
        cumulativoW->clear();
        cumulativo* bc = dynamic_cast<cumulativo*> (b);
        if (bc->presenzaMuseo(Basilica_Palladiana))
            cumulativoW->appendPlainText("●Basilica Palladiana");
        if (bc->presenzaMuseo(Palazzo_Chiericati))
            cumulativoW->appendPlainText("●Palazzo Chiericati");
        if (bc->presenzaMuseo(Museo_Naturalistico))
            cumulativoW->appendPlainText("●Museo Naturalistico");
        if (bc->presenzaMuseo(Teatro_Olimpico))
            cumulativoW->appendPlainText("●Teatro Olimpico");
        if (bc->presenzaMuseo(Santa_Corona))
            cumulativoW->appendPlainText("●Santa Corona");
        if (bc->presenzaMuseo(Palazzo_Thiene))
            cumulativoW->appendPlainText("●Palazzo Thiene");
    }

}

void eliminaBW::slotSvuotaL() {
    if (l->isEmpty() == 0) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Svuota lista", "Sei sicuro di voler svuotare la lista?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)  {
            l->svuota();
            QMessageBox::information(this, "Svuota lista", "Lista svuotata!");
            emit sigModifica();
        }
    }
    else
        QMessageBox::critical(this, "Errore", "Lista vuota!");
    return;
}
