#ifndef NOTES_H
#define NOTES_H

#include <QString>
#include <QDate>

class Notes
{
private:
    int _number;
    QString _note_text;
    QString _header;
    QString _group;
    QString _current_date;
public:
    Notes();
    explicit Notes(int number,
                   const QString &note_text,
                   const QString &header,
                   const QString &group,
                   const QString &current_date):
        _number(number), _note_text(note_text), _header(header), _group(group), _current_date(current_date) {}
   int number() const;
   QString note_text() const;
   QString header() const;
   QString group() const;
   QString current_date() const;
   void setNumber(int number);
   void setNoteText(QString &note_text);
   void setHeader(QString &header);
   void setGroup(QString &group);
   void setDate(QString &current_date);
};

#endif // NOTES_H
