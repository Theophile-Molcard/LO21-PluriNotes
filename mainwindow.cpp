#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notewindow.h"

#include <QWidget>
#include <QMenuBar>

#include<QErrorMessage>

#include <QPushButton>


/// Constructeur / Destructeur MainWindow

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(600, 440);

    note_window = 0;
    article_window = 0;
    multimedia_window = 0;
    tache_window = 0;
    explo_window = 0;

    /// Les menus
    QMenu *menuNotes, *menuRef, *menuExplo;
    QAction *nouvelle_note, *explo_notes, *agenda_taches, *creer_ref;

    menuExplo = menuBar()->addMenu("Afficher");
    explo_notes = menuExplo->addAction("Notes");

    QObject::connect(explo_notes, SIGNAL(triggered(bool)), this, SLOT(ouvrir_explorateur()) );

    agenda_taches = menuExplo->addAction("Taches");

    QObject::connect(agenda_taches, SIGNAL(triggered(bool)), this, SLOT(ouvrir_agenda_taches()) );

    menuNotes = menuBar()->addMenu("Note");
    nouvelle_note = menuNotes->addAction("Nouvelle");

    QObject::connect(nouvelle_note, SIGNAL(triggered(bool)), this, SLOT(cree_note()) );

    menuRef = menuBar()->addMenu(tr("Relation"));
    creer_ref = menuRef->addAction("créer");

    QObject::connect(creer_ref, SIGNAL(triggered(bool)), this, SLOT(ouvrir_crea_ref()) );



}

MainWindow::~MainWindow()
{
    delete ui;
}

/// Slots

void MainWindow::create() {

    if(note_window->getId() != "" && note_window->getTitle() != "")
    {
        if(note_window->getType() == "Article")            editeur_article();
        else if(note_window->getType() == "Multimedia")    editeur_multimedia();
        else if(note_window->getType() == "Tache")         editeur_tache();

        note_window->close();
    }
    else
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("Entrez le Titre et l'ID");
    }
}

void MainWindow::cree_note() {
    if(article_window) article_window->close();
    if(multimedia_window) multimedia_window->close();
    if(tache_window) tache_window->close();

    if(note_window) note_window->close();
    note_window =  new NoteWindow(this);

    QObject::connect(note_window->getPushButton(), SIGNAL(clicked(bool)), this, SLOT(create()) );
    note_window->show();
}

void MainWindow::ouvrir_explorateur() {
    if(explo_window) explo_window->close();
    explo_window =  new ExplorateurWindow(this);
    //connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvre_note()));
    explo_window->show();
}

void MainWindow::ouvrir_agenda_taches() {
    if(explo_window) explo_window->close();
    explo_window =  new ExplorateurWindow(0, this);
    //connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvre_note()));
    explo_window->show();
}

void MainWindow::ouvre_note() {
    if(article_window) article_window->close();
    if(multimedia_window) multimedia_window->close();
    if(tache_window) tache_window->close();

    if(note_window) note_window->close();

    NotesManager& NM = NotesManager::donneInstance();

    Note& note = NM.getNote( explo_window->getIdIndice(explo_window->getListe()->currentRow()) );


    if(typeid(note)==typeid(Tache))
        ouvre_tache(note);
    else if(typeid(note)==typeid(Multimedia))
        ouvre_multi(note);
    else
        ouvre_article(note);

}

void MainWindow::ouvre_tache(Note &note){
    tache_window = new TacheWindow(note, this);
    tache_window->show();
}


void MainWindow::ouvre_multi(Note &note){
    multimedia_window = new MultimediaWindow(note, this);
    multimedia_window->show();
}


void MainWindow::ouvre_article(Note &note){
    article_window = new ArticleWindow(note, this);
    article_window->show();
}


/// Editeurs de notes

// ID + TITLE

void MainWindow::editeur_article(){

    article_window = new ArticleWindow( note_window->getId(), note_window->getTitle(), this);
    article_window->show();

}

void MainWindow::editeur_multimedia(){

    multimedia_window = new MultimediaWindow( note_window->getId(), note_window->getTitle(), this);
    multimedia_window->show();

}

void MainWindow::editeur_tache(){

    tache_window = new TacheWindow( note_window->getId(), note_window->getTitle(), this);
    tache_window->show();

}

///Editeur de references


void MainWindow::ouvrir_crea_ref(){
    crea_rela_window = new CreationRelationWindow(this);
    crea_rela_window->show();
}
















