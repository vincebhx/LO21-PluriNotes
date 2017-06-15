#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <vector>

class Widget;
/*!
 * \brief The Mediator class : Design Pattern Mediator : assure l'échange d'informations entre les différentes tout en conservant l'indépendance
 * de ces fenêtres entre elles, le mediator est un singleton
 */
class Mediator
{
public:
    /*!
     * \brief addComponent : ajoute un composant de type Widget au Mediator
     * \param w : Widget
     */
    void addComponent(Widget* w);
    /*!
     * \brief instance
     * \return instance unique du médiator
     */
    static Mediator* instance() ;
    /*!
     * \brief disributeMessage : distribue le message reçu à tous les composants du mediator
     * \param sender : composant envoyant le message
     * \param msg : message envoyé
     */
    void disributeMessage(Widget* sender, QString msg);

private:
    Mediator() : component() {};
    /*!
     * \brief component : vecteur de Widget composant le mediator
     */
    std::vector<Widget*> component;
    /*!
     * \brief _instance : instance unique du mediator
     */
    static Mediator* _instance;
};

/*!
 * \brief The Widget class : classe mère des autres fenêtres qui seront ajoutées au mediator
 */
class Widget
{
protected :
    /*!
     * \brief med : prend en attribut un mediator
     */
    Mediator* med;

public:
    Widget() : med(Mediator::instance()){}
    /*!
     * \brief sendMessage : distribue le message a tous les composants
     * \param msg
     */
    virtual void sendMessage(QString msg) { med->disributeMessage(this, msg); }
    /*!
     * \brief receiveMessage : instructions à executer lorsque le message "Ajout Note" est reçue, s'il n'y
     * pas d'instructions particulières à exécuter la fonction ne sera pas redéfinies dans les classes filles
     */
    virtual void receiveMessage(){}
    /*!
     * \brief receiveMessageCorbeille : instructions à executer lorsque le message "Corbeille" est reçue, s'il n'y
     * pas d'instructions particulières à exécuter la fonction ne sera pas redéfinies dans les classes filles
     */
    virtual void receiveMessageCorbeille(){}
    /*!
     * \brief receiveMessageARelation : instructions à executer lorsque le message "Ajout Relation" est reçue, s'il n'y
     * pas d'instructions particulières à exécuter la fonction ne sera pas redéfinies dans les classes filles
     */
    virtual void receiveMessageARelation() {}
    /*!
     * \brief receiveMessageMRelation : instructions à executer lorsque le message "Modification Note" est reçue, s'il n'y
     * pas d'instructions particulières à exécuter la fonction ne sera pas redéfinies dans les classes filles
     */
    virtual void receiveMessageMRelation() {}
    /*!
     * \brief getCode : retourne un code qui sera utilisée lors de la distribution des messages, elle sera réimplémentée dans chaque classe fille
     * \return le code au format QString
     */
    virtual QString getCode() = 0;

};

#endif // MEDIATOR_H
