#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notewindow.h"

#include <QWidget>
#include <QMenuBar>

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu *menuNotes, *menuTypeNotes, *menuRef;

    menuNotes = menuBar()->addMenu(tr("Note"));
    menuTypeNotes = menuNotes->addMenu("Nouvelle...");
    menuTypeNotes->addAction("tache");

    menuRef = menuBar()->addMenu(tr("Référence"));
    menuRef->addAction("autre");




    NoteWindow* fenetre_note;
    fenetre_note = new NoteWindow();
    setCentralWidget(fenetre_note);
}

MainWindow::~MainWindow()
{
    delete ui;
}
