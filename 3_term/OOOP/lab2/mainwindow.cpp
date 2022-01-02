#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "notes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tbwNotes->setColumnWidth(0,1);
    ui->tbwNotes->setColumnWidth(1,100);
    ui->tbwNotes->setColumnWidth(2,180);
    ui->tbwNotes->setColumnWidth(3,75);
    ui->tbwNotes->setColumnWidth(4,320);
    ui->tbwNotes->setColumnHidden(0,true);
    ui->tbwArchive->setColumnWidth(0,1);
    ui->tbwArchive->setColumnWidth(1,100);
    ui->tbwArchive->setColumnWidth(2,180);
    ui->tbwArchive->setColumnWidth(3,75);
    ui->tbwArchive->setColumnWidth(4,320);
    ui->tbwArchive->setColumnHidden(0,true);
    ui->tbwArchive->setHidden(true);
    ui->btnShowNotes->setHidden(true);
    ui->btnReestablish->setHidden(true);
    ui->listWidget->setCurrentRow(6);
    load_number();
    load_from_file();
    load_archive();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_note_to_table(const Notes &note)
{
    int rows = ui->tbwNotes->rowCount();
    ui->tbwNotes->setRowCount(rows+1);

    QTableWidgetItem* item = new QTableWidgetItem(QString::number(note.number()));
    ui->tbwNotes->setItem(rows, 0, item);

    item = new QTableWidgetItem(note.header());
    ui->tbwNotes->setItem(rows, 1, item);

    item = new QTableWidgetItem(note.current_date());
    ui->tbwNotes->setItem(rows, 2, item);

    item = new QTableWidgetItem(note.group());
    ui->tbwNotes->setItem(rows, 3, item);

    item = new QTableWidgetItem(note.note_text());
    ui->tbwNotes->setItem(rows, 4, item);
}

void MainWindow::load_from_file(QString conditional)
{
    QFile file{"data.txt"};
    ui->tbwNotes->clearContents();
    ui->tbwNotes->setRowCount(0);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    Notes current_note;
    while (!in.atEnd())
    {
        current_note.setNumber(in.readLine().toInt());
        QString line = in.readLine();
        current_note.setHeader(line);
        line=in.readLine();
        current_note.setDate(line);
        line=in.readLine();
        current_note.setGroup(line);
        line=in.readLine();
        QString text="";
        do
        {
            text+=line;
            text+="\n";
            line=in.readLine();
        } while(line!="*#*");
        current_note.setNoteText(text);
        if(conditional=="show all")
        {
            add_note_to_table(current_note);
        }
        else if(conditional==current_note.group())
        {
            add_note_to_table(current_note);
        }
    }
    file.close();
    ui->tbwNotes->sortByColumn(2,Qt::AscendingOrder);
}

void MainWindow::add_note_to_archive(const Notes &note)
{
    int rows = ui->tbwArchive->rowCount();
    ui->tbwArchive->setRowCount(rows+1);

    QTableWidgetItem* item = new QTableWidgetItem(QString::number(note.number()));
    ui->tbwArchive->setItem(rows, 0, item);

    item = new QTableWidgetItem(note.header());
    ui->tbwArchive->setItem(rows, 1, item);

    item = new QTableWidgetItem(note.current_date());
    ui->tbwArchive->setItem(rows, 2, item);

    item = new QTableWidgetItem(note.group());
    ui->tbwArchive->setItem(rows, 3, item);

    item = new QTableWidgetItem(note.note_text());
    ui->tbwArchive->setItem(rows, 4, item);
}

void MainWindow::load_archive(QString conditional)
{
    QFile file{"archive.txt"};
    ui->tbwArchive->clearContents();
    ui->tbwArchive->setRowCount(0);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    Notes current_note;
    while (!in.atEnd())
    {
        current_note.setNumber(in.readLine().toInt());
        QString line = in.readLine();
        current_note.setHeader(line);
        line=in.readLine();
        current_note.setDate(line);
        line=in.readLine();
        current_note.setGroup(line);
        line=in.readLine();
        QString text="";
        do
        {
            text+=line;
            text+="\n";
            line=in.readLine();
        } while(line!="*#*");
        current_note.setNoteText(text);
        if(conditional=="show all")
        {
            add_note_to_archive(current_note);
        }
        else if(conditional==current_note.group())
        {
            add_note_to_archive(current_note);
        }
    }
    file.close();
    ui->tbwArchive->sortByColumn(2,Qt::AscendingOrder);
}

