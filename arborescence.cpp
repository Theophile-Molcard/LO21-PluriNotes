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
    NotesManager& NM = NotesManager::donneInstance();
    RelationManager& RM = RelationManager::donneInstance();
    Relation* rel;
    Couple* cpl;

    for( RelationManager::Iterator r_it = RM.getIterator() ; !r_it.isdone() ; r_it++)
    {
        rel = *r_it;

        for( Relation::Iterator c_it = rel->getIterator() ; !c_it.isdone() ; c_it++)
        {
            cpl = *c_it;
            if(cpl->gety()==note.getId() && !id_asc_root.contains(cpl->getx())){
                if((NM.getNote(cpl->getx()).etatToString() == "active" || (NM.getNote(cpl->getx()).etatToString() == "archive" && rel->getTitre() == "Reference" ))){
                    id_asc_root.append(cpl->getx());
                    setAscendants( cpl->getx(), addRoot(ascendants, cpl->getx()) );
                }
            }
        }


    }

}

void Arborescence::setAscendants(QString id, QTreeWidgetItem* tree){
    id_asc.append(id);
    NotesManager& NM = NotesManager::donneInstance();
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
                if((NM.getNote(cpl->getx()).etatToString() == "active" || (NM.getNote(cpl->getx()).etatToString() == "archive" && rel->getTitre() == "Reference" )) ){
                    setAscendants(cpl->getx(), addChild(tree, cpl->getx()));
                }
            }
        }


    }

}

void Arborescence::setDescendantsRacine(Note& note){
    NotesManager& NM = NotesManager::donneInstance();
    RelationManager& RM = RelationManager::donneInstance();
    Relation* rel;
    Couple* cpl;

    for( RelationManager::Iterator r_it = RM.getIterator() ; !r_it.isdone() ; r_it++)
    {
        rel = *r_it;

        for( Relation::Iterator c_it = rel->getIterator() ; !c_it.isdone() ; c_it++)
        {
            cpl = *c_it;
            if(cpl->getx()==note.getId() && !id_dsc_root.contains(cpl->gety())){
                if( (NM.getNote(cpl->gety()).etatToString() == "active" || (NM.getNote(cpl->gety()).etatToString() == "archive" && rel->getTitre() == "Reference" )) ){
                    id_dsc_root.append(cpl->gety());
                    setDescendants( cpl->gety(), addRoot(descendants, cpl->gety()) );
                }
            }
        }


    }

}

void Arborescence::setDescendants(QString id, QTreeWidgetItem* tree){
    id_dsc.append(id);
    NotesManager& NM = NotesManager::donneInstance();
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
                if( (NM.getNote(cpl->gety()).etatToString() == "active" || (NM.getNote(cpl->gety()).etatToString() == "archive" && rel->getTitre() == "Reference" )) ){
                    setDescendants(cpl->gety(), addChild(tree, cpl->gety()));
                }
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




















