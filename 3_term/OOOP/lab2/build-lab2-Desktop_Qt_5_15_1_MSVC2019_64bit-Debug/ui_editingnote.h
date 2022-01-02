/********************************************************************************
** Form generated from reading UI file 'editingnote.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITINGNOTE_H
#define UI_EDITINGNOTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditingNote
{
public:
    QWidget *centralwidget;
    QLabel *label_HD;
    QTextEdit *textEdit;
    QLabel *label_TXT;
    QPushButton *btnSave;
    QPushButton *btnSave_2;
    QLabel *label;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EditingNote)
    {
        if (EditingNote->objectName().isEmpty())
            EditingNote->setObjectName(QString::fromUtf8("EditingNote"));
        EditingNote->resize(463, 459);
        centralwidget = new QWidget(EditingNote);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_HD = new QLabel(centralwidget);
        label_HD->setObjectName(QString::fromUtf8("label_HD"));
        label_HD->setGeometry(QRect(10, 10, 121, 21));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_HD->sizePolicy().hasHeightForWidth());
        label_HD->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        label_HD->setFont(font);
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 70, 441, 311));
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        label_TXT = new QLabel(centralwidget);
        label_TXT->setObjectName(QString::fromUtf8("label_TXT"));
        label_TXT->setGeometry(QRect(10, 40, 161, 21));
        sizePolicy.setHeightForWidth(label_TXT->sizePolicy().hasHeightForWidth());
        label_TXT->setSizePolicy(sizePolicy);
        label_TXT->setFont(font);
        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(10, 390, 201, 41));
        sizePolicy.setHeightForWidth(btnSave->sizePolicy().hasHeightForWidth());
        btnSave->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(13);
        btnSave->setFont(font1);
        btnSave_2 = new QPushButton(centralwidget);
        btnSave_2->setObjectName(QString::fromUtf8("btnSave_2"));
        btnSave_2->setGeometry(QRect(340, 390, 111, 41));
        sizePolicy.setHeightForWidth(btnSave_2->sizePolicy().hasHeightForWidth());
        btnSave_2->setSizePolicy(sizePolicy);
        btnSave_2->setFont(font1);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 10, 311, 21));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(9);
        label->setFont(font2);
        EditingNote->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(EditingNote);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        EditingNote->setStatusBar(statusbar);

        retranslateUi(EditingNote);

        QMetaObject::connectSlotsByName(EditingNote);
    } // setupUi

    void retranslateUi(QMainWindow *EditingNote)
    {
        EditingNote->setWindowTitle(QCoreApplication::translate("EditingNote", "MainWindow", nullptr));
        label_HD->setText(QCoreApplication::translate("EditingNote", "Node header:", nullptr));
        label_TXT->setText(QCoreApplication::translate("EditingNote", "Node text", nullptr));
        btnSave->setText(QCoreApplication::translate("EditingNote", "Edit and close", nullptr));
        btnSave_2->setText(QCoreApplication::translate("EditingNote", "Cancel", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EditingNote: public Ui_EditingNote {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITINGNOTE_H
