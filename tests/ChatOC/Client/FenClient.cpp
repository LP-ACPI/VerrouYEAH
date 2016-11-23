#include "FenClient.h"

/**
 *      Constructeur de la fenêtre du client
 *
 * @brief FenClient::FenClient
 */
FenClient::FenClient()
{
    setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    tailleMessage = 0;
}


/**
 * Tentative de connexion au serveur - clic sur "connexion"
 *
 * @brief FenClient::on_boutonConnexion_clicked
 */
void FenClient::on_boutonConnexion_clicked()
{
    // On annonce sur la fenêtre qu'on est en train de se connecter
    listeMessages->append(tr("<em>Tentative de connexion en cours...</em>"));
    boutonConnexion->setEnabled(false);

    socket->abort(); // On désactive les connexions précédentes s'il y en a
    socket->connectToHost(serveurIP->text(), serveurPort->value()); // On se connecte au serveur demandé
}


/**
 * Envoi d'un message au serveur - clic sur "envoyer"
 *
 * @brief FenClient::on_boutonEnvoyer_clicked
 */
void FenClient::on_boutonEnvoyer_clicked()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    // On prépare le paquet à envoyer
    QString messageAEnvoyer = tr("<strong>") + pseudo->text() +tr("</strong> : ") + message->text();

    out << (quint16) 0;
    out << messageAEnvoyer;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet); // On envoie le paquet

    message->clear(); // On vide la zone d'écriture du message
    message->setFocus(); // Et on remet le curseur à l'intérieur
}

/**
 * gestion de l'appui sur entrée - simuler clic sur "envoyer"
 * @brief FenClient::on_message_returnPressed
 */
void FenClient::on_message_returnPressed()
{
    on_boutonEnvoyer_clicked();
}

/**
 *
 * Slot appelé sur réception des paquets de données depuis le serveur
 *
 * @brief FenClient::donneesRecues
 */
void FenClient::donneesRecues()
{
    /* Même principe que lorsque le serveur reçoit un paquet :
    On essaie de récupérer la taille du message
    Une fois qu'on l'a, on attend d'avoir reçu le message entier (en se basant sur la taille annoncée tailleMessage)
    */
    QDataStream in(socket);

    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> tailleMessage;
    }

    if (socket->bytesAvailable() < tailleMessage)
        return;


    // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
    QString messageRecu;
    in >> messageRecu;

    // On affiche le message sur la zone de Chat
    listeMessages->append(messageRecu);

    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}

/**
 *
 *  slot appelé lorsque la connexion au serveur a réussi
 *
 * @brief FenClient::connecte
 */
void FenClient::connecte()
{
    listeMessages->append(tr("<em>Connexion réussie !</em>"));
    boutonConnexion->setEnabled(true);
}

/**
 *
 * Slot  appelé sur déconnexion du serveur
 *
 * @brief FenClient::deconnecte
 */
void FenClient::deconnecte()
{
    listeMessages->append(tr("<em>Déconnecté du serveur</em>"));
}


/**
 *
 * Slot appelé sur détection d'erreur de socket
 *
 * @brief FenClient::erreurSocket
 * @param erreur
 */
void FenClient::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            listeMessages->append(tr("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            listeMessages->append(tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            listeMessages->append(tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
            break;
        default:
            listeMessages->append(tr("<em>ERREUR : ") + socket->errorString() + tr("</em>"));
    }

    boutonConnexion->setEnabled(true);
}
