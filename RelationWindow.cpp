#include "RelationWindow.h"
#include "Notes.h"
#include "relations.h"
#include <typeinfo>
#include <QDebug>
#include <QErrorMessage>
#include <QMessageBox>
#include "mainwindow.h"
#include <QApplication>

CreationRelationWindow::CreationRelationWindow(QWidget *parent): QWidget(parent)
{

    setFixedSize(200, 400);
    move(400, 40);

    fenetre_vbox = new QVBoxLayout;

    titre_hbox = new QHBoxLayout;
    titre_label = new QLabel("titre");
    titre = new QLineEdit;

    titre_hbox->addWidget(titre_label);
    titre_hbox->addWidget(titre);

    description_hbox = new QHBoxLayout;
    description_label = new QLabel("Description");
    description = new QTextEdit;

    description_hbox->addWidget(description_label);
    description_hbox->addWidget(description);

    non_oriente = new QCheckBox("non orienté");


    button_create = new QPushButton("créer");
    button_close = new QPushButton("retour");
    connect(button_close, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(button_create,SIGNAL(clicked(bool)),this, SLOT(create()));

    button_layout = new QHBoxLayout;
    button_layout->addWidget(button_create);
    button_layout->addWidget(button_close);

    fenetre_vbox->addLayout(titre_hbox);
    fenetre_vbox->addLayout(description_hbox);
    fenetre_vbox->addWidget(non_oriente);
    fenetre_vbox->addLayout(button_layout);


    this->setLayout(fenetre_vbox);
}


CreationRelationWindow::CreationRelationWindow(Relation *rela, QWidget *parent): QWidget(parent)
{

    setFixedSize(200, 400);
    move(400, 40);

    fenetre_vbox = new QVBoxLayout;

    titre_hbox = new QHBoxLayout;
    titre_label = new QLabel("titre");
    titre = new QLineEdit;
    titre->setText(rela->getTitre());
    titre_ancien = rela->getTitre();

    titre_hbox->addWidget(titre_label);
    titre_hbox->addWidget(titre);

    description_hbox = new QHBoxLayout;
    description_label = new QLabel("Description");
    description = new QTextEdit;
    description->setText(rela->getDescription());

    description_hbox->addWidget(description_label);
    description_hbox->addWidget(description);

    non_oriente = new QCheckBox("non orienté");
    non_oriente->setChecked(!(rela->getOrientee()));
    non_oriente->setEnabled(false);


    button_create = new QPushButton("+ couple");
    button_close = new QPushButton("retour");
    connect(button_close, SIGNAL(clicked(bool)), this, SLOT(close()));


    button_save = new QPushButton("save");
    connect(button_save, SIGNAL(clicked(bool)), this, SLOT(save()));

    button_delete = new QPushButton("delete");
    connect(button_delete, SIGNAL(clicked(bool)), this, SLOT(delete_rela()));

    button_layout_1 = new QHBoxLayout;
    button_layout_2 = new QHBoxLayout;
    button_layout_1->addWidget(button_create);
    button_layout_1->addWidget(button_save);
    button_layout_2->addWidget(button_close);
    button_layout_2->addWidget(button_delete);

    fenetre_vbox->addLayout(titre_hbox);
    fenetre_vbox->addLayout(description_hbox);
    fenetre_vbox->addWidget(non_oriente);
    fenetre_vbox->addLayout(button_layout_1);
    fenetre_vbox->addLayout(button_layout_2);


    this->setLayout(fenetre_vbox);
}

ExplorateurRelationWindow::ExplorateurRelationWindow(QWidget *parent): QWidget(parent)
{


    setFixedSize(200, 400);
    move(400, 40);

    fenetre_vbox = new QVBoxLayout;

    titre = new QLabel("Toutes les relations");

    RelationManager& RM = RelationManager::donneInstance();


    liste = new QListWidget;

    for( RelationManager::Iterator it1 = RM.getIterator() ; !it1.isdone() ; it1++){
        if((*it1)->getTitre()!="Reference"){
            liste->addItem((*it1)->getTitre());
        }
    }

    button_close = new QPushButton("fermer");
    connect(button_close, SIGNAL(clicked(bool)), this, SLOT(close()));


    button_layout = new QHBoxLayout;
    button_layout->addWidget(button_close);

    fenetre_vbox->addWidget(titre);
    fenetre_vbox->addWidget(liste);
    fenetre_vbox->addLayout(button_layout);


    this->setLayout(fenetre_vbox);
}




CoupleWindow::CoupleWindow(Relation* rela, QWidget *parent): QWidget(parent)
{

    setFixedSize(200, 400);
    move(400, 40);

    fenetre_vbox = new QVBoxLayout;

    titre_rela = new QLabel(rela->getTitre());

    couple_hbox = new QHBoxLayout;
    couple_label = new QLabel("label");
    couple = new QLineEdit;

    couple_hbox->addWidget(couple_label);
    couple_hbox->addWidget(couple);

    liste_x = new QListWidget;

    NotesManager& NM = NotesManager::donneInstance();

    for( NotesManager::Iterator it1 = NM.getIterator() ; !it1.isdone() ; it1++){
        if((*it1)->etatToString() == "active"){
            liste_x->addItem((*it1)->getTitre());
            tab_id_x.append((*it1)->getId());
        }
    }

    liste_y = new QListWidget;

    for( NotesManager::Iterator it2 = NM.getIterator() ; !it2.isdone() ; it2++){
        if((*it2)->etatToString() == "active"){
            liste_y->addItem((*it2)->getTitre());
            tab_id_y.append((*it2)->getId());
        }
    }


    button_create = new QPushButton("créer");
    button_close = new QPushButton("fermer");
    connect(button_close, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(button_create, SIGNAL(clicked(bool)), this, SLOT(save()));


    button_layout = new QHBoxLayout;
    button_layout->addWidget(button_create);
    button_layout->addWidget(button_close);

    fenetre_vbox->addWidget(titre_rela);
    fenetre_vbox->addLayout(couple_hbox);
    fenetre_vbox->addWidget(liste_x);
    fenetre_vbox->addWidget(liste_y);
    fenetre_vbox->addLayout(button_layout);


    this->setLayout(fenetre_vbox);
}

void CreationRelationWindow::create(){
    if(this->titre->text() != "" && this->description->toPlainText() != ""){
        RelationManager& RM = RelationManager::donneInstance();
        if(RM.existeRelation(titre->text()))
        {
            QErrorMessage* em = new QErrorMessage;
            em->showMessage("Attention ce titre existe déjà");

        }
        else
        {
            Relation* rel = new Relation(titre->text(),description->toPlainText(),!non_oriente->isChecked());
            RM.addRelation(rel);
        }
        QMessageBox::information(this, "Bravo", "Sauvegarde Reussie !");
    }
    else
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("Entrez le Titre et une description");
    }
}

void CreationRelationWindow::save(){
    if(this->titre->text() != "" && this->description->toPlainText() != ""){
        RelationManager& RM = RelationManager::donneInstance();

        if(titre->text() != titre_ancien && RM.existeRelation(titre->text()))
        {
            QErrorMessage* em = new QErrorMessage;
            em->showMessage("Attention ce titre existe déjà");

        }
        else
        {
            Relation& rel = RM.getRelation(titre_ancien);
            rel.setTitre(titre->text());
            rel.setDescription(description->toPlainText());
            QMessageBox::information(this, "Bravo", "Sauvegarde Reussie !");
        }

    }
    else
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("Entrez le Titre et une description");
    }
}

