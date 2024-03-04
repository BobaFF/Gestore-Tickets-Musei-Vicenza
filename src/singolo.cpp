#include "singolo.h"

singolo::singolo(QString id, unsigned int e, QString r, QDate d, Museo m): biglietto(id,e,r,d), museo(m){
    setPrezzoBase();
};

Museo singolo::getMuseo() const {
    return museo;
}

void singolo::setMuseo(Museo m) {
    museo = m;
    setPrezzoBase();
}

void singolo::setPrezzoBase() {
    switch (museo) {
    case Basilica_Palladiana:
        prezzo = 5;
        break;
    case Palazzo_Chiericati:
        prezzo = 9;
        break;
    case Palazzo_Thiene:
        prezzo = 7;
        break;
    case Teatro_Olimpico:
        prezzo = 12;
        break;
    default:
        prezzo = 4;
        break;
    }
}
