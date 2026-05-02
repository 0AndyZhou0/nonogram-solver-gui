#include "restrictions.h"
#include "ui_restrictions.h"
#include <QRegularExpression>

Restrictions::Restrictions(Type type, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Restrictions)
{
    ui->setupUi(this);
    this->type = type;
    if (type == Type::Row)
    {
        whitespace = " ";
    } else if (type == Type::Column)
    {
        whitespace = "\n";
    }
    text_edit = new QPlainTextEdit(this);
    text_edit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    text_edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    text_edit->setLineWrapMode(QPlainTextEdit::NoWrap);
    connect(text_edit, &QPlainTextEdit::textChanged, this, &Restrictions::format_text);
}

void Restrictions::format_text()
{
    text_edit->blockSignals(true);
    QString text = text_edit->toPlainText();
    int length = text.length();
    int position = text_edit->textCursor().position();
    text = text.replace(QRegularExpression("[^\\d\\s]+"), "");
    text = text.replace(QRegularExpression("\\s+"), whitespace);
    position -= length - text.length();

    text_edit->setPlainText(text);
    QTextCursor cursor = text_edit->textCursor();
    cursor.setPosition(position, QTextCursor::MoveAnchor);
    text_edit->setTextCursor(cursor);
    text_edit->blockSignals(false);
}

void Restrictions::setWidth(int size)
{
    text_edit->setMinimumWidth(size);
    text_edit->setMaximumWidth(size);
}

void Restrictions::setHeight(int size)
{
    text_edit->setMinimumHeight(size);
    text_edit->setMaximumHeight(size);
}

void Restrictions::setSize(int width, int height)
{
    setWidth(width);
    setHeight(height);
}

QList<int> Restrictions::get_restrictions()
{
    QStringList strs = text_edit->toPlainText().split(whitespace);
    QList<int> restrictions;
    for (size_t i = 0; i < strs.length(); i++)
    {
        int number = strs[i].toInt();
        if (number > 0 && number < 100)
        {
            restrictions.push_back(number);
        }
    }
    if (restrictions.length() == 0)
    {
        restrictions.push_back(0);
    }
    return restrictions;
}

Restrictions::~Restrictions()
{
    delete ui;
}
