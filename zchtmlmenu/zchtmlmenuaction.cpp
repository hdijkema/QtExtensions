#include "zchtmlmenuaction.h"
#include "zchtmlmenuiconengine.h"

static QChar *_my_string = nullptr;

zcHtmlMenuAction::zcHtmlMenuAction(QWidget *parent)
    : zcHtmlMenuAction(QIcon(), QString(), parent)
{
}

zcHtmlMenuAction::zcHtmlMenuAction(const QString &html, QWidget *parent)
    : zcHtmlMenuAction(QIcon(), html, parent)
{
}

zcHtmlMenuAction::zcHtmlMenuAction(const QIcon &icon, const QString &html, QWidget *parent)
    : QWidgetAction(parent)
{
    _html_icon = icon;
    _html = html;

    if (_my_string == nullptr) {
        _my_string = new QChar[1];
    }

    _empty_icon = QIcon(new zcHtmlMenuIconEngine());
    _empty_string.setRawData(_my_string, 1);

    setIcon(_empty_icon);
    setText(_empty_string);

    connect(this, &QAction::changed, this, &zcHtmlMenuAction::handleChanged);
}

zcHtmlMenuAction::~zcHtmlMenuAction()
{

}

void zcHtmlMenuAction::setHtmlIcon(const QIcon &icon)
{
    _html_icon = icon;
    emit htmlChanged();
}

void zcHtmlMenuAction::setHtml(const QString &html)
{
    _html = html;
    emit htmlChanged();
}

QIcon zcHtmlMenuAction::htmlIcon() const
{
    return _html_icon;
}

QString zcHtmlMenuAction::html() const
{
    return _html;
}

void zcHtmlMenuAction::handleChanged()
{
    QIcon icn = icon();
    QString str = text();

    bool set_icon = true;
    if (icn.name() == "zcHtmlMenuIcon") {
        set_icon = false;
    }

    bool set_html = true;
    if (str.constData() == _my_string) {
        set_html = false;
    }

    bool b = blockSignals(true);
    setIcon(_empty_icon);
    setText(_empty_string);
    blockSignals(b);

    if (set_icon) _html_icon = icn;
    if (set_html) _html = str;

    emit htmlChanged();
}

