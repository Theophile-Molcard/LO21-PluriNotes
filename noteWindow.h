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
    QPushButton* getPushButton(){ return create_button; }
    QString getId(){ return id->text(); }
    QString getTitle(){ return title->text(); }
    QString getType(){ return type->currentText(); }

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


class MultimediaWindow : public QWidget{

    Q_OBJECT

public:
    MultimediaWindow(QString _id, QString _title, QWidget *parent = 0);

private:

    QVBoxLayout *fenetre_vbox;

    // ID
    QHBoxLayout *id_hbox;
    QLabel *id_label;
    QLabel *id;

    QHBoxLayout *title_hbox;
    QLabel *title_label;
    QLineEdit *title;

    QHBoxLayout *description_hbox;
    QLabel *description_label;
    QTextEdit *description;

    QHBoxLayout *fichier_hbox;
    QComboBox *fichier_type;
    QPushButton *fichier;

    QPushButton *save_button;

public slots:
    void save(){}

};



class TacheWindow : public QWidget{

    Q_OBJECT

public:
    TacheWindow(QString _id, QString _title, QWidget *parent = 0);

private:

    QVBoxLayout *fenetre_vbox;

    // ID
    QHBoxLayout *id_hbox;
    QLabel *id_label;
    QLabel *id;

    QHBoxLayout *title_hbox;
    QLabel *title_label;
    QLineEdit *title;

    QHBoxLayout *action_hbox;
    QLabel *action_label;
    QTextEdit *action;

    QHBoxLayout *priorite_hbox;
    QLabel *priorite_label;
    QLineEdit *priorite;

    QHBoxLayout *echeance_hbox;
    QLabel *echeance_label;
    QLineEdit *echeance;

    QHBoxLayout *statut_hbox;
    QLabel *statut_label;
    QComboBox *statut;

    QPushButton *save_button;

public slots:
    void save(){}

};

#endif // NOTEWINDOW_H
