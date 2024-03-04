#ifndef SINGOLOORDINARIO_H
#define SINGOLOORDINARIO_H

#include "singolo.h"

class singoloOrdinario: public singolo{
public:
    singoloOrdinario(QString, unsigned int, QString, QDate, Museo);
    int calcolaPrezzo() const override final;
    singoloOrdinario* clone() const override final;
};

#endif // SINGOLOORDINARIO_H