void CreationRelationWindow::delete_rela(){
    RelationManager& RM = RelationManager::donneInstance();
    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        if ( widget->windowTitle() == "PluriNote")
        {
            qDebug() << titre_ancien;
           qobject_cast<MainWindow*>(widget)->deleteRelation(&(RM.getRelation(titre_ancien)));
           qDebug() << "lolol";
        }
    }
    QMessageBox::information(this, "Bravo", "Suppression Reussie !");
}

void CoupleWindow::save(){
    if(this->liste_x->currentRow() !=-1 && this->liste_y->currentRow() != -1 ){
        RelationManager& RM = RelationManager::donneInstance();
        Relation& rel = RM.getRelation(titre_rela->text());
        if(rel.existeCouple(tab_id_x[ liste_x->currentRow() ],tab_id_y[ liste_y->currentRow() ] ))
        {
            QErrorMessage* em = new QErrorMessage;
            em->showMessage("Ce couple existe déjà");
        }
        else if(tab_id_x[ liste_x->currentRow() ] == tab_id_y[ liste_y->currentRow() ])
        {
            QErrorMessage* em = new QErrorMessage;
            em->showMessage("Impossible de créer une relation entre deux mêmes notes");
        }
        else
        {
            QString label;
            qDebug() << couple->text();
            if(couple->text() == "") label = "default";
            else label = couple->text();
            qDebug()<<tab_id_x[ liste_x->currentRow() ];
            qDebug() << tab_id_y[ liste_y->currentRow() ];
            rel.addCouple( tab_id_x[ liste_x->currentRow() ],  tab_id_y[ liste_y->currentRow() ],label);
            QMessageBox::information(this, "Bravo", "Sauvegarde Reussie !");
        }

    }
    else
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("Choisissez un couple");
    }

}


