#include "notewindow.h"
#include "mainwindow.h"

#include <QErrorMessage>


/// Créateur de Notes - MainWindow::ouvrir_fenetre()

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

    button_hbox = new QHBoxLayout;
    create_button = new QPushButton("create");
    close_button = new QPushButton("close");
    connect(close_button, SIGNAL(clicked(bool)), this, SLOT(close()));

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    type_hbox->addWidget(type_label); type_hbox->addWidget(type);
    button_hbox->addWidget(create_button); button_hbox->addWidget(close_button);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(type_hbox);
    fenetre_vbox->addLayout(button_hbox);


    this->setLayout(fenetre_vbox);

}




/// Editeur d'Articles

// Constructeur ID + TITLE - MainWindow::create()

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

    button_hbox = new QHBoxLayout;
    save_button = new QPushButton("save");
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));
    close_button = new QPushButton("close");
    connect(close_button, SIGNAL(clicked(bool)), this, SLOT(close()));

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    text_hbox->addWidget(text_label); text_hbox->addWidget(text);
    button_hbox->addWidget(save_button); button_hbox->addWidget(close_button);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(text_hbox);
    fenetre_vbox->addLayout(button_hbox);


    this->setLayout(fenetre_vbox);

}




/// Editeur Multimédia

// Constructeur ID + TITLE - MainWindow::create()

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
    connect(fichier, SIGNAL(clicked(bool)), this, SLOT(trouveFichier()));

    button_hbox = new QHBoxLayout;
    save_button = new QPushButton("save");
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));
    close_button = new QPushButton("close");
    connect(close_button, SIGNAL(clicked(bool)), this, SLOT(close()));

    printed_path = new QLabel("C:\\....\\fichier.xxx");
    path = "";

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    description_hbox->addWidget(description_label); description_hbox->addWidget(description);
    fichier_hbox->addWidget(fichier_type); fichier_hbox->addWidget(fichier);
    button_hbox->addWidget(save_button); button_hbox->addWidget(close_button);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(description_hbox);
    fenetre_vbox->addLayout(fichier_hbox);
    fenetre_vbox->addWidget(printed_path);
    fenetre_vbox->addLayout(button_hbox);


    this->setLayout(fenetre_vbox);

}

void MultimediaWindow::trouveFichier(){
    QFileDialog* qfd = new QFileDialog;
    path = qfd->getOpenFileName();
    printed_path->setText("C:/  ...  "+path.right(20));
}



/// Editeur de Taches

// Constructeur ID + TITLE - MainWindow::create()
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
    priorite->setMaximumWidth(20);
    priorite->setValidator( new QIntValidator(0, 5, this) );

    echeance_hbox = new QHBoxLayout;
    echeance_label = new QLabel("Date");
    echeance = new QDateTimeEdit;

    statut_hbox = new QHBoxLayout;
    statut_label = new QLabel("Statut");
    statut = new QComboBox;
    statut->addItem("En Atente");
    statut->addItem("En Cours");
    statut->addItem("Terminé");

    button_hbox = new QHBoxLayout;
    save_button = new QPushButton("save");
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));
    close_button = new QPushButton("close");
    connect(close_button, SIGNAL(clicked(bool)), this, SLOT(close()));


    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    action_hbox->addWidget(action_label); action_hbox->addWidget(action);
    priorite_hbox->addWidget(priorite_label); priorite_hbox->addWidget(priorite);
    echeance_hbox->addWidget(echeance_label); echeance_hbox->addWidget(echeance);
    statut_hbox->addWidget(statut_label); statut_hbox->addWidget(statut);
    button_hbox->addWidget(save_button); button_hbox->addWidget(close_button);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(action_hbox);
    fenetre_vbox->addLayout(priorite_hbox);
    fenetre_vbox->addLayout(echeance_hbox);
    fenetre_vbox->addLayout(button_hbox);


    this->setLayout(fenetre_vbox);

}


/// Saves

// Save article

void ArticleWindow::save(){

    if(this->getTitle() != "" && this->getText() != "")
    {
        /// Enregistrer note, faire appel à note manager ?
    }
    else
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("Entrez le Titre et du Texte ");
    }

}

// Save tache

void TacheWindow::save(){

    if(this->getTitle() != "" && this->getAction() != "")
    {
        /// Enregistrer note, faire appel à note manager ?
    }
    else
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("Entrez le Titre et une Action");
    }

}

// Save multimedia

void MultimediaWindow::save(){

    if(this->getTitle() != "" && this->getDescription() != "" && this->path != "")
    {
        /// Enregistrer note, faire appel à note manager ?
    }
    else
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("Entrez le Titre, un Fichier et une Description ");
    }

}







