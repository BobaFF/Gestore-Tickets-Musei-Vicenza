#include "biglietto.h"

int countMusei(Museo m[6]) {
    int count = 0;
    for (int i = 0; i<6; i++) {
        if (m[i] != null)
            count ++;
    }
    return count;
}

Museo selectMuseo(Museo m[6]) {
    int i = 0;
    while (m[i] == null)
        i++;
    return m[i];
};

QString MuseoToString(Museo m) {
switch (m) {
    case Basilica_Palladiana:
        return "Basilica Palladiana";
        break;
    case Palazzo_Chiericati:
        return "Palazzo Chiericati";
        break;
    case Palazzo_Thiene:
        return "Palazzo Thiene";
        break;
    case Teatro_Olimpico:
        return "Teatro Olimpico";
        break;
    case Museo_Naturalistico:
        return "Museo Naturalistico";
        break;
    case Santa_Corona:
        return "Santa Corona";
        break;
    default:
        return "Nessuna visita";
        break;
    }
}

biglietto::biglietto(QString id, unsigned int e, QString r, QDate d): ID(id), età(e), residenza(r), data(d)  {}

void biglietto::setID(QString s) {
    ID = s;
}

QString biglietto::getID() const {
    return ID;
}

void biglietto::setEtà(unsigned int e) {
    età = e;
}

unsigned int biglietto::getEtà() const {
    return età;
}

void biglietto::setResidenza(QString r){
    residenza = r;
}
QString biglietto::getResidenza() const {
    return residenza;
}

void biglietto::setData(QDate d) {
    data = d;
}
QDate biglietto::getData() const {
    return data;
}

int biglietto::getPrezzoBase() const {
    return prezzo;
}

biglietto::~biglietto() {

}
