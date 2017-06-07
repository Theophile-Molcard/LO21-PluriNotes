#include "notewindow.h"
#include "mainwindow.h"

#include <QErrorMessage>
#include <QMessageBox>
#include <mainwindow.h>

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

ArticleWindow::ArticleWindow(Note &note, QWidget *parent) : QWidget(parent)
{
    Article& article_note = dynamic_cast<Article&>(note);

    setFixedSize(200, 400);
    move(200, 40);


    fenetre_vbox = new QVBoxLayout;

    id_hbox = new QHBoxLayout;
    id_label = new QLabel("Identifiant");
    id = new QLabel(article_note.getId());

    title_hbox = new QHBoxLayout;
    title_label = new QLabel("Titre");
    title = new QLineEdit;
    title->setText(article_note.getTitre());

    text_hbox = new QHBoxLayout;
    text_label = new QLabel("Texte");
    text = new QTextEdit;
    text->setText(article_note.getTexte());

    button_hbox = new QHBoxLayout;
    save_button = new QPushButton("save");
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));
    close_button = new QPushButton("close");
    connect(close_button, SIGNAL(clicked(bool)), this, SLOT(close()));
    delete_button = new QPushButton("delete");
    connect(delete_button, SIGNAL(clicked(bool)), this, SLOT(deleteArticle()));

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    text_hbox->addWidget(text_label); text_hbox->addWidget(text);
    button_hbox->addWidget(save_button); button_hbox->addWidget(close_button); button_hbox->addWidget(delete_button);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(text_hbox);
    fenetre_vbox->addLayout(button_hbox);

    if(article_note.etatToString() == "archive"){
        title->setEnabled(false);
        text->setEnabled(false);
        button_hbox->removeWidget(delete_button);

        save_button->setText("Restaurer");
        disconnect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));
        connect(save_button, SIGNAL(clicked(bool)), this, SLOT(restaureArchive()));
    }


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
    fichier_type->addItem("image");
    fichier_type->addItem("video");
    fichier_type->addItem("audio");
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
    path = QFileDialog::getOpenFileName();
    printed_path->setText("C:/  ...  "+path.right(20));
}

MultimediaWindow::MultimediaWindow(Note& note, QWidget *parent) : QWidget(parent)
{

    Multimedia& multi_note = dynamic_cast<Multimedia&>(note);


    setFixedSize(200, 400);
    move(200, 40);


    fenetre_vbox = new QVBoxLayout;

    id_hbox = new QHBoxLayout;
    id_label = new QLabel("Identifiant");
    id = new QLabel(multi_note.getId());

    title_hbox = new QHBoxLayout;
    title_label = new QLabel("Titre");
    title = new QLineEdit;
    title->setText(multi_note.getTitre());

    description_hbox = new QHBoxLayout;
    description_label = new QLabel("Description");
    description = new QTextEdit;
    description->setText(multi_note.getDescription());

    fichier_hbox = new QHBoxLayout;
    fichier_type = new QComboBox;
    fichier_type->addItem("image");
    fichier_type->addItem("video");
    fichier_type->addItem("audio");
    if(multi_note.typeToString()== "video")
        fichier_type->setCurrentIndex(1);
    if(multi_note.typeToString()== "audio")
        fichier_type->setCurrentIndex(2);
    fichier = new QPushButton("fichier");
    connect(fichier, SIGNAL(clicked(bool)), this, SLOT(trouveFichier()));

    button_hbox = new QHBoxLayout;
    save_button = new QPushButton("save");
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));
    close_button = new QPushButton("close");
    connect(close_button, SIGNAL(clicked(bool)), this, SLOT(close()));
    delete_button = new QPushButton("delete");
    connect(delete_button, SIGNAL(clicked(bool)), this, SLOT(deleteMulti()));

    printed_path = new QLabel("C:/  ...  "+multi_note.getFicher().right(20));
    path = multi_note.getFicher();

    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    description_hbox->addWidget(description_label); description_hbox->addWidget(description);
    fichier_hbox->addWidget(fichier_type); fichier_hbox->addWidget(fichier);
    button_hbox->addWidget(save_button); button_hbox->addWidget(close_button); button_hbox->addWidget(delete_button);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(description_hbox);
    fenetre_vbox->addLayout(fichier_hbox);
    fenetre_vbox->addWidget(printed_path);
    fenetre_vbox->addLayout(button_hbox);

    if(multi_note.etatToString() == "archive"){
        title->setEnabled(false);
        description->setEnabled(false);
        fichier->setEnabled(false);
        fichier_type->setEnabled(false);
        button_hbox->removeWidget(delete_button);


        save_button->setText("Restaurer");
        disconnect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));
        connect(save_button, SIGNAL(clicked(bool)), this, SLOT(restaureArchive()));
    }


    this->setLayout(fenetre_vbox);


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
    statut->addItem("attente");

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
    fenetre_vbox->addLayout(statut_hbox);
    fenetre_vbox->addLayout(button_hbox);


    this->setLayout(fenetre_vbox);

}

