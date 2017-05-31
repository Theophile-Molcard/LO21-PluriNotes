#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>

#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>


class NoteWindow : public QWidget{

    Q_OBJECT

public:
    NoteWindow(QWidget *parent = 0);
    void editeur_article();
    void editeur_multimedia(){}
    void editeur_tache(){}

private:

    QVBoxLayout *fenetre_vbox;

    // ID
    QHBoxLayout *id_hbox;
    QLabel *id_label;
    QLineEdit *id;

    QHBoxLayout *title_hbox;
    QLabel *title_label;
    QLineEdit *title;

    QHBoxLayout *type_hbox;
    QLabel *type_label;
    QComboBox *type;


    QPushButton *create_button;

public slots:
    void create() {
        if(type->currentText() == "Article")            editeur_article();
        else if(type->currentText() == "Multimedia")    editeur_multimedia();
        else if(type->currentText() == "Tache")         editeur_tache();
    }

};



class ArticleWindow : public QWidget{

    Q_OBJECT

public:
    ArticleWindow(QString _id, QString _title, QWidget *parent = 0);

private:

    QVBoxLayout *fenetre_vbox;

    // ID
    QHBoxLayout *id_hbox;
    QLabel *id_label;
    QLabel *id;

    QHBoxLayout *title_hbox;
    QLabel *title_label;
    QLineEdit *title;

    QHBoxLayout *text_hbox;
    QLabel *text_label;
    QTextEdit *text;

    QPushButton *save_button;

public slots:
    void save(){}

};

#endif // NOTEWINDOW_H
