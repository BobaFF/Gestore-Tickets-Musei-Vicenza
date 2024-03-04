#include "singoloridotto.h"

int singoloRidotto::Riduzione = 2;

singoloRidotto::singoloRidotto(QString id, unsigned int e, QString r, QDate d, Museo m, bool g): singolo(id,e,r,d,m), gratuito(g){}

bool singoloRidotto::isGratuito() const {
    return gratuito;
}

void singoloRidotto::setGratuito(bool g) {
    gratuito = g;
}
int singoloRidotto::calcolaPrezzo() const {
    if ((getEtà() <= 3) || gratuito == 1)
        return 0;
    else
        return getPrezzoBase() - Riduzione;
}

singoloRidotto* singoloRidotto::clone() const {
    return new singoloRidotto(*this);
}
