#include "singoloordinario.h"

singoloOrdinario::singoloOrdinario(QString id, unsigned int e, QString r, QDate d, Museo m): singolo(id,e,r,d,m) {}

int singoloOrdinario::calcolaPrezzo() const {
    return getPrezzoBase();
}

singoloOrdinario* singoloOrdinario::clone() const {
    return new singoloOrdinario(*this);
}
