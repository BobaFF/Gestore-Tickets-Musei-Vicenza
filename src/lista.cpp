#include "lista.h"

visualizzaLW::visualizzaLW(listaBiglietti* lista, QWidget* parent): QDialog(parent), l(lista)
{
    setWindowTitle("Lista biglietti");
    resize(720, 480);
    setModal(true);
    vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(50, 25, 50, 25);


    listaB = new QPlainTextEdit(this);
    listaB ->setReadOnly(true);
    visualizzaL();

    IndietroB = new QPushButton ("Indietro", this);

    vlayout->addWidget(listaB);
    vlayout->addWidget(IndietroB);

    connect(IndietroB, SIGNAL(clicked(bool)), this, SLOT(close()));

}

void visualizzaLW::visualizzaL() {
    if (l->isEmpty())
        listaB->appendPlainText("Lista vuota!");
    else {
        for(listaBiglietti::iterator it = l->begin(); it != l->end(); ++it) {
            biglietto* b = (*l)[it];
            QString biglietto = "●ID: " + b->getID();
            QString EPD = "Età: " + QString::number(b->getEtà()) + " | Residenza: " + b->getResidenza() + " | Data: " + QString::number(b->getData().day())+'/'+QString::number(b->getData().month())+'/'+QString::number(b->getData().year());
            QString prezzo = " | Prezzo: " + QString::number(b->calcolaPrezzo()) + "€";
            singolo* bs = dynamic_cast <singolo*> (b);
            if (bs) {
                biglietto = biglietto+ " | Tipo: singolo | "  + EPD +  " | Museo: " + MuseoToString(bs->getMuseo()) + prezzo;
            }
            else {
                cumulativo* bc = dynamic_cast<cumulativo*> (b);
                biglietto = biglietto + " | Tipo: cumulativo | "  + EPD + " | Musei: ";
                if (bc->presenzaMuseo(Basilica_Palladiana))
                    biglietto = biglietto + MuseoToString(Basilica_Palladiana) + ", ";
                if (bc->presenzaMuseo(Palazzo_Chiericati))
                    biglietto = biglietto + MuseoToString(Palazzo_Chiericati) + ", ";
                if (bc->presenzaMuseo(Museo_Naturalistico))
                    biglietto = biglietto + MuseoToString(Museo_Naturalistico) + ", ";
                if (bc->presenzaMuseo(Teatro_Olimpico))
                    biglietto = biglietto + MuseoToString(Teatro_Olimpico) + ", ";
                if (bc->presenzaMuseo(Santa_Corona))
                    biglietto = biglietto + MuseoToString(Santa_Corona) + ", ";
                if (bc->presenzaMuseo(Palazzo_Thiene))
                    biglietto = biglietto + MuseoToString(Palazzo_Thiene) + ", ";
                biglietto += prezzo;
            }
            listaB->appendPlainText(biglietto);
        }
    }
}
