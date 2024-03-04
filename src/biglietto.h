#ifndef BIGLIETTO_H
#define BIGLIETTO_H

#include <QString>
#include <QDate>

enum Museo {null, Basilica_Palladiana, Palazzo_Chiericati, Museo_Naturalistico, Teatro_Olimpico, Santa_Corona, Palazzo_Thiene};

int countMusei(Museo[6]);

Museo selectMuseo(Museo[6]);

QString MuseoToString(Museo);

class biglietto {
private:
    QString ID;
    unsigned int età;
    QString residenza;
    QDate data;
protected:
    int prezzo;
    virtual void setPrezzoBase() = 0;
public:
    void setID(QString);
    QString getID() const;

    void setEtà(unsigned int);
    unsigned int getEtà() const;

    void setResidenza(QString);
    QString getResidenza() const;

    void setData(QDate);
    QDate getData() const;

    int getPrezzoBase() const; //PREZZO DI PARTENZA

    virtual int calcolaPrezzo() const= 0; //CALCOLA IL PREZZO DEFINITIVO
    virtual biglietto* clone() const = 0;

    virtual ~biglietto();

    biglietto(QString, unsigned int, QString, QDate);

};

#endif // BIGLIETTO_H
