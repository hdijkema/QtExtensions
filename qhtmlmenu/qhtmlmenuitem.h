#ifndef INTERNAL_QHTMLMENUITEM_H
#define INTERNAL_QHTMLMENUITEM_H

#include <QWidget>
#include <QMenu>
#include <QLabel>
#include <QIcon>

class QHtmlMenu;

class internal_QHtmlMenuItem : public QWidget
{
    Q_OBJECT
private:
    QHtmlMenu    *_my_menu;
    QLabel       *_label;
    QLabel       *_l_icon;

public:
    internal_QHtmlMenuItem(QHtmlMenu *parent);
    internal_QHtmlMenuItem(const QString &html_label, QHtmlMenu *parent);
    internal_QHtmlMenuItem(const QIcon &icn, const QString &html_label, QHtmlMenu *parent);

public:
    void setHtml(const QString &html);
    void setIcon(const QIcon &icon);

    // QWidget interface
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void clicked();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // INTERNAL_QHTMLMENUITEM_H
