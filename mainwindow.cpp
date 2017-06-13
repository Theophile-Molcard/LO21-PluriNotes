#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notewindow.h"

#include <QWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>

#include<QErrorMessage>

#include <QPushButton>
#include <QDebug>


/// Constructeur / Destructeur MainWindow

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    undoStack = new QUndoStack(this);

    NotesManager& NM = NotesManager::donneInstance();
    NM.LoadFileXML();

    RelationManager& RM = RelationManager::donneInstance();
    if(!RM.existeRelation("Reference"))
    {
        RM.createReference();
    }

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
    arbo = 0;

    fermer_arbo();

    pref_arbo = false;
    pref_corbeille = false;

    /// Les menus
    QMenu *menuNotes, *menuRef, *menuExplo, *menuPref, *editMenu;
    QAction *nouvelle_note, *explo_notes, *explo_archives, *explo_corbeille, *agenda_taches, *creer_ref, *enrichir_ref, *affiche_couples, *preference_arbo, *preference_corbeille;

    /// exploration

    menuExplo = menuBar()->addMenu("Afficher");
    explo_notes = menuExplo->addAction("Notes");

    QObject::connect(explo_notes, SIGNAL(triggered(bool)), this, SLOT(ouvrir_explorateur()) );

    agenda_taches = menuExplo->addAction("Taches");

    QObject::connect(agenda_taches, SIGNAL(triggered(bool)), this, SLOT(ouvrir_agenda_taches()) );

    explo_archives = menuExplo->addAction("Archives");

    QObject::connect(explo_archives, SIGNAL(triggered(bool)), this, SLOT(ouvrir_archives()) );

    explo_corbeille = menuExplo->addAction("Corbeille");

    QObject::connect(explo_corbeille, SIGNAL(triggered(bool)), this, SLOT(ouvrir_corbeille()) );


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

    /// Preferences
    QSettings settings("config.ini",QSettings::IniFormat);
    menuPref = menuBar()->addMenu(tr("Préférences"));
    preference_arbo = menuPref->addAction("arborescence");
    preference_arbo->setCheckable(true);

    pref_arbo = settings.value("AffArbo", false).toBool();
    preference_arbo->setChecked(pref_arbo);

    if(pref_arbo){
        setFixedSize(800, 440);
    }
    else{
        setFixedSize(600, 440);
    }

    QObject::connect(preference_arbo, SIGNAL(toggled(bool)), this, SLOT(elargir()) );

    preference_corbeille = menuPref->addAction("corbeille auto");
    preference_corbeille->setCheckable(true);

    pref_corbeille = settings.value("VidageAuto", false).toBool();
    preference_corbeille->setChecked(pref_corbeille);

    QObject::connect(preference_corbeille, SIGNAL(toggled(bool)), this, SLOT(corbeilleAuto()));

    ///Undo Redo
    undoAction = undoStack->createUndoAction(this, tr("&Annuler"));
    undoAction->setShortcuts(QKeySequence::Undo);

    redoAction = undoStack->createRedoAction(this, tr("&Rétablir"));
    redoAction->setShortcuts(QKeySequence::Redo);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);


}

void MainWindow::closeEvent (QCloseEvent *event)
{
    NotesManager& NM = NotesManager::donneInstance();
    QSettings settings("config.ini",QSettings::IniFormat);
    bool VidageAuto = settings.value("VidageAuto", false ).toBool();
    if(!VidageAuto && NM.testCorbeille() )
    {
        QMessageBox msg;
        msg.setText("Avant de quitter");
        msg.setInformativeText("Voulez-vous vider la corbeille?");
        QAbstractButton *OuiBouton = msg.addButton(QString("Vider"), QMessageBox::YesRole);
        QAbstractButton *NonBouton = msg.addButton(QString("Restaurer"), QMessageBox::YesRole);
        /*msg.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
        msg.setDefaultButton(QMessageBox::No);
        int ret = msg.exec();
        switch (ret) {
          case QMessageBox::Yes:
              NM.viderCorbeille();
              break;
          case QMessageBox::No:
                 NM.restaurerCorbeille();
              break;
          default:

              break;
        }*/

        msg.exec();
        if(msg.clickedButton() == OuiBouton)
        {
            NM.viderCorbeille();
        }
        else if(msg.clickedButton() == NonBouton)
        {
            NM.restaurerCorbeille();
        }
        event->accept();
    }

}


