#include "explorateurWindow.h"
#include "Notes.h"
#include <typeinfo>
#include <QDebug>
#include <QMessageBox>

ExplorateurWindow::ExplorateurWindow(QWidget *parent): QWidget(parent)
{

    setFixedSize(200, 400);
    move(0, 40);

    fenetre_vbox = new QVBoxLayout;

    titre = new QLabel("toutes les notes");

    liste = new QListWidget;

    NotesManager& NM = NotesManager::donneInstance();

    for( NotesManager::Iterator it = NM.getIterator() ; !it.isdone() ; it++){
        if((*it)->etatToString()=="active"){
            liste->addItem((*it)->getTitre());
            tab_id.append((*it)->getId());
        }
    }


    button_open = new QPushButton("versions");
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

    setFixedSize(200, 400);
    move(0, 40);

    fenetre_vbox = new QVBoxLayout;

    titre = new QLabel("Agenda des Taches");

    liste = new QListWidget;

    NotesManager& NM = NotesManager::donneInstance();

    if( i == 0 )
    {

        QList<int> tab_prio;
        QList<QDateTime> tab_date;

        for( NotesManager::Iterator it = NM.getIterator() ; !it.isdone() ; it++){
            if(typeid(*(*it))==typeid(Tache) && (*it)->etatToString()=="active"){
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
    }
    else if(i == 1)
    {
        for( NotesManager::Iterator it = NM.getIterator() ; !it.isdone() ; it++){
            if((*it)->etatToString()=="archive"){
                liste->addItem((*it)->getTitre());
                tab_id.append((*it)->getId());
            }
        }

    }
    else if(i == 2)
    {

        for( NotesManager::Iterator it = NM.getIterator() ; !it.isdone() ; it++){
            if((*it)->etatToString()=="corbeille"){
                liste->addItem((*it)->getTitre());
                tab_id.append((*it)->getId());
            }
        }

    }


    button_open = new QPushButton("versions");
    button_close = new QPushButton("fermer");
    connect(button_close, SIGNAL(clicked(bool)), this, SLOT(close()));

    button_layout = new QHBoxLayout;
    if(i != 1)
        button_layout->addWidget(button_open);

    button_layout->addWidget(button_close);

    fenetre_vbox->addWidget(titre);
    fenetre_vbox->addWidget(liste);
    fenetre_vbox->addLayout(button_layout);


    this->setLayout(fenetre_vbox);
}

ExplorateurWindow::ExplorateurWindow(Note& note, QWidget *parent): QWidget(parent)
{

    setFixedSize(200, 400);
    move(0, 40);

    fenetre_vbox = new QVBoxLayout;

    NoteId = note.getId();
    titre = new QLabel("Memento de "+note.getId()+" : \""+note.getTitre()+"\"\nCréation : "+note.getDateCrea().toString("dd/MM/yyyy hh:mm:ss"));

    liste = new QListWidget;


    for( Gardien::Iterator i = note.getGardien()->getIterator(); !i.isdone() ; i++)
        liste->addItem((*i)->getDateModif().toString("dd/MM/yyyy hh:mm:ss"));


    button_open = new QPushButton("restaurer");
    button_close = new QPushButton("fermer");
    connect(button_close, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(button_open, SIGNAL(clicked(bool)), this, SLOT(restaurerVersion()));

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



void ExplorateurWindow::restaurerVersion(){
    NotesManager& NM = NotesManager::donneInstance();
    Note& note = NM.getNote(NoteId);
    NM.saveVersion(&note);
    qDebug() << "llala";
    NM.restateVersion(&note, QDateTime::fromString(liste->currentItem()->text(),"dd/MM/yyyy hh:mm:ss"));
    qDebug() << "llola";
    QMessageBox::information(this, "Bravo", "Restauration Réussie !");

}










