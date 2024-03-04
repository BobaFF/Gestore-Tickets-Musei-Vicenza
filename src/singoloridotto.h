#ifndef SINGOLORIDOTTO_H
#define SINGOLORIDOTTO_H

#include "singolo.h"

class singoloRidotto: public singolo{
private:
    bool gratuito;
    static int Riduzione;
public:
    singoloRidotto(QString, unsigned int, QString, QDate, Museo, bool);
    int calcolaPrezzo() const override final;
    bool isGratuito() const;
    void setGratuito(bool);
    singoloRidotto* clone() const override final;
};

#endif // SINGOLORIDOTTO_H
