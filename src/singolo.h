#ifndef SINGOLO_H
#define SINGOLO_H

#include "biglietto.h"

class singolo: public biglietto {
private:
    Museo museo;
    void setPrezzoBase() override final;
public:
    void setMuseo(Museo);
    Museo getMuseo() const;
    singolo(QString, unsigned int, QString, QDate, Museo);
};

#endif // SINGOLO_H
