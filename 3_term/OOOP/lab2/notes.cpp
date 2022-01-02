#include "notes.h"

Notes::Notes()
{

}

int Notes::number() const
{
    return _number;
}

QString Notes::note_text() const
{
    return _note_text;
}

QString Notes::header() const
{
    return _header;
}

QString Notes::group() const
{
    return _group;
}

QString Notes::current_date() const
{
    return _current_date;
}

void Notes::setNumber(int number)
{
    _number=number;
}

void Notes::setNoteText(QString &note_text)
{
    _note_text=note_text;
}

void Notes::setHeader(QString &header)
{
    _header=header;
}

void Notes::setGroup(QString &group)
{
    _group=group;
}

void Notes::setDate(QString &current_date)
{
    _current_date=current_date;
}
