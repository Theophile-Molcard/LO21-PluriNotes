#include "notewindow.h"
#include "mainwindow.h"

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

    create_button = new QPushButton("créer");
    connect(create_button, SIGNAL(clicked(bool)), this, SLOT(create()));

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    type_hbox->addWidget(type_label); type_hbox->addWidget(type);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(type_hbox);
    fenetre_vbox->addWidget(create_button);


    this->setLayout(fenetre_vbox);

}

void NoteWindow::editeur_article(){

    ArticleWindow* a_w = new ArticleWindow(id->text(), title->text(), this);
    MainWindow *fenetre_principale;
    fenetre_principale->setCentralWidget(a_w);

}


ArticleWindow::ArticleWindow(QString _id, QString _title, QWidget *parent) : QWidget(parent)
{


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
