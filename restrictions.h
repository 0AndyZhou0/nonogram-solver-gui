#ifndef RESTRICTIONS_H
#define RESTRICTIONS_H

#include <QWidget>
#include <QPlainTextEdit>

namespace Ui {
class Restrictions;
}

class Restrictions : public QWidget
{
    Q_OBJECT

public:
    enum Type {Row, Column};
    explicit Restrictions(Restrictions::Type type, QWidget *parent = nullptr);
    ~Restrictions();
    QList<int> get_restrictions();
    Type type;
    QString whitespace;
    void setWidth(int size);
    void setHeight(int size);
    void setSize(int width, int height);

private:
    Ui::Restrictions *ui;
    QPlainTextEdit* text_edit;

private slots:
    void format_text();
};

#endif // RESTRICTIONS_H
