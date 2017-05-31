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

    /// Les menus
    QMenu *menuNotes, *menuRef;
    QAction *nouvelle_note;

    menuNotes = menuBar()->addMenu("Note");
    nouvelle_note = menuNotes->addAction("Nouvelle");

    QObject::connect(nouvelle_note, SIGNAL(triggered(bool)), this, SLOT(ouvrir_fenetre()) );

    menuRef = menuBar()->addMenu(tr("Référence"));
    menuRef->addAction("autre");


}

MainWindow::~MainWindow()
{
    delete ui;
}
