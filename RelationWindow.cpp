#include "RelationWindow.h"
#include "Notes.h"
#include <typeinfo>
#include <QDebug>

CreationRelationWindow::CreationRelationWindow(QWidget *parent): QWidget(parent)
{

    setFixedSize(200, 400);
    move(400, 40);

    fenetre_vbox = new QVBoxLayout;

    titre_hbox = new QHBoxLayout;
    titre_label = new QLabel("titre");
    titre = new QLineEdit;

    titre_hbox->addWidget(titre_label);
    titre_hbox->addWidget(titre);

    description_hbox = new QHBoxLayout;
    description_label = new QLabel("Description");
    description = new QTextEdit;

    description_hbox->addWidget(description_label);
    description_hbox->addWidget(description);

    non_oriente = new QCheckBox("non orienté");

    liste_x = new QListWidget;

    NotesManager& NM = NotesManager::donneInstance();

    for( NotesManager::Iterator it1 = NM.getIterator() ; !it1.isdone() ; it1++){
        liste_x->addItem((*it1)->getTitre());
        tab_id_x.append((*it1)->getId());
    }

    liste_y = new QListWidget;

    for( NotesManager::Iterator it2 = NM.getIterator() ; !it2.isdone() ; it2++){
        liste_y->addItem((*it2)->getTitre());
        tab_id_y.append((*it2)->getId());
    }


    button_create = new QPushButton("créer");
    button_close = new QPushButton("fermer");
    connect(button_close, SIGNAL(clicked(bool)), this, SLOT(close()));


    button_layout = new QHBoxLayout;
    button_layout->addWidget(button_create);
    button_layout->addWidget(button_close);

    fenetre_vbox->addLayout(titre_hbox);
    fenetre_vbox->addLayout(description_hbox);
    fenetre_vbox->addWidget(non_oriente);
    fenetre_vbox->addWidget(liste_x);
    fenetre_vbox->addWidget(liste_y);
    fenetre_vbox->addLayout(button_layout);


    this->setLayout(fenetre_vbox);
}
