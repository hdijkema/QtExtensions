#ifndef ZCHTMLMENUACTION_H
#define ZCHTMLMENUACTION_H

#include <QWidgetAction>

class zcHtmlMenuAction : public QWidgetAction
{
    Q_OBJECT
private:
    QIcon   _html_icon;
    QString _html;

    QIcon    _empty_icon;
    QString  _empty_string;

public:
    explicit zcHtmlMenuAction(QWidget *parent = nullptr);
    explicit zcHtmlMenuAction(const QString &html, QWidget *parent = nullptr);
    explicit zcHtmlMenuAction(const QIcon &icon, const QString &html, QWidget *parent = nullptr);
   ~zcHtmlMenuAction();

public:
    void setHtmlIcon(const QIcon &icon);
    void setHtml(const QString &html);

public:
    QIcon htmlIcon() const;
    QString html() const;

private slots:
    void handleChanged();

signals:
    void htmlChanged();
};

#endif // ZCHTMLMENUACTION_H
