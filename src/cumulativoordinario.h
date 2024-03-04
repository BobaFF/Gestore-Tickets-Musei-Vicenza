#ifndef CUMULATIVOORDINARIO_H
#define CUMULATIVOORDINARIO_H

#include "cumulativo.h"

class cumulativoOrdinario: public cumulativo{
public:
    cumulativoOrdinario(QString, unsigned int, QString, QDate, Museo [6]);
    int calcolaPrezzo() const override final;
    cumulativoOrdinario* clone() const override final;
};

#endif // CUMULATIVOORDINARIO_H
