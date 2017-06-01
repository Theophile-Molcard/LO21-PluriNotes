#include "notewindow.h"
#include "mainwindow.h"

NoteWindow::NoteWindow(QWidget *parent) : QWidget(parent)
{

    setFixedSize(200, 400);
    move(200, 40);

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

    create_button = new QPushButton("créer");

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    type_hbox->addWidget(type_label); type_hbox->addWidget(type);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(type_hbox);
    fenetre_vbox->addWidget(create_button);


    this->setLayout(fenetre_vbox);

}


ArticleWindow::ArticleWindow(QString _id, QString _title, QWidget *parent) : QWidget(parent)
{

    setFixedSize(200, 400);
    move(200, 40);


    fenetre_vbox = new QVBoxLayout;

    id_hbox = new QHBoxLayout;
    id_label = new QLabel("Identifiant");
    id = new QLabel(_id);

    title_hbox = new QHBoxLayout;
    title_label = new QLabel("Titre");
    title = new QLineEdit;
    title->setText(_title);

    text_hbox = new QHBoxLayout;
    text_label = new QLabel("Texte");
    text = new QTextEdit;


    save_button = new QPushButton("save");
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    text_hbox->addWidget(text_label); text_hbox->addWidget(text);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(text_hbox);
    fenetre_vbox->addWidget(save_button);


    this->setLayout(fenetre_vbox);

}



MultimediaWindow::MultimediaWindow(QString _id, QString _title, QWidget *parent) : QWidget(parent)
{

    setFixedSize(200, 400);
    move(200, 40);


    fenetre_vbox = new QVBoxLayout;

    id_hbox = new QHBoxLayout;
    id_label = new QLabel("Identifiant");
    id = new QLabel(_id);

    title_hbox = new QHBoxLayout;
    title_label = new QLabel("Titre");
    title = new QLineEdit;
    title->setText(_title);

    description_hbox = new QHBoxLayout;
    description_label = new QLabel("Description");
    description = new QTextEdit;

    fichier_hbox = new QHBoxLayout;
    fichier_type = new QComboBox;
    fichier_type->addItem("Image");
    fichier_type->addItem("Vidéo");
    fichier_type->addItem("Audio");
    fichier = new QPushButton("fichier");


    save_button = new QPushButton("save");
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    description_hbox->addWidget(description_label); description_hbox->addWidget(description);
    fichier_hbox->addWidget(fichier_type); fichier_hbox->addWidget(fichier);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(description_hbox);
    fenetre_vbox->addLayout(fichier_hbox);
    fenetre_vbox->addWidget(save_button);


    this->setLayout(fenetre_vbox);

}



TacheWindow::TacheWindow(QString _id, QString _title, QWidget *parent) : QWidget(parent)
{

    setFixedSize(200, 400);
    move(200, 40);


    fenetre_vbox = new QVBoxLayout;

    id_hbox = new QHBoxLayout;
    id_label = new QLabel("Identifiant");
    id = new QLabel(_id);

    title_hbox = new QHBoxLayout;
    title_label = new QLabel("Titre");
    title = new QLineEdit;
    title->setText(_title);

    action_hbox = new QHBoxLayout;
    action_label = new QLabel("Action");
    action = new QTextEdit;

    priorite_hbox = new QHBoxLayout;
    priorite_label = new QLabel("Priorité");
    priorite = new QLineEdit;

    echeance_hbox = new QHBoxLayout;
    echeance_label = new QLabel("Date");
    echeance = new QLineEdit;

    statut_hbox = new QHBoxLayout;
    statut_label = new QLabel("Statut");
    statut = new QComboBox;
    statut->addItem("En Atente");
    statut->addItem("En Cours");
    statut->addItem("Terminé");


    save_button = new QPushButton("save");
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    action_hbox->addWidget(action_label); action_hbox->addWidget(action);
    priorite_hbox->addWidget(priorite_label); priorite_hbox->addWidget(priorite);
    echeance_hbox->addWidget(echeance_label); echeance_hbox->addWidget(echeance);
    statut_hbox->addWidget(statut_label); statut_hbox->addWidget(statut);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(action_hbox);
    fenetre_vbox->addLayout(priorite_hbox);
    fenetre_vbox->addLayout(echeance_hbox);
    fenetre_vbox->addWidget(save_button);


    this->setLayout(fenetre_vbox);

}
