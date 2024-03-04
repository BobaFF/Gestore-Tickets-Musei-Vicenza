#ifndef CUMULATIVO_H
#define CUMULATIVO_H

#include "biglietto.h"

#include <vector>

class cumulativo: public biglietto{
private:
    std::vector<Museo> musei;
    void setPrezzoBase() override final;
public:
    cumulativo(QString, unsigned int, QString, QDate, Museo [6]);
    void setMusei(Museo [6]);
    int Numero_musei() const;
    bool presenzaMuseo(Museo) const;
};

#endif // CUMULATIVO_H