TacheWindow::TacheWindow(Note &note, QWidget *parent) : QWidget(parent)
{

    Tache& tache_note = dynamic_cast<Tache&>(note);

    setFixedSize(200, 400);
    move(200, 40);


    fenetre_vbox = new QVBoxLayout;

    id_hbox = new QHBoxLayout;
    id_label = new QLabel("Identifiant");
    id = new QLabel(tache_note.getId());

    title_hbox = new QHBoxLayout;
    title_label = new QLabel("Titre");
    title = new QLineEdit;
    title->setText(tache_note.getTitre());

    action_hbox = new QHBoxLayout;
    action_label = new QLabel("Action");
    action = new QTextEdit;
    action->setText(tache_note.getAction());

    priorite_hbox = new QHBoxLayout;
    priorite_label = new QLabel("Priorité");
    priorite = new QLineEdit;
    priorite->setText(QString::number(tache_note.getPriorite()));
    priorite->setMaximumWidth(20);
    priorite->setValidator( new QIntValidator(0, 5, this) );


    echeance_hbox = new QHBoxLayout;
    echeance_label = new QLabel("Date");
    echeance = new QDateTimeEdit;
    echeance->setDateTime(tache_note.getDateEcheance());

    statut_hbox = new QHBoxLayout;
    statut_label = new QLabel("Statut");
    statut = new QComboBox;
    statut->addItem("attente");
    statut->addItem("cours");
    statut->addItem("termine");
    statut->setCurrentText(tache_note.statutToString());


    button_hbox = new QHBoxLayout;
    save_button = new QPushButton("save");
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));
    close_button = new QPushButton("close");
    connect(close_button, SIGNAL(clicked(bool)), this, SLOT(close()));
    delete_button = new QPushButton("delete");
    connect(delete_button, SIGNAL(clicked(bool)), this, SLOT(deleteTache()));


    id_hbox->addWidget(id_label); id_hbox->addWidget(id);
    title_hbox->addWidget(title_label); title_hbox->addWidget(title);
    action_hbox->addWidget(action_label); action_hbox->addWidget(action);
    priorite_hbox->addWidget(priorite_label); priorite_hbox->addWidget(priorite);
    echeance_hbox->addWidget(echeance_label); echeance_hbox->addWidget(echeance);
    statut_hbox->addWidget(statut_label); statut_hbox->addWidget(statut);
    button_hbox->addWidget(save_button); button_hbox->addWidget(close_button); button_hbox->addWidget(delete_button);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(title_hbox);
    fenetre_vbox->addLayout(action_hbox);
    fenetre_vbox->addLayout(priorite_hbox);
    fenetre_vbox->addLayout(echeance_hbox);
    fenetre_vbox->addLayout(statut_hbox);
    fenetre_vbox->addLayout(button_hbox);

    if(tache_note.etatToString() == "archive"){
        title->setEnabled(false);
        action->setEnabled(false);
        echeance->setEnabled(false);
        priorite->setEnabled(false);
        statut->setEnabled(false);

        button_hbox->removeWidget(delete_button);

        save_button->setText("Restaurer");
        disconnect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));
        connect(save_button, SIGNAL(clicked(bool)), this, SLOT(restaureArchive()));
    }


    this->setLayout(fenetre_vbox);

}


/// Saves

// Save article

