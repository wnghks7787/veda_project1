/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *idPwVLayout;
    QHBoxLayout *idHLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit;
    QVBoxLayout *buttonVLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(508, 152);
        horizontalLayout_2 = new QHBoxLayout(Widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        checkBox = new QCheckBox(Widget);
        checkBox->setObjectName("checkBox");

        horizontalLayout_2->addWidget(checkBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        idPwVLayout = new QVBoxLayout();
        idPwVLayout->setObjectName("idPwVLayout");
        idHLayout = new QHBoxLayout();
        idHLayout->setObjectName("idHLayout");
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");

        idHLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(Widget);
        lineEdit_2->setObjectName("lineEdit_2");

        idHLayout->addWidget(lineEdit_2);


        idPwVLayout->addLayout(idHLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(Widget);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_3->addWidget(lineEdit);


        idPwVLayout->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(idPwVLayout);

        buttonVLayout = new QVBoxLayout();
        buttonVLayout->setObjectName("buttonVLayout");
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName("pushButton");

        buttonVLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName("pushButton_2");

        buttonVLayout->addWidget(pushButton_2);


        horizontalLayout->addLayout(buttonVLayout);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 1);

        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        checkBox->setText(QCoreApplication::translate("Widget", "CheckBox", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "ID", nullptr));
        label->setText(QCoreApplication::translate("Widget", "PW", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "Login", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "Sign Up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
