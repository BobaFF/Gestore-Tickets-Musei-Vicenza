#include "cumulativoordinario.h"

cumulativoOrdinario::cumulativoOrdinario(QString id, unsigned int e, QString r, QDate d, Museo m[6]): cumulativo(id,e,r,d,m){};

int cumulativoOrdinario::calcolaPrezzo() const {
    return getPrezzoBase();
}

cumulativoOrdinario* cumulativoOrdinario::clone() const {
    return new cumulativoOrdinario(*this);
}
