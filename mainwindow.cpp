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
    crea_rela_window = 0;
    explo_rela_window = 0;
    couple_window = 0;
    rela_viz_window = 0;

    /// Les menus
    QMenu *menuNotes, *menuRef, *menuExplo;
    QAction *nouvelle_note, *explo_notes, *explo_archives, *agenda_taches, *creer_ref, *enrichir_ref, *affiche_couples;

    /// exploration

    menuExplo = menuBar()->addMenu("Afficher");
    explo_notes = menuExplo->addAction("Notes");

    QObject::connect(explo_notes, SIGNAL(triggered(bool)), this, SLOT(ouvrir_explorateur()) );

    agenda_taches = menuExplo->addAction("Taches");

    QObject::connect(agenda_taches, SIGNAL(triggered(bool)), this, SLOT(ouvrir_agenda_taches()) );

    explo_archives = menuExplo->addAction("Archives");

    QObject::connect(explo_archives, SIGNAL(triggered(bool)), this, SLOT(ouvrir_archives()) );


    /// Nouvelles notes

    menuNotes = menuBar()->addMenu("Note");
    nouvelle_note = menuNotes->addAction("Nouvelle");

    QObject::connect(nouvelle_note, SIGNAL(triggered(bool)), this, SLOT(cree_note()) );


    /// Relations
    menuRef = menuBar()->addMenu(tr("Relation"));
    creer_ref = menuRef->addAction("créer");

    QObject::connect(creer_ref, SIGNAL(triggered(bool)), this, SLOT(ouvrir_crea_rela()) );

    enrichir_ref = menuRef->addAction("parcourir");

    QObject::connect(enrichir_ref, SIGNAL(triggered(bool)), this, SLOT(parcourir_rela()) );

    affiche_couples = menuRef->addAction("couples");

    QObject::connect(affiche_couples, SIGNAL(triggered(bool)), this, SLOT(visualiser_rela()) );



}

MainWindow::~MainWindow()
{
    delete ui;
}

/// Slots

void MainWindow::fermer_slot_1(){

    if(article_window) article_window->close();
    if(multimedia_window) multimedia_window->close();
    if(tache_window) tache_window->close();

    if(note_window) note_window->close();

}
void MainWindow::fermer_slot_2(){

    if(explo_window) explo_window->close();

}

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
    fermer_slot_1();

    note_window =  new NoteWindow(this);

    QObject::connect(note_window->getPushButton(), SIGNAL(clicked(bool)), this, SLOT(create()) );
    note_window->show();
}

void MainWindow::ouvrir_explorateur() {
    fermer_slot_2();

    explo_window =  new ExplorateurWindow(this);
    //connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvre_note()));
    explo_window->show();
}

void MainWindow::ouvrir_agenda_taches() {
    fermer_slot_2();

    explo_window =  new ExplorateurWindow(0, this);
    //connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvre_note()));
    explo_window->show();
}

void MainWindow::ouvrir_archives() {
    fermer_slot_2();

    explo_window =  new ExplorateurWindow(1, this);
    //connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvre_note()));
    explo_window->show();
}

void MainWindow::ouvre_note() {
    fermer_slot_1();

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
    connect(tache_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_agenda_taches()));
    connect(tache_window->getDeleteButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_agenda_taches()));
    connect(tache_window->getDeleteButton(), SIGNAL(clicked(bool)), tache_window, SLOT(close()));

    tache_window->show();
}


void MainWindow::ouvre_multi(Note &note){
    multimedia_window = new MultimediaWindow(note, this);
    connect(multimedia_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    connect(multimedia_window->getDeleteButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    connect(multimedia_window->getDeleteButton(), SIGNAL(clicked(bool)), multimedia_window, SLOT(close()));
    multimedia_window->show();
}


void MainWindow::ouvre_article(Note &note){
    article_window = new ArticleWindow(note, this);
    connect(article_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    connect(article_window->getDeleteButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    connect(article_window->getDeleteButton(), SIGNAL(clicked(bool)), article_window, SLOT(close()));
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

void MainWindow::fermer_slot_3(){

    if(crea_rela_window) crea_rela_window->close();
    if(explo_rela_window) explo_rela_window->close();
    if(couple_window) couple_window->close();
    if(rela_viz_window) rela_viz_window->close();

}


void MainWindow::ouvrir_crea_rela(){
    fermer_slot_3();

    crea_rela_window = new CreationRelationWindow(this);
    crea_rela_window->show();
}

void MainWindow::parcourir_rela(){
    fermer_slot_3();

    explo_rela_window = new ExplorateurRelationWindow(this);

    connect(explo_rela_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvrir_rela()) );

    explo_rela_window->show();
}

void MainWindow::ouvrir_rela(){

    QString titre_rela = explo_rela_window->getListe()->currentItem()->text();
    fermer_slot_3();

    RelationManager& RM = RelationManager::donneInstance();

    crea_rela_window = new CreationRelationWindow(&RM.getRelation(titre_rela), this);

    connect(crea_rela_window->getButtonCreate(), SIGNAL(clicked(bool)), this, SLOT(ouvre_couplage()));

    connect(crea_rela_window->getButtonClose(), SIGNAL(clicked(bool)), this, SLOT(parcourir_rela()));

    crea_rela_window->show();
}

void MainWindow::ouvre_couplage(){

    RelationManager& RM = RelationManager::donneInstance();

    Relation* rela = &RM.getRelation( crea_rela_window->getTitre()->text() );

    fermer_slot_3();

    couple_window = new CoupleWindow(rela, this);
    couple_window->show();


}

void MainWindow::visualiser_rela(){

    fermer_slot_3();

    rela_viz_window = new RelationVizingWindow(this);

    rela_viz_window->show();

}