MainWindow::~MainWindow()
{

    NotesManager::supprimeInstance();
    RelationManager::supprimeInstance();
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
    if(pref_arbo) setFixedWidth(800);

    explo_window =  new ExplorateurWindow(this);
    connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur_memento()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvre_note()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvrir_arbo()));
    explo_window->show();
}

void MainWindow::ouvrir_agenda_taches() {
    fermer_slot_2();
    if(pref_arbo) setFixedWidth(800);

    explo_window =  new ExplorateurWindow(0, this);
    connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur_memento()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvre_note()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvrir_arbo()));
    explo_window->show();
}

void MainWindow::ouvrir_archives() {
    fermer_slot_2();
    fermer_arbo();

    explo_window =  new ExplorateurWindow(1, this);
    //connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvre_note()));
    //connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvrir_arbo()));
    explo_window->getTitreWidget()->setText("archives");
    explo_window->show();
}

void MainWindow::ouvrir_corbeille() {
    fermer_slot_2();
    fermer_arbo();

    explo_window =  new ExplorateurWindow(2, this);
    //connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note()));
    connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvre_note()));
    //connect(explo_window->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ouvrir_arbo()));
    explo_window->getTitreWidget()->setText("Corbeille");
    explo_window->getButtonOpen()->setText("restaurer corbeille");

    connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(restaure_corbeille()));

    explo_window->show();
}

void MainWindow::ouvre_note() {
    fermer_slot_1();
    qDebug() << "coucou";
    NotesManager& NM = NotesManager::donneInstance();

    Note& note = NM.getNote( explo_window->getIdIndice(explo_window->getListe()->currentRow()) );


    if(typeid(note)==typeid(Tache))
        ouvre_tache(note);
    else if(typeid(note)==typeid(Multimedia))
        ouvre_multi(note);
    else
        ouvre_article(note);

}

void MainWindow::ouvre_note_asc() {
    if(arbo->getAscendants()->currentColumn() != -1){
        fermer_slot_1();

        NotesManager& NM = NotesManager::donneInstance();

        Note& note = NM.getNote( arbo->getAscendants()->currentItem()->text(0) );


        if(typeid(note)==typeid(Tache))
            ouvre_tache(note);
        else if(typeid(note)==typeid(Multimedia))
            ouvre_multi(note);
        else
            ouvre_article(note);

        ouvrir_arbo();
    }

}

void MainWindow::ouvre_note_desc() {
    if(arbo->getDescendants()->currentColumn() != -1){
        fermer_slot_1();

        NotesManager& NM = NotesManager::donneInstance();

        Note& note = NM.getNote( arbo->getDescendants()->currentItem()->text(0) );


        if(typeid(note)==typeid(Tache))
            ouvre_tache(note);
        else if(typeid(note)==typeid(Multimedia))
            ouvre_multi(note);
        else
            ouvre_article(note);

        ouvrir_arbo();
    }

}

void MainWindow::ouvre_tache(Note &note){
    tache_window = new TacheWindow(note, this);
    connect(tache_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(fermer_arbo()));
    if(explo_window->getTitre() == "toutes les notes" || explo_window->getTitre() == "archives")
        connect(tache_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    else
        connect(tache_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_agenda_taches()));

    if(explo_window->getTitre() == "toutes les notes" || explo_window->getTitre() == "archives")
        connect(tache_window->getDeleteButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    else
        connect(tache_window->getDeleteButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_agenda_taches()));
    connect(tache_window->getDeleteButton(), SIGNAL(clicked(bool)), tache_window, SLOT(close()));
    tache_window->show();
}


