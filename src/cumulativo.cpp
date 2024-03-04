#include "cumulativo.h"

static int musei_4 = 15;
static int musei_6 = 20;

cumulativo::cumulativo(QString id, unsigned int e, QString r, QDate d, Museo m[6]): biglietto(id,e,r,d) {
    bool check = 1;
    for (auto i = 0; i< 6; ++i) {
        if (m[i] != null)
            musei.push_back(m[i]);
        for (auto j = i; j>0; --j) {
            if ((m[j] == m[j-1]) && m[j] != null)
                check = 0;
        }
    }
    if (check==0)
        musei.clear();
    else
        setPrezzoBase();
}

void cumulativo::setMusei(Museo m[6]) {
    musei.clear();
    bool check = 1;
    for (auto i = 0; i< 6; ++i) {
        if (m[i] != null)
            musei.push_back(m[i]);
        for (auto j = i; j>0; --j) {
            if ((m[j] == m[j-1]) && m[j] != null)
                check = 0;
        }
    }
    if(check==0)
        musei.clear();
    else setPrezzoBase();
}

int cumulativo::Numero_musei() const {
    int count = 0;
    for (auto i = musei.begin(); i!= musei.end(); ++i)
        count++;
    return count;
}

void cumulativo::setPrezzoBase() {
    if (Numero_musei() <= 4)
        prezzo = musei_4;
    else prezzo = musei_6;
}

bool cumulativo::presenzaMuseo(Museo m) const {
    for (auto it = 0; it!= int(musei.size()); ++it) {
        if (musei[it] == m)
            return true;
    }
    return false;
}