RelationVizingWindow::RelationVizingWindow(QWidget *parent): QWidget(parent)
{


    setFixedSize(200, 400);
    move(400, 40);

    label=0;

    fenetre_vbox = new QVBoxLayout;

    relation = new QComboBox;

    RelationManager& RM = RelationManager::donneInstance();


    for( RelationManager::Iterator it1 = RM.getIterator() ; !it1.isdone() ; it1++){
        relation->addItem((*it1)->getTitre());
    }


    liste_couples = new QListWidget;

    Relation& r = RM.getRelation(relation->currentText());
    NotesManager& NM = NotesManager::donneInstance();

    for( Relation::Iterator it = r.getIterator() ; !it.isdone() ; it++){
        if(NM.getNote((*it)->getx()).etatToString() == "active" && (NM.getNote((*it)->gety()).etatToString() == "active" || r.getTitre() == "Reference" ) ){
            liste_couples->addItem((*it)->getx()+" -> "+(*it)->gety());
        }

    }

    connect(relation, SIGNAL(currentIndexChanged(int)), this, SLOT(activer_suppr()));

    connect(liste_couples, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editer_couple()));


    connect(relation, SIGNAL(activated(int)), this, SLOT(afficherCouples()) );


    button_supprimer = new QPushButton("supprimer");
    button_supprimer->setEnabled(false);
    button_close = new QPushButton("fermer");
    connect(button_close, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(button_supprimer, SIGNAL(clicked(bool)),this,SLOT(deleteCouple()));

    button_layout = new QHBoxLayout;
    button_layout->addWidget(button_supprimer);
    button_layout->addWidget(button_close);

    fenetre_vbox->addWidget(relation);
    fenetre_vbox->addWidget(liste_couples);
    fenetre_vbox->addLayout(button_layout);


    this->setLayout(fenetre_vbox);
}

void RelationVizingWindow::afficherCouples(){
    RelationManager& RM = RelationManager::donneInstance();

    liste_couples->clear();

    Relation& r = RM.getRelation(relation->currentText());
    NotesManager& NM = NotesManager::donneInstance();

    for( Relation::Iterator it = r.getIterator() ; !it.isdone() ; it++){
        if((NM.getNote((*it)->getx()).etatToString() == "active") && (NM.getNote((*it)->gety()).etatToString() == "active" || r.getTitre() == "Reference" ) ){
            liste_couples->addItem((*it)->getx()+" -> "+(*it)->gety());
        }
    }


}

