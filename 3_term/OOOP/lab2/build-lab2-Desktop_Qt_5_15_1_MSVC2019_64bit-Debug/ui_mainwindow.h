/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableWidget *tbwNotes;
    QLabel *label_1;
    QPushButton *btnSave;
    QComboBox *cmbTypes;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *btnArchive;
    QTableWidget *tbwArchive;
    QPushButton *btnShowArchive;
    QPushButton *btnShowNotes;
    QPushButton *btnReestablish;
    QListWidget *listWidget;
    QLabel *label_4;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1253, 604);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1253, 604));
        MainWindow->setMaximumSize(QSize(1253, 604));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tbwNotes = new QTableWidget(centralwidget);
        if (tbwNotes->columnCount() < 5)
            tbwNotes->setColumnCount(5);
        QFont font;
        font.setPointSize(1);
        font.setKerning(false);
        font.setStyleStrategy(QFont::NoAntialias);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font);
        tbwNotes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        tbwNotes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        tbwNotes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        tbwNotes->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbwNotes->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tbwNotes->setObjectName(QString::fromUtf8("tbwNotes"));
        tbwNotes->setGeometry(QRect(320, 30, 791, 471));
        sizePolicy.setHeightForWidth(tbwNotes->sizePolicy().hasHeightForWidth());
        tbwNotes->setSizePolicy(sizePolicy);
        tbwNotes->setFrameShape(QFrame::StyledPanel);
        tbwNotes->setFrameShadow(QFrame::Sunken);
        tbwNotes->setLineWidth(0);
        tbwNotes->setAutoScroll(true);
        tbwNotes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbwNotes->setTabKeyNavigation(true);
        tbwNotes->setProperty("showDropIndicator", QVariant(true));
        tbwNotes->setDragDropOverwriteMode(true);
        tbwNotes->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tbwNotes->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbwNotes->setShowGrid(false);
        tbwNotes->setGridStyle(Qt::NoPen);
        tbwNotes->setWordWrap(false);
        tbwNotes->setCornerButtonEnabled(false);
        tbwNotes->setColumnCount(5);
        label_1 = new QLabel(centralwidget);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setGeometry(QRect(10, 130, 161, 21));
        sizePolicy.setHeightForWidth(label_1->sizePolicy().hasHeightForWidth());
        label_1->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(12);
        label_1->setFont(font1);
        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(10, 520, 111, 41));
        sizePolicy.setHeightForWidth(btnSave->sizePolicy().hasHeightForWidth());
        btnSave->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(13);
        btnSave->setFont(font2);
        cmbTypes = new QComboBox(centralwidget);
        cmbTypes->addItem(QString());
        cmbTypes->addItem(QString());
        cmbTypes->addItem(QString());
        cmbTypes->addItem(QString());
        cmbTypes->addItem(QString());
        cmbTypes->addItem(QString());
        cmbTypes->setObjectName(QString::fromUtf8("cmbTypes"));
        cmbTypes->setGeometry(QRect(120, 80, 111, 31));
        sizePolicy.setHeightForWidth(cmbTypes->sizePolicy().hasHeightForWidth());
        cmbTypes->setSizePolicy(sizePolicy);
        cmbTypes->setFont(font1);
        cmbTypes->setEditable(false);
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 160, 291, 341));
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 30, 291, 31));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 121, 21));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 80, 121, 31));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font1);
        btnArchive = new QPushButton(centralwidget);
        btnArchive->setObjectName(QString::fromUtf8("btnArchive"));
        btnArchive->setGeometry(QRect(600, 520, 161, 41));
        sizePolicy.setHeightForWidth(btnArchive->sizePolicy().hasHeightForWidth());
        btnArchive->setSizePolicy(sizePolicy);
        btnArchive->setFont(font2);
        tbwArchive = new QTableWidget(centralwidget);
        if (tbwArchive->columnCount() < 5)
            tbwArchive->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem5->setFont(font);
        tbwArchive->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignCenter);
        tbwArchive->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setTextAlignment(Qt::AlignCenter);
        tbwArchive->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setTextAlignment(Qt::AlignCenter);
        tbwArchive->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbwArchive->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        tbwArchive->setObjectName(QString::fromUtf8("tbwArchive"));
        tbwArchive->setGeometry(QRect(320, 30, 791, 471));
        sizePolicy.setHeightForWidth(tbwArchive->sizePolicy().hasHeightForWidth());
        tbwArchive->setSizePolicy(sizePolicy);
        tbwArchive->setFrameShape(QFrame::StyledPanel);
        tbwArchive->setFrameShadow(QFrame::Sunken);
        tbwArchive->setLineWidth(0);
        tbwArchive->setAutoScroll(true);
        tbwArchive->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbwArchive->setTabKeyNavigation(true);
        tbwArchive->setProperty("showDropIndicator", QVariant(true));
        tbwArchive->setDragDropOverwriteMode(true);
        tbwArchive->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tbwArchive->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbwArchive->setShowGrid(false);
        tbwArchive->setGridStyle(Qt::NoPen);
        tbwArchive->setWordWrap(false);
        tbwArchive->setCornerButtonEnabled(false);
        tbwArchive->setColumnCount(5);
        btnShowArchive = new QPushButton(centralwidget);
        btnShowArchive->setObjectName(QString::fromUtf8("btnShowArchive"));
        btnShowArchive->setGeometry(QRect(1130, 80, 111, 41));
        sizePolicy.setHeightForWidth(btnShowArchive->sizePolicy().hasHeightForWidth());
        btnShowArchive->setSizePolicy(sizePolicy);
        btnShowArchive->setFont(font2);
        btnShowNotes = new QPushButton(centralwidget);
        btnShowNotes->setObjectName(QString::fromUtf8("btnShowNotes"));
        btnShowNotes->setGeometry(QRect(1130, 80, 111, 41));
        sizePolicy.setHeightForWidth(btnShowNotes->sizePolicy().hasHeightForWidth());
        btnShowNotes->setSizePolicy(sizePolicy);
        btnShowNotes->setFont(font2);
        btnReestablish = new QPushButton(centralwidget);
        btnReestablish->setObjectName(QString::fromUtf8("btnReestablish"));
        btnReestablish->setGeometry(QRect(600, 520, 161, 41));
        sizePolicy.setHeightForWidth(btnReestablish->sizePolicy().hasHeightForWidth());
        btnReestablish->setSizePolicy(sizePolicy);
        btnReestablish->setFont(font2);
        listWidget = new QListWidget(centralwidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(1120, 190, 121, 221));
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setFont(font1);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1120, 160, 121, 21));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tbwNotes->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Header", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tbwNotes->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tbwNotes->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Group", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tbwNotes->horizontalHeaderItem(4);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Text", nullptr));
        label_1->setText(QCoreApplication::translate("MainWindow", "Node text", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        cmbTypes->setItemText(0, QCoreApplication::translate("MainWindow", "default", nullptr));
        cmbTypes->setItemText(1, QCoreApplication::translate("MainWindow", "daily", nullptr));
        cmbTypes->setItemText(2, QCoreApplication::translate("MainWindow", "home", nullptr));
        cmbTypes->setItemText(3, QCoreApplication::translate("MainWindow", "travel", nullptr));
        cmbTypes->setItemText(4, QCoreApplication::translate("MainWindow", "personal", nullptr));
        cmbTypes->setItemText(5, QCoreApplication::translate("MainWindow", "work", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Node header", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Node type:", nullptr));
        btnArchive->setText(QCoreApplication::translate("MainWindow", "Add to archieve", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tbwArchive->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Header", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tbwArchive->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tbwArchive->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Group", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tbwArchive->horizontalHeaderItem(4);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Text", nullptr));
        btnShowArchive->setText(QCoreApplication::translate("MainWindow", "Archive", nullptr));
        btnShowNotes->setText(QCoreApplication::translate("MainWindow", "Notes", nullptr));
        btnReestablish->setText(QCoreApplication::translate("MainWindow", "Reestablish", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "default", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "daily", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MainWindow", "home", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("MainWindow", "travel", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("MainWindow", "personal", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("MainWindow", "work", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("MainWindow", "show all", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        label_4->setText(QCoreApplication::translate("MainWindow", "Filter:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
