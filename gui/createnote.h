#ifndef CREATENOTE_H
#define CREATENOTE_H

#include <QDialog>
#include <QTextEdit>

namespace Ui {
class CreateNote;
}

class CreateNote : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNote(QWidget *parent = 0);
    ~CreateNote();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateNote *ui;
};



#endif // CREATENOTE_H
