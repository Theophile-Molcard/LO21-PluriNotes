#include "explorateurWindow.h"
#include "Notes.h"
#include <typeinfo>
#include <QDebug>

ExplorateurWindow::ExplorateurWindow(QWidget *parent): QWidget(parent)
{

    setFixedSize(200, 400);
    move(0, 40);

    fenetre_vbox = new QVBoxLayout;

    titre = new QLabel("toutes les notes");

    liste = new QListWidget;

    NotesManager& NM = NotesManager::donneInstance();

    for( NotesManager::Iterator it = NM.getIterator() ; !it.isdone() ; it++){
        liste->addItem((*it)->getTitre());
        tab_id.append((*it)->getId());
    }


    button_open = new QPushButton("à définir...");
    button_close = new QPushButton("fermer");
    connect(button_close, SIGNAL(clicked(bool)), this, SLOT(close()));

    button_layout = new QHBoxLayout;
    button_layout->addWidget(button_open);
    button_layout->addWidget(button_close);

    fenetre_vbox->addWidget(titre);
    fenetre_vbox->addWidget(liste);
    fenetre_vbox->addLayout(button_layout);


    this->setLayout(fenetre_vbox);
}


ExplorateurWindow::ExplorateurWindow(int i, QWidget *parent): QWidget(parent)
{
    i++; //ne sert à riennnnn

    setFixedSize(200, 400);
    move(0, 40);

    fenetre_vbox = new QVBoxLayout;

    titre = new QLabel("toutes les notes");

    liste = new QListWidget;

    NotesManager& NM = NotesManager::donneInstance();

    QList<int> tab_prio;
    QList<QDateTime> tab_date;

    for( NotesManager::Iterator it = NM.getIterator() ; !it.isdone() ; it++){
        if(typeid(*(*it))==typeid(Tache)){
            if(dynamic_cast<Tache*>(*it)->getDateEcheance() > QDateTime::currentDateTime()){
                tab_id.append((*it)->getId());
                tab_date.append(dynamic_cast<Tache*>(*it)->getDateEcheance());
                tab_prio.append(dynamic_cast<Tache*>(*it)->getPriorite());
            }
        }
    }

    sortByPrioDate(tab_id, tab_date, tab_prio);

    for(int i = 0; i < tab_id.size() ; i++)
        liste->addItem(NM.getNote(tab_id[i]).getTitre());


    button_open = new QPushButton("à définir...");
    button_close = new QPushButton("fermer");
    connect(button_close, SIGNAL(clicked(bool)), this, SLOT(close()));

    button_layout = new QHBoxLayout;
    button_layout->addWidget(button_open);
    button_layout->addWidget(button_close);

    fenetre_vbox->addWidget(titre);
    fenetre_vbox->addWidget(liste);
    fenetre_vbox->addLayout(button_layout);


    this->setLayout(fenetre_vbox);
}

void sortByPrioDate(QList<QString>& id, QList<QDateTime> date, QList<int> prio){ // tri non max opti mais pas grave

    QString temp;
    QDateTime temp_d;
    int temp_p, max;

    for( int i = 0; i < id.size() ; i++ ){
        max = i;
        for(int j = 0 ; j < id.size() ; j++){
            if(prio[j]<prio[max])
                max = j;
            else if(prio[j]==prio[max] && date[j] > date[max]){
                qDebug()<<"Comparaison de dates";
                max = j;
            }
        }
        temp = id[i];
        id[i] = id[max];
        id[max] = temp;

        temp_p = prio[i];
        prio[i] = prio[max];
        prio[max] = temp_p;

        temp_d = date[i];
        date[i] = date[max];
        date[max] = temp_d;

    }


}