void RelationVizingWindow::afficherCouplesRelation(QString rel){
    RelationManager& RM = RelationManager::donneInstance();
    qDebug() << "adazd";
    liste_couples->clear();

    Relation& r = RM.getRelation(rel);
    NotesManager& NM = NotesManager::donneInstance();
    int index = relation->findText(rel);
    if ( index != -1 ) {
        qDebug() << index;
       relation->setCurrentIndex(index);
    }

    for( Relation::Iterator it = r.getIterator() ; !it.isdone() ; it++){
        if((NM.getNote((*it)->getx()).etatToString() == "active") && (NM.getNote((*it)->gety()).etatToString() == "active" || r.getTitre() == "Reference" ) ){
            liste_couples->addItem((*it)->getx()+" -> "+(*it)->gety());
        }
    }
}

void RelationVizingWindow::editer_couple(){


    RelationManager& RM = RelationManager::donneInstance();

    Relation& r = RM.getRelation(relation->currentText());

    QString label_initial;
    Relation::Iterator it = r.getIterator();

    for( int i = 0 ; i<liste_couples->currentRow() ; i++) it++;

    if(label){
        label->setText((*it)->getLabel());
    }
    else{
        label_hbox = new QHBoxLayout;
        label_label = new QLabel("label");
        label_save = new QPushButton("ok");
        label = new QLineEdit((*it)->getLabel());
        connect(label_save, SIGNAL(clicked(bool)), this, SLOT(saveLabel()));

        label_hbox->addWidget(label); label_hbox->addWidget(label_save);

        fenetre_vbox->addWidget(label_label);
        fenetre_vbox->addLayout(label_hbox);

    }
}


void RelationVizingWindow::saveLabel(){
    if(this->label->text() != ""){
        RelationManager& RM = RelationManager::donneInstance();
        Relation& r = RM.getRelation(relation->currentText());
        qDebug() << label->text();
        QStringList liste =  liste_couples->currentItem()->text().split(" -> ");
        qDebug() << liste[0];
        qDebug() << liste[1];
        Couple& c = r.getCouple(liste[0],liste[1]);
        if(!r.getOrientee())
        {
            Couple& c2 = r.getCouple(liste[1],liste[0]);
            c.setLabel(label->text());
            c2.setLabel(label->text());
        }
        else
        {
            c.setLabel(label->text());
        }
        QMessageBox::information(this, "Bravo", "Sauvegarde Reussie !");

    }
    else
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("Entrez le Titre et une description");
    }
}



void RelationVizingWindow::deleteCouple(){
    if(relation->currentText() == "Reference")
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("On ne peut pas supprimer un couple de la relation Reference");
    }
    else if(liste_couples->currentRow() != -1)
    {
        RelationManager& RM = RelationManager::donneInstance();
        Relation& r = RM.getRelation(relation->currentText());
        QStringList liste =  liste_couples->currentItem()->text().split(" -> ");
        qDebug() << liste[0];
        qDebug() << liste[1];
        r.deleteCouple(liste[0],liste[1]);
        foreach (QWidget *widget, QApplication::topLevelWidgets()) {
            if ( widget->windowTitle() == "PluriNote")
            {
               qobject_cast<MainWindow*>(widget)->deleteCouple(relation->currentText(),liste[0],liste[1] );
            }
        }
        QMessageBox::information(this, "Bravo", "Supression Reussie !");
        //afficherCouples();
        if(label){
            fenetre_vbox->removeWidget(label_label);
            label_hbox->removeWidget(label);
            label_hbox->removeWidget(label_save);
            label->close();
            label_save->close();
            label_label->close();
            label = 0;
        }
    }
    else
    {
        QErrorMessage* em = new QErrorMessage;
        em->showMessage("Selectionnez un couple");
    }
}







