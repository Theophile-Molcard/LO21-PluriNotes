#include "notewindow.h"

NoteWindow::NoteWindow(QWidget *parent) : QWidget(parent)
{

    fenetre_vbox = new QVBoxLayout;

    id_hbox = new QHBoxLayout;
    id_label = new QLabel("Identifiant");
    id = new QLineEdit;

    title_hbox = new QHBoxLayout;
    title_label = new QLabel("Titre");
    title = new QLineEdit;

    type_hbox = new QHBoxLayout;
    type_label = new QLabel("Type");
    type = new QComboBox;

    type->addItem("Tache");
    type->addItem("Article");
    type->addItem("Multimedia");

    create = new QPushButton("créer");

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    type_hbox->addWidget(type_label); type_hbox->addWidget(type);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(type_hbox);
    fenetre_vbox->addWidget(create);

    this->setLayout(fenetre_vbox);


}
