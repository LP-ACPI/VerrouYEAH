/********************************************************************************
** Form generated from reading UI file 'formsauvegarde.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMSAUVEGARDE_H
#define UI_FORMSAUVEGARDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormSauvegarde
{
public:
    QLineEdit *lineEdit;
    QLabel *icon;
    QLabel *label_2;
    QLineEdit *sourceInput;
    QPushButton *sourceChoiceButton;
    QPushButton *targetChoiceButton;
    QLineEdit *targetInput;
    QLabel *label_3;
    QDialogButtonBox *authButtonBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QTimeEdit *timeEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QTextEdit *notesInput;

    void setupUi(QWidget *FormSauvegarde)
    {
        if (FormSauvegarde->objectName().isEmpty())
            FormSauvegarde->setObjectName(QStringLiteral("FormSauvegarde"));
        FormSauvegarde->resize(371, 391);
        lineEdit = new QLineEdit(FormSauvegarde);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 30, 251, 31));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        lineEdit->setFont(font);
        lineEdit->setStyleSheet(QStringLiteral(""));
        lineEdit->setFrame(false);
        icon = new QLabel(FormSauvegarde);
        icon->setObjectName(QStringLiteral("icon"));
        icon->setGeometry(QRect(270, 30, 41, 31));
        label_2 = new QLabel(FormSauvegarde);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 90, 51, 31));
        sourceInput = new QLineEdit(FormSauvegarde);
        sourceInput->setObjectName(QStringLiteral("sourceInput"));
        sourceInput->setGeometry(QRect(110, 90, 121, 31));
        sourceChoiceButton = new QPushButton(FormSauvegarde);
        sourceChoiceButton->setObjectName(QStringLiteral("sourceChoiceButton"));
        sourceChoiceButton->setGeometry(QRect(230, 90, 61, 31));
        targetChoiceButton = new QPushButton(FormSauvegarde);
        targetChoiceButton->setObjectName(QStringLiteral("targetChoiceButton"));
        targetChoiceButton->setGeometry(QRect(230, 150, 61, 31));
        targetInput = new QLineEdit(FormSauvegarde);
        targetInput->setObjectName(QStringLiteral("targetInput"));
        targetInput->setGeometry(QRect(110, 150, 121, 31));
        label_3 = new QLabel(FormSauvegarde);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 150, 51, 31));
        authButtonBox = new QDialogButtonBox(FormSauvegarde);
        authButtonBox->setObjectName(QStringLiteral("authButtonBox"));
        authButtonBox->setGeometry(QRect(30, 330, 281, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Monospace"));
        font1.setPointSize(12);
        authButtonBox->setFont(font1);
        authButtonBox->setStyleSheet(QStringLiteral(""));
        authButtonBox->setOrientation(Qt::Horizontal);
        authButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        authButtonBox->setCenterButtons(false);
        layoutWidget = new QWidget(FormSauvegarde);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 200, 281, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        timeEdit = new QTimeEdit(layoutWidget);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));

        horizontalLayout->addWidget(timeEdit);

        layoutWidget1 = new QWidget(FormSauvegarde);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 240, 281, 81));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_2->addWidget(label_5);

        notesInput = new QTextEdit(layoutWidget1);
        notesInput->setObjectName(QStringLiteral("notesInput"));

        horizontalLayout_2->addWidget(notesInput);


        retranslateUi(FormSauvegarde);

        QMetaObject::connectSlotsByName(FormSauvegarde);
    } // setupUi

    void retranslateUi(QWidget *FormSauvegarde)
    {
        FormSauvegarde->setWindowTitle(QApplication::translate("FormSauvegarde", "Form", 0));
        lineEdit->setText(QApplication::translate("FormSauvegarde", "Nom Sauvegarde", 0));
        icon->setText(QApplication::translate("FormSauvegarde", "icon", 0));
        label_2->setText(QApplication::translate("FormSauvegarde", "Source", 0));
        sourceChoiceButton->setText(QString());
        targetChoiceButton->setText(QString());
        label_3->setText(QApplication::translate("FormSauvegarde", "Cible", 0));
        label_4->setText(QApplication::translate("FormSauvegarde", "Fr\303\251quence", 0));
        label_5->setText(QApplication::translate("FormSauvegarde", "Notes", 0));
    } // retranslateUi

};

namespace Ui {
    class FormSauvegarde: public Ui_FormSauvegarde {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSAUVEGARDE_H
