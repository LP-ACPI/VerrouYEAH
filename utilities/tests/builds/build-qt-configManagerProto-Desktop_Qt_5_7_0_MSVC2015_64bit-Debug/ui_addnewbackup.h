/********************************************************************************
** Form generated from reading UI file 'addnewbackup.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWBACKUP_H
#define UI_ADDNEWBACKUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddNewBackup
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *saveNameLabel;
    QLineEdit *saveNameInput;
    QHBoxLayout *horizontalLayout_2;
    QLabel *srcDirLabel;
    QPushButton *srcDirChoose;
    QHBoxLayout *horizontalLayout;
    QLabel *trgDirLabel;
    QPushButton *trgDirChoose;
    QLabel *commentLabel;
    QPlainTextEdit *commentInput;
    QDialogButtonBox *newBackupButtonBox;

    void setupUi(QDialog *AddNewBackup)
    {
        if (AddNewBackup->objectName().isEmpty())
            AddNewBackup->setObjectName(QStringLiteral("AddNewBackup"));
        AddNewBackup->resize(305, 405);
        layoutWidget = new QWidget(AddNewBackup);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 260, 352));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        saveNameLabel = new QLabel(layoutWidget);
        saveNameLabel->setObjectName(QStringLiteral("saveNameLabel"));

        horizontalLayout_3->addWidget(saveNameLabel);

        saveNameInput = new QLineEdit(layoutWidget);
        saveNameInput->setObjectName(QStringLiteral("saveNameInput"));

        horizontalLayout_3->addWidget(saveNameInput);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        srcDirLabel = new QLabel(layoutWidget);
        srcDirLabel->setObjectName(QStringLiteral("srcDirLabel"));

        horizontalLayout_2->addWidget(srcDirLabel);

        srcDirChoose = new QPushButton(layoutWidget);
        srcDirChoose->setObjectName(QStringLiteral("srcDirChoose"));

        horizontalLayout_2->addWidget(srcDirChoose);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 10);
        trgDirLabel = new QLabel(layoutWidget);
        trgDirLabel->setObjectName(QStringLiteral("trgDirLabel"));

        horizontalLayout->addWidget(trgDirLabel);

        trgDirChoose = new QPushButton(layoutWidget);
        trgDirChoose->setObjectName(QStringLiteral("trgDirChoose"));

        horizontalLayout->addWidget(trgDirChoose);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(verticalLayout_2);

        commentLabel = new QLabel(layoutWidget);
        commentLabel->setObjectName(QStringLiteral("commentLabel"));

        verticalLayout->addWidget(commentLabel);


        verticalLayout_3->addLayout(verticalLayout);

        commentInput = new QPlainTextEdit(layoutWidget);
        commentInput->setObjectName(QStringLiteral("commentInput"));
        commentInput->setEnabled(true);
        commentInput->setMaximumSize(QSize(256, 250));
        commentInput->setBaseSize(QSize(150, 150));

        verticalLayout_3->addWidget(commentInput);


        verticalLayout_4->addLayout(verticalLayout_3);

        newBackupButtonBox = new QDialogButtonBox(layoutWidget);
        newBackupButtonBox->setObjectName(QStringLiteral("newBackupButtonBox"));
        newBackupButtonBox->setOrientation(Qt::Horizontal);
        newBackupButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(newBackupButtonBox);

        QWidget::setTabOrder(saveNameInput, srcDirChoose);
        QWidget::setTabOrder(srcDirChoose, trgDirChoose);
        QWidget::setTabOrder(trgDirChoose, commentInput);

        retranslateUi(AddNewBackup);
        QObject::connect(newBackupButtonBox, SIGNAL(accepted()), AddNewBackup, SLOT(accept()));
        QObject::connect(newBackupButtonBox, SIGNAL(rejected()), AddNewBackup, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddNewBackup);
    } // setupUi

    void retranslateUi(QDialog *AddNewBackup)
    {
        AddNewBackup->setWindowTitle(QApplication::translate("AddNewBackup", "Dialog", 0));
        saveNameLabel->setText(QApplication::translate("AddNewBackup", "Nom", 0));
        srcDirLabel->setText(QApplication::translate("AddNewBackup", "Source", 0));
        srcDirChoose->setText(QApplication::translate("AddNewBackup", "choisir la source", 0));
        trgDirLabel->setText(QApplication::translate("AddNewBackup", "Cible", 0));
        trgDirChoose->setText(QApplication::translate("AddNewBackup", "choisir destination", 0));
        commentLabel->setText(QApplication::translate("AddNewBackup", "Commentaire:", 0));
    } // retranslateUi

};

namespace Ui {
    class AddNewBackup: public Ui_AddNewBackup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWBACKUP_H
