#ifndef ARBORESCENCE_H
#define ARBORESCENCE_H

ArborescenceWindow::CoupleWindow(Relation* rela, QWidget *parent): QWidget(parent)
{

    setFixedSize(200, 400);
    move(400, 40);

    fenetre_vbox = new QVBoxLayout;

    titre_rela = new QLabel(rela->getTitre());

    couple_hbox = new QHBoxLayout;
    couple_label = new QLabel("label");
    couple = new QLineEdit;

    couple_hbox->addWidget(couple_label);
    couple_hbox->addWidget(couple);

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
    connect(button_create, SIGNAL(clicked(bool)), this, SLOT(save()));

    button_layout = new QHBoxLayout;
    button_layout->addWidget(button_create);
    button_layout->addWidget(button_close);

    fenetre_vbox->addWidget(titre_rela);
    fenetre_vbox->addLayout(couple_hbox);
    fenetre_vbox->addWidget(liste_x);
    fenetre_vbox->addWidget(liste_y);
    fenetre_vbox->addLayout(button_layout);


    this->setLayout(fenetre_vbox);

#endif // ARBORESCENCE_H