void ArticleWindow::save(){

    if(this->getTitle() != "" && this->getText() != "")
    {
        NotesManager& NM = NotesManager::donneInstance();
        if(NM.existeNote(this->id->text())){
            RelationManager& RM = RelationManager::donneInstance();
            bool test = RM.updateReference(id->text(), text->toPlainText()+title->text());
            if(test)
            {
                Article& article = dynamic_cast<Article&>(NM.getNote(id->text()));
                article.setTexte(text->toPlainText());
                article.setTitre(title->text());
                QMessageBox::information(this, "Bravo", "Sauvegarde Reussie !");
            }
            else
            {
                QErrorMessage* em = new QErrorMessage;
                em->showMessage("On ne peut pas faire de référence vers une note qui n'existe pas.");
            }

        }
        else
        {
            Article* article = new Article(id->text(),title->text(), text->toPlainText());
            NM.addNote(article);
            RelationManager& RM = RelationManager::donneInstance();
            bool test = RM.updateReference(id->text(), text->toPlainText()+title->text());
            if(test)
            {
                QMessageBox::information(this, "Bravo", "Sauvegarde Réussie !");
            }
            else
            {
                QErrorMessage* em = new QErrorMessage;
                em->showMessage("Sauvegarde réussie mais aucune référence n'a été prise en compte, on ne peut pas faire de référence vers une note qui n'existe pas.");
            }
        }

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
        NotesManager& NM = NotesManager::donneInstance();
        if(NM.existeNote(this->id->text())){
            RelationManager& RM = RelationManager::donneInstance();
            bool test = RM.updateReference(id->text(), action->toPlainText()+title->text());
            if(test)
            {
                Tache& tache = dynamic_cast<Tache&>(NM.getNote(id->text()));
                tache.setAction(action->toPlainText());
                tache.setTitre(title->text());
                tache.setDateEcheance(echeance->dateTime());
                tache.setPriority(priorite->text().toUInt());
                if(statut->currentText() == "termine")
                    tache.setStatut(termine);
                else if(statut->currentText() == "cours")
                    tache.setStatut(cours);
                else
                    tache.setStatut(attente);
                QMessageBox::information(this, "Bravo", "Sauvegarde Reussie !");
            }
            else
            {
                QErrorMessage* em = new QErrorMessage;
                em->showMessage("On ne peut pas faire de référence vers une note qui n'existe pas.");
            }

        }
        else
        {
            Tache* tache = new Tache(id->text(),title->text(), action->toPlainText(),echeance->dateTime(),priorite->text().toUInt());
            NM.addNote(tache);
            RelationManager& RM = RelationManager::donneInstance();
            bool test = RM.updateReference(id->text(), action->toPlainText()+title->text());
            if(test)
            {
                QMessageBox::information(this, "Bravo", "Sauvegarde Réussie !");
            }
            else
            {
                QErrorMessage* em = new QErrorMessage;
                em->showMessage("Sauvegarde réussie mais aucune référence n'a été prise en compte, on ne peut pas faire de référence vers une note qui n'existe pas.");
            }
        }

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
        NotesManager& NM = NotesManager::donneInstance();
        if(NM.existeNote(this->id->text())){
            RelationManager& RM = RelationManager::donneInstance();
            bool test = RM.updateReference(id->text(), description->toPlainText()+title->text());
            if(test)
            {
                Multimedia& multi = dynamic_cast<Multimedia&>(NM.getNote(id->text()));
                multi.setDescription(description->toPlainText());
                multi.setFichier(path);
                multi.setTitre(title->text());
                if(fichier_type->currentText() == "video")
                    multi.setType(video);
                else if(fichier_type->currentText() == "audio")
                    multi.setType(audio);
                else
                    multi.setType(image);
                QMessageBox::information(this, "Bravo", "Sauvegarde Réussie !");
            }
            else
            {
                QErrorMessage* em = new QErrorMessage;
                em->showMessage("On ne peut pas faire de référence vers une note qui n'existe pas.");
            }

        }
        else
        {
            TypeMultimedia type;
            if(fichier_type->currentText() == "video")
                type = video;
            else if(fichier_type->currentText() == "audio")
                type = audio;
            else
                type = image;
            Multimedia* multi = new Multimedia(id->text(),title->text(),description->toPlainText(),path,type);
            NM.addNote(multi);
            RelationManager& RM = RelationManager::donneInstance();
            bool test = RM.updateReference(id->text(), description->toPlainText()+title->text());
            if(test)
            {
                QMessageBox::information(this, "Bravo", "Sauvegarde Réussie !");
            }
            else
            {
                QErrorMessage* em = new QErrorMessage;
                em->showMessage("Sauvegarde réussie mais aucune référence n'a été prise en compte, on ne peut pas faire de référence vers une note qui n'existe pas.");
            }

        }

    }
    else
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("Entrez le Titre, un Fichier et une Description ");
    }

}


void ArticleWindow::deleteArticle(){
    NotesManager& NM = NotesManager::donneInstance();
    NM.deleteNote(this->id->text());
    QMessageBox::information(this, "Bravo", "Suppression Réussie !");
}

void ArticleWindow::restaureArchive(){
    NotesManager& NM = NotesManager::donneInstance();
    if(NM.getNote(id->text()).etatToString() == "archive")
    {
        NM.restaurerArchiveNote(id->text());
        QMessageBox::information(this, "Bravo", "Restauration Réussie !");
        close();
    }
}

void TacheWindow::deleteTache(){
    NotesManager& NM = NotesManager::donneInstance();
    NM.deleteNote(this->id->text());
    QMessageBox::information(this, "Bravo", "Suppression Réussie !");
}

void TacheWindow::restaureArchive(){
    NotesManager& NM = NotesManager::donneInstance();
    if(NM.getNote(id->text()).etatToString() == "archive")
    {
        NM.restaurerArchiveNote(id->text());
        QMessageBox::information(this, "Bravo", "Restauration Réussie !");
        close();
    }
}

void MultimediaWindow::deleteMulti(){
    NotesManager& NM = NotesManager::donneInstance();
    NM.deleteNote(this->id->text());
    QMessageBox::information(this, "Bravo", "Suppression Réussie !");
}

void MultimediaWindow::restaureArchive(){
    NotesManager& NM = NotesManager::donneInstance();
    if(NM.getNote(id->text()).etatToString() == "archive")
    {
        NM.restaurerArchiveNote(id->text());
        QMessageBox::information(this, "Bravo", "Restauration Réussie !");
        close();
    }
}



