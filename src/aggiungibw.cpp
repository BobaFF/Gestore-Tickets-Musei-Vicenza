#include "aggiungibw.h"

aggiungiBW::aggiungiBW(listaBiglietti* lista, QWidget *parent)
    : QDialog(parent), l(lista)
{
    setWindowTitle("Inserisci biglietto");
    resize(400, 500);
    setMinimumSize(400,500);
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(50, 25, 50, 25);
    setModal(true);


    gridER = new QGridLayout();
    gridER->setContentsMargins(1, 25, 1, 0);

    tipi = new QHBoxLayout();
    tipi->setContentsMargins(1, 0, 1, 0);

    museiL = new QGridLayout();

    idL = new QLabel ("ID", this);
    layout->addWidget(idL, 0, Qt::AlignBottom|Qt::AlignCenter);

    idB = new QLineEdit (this);
    layout->addWidget(idB);

    etaL = new QLabel ("Età", this);
    gridER->addWidget(etaL, 1, 1, Qt::AlignHCenter| Qt::AlignBottom);

    etaB = new QSpinBox(this);
    gridER->addWidget(etaB, 2, 1, Qt::AlignHCenter| Qt::AlignBottom);
    etaB->setRange(0, 100);
    etaB->setValue(18);

    residenzaL = new QLabel ("Residenza", this);
    gridER->addWidget(residenzaL, 1, 2, Qt::AlignHCenter|Qt::AlignBottom);

    residenzaB = new QLineEdit(this);
    gridER->addWidget(residenzaB, 2, 2, Qt::AlignHCenter| Qt::AlignBottom);

    dataL = new QLabel ("Data", this);
    gridER->addWidget(dataL, 1, 3, Qt::AlignHCenter|Qt::AlignBottom);

    dataB = new QDateEdit(this);
    dataB->setDate(QDate::currentDate());
    gridER->addWidget(dataB, 2, 3, Qt::AlignHCenter|Qt::AlignCenter);

    ordinarioB = new QRadioButton("Ordinario");
    tipi->addWidget(ordinarioB, 0, Qt::AlignCenter);
    ordinarioB->setChecked(true);

    ridottoB = new QRadioButton("Ridotto");
    tipi->addWidget(ridottoB, 0, Qt::AlignCenter);

    gratuitoB = new QRadioButton("Gratuito");
    tipi->addWidget(gratuitoB, 0, Qt::AlignCenter);


    nMusei = new QLabel("Musei");

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

    inserisciB = new QPushButton("Inserisci biglietto");

    costoL = new QLabel("Costo biglietto");

    costoB = new QLineEdit(this);
    costoB->setAlignment(Qt::AlignHCenter);
    costoB->setReadOnly(true);


    IndietroB = new QPushButton ("Indietro", this);

    layout->addLayout(gridER);
    layout->addLayout(tipi);
    layout->addWidget(nMusei, 0, Qt::AlignBottom | Qt::AlignHCenter);
    layout->addLayout(museiL);
    layout->addWidget(costoL, 0 , Qt::AlignBottom |Qt::AlignHCenter);
    layout->addWidget(costoB);
    layout->addWidget(inserisciB);
    layout->addWidget(IndietroB);


    connect(IndietroB, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(inserisciB, SIGNAL(clicked(bool)), this, SLOT(aggiungiBiglietto()));
}

void aggiungiBW::aggiungiBiglietto() {
    QString id = idB->text();

    if (id == "")
        QMessageBox::critical(this, "Errore", "Inserire un ID");
    else {
        unsigned int eta = etaB->value();
        QDate data = dataB->date();
        QString provincia = residenzaB->text().toUpper();
        biglietto* b;
        bool gratuito = gratuitoB->isChecked();

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
        Museo museosingolo = selectMuseo(musei);

        if (i == 0)
            QMessageBox::critical(this, "Errore", "Selezionare almeno un museo");
        else  {
            if (i == 1) {
                if(eta>3 && ordinarioB->isChecked())
                    b = new singoloOrdinario(id, eta, provincia, data, museosingolo);
                else
                    b = new singoloRidotto(id, eta, provincia, data, museosingolo, gratuito);
            }
            else {
                if (eta>3 && ordinarioB->isChecked() && (provincia != "VI"))
                    b = new cumulativoOrdinario(id,eta, provincia, data, musei);
                else
                    b = new cumulativoRidotto(id,eta,provincia, data, musei, gratuito);
            }
        costoB->setText(QString::number(b->calcolaPrezzo()) + "€");
        l->InserisciInTesta(b);
        QMessageBox::information(this, "Inserimento", "Biglietto inserito nella lista!");
        emit sigAggiorna();
        }
    }
}
