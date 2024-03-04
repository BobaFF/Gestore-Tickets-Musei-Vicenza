#ifndef CUMULATIVORIDOTTO_H
#define CUMULATIVORIDOTTO_H

#include "cumulativo.h"

class cumulativoRidotto: public cumulativo{
private:
    bool gratuito;
    static int RiduzioneResidenti;
    static int RiduzioneStandard;
public:
    cumulativoRidotto(QString, unsigned int, QString, QDate, Museo [6], bool);
    bool isGratuito() const;
    void setGratuito(bool);
    int calcolaPrezzo() const override final;
    cumulativoRidotto* clone() const override final;

};

#endif // CUMULATIVORIDOTTO_H
