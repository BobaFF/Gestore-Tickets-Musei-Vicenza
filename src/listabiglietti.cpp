#include "listabiglietti.h"
#include "cumulativo.h"
#include "singolo.h"

//class smartp
listaBiglietti::smartp::smartp(nodo* p): punt(p) {
    if (punt)
        punt->riferimenti ++;
}

listaBiglietti::smartp::smartp(const smartp& s) : punt(s.punt) {
    if (punt)
        punt->riferimenti++;
}

listaBiglietti::smartp::~smartp() {
    if (punt) {
        punt->riferimenti--;
        if(punt->riferimenti == 0)
            delete punt;
    }
}

listaBiglietti::smartp& listaBiglietti::smartp::operator=(const smartp& s){
    if (this!=&s) {
        nodo* t=punt;
        punt=s.punt;
        if (punt) punt->riferimenti++;
        if (t) {
            t->riferimenti--;
            if (t->riferimenti==0)
                delete t;
        }
    }
    return *this;
}

listaBiglietti::nodo& listaBiglietti::smartp::operator*() const {
    return *punt;
}

listaBiglietti::nodo* listaBiglietti::smartp::operator->() const {
    return punt;
}

bool listaBiglietti::smartp::operator==(const smartp& s) const {
    return punt==s.punt;
}

bool listaBiglietti::smartp::operator!=(const smartp& s) const {
    return punt!=s.punt;
}


//class nodo
listaBiglietti::nodo::nodo(): riferimenti(0) {}

listaBiglietti::nodo::nodo(biglietto* b, const smartp& p): info(b), next(p), riferimenti(0) {}

listaBiglietti::nodo::~nodo() {
    delete info;
}

//class iterator

bool listaBiglietti::iterator::operator==(const iterator& i) const {
    return punt == i.punt;
}

bool listaBiglietti::iterator::operator!=(const iterator& i) const {
    return punt != i.punt;
}

listaBiglietti::iterator& listaBiglietti::iterator::operator++() {
    if (punt)
        punt = (*punt).next.punt;
    return *this;
}

listaBiglietti::iterator listaBiglietti::iterator::operator++(int) {
    iterator aux = *this;
    if (punt)
        punt = (*punt).next.punt;
    return aux;
}

//metodi iterator

listaBiglietti::iterator listaBiglietti::begin() const {
    iterator aux;
    aux.punt = first.punt;
    return aux;
}
listaBiglietti::iterator listaBiglietti::end() const {
    iterator aux;
    aux.punt =  0;
    return aux;
}

biglietto* listaBiglietti::operator[] (const iterator& it) const {
    return (it.punt)->info;
}


//metodi lista

bool listaBiglietti::isEmpty() const {
    return first == 0;
}

void listaBiglietti::svuota() {
    delete first.punt;
    first.punt = 0;
}

void listaBiglietti::InserisciInTesta(biglietto* b) {
    first = new nodo (b, first);
}

void listaBiglietti::InserisciInCoda(biglietto* b) {
    if (first == 0)
        first = new nodo (b,0);
    else {
        smartp p = first;
        while (p->next != 0)
            p = p->next;
        p->next = new nodo(b, 0);
    }
}

int listaBiglietti::TotaleBigliettiEmessi() const {
    int count = 0;
    for (listaBiglietti::iterator it = begin(); it != end(); ++it)
        count ++;
    return count;
}

int listaBiglietti::countSingolo() const {
    int count = 0;
    if(!isEmpty()) {
        for (listaBiglietti::iterator it = begin(); it!= end(); ++it) {
            if (dynamic_cast<singolo*> (it.punt->info))
                count++;
        }
    }
    return count;
}

int listaBiglietti::countCumulativo() const {
    int count = 0;
    if(!isEmpty()) {
        for (listaBiglietti::iterator it = begin(); it!= end(); ++it) {
            if (dynamic_cast<cumulativo*> (it.punt->info))
                count++;
        }
    }
    return count;
}


biglietto* listaBiglietti::trovaBiglietto(QString b) const{
    for (listaBiglietti::iterator it = begin(); it!= end(); ++it) {
        if (it.punt->info->getID() == b)
            return it.punt->info;
    }
    return 0;
}

biglietto* listaBiglietti::RimuoviDaTesta() {
    if (first==0)
        return 0;
    biglietto* b=first->info->clone();
    first=first->next;
    return b;
}

biglietto* listaBiglietti::RimuoviDaCoda() {
    if (first == 0)
        return 0;
    if (first->next == 0) {
        biglietto* b = first->info->clone();
        first = 0;
        return b;
    }
    smartp p = first;
    smartp prec = 0;
    while (p->next!= 0) {
        prec = p;
        p = p->next;
    }
    biglietto*  b = p->info->clone();
    prec->next = 0;
    return b;
}

biglietto* listaBiglietti::rimuoviBiglietto(QString s) {
    smartp p = first, prec, q;
    smartp primo = first;
    biglietto* b = 0;
    first = 0;
    while(p!=0 && !(p->info->getID() == s)) {
        q = new nodo(p->info, p->next);
        if (prec == 0)
            first = q;
        else
            prec->next = q;
        prec = q;
        p = p->next;
    }
    if (p==0)
        first = primo;
    else
        if (prec == 0) {
            b = primo->info->clone();
            first = p->next;
        }
        else {
            b = p->info->clone();
            prec->next = p->next;
        }
    return b;
}

int listaBiglietti::guadagnoTotale() const {
    int guadagno = 0;
    if (isEmpty())
        return 0;
    for (listaBiglietti::iterator it = begin(); it!= end(); ++it)
        guadagno += it.punt->info->calcolaPrezzo();
    return guadagno;
}

int listaBiglietti::visiteMuseo(const Museo& m) const{
    int count = 0;
    if(isEmpty())
        return 0;
    for (listaBiglietti::iterator it = begin(); it != end(); ++it) {
        singolo* s = dynamic_cast<singolo*>(it.punt->info);
        cumulativo* c = dynamic_cast<cumulativo*> (it.punt->info);
        if (!c && s && (s->getMuseo() == m))
            count++;
        else if (c && !s && c->presenzaMuseo(m))
            count++;
    }
    return count;
}

QString listaBiglietti::museoPiuVisitato() const {
    int Musei[7] = {0,0,0,0,0,0,0};
    int max = 0;
    for (int i = 1; i<=6; ++i) {
        Musei[i] = visiteMuseo(Museo(i));
        if (Musei[i] > Musei[max])
            max = i;
    }
    return MuseoToString(Museo(max));
}


