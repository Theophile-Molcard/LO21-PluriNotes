#include "explorateurWindow.h"
#include "Notes.h"

ExplorateurWindow::ExplorateurWindow(QWidget *parent){

    setFixedSize(200, 400);
    move(0, 40);

    fenetre_vbox = new QVBoxLayout;

    titre = new QLabel("toutes les notes");

    liste = new QListView;
    //liste->addAction("blabla");
    //liste->addAction("blibli");

    button_open = new QPushButton("ouvrir");
    button_close = new QPushButton("fermer");

    button_layout = new QHBoxLayout;
    button_layout->addWidget(button_open);
    button_layout->addWidget(button_close);

    fenetre_vbox->addWidget(titre);
    fenetre_vbox->addWidget(liste);
    fenetre_vbox->addLayout(button_layout);


    this->setLayout(fenetre_vbox);
}
