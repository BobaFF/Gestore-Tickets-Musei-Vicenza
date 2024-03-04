#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    setWindowTitle("Musei Civici di Vicenza");
    resize(550, 400);
    setMinimumSize(550,400);
    widget = new QWidget(this);
    layout = new QVBoxLayout(widget);
    layout->setContentsMargins(50, 25, 50, 25);

    menuB = new QMenuBar();
    menuB->setGeometry(0, 0, 1271, 21);
    fileB = new QMenu("File", menuB);
    setMenuBar(menuB);

    apriA=new QAction("Apri",this);
    salvaA=new QAction("Salva",this);

    menuB->addAction(fileB->menuAction());
    fileB->addAction(apriA);
    fileB->addAction(salvaA);

    InserisciBigliettoB = new QPushButton ("Inserisci biglietto", widget);
    layout->addWidget(InserisciBigliettoB);

    ModificaBigliettoB = new QPushButton ("Modifica biglietto", widget);
    layout->addWidget(ModificaBigliettoB);

    RimuoviBigliettoB = new QPushButton("Elimina biglietti", widget);
    layout->addWidget(RimuoviBigliettoB);

    VisualizzaListaB = new QPushButton("Visualizza lista", widget);
    layout->addWidget(VisualizzaListaB);

    statistiche = new QGridLayout();;

    vendutiL = new QLabel ("Biglietti venduti:");
    vendutiL->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    statistiche->addWidget(vendutiL, 1, 1, Qt::AlignBottom | Qt::AlignHCenter);
    vendutiB = new QLineEdit();
    vendutiB->setReadOnly(true);
    vendutiB->setAlignment(Qt::AlignHCenter);
    statistiche->addWidget(vendutiB, 2, 1, Qt::AlignTop | Qt::AlignHCenter);

    singoloL = new QLabel ("Biglietti singoli:");
    statistiche->addWidget(singoloL, 3, 1, Qt::AlignBottom | Qt::AlignHCenter);
    singoloB = new QLineEdit();
    singoloB->setReadOnly(true);
    singoloB->setAlignment(Qt::AlignHCenter);
    statistiche->addWidget(singoloB, 4, 1, Qt::AlignTop | Qt::AlignHCenter);

    cumulativoL = new QLabel ("Biglietti cumulativi:");
    statistiche->addWidget(cumulativoL, 3, 2, Qt::AlignBottom | Qt::AlignCenter);
    cumulativoB = new QLineEdit();
    cumulativoB->setReadOnly(true);
    cumulativoB->setAlignment(Qt::AlignHCenter);
    statistiche->addWidget(cumulativoB, 4, 2, Qt::AlignTop | Qt::AlignCenter);

    museoL = new QLabel ("Museo più visitato:");
    statistiche->addWidget(museoL, 1, 2, Qt::AlignBottom | Qt::AlignCenter);
    museoB = new QLineEdit();
    museoB->setReadOnly(true);
    museoB->setAlignment(Qt::AlignHCenter);
    statistiche->addWidget(museoB, 2, 2, Qt::AlignTop | Qt::AlignCenter);

    guadagnoL = new QLabel ("Incasso totale:");
    guadagnoB = new QLineEdit();
    guadagnoB->setReadOnly(true);
    guadagnoB->setAlignment(Qt::AlignHCenter);

    EsciB = new QPushButton("Esci", widget);

    layout->addLayout(statistiche);
    layout->addWidget(guadagnoL, 0, Qt::AlignBottom | Qt::AlignCenter);
    layout->addWidget(guadagnoB, 0, Qt::AlignTop | Qt::AlignCenter);
    layout->addWidget(EsciB);

    slotAggiornaStatistiche();
    setCentralWidget(widget);

    //connects
    connect(InserisciBigliettoB, SIGNAL(clicked(bool)), this, SLOT(slotAggiungiB()));
    connect(ModificaBigliettoB, SIGNAL(clicked(bool)), this, SLOT(slotModificaB()));
    connect(VisualizzaListaB, SIGNAL(clicked(bool)), this, SLOT(slotVisualizzaL()));
    connect(RimuoviBigliettoB, SIGNAL(clicked(bool)), this, SLOT(slotEliminaB()));
    connect(apriA, SIGNAL(triggered(bool)), this, SLOT(slotApriFile()));
    connect(salvaA, SIGNAL(triggered(bool)), this, SLOT(slotSalva()));
    connect(EsciB, SIGNAL(clicked(bool)), this, SLOT(close()));
}

