#ifndef AJOUTERRELATION_H
#define AJOUTERRELATION_H

#include <QDialog>

namespace Ui {
class AjouterRelation;
}

class AjouterRelation : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterRelation(QWidget *parent = 0);
    ~AjouterRelation();

private:
    Ui::AjouterRelation *ui;
};

#endif // AJOUTERRELATION_H
