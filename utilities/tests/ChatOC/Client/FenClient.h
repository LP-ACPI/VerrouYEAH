#ifndef H_FENCLIENT
#define H_FENCLIENT

#include <QtWidgets>
#include <QtNetwork>
#include "ui_FenClient.h"


class FenClient : public QWidget, private Ui::FenClient
{
    Q_OBJECT

    public:
        FenClient();

    private slots:
        void on_boutonConnexion_clicked();
        void on_boutonEnvoyer_clicked();
        void on_message_returnPressed();
        void donneesRecues();
        void connecte();
        void deconnecte();
        void erreurSocket(QAbstractSocket::SocketError erreur);

    private:
        QTcpSocket *socket; // Représente le serveur
        quint16 tailleMessage;
};

#endif // H_FENCLIENT