//slots
void MainWindow::slotAggiungiB() {
    aggiungiBW* aggBW = new aggiungiBW(&lista, this);
    aggBW->show();
    connect(aggBW, SIGNAL(sigAggiorna()), this, SLOT(slotAggiornaStatistiche()));
};


void MainWindow::slotVisualizzaL() {
    visualizzaLW* visLW = new visualizzaLW(&lista, this);
    visLW->show();
}

void MainWindow::slotModificaB() {
    modificaBW* modBW = new modificaBW(&lista, this);
    modBW->show();
    connect(modBW, SIGNAL(sigModifica()), this, SLOT(slotAggiornaStatistiche()));
}

void MainWindow::slotEliminaB() {
    eliminaBW* eliBW = new eliminaBW(&lista, this);
    eliBW->show();
    connect(eliBW, SIGNAL(sigModifica()), this, SLOT(slotAggiornaStatistiche()));
}

void MainWindow::slotAggiornaStatistiche() {
    vendutiB->setText(QString::number(lista.TotaleBigliettiEmessi()));
    museoB->setText(lista.museoPiuVisitato());
    guadagnoB->setText(QString::number(lista.guadagnoTotale())  + "€" );
    singoloB->setText(QString::number(lista.countSingolo()));
    cumulativoB->setText(QString::number(lista.countCumulativo()));
}


void MainWindow::slotApriFile() {
    QString nomeFile;
    nomeFile=QDir::currentPath()+ "/dati.xml";
    QFile file(nomeFile);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //Errore in apertura
        QMessageBox::critical(this, "Errore", "Impossibile aprire il file");
        return;
    }

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&file);
    xmlReader.readNext();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.isStartElement()) {

            QString id = "";
            int eta = 0;
            QString provincia = "";
            QDate data;

            if(xmlReader.name().toString() == "MuseiCivicidiVicenza")
                xmlReader.readNext();
            else if (xmlReader.name().toString() == "SingoloOrdinario" || xmlReader.name().toString() == "SingoloRidotto" || xmlReader.name().toString() == "CumulativoOrdinario" || xmlReader.name().toString() == "CumulativoRidotto") {
                Museo m = null;
                Museo mc[6] {null,null,null,null,null,null};
                bool ridotto = false;
                bool gratuito = false;
                bool cumulativo = false;
                int countM = 0;

                while (!xmlReader.atEnd()) {
                    if(xmlReader.isEndElement()) {
                        xmlReader.readNext();
                        if (ridotto && !cumulativo) {
                            singoloRidotto* b = new singoloRidotto(id,eta,provincia,data, m, gratuito);
                            lista.InserisciInTesta(b);
                        }
                        else if (ridotto && cumulativo) {
                            cumulativoRidotto* b = new cumulativoRidotto(id,eta,provincia,data, mc, gratuito);
                            lista.InserisciInTesta(b);
                        }
                        else if (!ridotto && cumulativo) {
                            cumulativoOrdinario* b = new cumulativoOrdinario(id,eta,provincia,data, mc);
                            lista.InserisciInTesta(b);
                        }
                        else {
                            singoloOrdinario* b = new singoloOrdinario(id,eta,provincia,data, m);
                            lista.InserisciInTesta(b);
                        }
                        break;
                    }
                    else if (xmlReader.isCharacters())
                        xmlReader.readNext();
                    else if (xmlReader.isStartElement()) {
                        if (xmlReader.name().toString() == "Museo") //caso biglietto singolo
                            m = Museo(xmlReader.readElementText().toInt());
                        else if (xmlReader.name().toString() == "Musei") { //caso biglietto cumulativo
                            cumulativo = true;
                            mc[countM] = Museo(xmlReader.readElementText().toInt());
                            countM ++;
                        }
                        else if (xmlReader.name().toString() == "Gratuito") {
                            ridotto = true;
                            gratuito = xmlReader.readElementText().toInt();
                        }
                        else if (xmlReader.name().toString() == "Id")
                            id = xmlReader.readElementText();
                        else if (xmlReader.name().toString() == "Età")
                            eta = xmlReader.readElementText().toInt();
                        else if (xmlReader.name().toString() == "Provincia")
                            provincia = xmlReader.readElementText();
                        else if (xmlReader.name().toString() == "Data")
                            data = QDate::fromString(xmlReader.readElementText(), "dd.MM.yyyy");
                        xmlReader.readNext();
                    }
                    else xmlReader.readNext();
                }


            }
        }
        else xmlReader.readNext();
    }
    file.close();
    slotAggiornaStatistiche();
    QMessageBox::information(this, "Apertura", "Lista caricata con successo");
}

