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

    /// Les menus
    QMenu *menuNotes, *menuRef;
    QAction *nouvelle_note;

    menuNotes = menuBar()->addMenu("Note");
    nouvelle_note = menuNotes->addAction("Nouvelle");

    QObject::connect(nouvelle_note, SIGNAL(triggered(bool)), this, SLOT(ouvrir_note()) );

    menuRef = menuBar()->addMenu(tr("Référence"));
    menuRef->addAction("autre");



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

void MainWindow::ouvrir_note() {
    if(article_window) article_window->close();
    if(multimedia_window) multimedia_window->close();
    if(tache_window) tache_window->close();

    if(note_window) note_window->close();
    note_window =  new NoteWindow(this);

    QObject::connect(note_window->getPushButton(), SIGNAL(clicked(bool)), this, SLOT(create()) );
    note_window->show();
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
