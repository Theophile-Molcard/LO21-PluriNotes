#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QFileDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateTimeEdit>


class NoteWindow : public QWidget{

    Q_OBJECT

public:
    NoteWindow(QWidget *parent = 0);
    QPushButton* getPushButton(){ return create_button; }
    QString getId() const { return id->text(); }
    QString getTitle() const { return title->text(); }
    QString getType() const { return type->currentText(); }

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

    QHBoxLayout *button_hbox;
    QPushButton *create_button;
    QPushButton *close_button;

};



class ArticleWindow : public QWidget{

    Q_OBJECT

public:
    ArticleWindow(QString _id, QString _title, QWidget *parent = 0);
    QString getTitle() const { return title->text(); }
    QString getText() const { return text->toPlainText(); }

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

    QHBoxLayout *button_hbox;
    QPushButton *save_button;
    QPushButton *close_button;

public slots:
    void save();

};


class MultimediaWindow : public QWidget{

    Q_OBJECT

public:
    MultimediaWindow(QString _id, QString _title, QWidget *parent = 0);
    QString getTitle() const { return title->text(); }
    QString getDescription() const { return description->toPlainText(); }
    QString getType() const { return fichier_type->currentText(); }

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

    QLabel *printed_path;
    QString path;

    QHBoxLayout *button_hbox;
    QPushButton *save_button;
    QPushButton *close_button;

public slots:
    void save();
    void trouveFichier();

};



class TacheWindow : public QWidget{

    Q_OBJECT

public:
    TacheWindow(QString _id, QString _title, QWidget *parent = 0);
    QString getTitle() const { return title->text(); }
    QString getAction() const { return action->toPlainText(); }
    QString getPriorite() const { return priorite->text(); }
    QDateTime getEcheance() const { return echeance->dateTime(); }
    QString getStatut() const { return statut->currentText(); }

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
    QDateTimeEdit *echeance;

    QHBoxLayout *statut_hbox;
    QLabel *statut_label;
    QComboBox *statut;

    QHBoxLayout *button_hbox;
    QPushButton *save_button;
    QPushButton *close_button;

public slots:
    void save();

};

#endif // NOTEWINDOW_H
