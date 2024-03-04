#ifndef LISTABIGLIETTI_H
#define LISTABIGLIETTI_H

#include "biglietto.h"

class listaBiglietti{
    friend class iterator;
private:
    class nodo;

    class smartp {
    public:
        nodo* punt;
        smartp(nodo* = 0);
        smartp(const smartp&);
        ~smartp();
        smartp& operator=(const smartp&);
        nodo& operator*() const;
        nodo* operator->() const;
        bool operator==(const smartp&) const;
        bool operator!=(const smartp&) const;
    };

    class nodo {
    public:
        nodo();
        nodo(biglietto*, const smartp&);
        biglietto* info;
        smartp next;
        int riferimenti;
        ~nodo();
    };

    smartp first;

public:

    class iterator {
        friend class listaBiglietti;
    private:
        listaBiglietti::nodo* punt;
    public:
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        iterator& operator++(); //++ prefisso
        iterator operator++(int); //++ postfisso
    };

    iterator begin() const;
    iterator end() const;
    biglietto* operator[] (const iterator&) const;

    //metodi di listaBiglietti
    listaBiglietti(): first(0) {};
    bool isEmpty() const;
    void svuota();
    void InserisciInTesta(biglietto*);
    biglietto* RimuoviDaTesta();
    void InserisciInCoda(biglietto*);
    biglietto* RimuoviDaCoda();
    int TotaleBigliettiEmessi() const;
    int countSingolo() const;
    int countCumulativo() const;
    biglietto* trovaBiglietto(QString) const;
    biglietto* rimuoviBiglietto(QString);
    int guadagnoTotale() const;
    int visiteMuseo(const Museo&) const;
    QString museoPiuVisitato() const;



};

#endif // LISTABIGLIETTI_H
