#include "arborescence.h"
#include "Notes.h"
#include "relations.h"

Arborescence::Arborescence(Note& note, QWidget *parent): QWidget(parent)
{

    setFixedSize(200, 400);
    move(600, 40);


    fenetre_vbox = new QVBoxLayout;

    label_hbox = new QHBoxLayout;
    id_label = new QLabel(note.getId());
    titre_label = new QLabel(note.getTitre());

    label_hbox->addWidget(id_label);
    label_hbox->addWidget(titre_label);

    ascendants = new QTreeWidget;
    setAscendantsRacine(note);

    descendants = new QTreeWidget;
    setDescendantsRacine(note);

    fenetre_vbox->addWidget(ascendants);
    fenetre_vbox->addLayout(label_hbox);
    fenetre_vbox->addWidget(descendants);


    this->setLayout(fenetre_vbox);
}


void Arborescence::setAscendantsRacine(Note& note){
    RelationManager& RM = RelationManager::donneInstance();
    Relation* rel;
    Couple* cpl;

    for( RelationManager::Iterator r_it = RM.getIterator() ; !r_it.isdone() ; r_it++)
    {
        rel = *r_it;

        for( Relation::Iterator c_it = rel->getIterator() ; !c_it.isdone() ; c_it++)
        {
            cpl = *c_it;
            if(cpl->gety()==note.getId()){
                id_asc.append(cpl->getx());
                setAscendants( cpl->getx(), addRoot(ascendants, cpl->getx()) );
            }
        }


    }

}

void Arborescence::setAscendants(QString id, QTreeWidgetItem* tree){
    RelationManager& RM = RelationManager::donneInstance();
    Relation* rel;
    Couple* cpl;

    for( RelationManager::Iterator r_it = RM.getIterator() ; !r_it.isdone() ; r_it++)
    {
        rel = *r_it;

        for( Relation::Iterator c_it = rel->getIterator() ; !c_it.isdone() ; c_it++)
        {
            cpl = *c_it;
            if(cpl->gety()==id && !id_asc.contains(cpl->getx())){
                id_asc.append(cpl->getx());
                setAscendants(cpl->getx(), addChild(tree, cpl->getx()));
            }
        }


    }

}

void Arborescence::setDescendantsRacine(Note& note){
    RelationManager& RM = RelationManager::donneInstance();
    Relation* rel;
    Couple* cpl;

    for( RelationManager::Iterator r_it = RM.getIterator() ; !r_it.isdone() ; r_it++)
    {
        rel = *r_it;

        for( Relation::Iterator c_it = rel->getIterator() ; !c_it.isdone() ; c_it++)
        {
            cpl = *c_it;
            if(cpl->getx()==note.getId()){
                id_dsc.append(cpl->gety());
                setAscendants( cpl->gety(), addRoot(descendants, cpl->gety()) );
            }
        }


    }

}

void Arborescence::setDescendants(QString id, QTreeWidgetItem* tree){
    RelationManager& RM = RelationManager::donneInstance();
    Relation* rel;
    Couple* cpl;

    for( RelationManager::Iterator r_it = RM.getIterator() ; !r_it.isdone() ; r_it++)
    {
        rel = *r_it;

        for( Relation::Iterator c_it = rel->getIterator() ; !c_it.isdone() ; c_it++)
        {
            cpl = *c_it;
            if(cpl->getx()==id && !id_dsc.contains(cpl->gety())){
                id_dsc.append(cpl->gety());
                setAscendants(cpl->gety(), addChild(tree, cpl->gety()));
            }
        }


    }

}


QTreeWidgetItem* Arborescence::addRoot(QTreeWidget *parent, QString nom){
    QTreeWidgetItem* itm = new QTreeWidgetItem(parent);
    itm->setText(0, nom);

    parent->addTopLevelItem(itm);
    return itm;
}

QTreeWidgetItem* Arborescence::addChild(QTreeWidgetItem *parent, QString nom){
    QTreeWidgetItem* itm = new QTreeWidgetItem(parent);
    itm->setText(0, nom);

    parent->addChild(itm);
    return itm;

}


















