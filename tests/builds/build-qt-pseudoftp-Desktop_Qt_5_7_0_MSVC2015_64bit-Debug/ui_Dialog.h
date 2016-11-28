/********************************************************************************
** Form generated from reading UI file 'Dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *logo;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QPushButton *transferButton;
    QPushButton *quitButton;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *transferChoice;
    QRadioButton *downloadChoice;
    QRadioButton *uploadChoice;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *serverLabel;
    QLineEdit *serverInput;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *clientLabel;
    QToolButton *file_dirChoice;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QComboBox *protoChoice;
    QLineEdit *hostInput;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *userInput;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *pwdInput;
    QButtonGroup *TransferChoice;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(398, 262);
        logo = new QLabel(Dialog);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(10, 30, 121, 91));
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 220, 158, 25));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        transferButton = new QPushButton(layoutWidget);
        transferButton->setObjectName(QStringLiteral("transferButton"));

        formLayout->setWidget(0, QFormLayout::LabelRole, transferButton);

        quitButton = new QPushButton(layoutWidget);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setMinimumSize(QSize(0, 23));
        quitButton->setMaximumSize(QSize(75, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, quitButton);

        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 150, 349, 53));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        transferChoice = new QVBoxLayout();
        transferChoice->setObjectName(QStringLiteral("transferChoice"));
        downloadChoice = new QRadioButton(layoutWidget1);
        TransferChoice = new QButtonGroup(Dialog);
        TransferChoice->setObjectName(QStringLiteral("TransferChoice"));
        TransferChoice->addButton(downloadChoice);
        downloadChoice->setObjectName(QStringLiteral("downloadChoice"));

        transferChoice->addWidget(downloadChoice);

        uploadChoice = new QRadioButton(layoutWidget1);
        TransferChoice->addButton(uploadChoice);
        uploadChoice->setObjectName(QStringLiteral("uploadChoice"));

        transferChoice->addWidget(uploadChoice);


        horizontalLayout_7->addLayout(transferChoice);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        serverLabel = new QLabel(layoutWidget1);
        serverLabel->setObjectName(QStringLiteral("serverLabel"));
        serverLabel->setStyleSheet(QStringLiteral(""));

        horizontalLayout_4->addWidget(serverLabel);

        serverInput = new QLineEdit(layoutWidget1);
        serverInput->setObjectName(QStringLiteral("serverInput"));

        horizontalLayout_4->addWidget(serverInput);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        clientLabel = new QLabel(layoutWidget1);
        clientLabel->setObjectName(QStringLiteral("clientLabel"));
        clientLabel->setStyleSheet(QStringLiteral(""));

        horizontalLayout_5->addWidget(clientLabel);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        file_dirChoice = new QToolButton(layoutWidget1);
        file_dirChoice->setObjectName(QStringLiteral("file_dirChoice"));
        file_dirChoice->setStyleSheet(QStringLiteral("width: 130px; "));

        horizontalLayout_6->addWidget(file_dirChoice);


        verticalLayout_3->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_3);

        widget = new QWidget(Dialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(142, 20, 237, 22));
        horizontalLayout_8 = new QHBoxLayout(widget);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout_8->addWidget(label);

        protoChoice = new QComboBox(widget);
        protoChoice->setObjectName(QStringLiteral("protoChoice"));

        horizontalLayout_8->addWidget(protoChoice);

        hostInput = new QLineEdit(widget);
        hostInput->setObjectName(QStringLiteral("hostInput"));

        horizontalLayout_8->addWidget(hostInput);

        widget1 = new QWidget(Dialog);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(142, 60, 202, 22));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        horizontalLayout_2->addWidget(label_4);

        userInput = new QLineEdit(widget1);
        userInput->setObjectName(QStringLiteral("userInput"));
        userInput->setStyleSheet(QLatin1String("lineEdit_3{\n"
"	border-radius: 4px;\n"
"}"));

        horizontalLayout_2->addWidget(userInput);

        widget2 = new QWidget(Dialog);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(142, 100, 220, 22));
        horizontalLayout_3 = new QHBoxLayout(widget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        horizontalLayout_3->addWidget(label_5);

        pwdInput = new QLineEdit(widget2);
        pwdInput->setObjectName(QStringLiteral("pwdInput"));
        pwdInput->setContextMenuPolicy(Qt::ActionsContextMenu);
        pwdInput->setAutoFillBackground(false);
        pwdInput->setStyleSheet(QStringLiteral(""));
        pwdInput->setFrame(true);
        pwdInput->setEchoMode(QLineEdit::Password);
        pwdInput->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_3->addWidget(pwdInput);

        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        logo->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        logo->setText(QString());
        transferButton->setText(QApplication::translate("Dialog", "Tranf\303\251rer", 0));
        quitButton->setText(QApplication::translate("Dialog", "Quitter", 0));
        downloadChoice->setText(QApplication::translate("Dialog", "T\303\251l\303\251charger", 0));
        uploadChoice->setText(QApplication::translate("Dialog", "Upload", 0));
        serverLabel->setText(QApplication::translate("Dialog", "Fichier \303\240 t\303\251l\303\251charger:", 0));
        clientLabel->setText(QApplication::translate("Dialog", "Dossier de destination:", 0));
        file_dirChoice->setText(QApplication::translate("Dialog", "...", 0));
        label->setText(QApplication::translate("Dialog", "H\303\264te", 0));
        protoChoice->clear();
        protoChoice->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "ftp://", 0)
         << QApplication::translate("Dialog", "sftp://", 0)
         << QApplication::translate("Dialog", "http://", 0)
         << QApplication::translate("Dialog", "https://", 0)
        );
        label_4->setText(QApplication::translate("Dialog", "utilisateur:", 0));
        label_5->setText(QApplication::translate("Dialog", "mot de passe:", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