void MainWindow::to_archive(int number)
{
    QFile archive{"archive.txt"};
    if (!archive.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;
    QFile file{"data.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream stream_a(&archive);
    QTextStream stream_f(&file);
    QString line;

    while(!stream_f.atEnd())
    {
        line=stream_f.readLine();
        if(line.toInt()==number)
        {
            stream_a<<line.toInt()<<"\n";
            stream_a<<stream_f.readLine()<<"\n";
            stream_a<<stream_f.readLine()<<"\n";
            stream_a<<stream_f.readLine()<<"\n";
            do
            {
                line=stream_f.readLine();
                stream_a<<line<<"\n";
            } while(line!="*#*");
        }
    }
    file.close();
    archive.close();
}

void MainWindow::from_archive(int number)
{
    QFile archive{"archive.txt"};
    if (!archive.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QFile file{"data.txt"};
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream stream_a(&archive);
    QTextStream stream_f(&file);
    QString line;

    while(!stream_a.atEnd())
    {
        line=stream_a.readLine();
        if(line.toInt()==number)
        {
            stream_f<<line.toInt()<<"\n";
            stream_f<<stream_a.readLine()<<"\n";
            stream_f<<stream_a.readLine()<<"\n";
            stream_f<<stream_a.readLine()<<"\n";
            do
            {
                line=stream_a.readLine();
                stream_f<<line<<"\n";
            } while(line!="*#*");
        }
    }
    file.close();
    archive.close();
}

void MainWindow::load_number()
{
    QFile num("number.txt");
    if (!num.exists())
    {
        this->number=0;
        if (!num.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
            return;
        QTextStream _num(&num);
        _num<<number<<"\n";
    }
    else
    {
        if (!num.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        this->number=num.readLine().toInt();
    }
    num.close();
}

void MainWindow::update_number()
{
    QFile num{"number.txt"};
    if (!num.open(QIODevice::ReadWrite |QIODevice::Truncate | QIODevice::Text))
        return;
    QTextStream _num(&num);
    _num<<number<<"\n";
}

void MainWindow::update_notes(int number)
{
    QFile file{"data.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QFile temp{"temp.txt"};
    if (!temp.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream stream_f(&file);
    QTextStream stream_t(&temp);
    QString line;

    while(!stream_f.atEnd())
    {
        line=stream_f.readLine();
        if(line.toInt()==number)
        {
            stream_t<<line.toInt()<<"\n";
            stream_t<<stream_f.readLine()<<"\n";
            stream_t<<stream_f.readLine()<<"\n";
            stream_t<<stream_f.readLine()<<"\n";
            do
            {
                line=stream_f.readLine();
                stream_t<<line<<"\n";
            } while(line!="*#*");
        }
    }
    file.close();
    temp.close();
}

void MainWindow::update_archive(int number)
{
    QFile file{"archive.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QFile temp{"temp.txt"};
    if (!temp.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream stream_f(&file);
    QTextStream stream_t(&temp);
    QString line;

    while(!stream_f.atEnd())
    {
        line=stream_f.readLine();
        if(line.toInt()==number)
        {
            stream_t<<line.toInt()<<"\n";
            stream_t<<stream_f.readLine()<<"\n";
            stream_t<<stream_f.readLine()<<"\n";
            stream_t<<stream_f.readLine()<<"\n";
            do
            {
                line=stream_f.readLine();
                stream_t<<line<<"\n";
            } while(line!="*#*");
        }
    }
    file.close();
    temp.close();
}

void MainWindow::on_btnSave_clicked()
{
    number++;
    Notes _note{number,
              ui->textEdit->toPlainText(),
              ui->lineEdit->text(),
              ui->cmbTypes->currentText(),
              QDateTime::currentDateTime().toString()};

    QFile file{"data.txt"};
        if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
                return;
        QTextStream stream(&file);
        stream<< _note.number()<<"\n";
        if(_note.header()=="")
        {
            QString temp="header";
            temp+=QString::number(_note.number());
            stream<<temp<<"\n";
            _note.setHeader(temp);
        }
        else
        {
            stream<< _note.header()<<"\n";
        }
            stream<< _note.current_date()<<"\n"
              << _note.group()<<"\n"
              << _note.note_text()<<"\n*#*\n";
        file.close();
    update_number();

    load_from_file(ui->listWidget->currentItem()->text());
    ui->textEdit->setText("");
    ui->lineEdit->setText("");
    ui->cmbTypes->setCurrentText("default");
    ui->tbwNotes->sortByColumn(2,Qt::AscendingOrder);
}

void MainWindow::on_btnArchive_clicked()
{
    ui->tbwNotes->setColumnHidden(0,false);
    QList<QTableWidgetItem* > items=ui->tbwNotes->selectedItems();
    QVector<QTableWidgetItem *> sad;
    QVector<int> archived_numbers;
    QVector<int> note_numbers;
    for(auto l:items){
        sad.push_back(l);
    }
    int rer=sad.size();
    for(int i=0;i<rer/5;i++)
    {
       to_archive(sad[i*5]->text().toInt());
       archived_numbers.push_back(sad[i*5]->text().toInt());
    }
    bool was=false;
    for(int i=1;i<=number;i++)
    {
        was=false;
        for(auto num:archived_numbers)
        {
            if(num==i)
            {
                was=true;
            }
        }
        if(!was)
        {
            note_numbers.push_back(i);
        }
    }
    for(auto nt:note_numbers)
    {
        update_notes(nt);
    }
    QFile::remove("data.txt");
    QFile::rename("temp.txt","data.txt");
    load_archive(ui->listWidget->currentItem()->text());
    load_from_file(ui->listWidget->currentItem()->text());
    ui->tbwNotes->setColumnHidden(0,true);
}

void MainWindow::on_tbwNotes_itemDoubleClicked(QTableWidgetItem *item)
{
    QTableWidgetItem* text=ui->tbwNotes->item(ui->tbwNotes->row(item),4);
    QTableWidgetItem* header=ui->tbwNotes->item(ui->tbwNotes->row(item),1);
    QMessageBox::information(0, header->text(), text->text());
}

void MainWindow::on_btnShowArchive_clicked()
{
    ui->tbwArchive->setHidden(false);
    ui->tbwNotes->setHidden(true);
    ui->btnShowArchive->setHidden(true);
    ui->btnShowNotes->setHidden(false);
    ui->btnReestablish->setHidden(false);
    ui->btnArchive->setHidden(true);
}

void MainWindow::on_btnShowNotes_clicked()
{
    ui->tbwArchive->setHidden(true);
    ui->tbwNotes->setHidden(false);
    ui->btnShowArchive->setHidden(false);
    ui->btnShowNotes->setHidden(true);
    ui->btnReestablish->setHidden(true);
    ui->btnArchive->setHidden(false);
}

void MainWindow::on_btnReestablish_clicked()
{
    ui->tbwArchive->setColumnHidden(0,false);
    QList<QTableWidgetItem* > items=ui->tbwArchive->selectedItems();
    QVector<QTableWidgetItem *> sad;
    QVector<int> archived_numbers;
    QVector<int> note_numbers;
    for(auto l:items){
        sad.push_back(l);
    }
    int rer=sad.size();
    for(int i=0;i<rer/5;i++)
    {
        from_archive(sad[i*5]->text().toInt());
        note_numbers.push_back(sad[i*5]->text().toInt());
    }
    bool was=false;
    for(int i=1;i<=number;i++)
    {
        was=false;
        for(auto num:note_numbers)
        {
            if(num==i)
            {
                was=true;
            }
        }
        if(!was)
        {
            archived_numbers.push_back(i);
        }
    }
    for(auto nt:archived_numbers)
    {
        update_archive(nt);
    }
    QFile::remove("archive.txt");
    QFile::rename("temp.txt","archive.txt");

    load_from_file(ui->listWidget->currentItem()->text());
    load_archive(ui->listWidget->currentItem()->text());
    ui->tbwArchive->setColumnHidden(0,true);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    load_from_file(item->text());
    load_archive(item->text());
}