void MainWindow::ouvre_multi(Note &note){
    multimedia_window = new MultimediaWindow(note, this);
    connect(multimedia_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    connect(multimedia_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(fermer_arbo()));
    connect(multimedia_window->getDeleteButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    connect(multimedia_window->getDeleteButton(), SIGNAL(clicked(bool)), multimedia_window, SLOT(close()));
    multimedia_window->show();
}


void MainWindow::ouvre_article(Note &note){
    article_window = new ArticleWindow(note, this);
    connect(article_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    connect(article_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(fermer_arbo()));
    connect(article_window->getDeleteButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    connect(article_window->getDeleteButton(), SIGNAL(clicked(bool)), article_window, SLOT(close()));
    article_window->show();
}


/// Editeurs de notes

// ID + TITLE

void MainWindow::editeur_article(){

    article_window = new ArticleWindow( note_window->getId(), note_window->getTitle(), this);
    connect(article_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(fermer_arbo()));
    connect(article_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    article_window->show();

}

void MainWindow::editeur_multimedia(){

    multimedia_window = new MultimediaWindow( note_window->getId(), note_window->getTitle(), this);
    connect(multimedia_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(fermer_arbo()));
    connect(multimedia_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    multimedia_window->show();

}

void MainWindow::editeur_tache(){

    tache_window = new TacheWindow( note_window->getId(), note_window->getTitle(), this);
    connect(tache_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(fermer_arbo()));
    connect(tache_window->getSaveButton(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
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
    if(explo_rela_window->getListe()->currentRow() != -1){
        QString titre_rela = explo_rela_window->getListe()->currentItem()->text();
        fermer_slot_3();

        RelationManager& RM = RelationManager::donneInstance();

        crea_rela_window = new CreationRelationWindow(&RM.getRelation(titre_rela), this);

        connect(crea_rela_window->getButtonCreate(), SIGNAL(clicked(bool)), this, SLOT(ouvre_couplage()));

        connect(crea_rela_window->getButtonClose(), SIGNAL(clicked(bool)), this, SLOT(parcourir_rela()));

        //connect(crea_rela_window->getButtonDelete(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_arbo()));

        crea_rela_window->show();
    }
}

void MainWindow::ouvre_couplage(){
    if(explo_rela_window->getListe()->currentRow() != -1){

        RelationManager& RM = RelationManager::donneInstance();

        Relation* rela = &RM.getRelation( crea_rela_window->getTitre()->text() );

        fermer_slot_3();

        couple_window = new CoupleWindow(rela, this);
        connect(couple_window->getButtonCreate(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_arbo()));
        couple_window->show();
    }


}

void MainWindow::visualiser_rela(){

    fermer_slot_3();

    rela_viz_window = new RelationVizingWindow(this);
    connect(rela_viz_window->getButtonSuprime(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_arbo()));

    rela_viz_window->show();

}

void MainWindow::visualiser_rela_specifique(QString rela){
    fermer_slot_3();

    rela_viz_window = new RelationVizingWindow(this);
    rela_viz_window->afficherCouplesRelation(rela);
    connect(rela_viz_window->getButtonSuprime(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_arbo()));

    rela_viz_window->show();
}

void MainWindow::visualiser_note_specifique(QString idNote){
    fermer_slot_1();

    NotesManager& NM = NotesManager::donneInstance();

    Note& note = NM.getNote(idNote);


    if(typeid(note)==typeid(Tache))
        ouvre_tache(note);
    else if(typeid(note)==typeid(Multimedia))
        ouvre_multi(note);
    else
        ouvre_article(note);

}


void MainWindow::ouvrir_arbo(){
    if(arbo && arbo->getButtonAsc()->hasFocus() && arbo->getAscendants()->currentColumn() != -1 ){
        NotesManager& NM = NotesManager::donneInstance();

        Note& note = NM.getNote( arbo->getAscendants()->currentItem()->text(0) );
        arbo->close();
        arbo = new Arborescence(note, this);
        connect(arbo->getButtonAsc(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note_asc()));
        connect(arbo->getButtonDesc(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note_desc()));
        arbo->show();

    }
    else if (arbo && arbo->getButtonDesc()->hasFocus() && arbo->getDescendants()->currentColumn() != -1 ){
        NotesManager& NM = NotesManager::donneInstance();

        Note& note = NM.getNote( arbo->getDescendants()->currentItem()->text(0) );
        arbo->close();
        arbo = new Arborescence(note, this);
        connect(arbo->getButtonAsc(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note_asc()));
        connect(arbo->getButtonDesc(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note_desc()));
        arbo->show();


    }
    else{
        if(arbo) arbo->close();
        if(pref_arbo) setFixedSize(800, 440);
        if(explo_window){
            if(explo_window->isVisible()){
                if(explo_window->getListe()->currentRow() != -1){
                    NotesManager& NM = NotesManager::donneInstance();

                    Note& note = NM.getNote( explo_window->getIdIndice(explo_window->getListe()->currentRow()) );
                    arbo = new Arborescence(note, this);
                    connect(arbo->getButtonAsc(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note_asc()));
                    connect(arbo->getButtonDesc(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note_desc()));
                    arbo->show();
                }
            }
        }

    }
}

void MainWindow::fermer_arbo(){
    if(arbo) arbo->close();
    setFixedSize(600, 440);
}



void MainWindow::restaure_corbeille(){
    NotesManager& NM = NotesManager::donneInstance();
    NM.restaurerCorbeille();
    QMessageBox::information(this, "Bravo", "Restauration de la corbeille Réussie !");
    fermer_slot_2();
    fermer_slot_1();
    ouvrir_explorateur();
}

void MainWindow::ouvrir_memento(){

    fermer_slot_1();

    NotesManager& NM = NotesManager::donneInstance();

    Note& note = NM.getNote( explo_window->getIdIndice(explo_window->getListe()->currentRow()) );

    ouvre_note();
}

void MainWindow::ouvrir_explorateur_memento() {

    if(explo_window->getListe()->currentRow() != -1){
        NotesManager& NM = NotesManager::donneInstance();

        Note& note = NM.getNote( explo_window->getIdIndice(explo_window->getListe()->currentRow()) );

        fermer_slot_2();

        explo_window = new ExplorateurWindow(note, this);
        explo_window->show();
        connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(fermer_arbo()));
        connect(explo_window->getButtonOpen(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_explorateur()));
    }

}

void MainWindow::corbeilleAuto(){

    QSettings settings("config.ini",QSettings::IniFormat);
    settings.setValue("VidageAuto",!pref_corbeille);


}

void MainWindow::deleteRelation(Relation *rel){
    QUndoCommand *deleteRelCommand = new DeleteRelationCommand(rel);
    qDebug() << "ccc";
    undoStack->push(deleteRelCommand);
}

void MainWindow::deleteCouple(QString rel, QString _x, QString _y, QString _label){
    QUndoCommand *deleteCoupleCommand = new DeleteCoupleCommand(rel,_x,_y, _label);
    undoStack->push(deleteCoupleCommand);
}


DeleteRelationCommand::DeleteRelationCommand(Relation *rel, QUndoCommand *parent): QUndoCommand(parent){
    Relation* NewRel = new Relation(rel->getTitre(),rel->getDescription(),true);
    Relation::Iterator it = rel->getIterator();
    while(!it.isdone())
    {
        NewRel->addCouple((*it)->getx(),(*it)->gety(),(*it)->getLabel());
        it++;
    }
    if(!rel->getOrientee())
    {
        NewRel->inverseOrientation();
    }
    relation = NewRel;
}

void DeleteRelationCommand::undo(){
    Relation* NewRel = new Relation(relation->getTitre(),relation->getDescription(),true);
    Relation::Iterator it = relation->getIterator();
    while(!it.isdone())
    {
        NewRel->addCouple((*it)->getx(),(*it)->gety(),(*it)->getLabel());
        it++;
    }
    if(!relation->getOrientee())
    {
        NewRel->inverseOrientation();
    }
    RelationManager& RM = RelationManager::donneInstance();
    RM.addRelation(NewRel);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        if ( widget->windowTitle() == "PluriNote")
        {
           qobject_cast<MainWindow*>(widget)->parcourir_rela();
           qobject_cast<MainWindow*>(widget)->ouvrir_arbo();
        }
    }
}

void DeleteRelationCommand::redo(){
    RelationManager& RM = RelationManager::donneInstance();
               qDebug() << "lalal";
    RM.deleteRelation(relation->getTitre());
               qDebug() << "lrlrl";

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        if ( widget->windowTitle() == "PluriNote")
        {
           qobject_cast<MainWindow*>(widget)->parcourir_rela();
           qobject_cast<MainWindow*>(widget)->ouvrir_arbo();
        }
    }
}

DeleteCoupleCommand::DeleteCoupleCommand(QString rel, QString _x, QString _y, QString _label, QUndoCommand *parent): relation(rel), x(_x), y(_y), label(_label), QUndoCommand(parent){}

void DeleteCoupleCommand::undo(){
    RelationManager& RM = RelationManager::donneInstance();
    RM.getRelation(relation).addCouple(x,y,label);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        if ( widget->windowTitle() == "PluriNote")
        {
           qobject_cast<MainWindow*>(widget)->visualiser_rela_specifique(relation);
           qobject_cast<MainWindow*>(widget)->ouvrir_arbo();
        }
    }
}

void DeleteCoupleCommand::redo(){
    RelationManager& RM = RelationManager::donneInstance();
    RM.getRelation(relation).deleteCouple(x,y);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        if ( widget->windowTitle() == "PluriNote")
        {
           qobject_cast<MainWindow*>(widget)->visualiser_rela_specifique(relation);
           qobject_cast<MainWindow*>(widget)->ouvrir_arbo();
        }
    }
}
