#include "cumulativoridotto.h"

int cumulativoRidotto::RiduzioneResidenti = 6;
int cumulativoRidotto::RiduzioneStandard = 3;

cumulativoRidotto::cumulativoRidotto(QString id, unsigned int e, QString r, QDate d, Museo m[6], bool g): cumulativo(id,e,r,d,m), gratuito (g){};

bool cumulativoRidotto::isGratuito() const {
    return gratuito;
}

void cumulativoRidotto::setGratuito(bool g) {
    gratuito = g;
}

int cumulativoRidotto::calcolaPrezzo() const {
    if (getEtà() <= 3 || isGratuito())
        return 0;
    else if (getResidenza() == "VI")
        return getPrezzoBase() - RiduzioneResidenti;
    else return getPrezzoBase() - RiduzioneStandard;
}

cumulativoRidotto* cumulativoRidotto::clone() const {
    return new cumulativoRidotto(*this);
}
