#ifndef TESTCOLORLABEL_H
#define TESTCOLORLABEL_H

#include <QWidget>
#include <QLabel>

class TestColorLabel : public QLabel
{
    Q_OBJECT
public:
    explicit TestColorLabel(QWidget *parent = nullptr);

signals:

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void setTextColor();
};

#endif // TESTCOLORLABEL_H
