
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "notes.h"

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDateTime>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QListWidgetItem>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int number;
private slots:
    void on_btnSave_clicked();

    void on_btnArchive_clicked();

    void on_tbwNotes_itemDoubleClicked(QTableWidgetItem *item);

    void on_btnShowArchive_clicked();

    void on_btnShowNotes_clicked();

    void on_btnReestablish_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    void add_note_to_table(const Notes &note);
    void load_from_file(QString conditional="show all");
    void add_note_to_archive(const Notes &note);
    void load_archive(QString conditional="show all");
    void to_archive(int number);
    void from_archive(int number);
    void load_number();
    void update_number();
    void update_notes(int number);
    void update_archive(int number);
};
#endif // MAINWINDOW_H