void MainWindow::slotSalva()
{
    QString nomeFile;
    nomeFile=QDir::currentPath()+"/dati.xml";
    QFile file(nomeFile);
    if (file.open(QIODevice::WriteOnly))
        slotSalvaFile(file);

}

void MainWindow::slotSalvaFile(QFile& file) {
    QXmlStreamWriter xmlWriter;
    xmlWriter.setDevice(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("MuseiCivicidiVicenza");

    for (listaBiglietti::iterator i = lista.begin(); i!=lista.end(); ++i) {
            biglietto* b=lista[i];
            QString id = b->getID();
            int eta = b->getEtà();
            QString provincia = b->getResidenza();
            QDate data = b->getData();
            singolo* bs = dynamic_cast<singolo*> (b);
            cumulativo*bc = dynamic_cast<cumulativo*> (b);
            if (bs) {
                Museo m = bs->getMuseo();
                if (dynamic_cast<singoloOrdinario*> (b))
                    xmlWriter.writeStartElement("SingoloOrdinario");
                else {
                    xmlWriter.writeStartElement("SingoloRidotto");
                    bool gratuito = dynamic_cast<singoloRidotto*> (b)->isGratuito();
                    xmlWriter.writeTextElement("Gratuito",QString::number(gratuito));
                }
                //xmlWriter.writeTextElement("Museo:",MuseoToString(m));
                if (m == Basilica_Palladiana)
                    xmlWriter.writeTextElement("Museo", "1");
                else if (m == Palazzo_Chiericati)
                    xmlWriter.writeTextElement("Museo", "2");
                else if (m == Museo_Naturalistico)
                    xmlWriter.writeTextElement("Museo", "3");
                else if (m == Teatro_Olimpico)
                    xmlWriter.writeTextElement("Museo", "4");
                else if (m == Santa_Corona)
                    xmlWriter.writeTextElement("Museo", "5");
                else if (m == Palazzo_Thiene)
                    xmlWriter.writeTextElement("Museo", "6");
            }
            else if (bc) {
                if (dynamic_cast<cumulativoOrdinario*>(b))
                    xmlWriter.writeStartElement("CumulativoOrdinario");
                else {
                    xmlWriter.writeStartElement("CumulativoRidotto");
                    bool gratuito = dynamic_cast<cumulativoRidotto*> (b)->isGratuito();
                    xmlWriter.writeTextElement("Gratuito",QString::number(gratuito));
                }

                if (bc->presenzaMuseo(Basilica_Palladiana))
                    xmlWriter.writeTextElement("Musei", "1");
                if (bc->presenzaMuseo(Palazzo_Chiericati))
                    xmlWriter.writeTextElement("Musei", "2");
                if (bc->presenzaMuseo(Museo_Naturalistico))
                    xmlWriter.writeTextElement("Musei", "3");
                if (bc->presenzaMuseo(Teatro_Olimpico))
                    xmlWriter.writeTextElement("Musei", "4");
                if (bc->presenzaMuseo(Santa_Corona))
                    xmlWriter.writeTextElement("Musei", "5");
                if (bc->presenzaMuseo(Palazzo_Thiene))
                    xmlWriter.writeTextElement("Musei", "6");
            }
            xmlWriter.writeTextElement("Id",id);
            xmlWriter.writeTextElement("Età", QString::number(eta));
            xmlWriter.writeTextElement("Provincia", provincia);
            xmlWriter.writeTextElement("Data", data.toString("dd.MM.yyyy"));
            xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    QMessageBox::information(this, "Salvataggio", "Salvataggio effettuato su dati.xml");
}
