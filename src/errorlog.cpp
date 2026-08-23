#include "errorlog.h"

#include <QDebug>

namespace {

// Mehr braucht niemand von Hand zu lesen; aeltere fallen hinten heraus
const int kMax = 200;

ErrorLog *g_log = nullptr;

} // namespace

ErrorLog::ErrorLog(QObject *parent) : QAbstractListModel(parent) {}

ErrorLog *ErrorLog::instance()
{
    if (!g_log)
        g_log = new ErrorLog;
    return g_log;
}

void ErrorLog::note(const QString &area, const QString &text, const QString &detail)
{
    instance()->add(area, text, detail);
}

int ErrorLog::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_rows.size();
}

QHash<int, QByteArray> ErrorLog::roleNames() const
{
    return { { WhenRole,   "when" },
             { AreaRole,   "area" },
             { TextRole,   "text" },
             { DetailRole, "detail" },
             { RepeatRole, "repeat" } };
}

QVariant ErrorLog::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_rows.size())
        return QVariant();
    const Entry &e = m_rows.at(index.row());
    switch (role) {
    case WhenRole:   return e.when.toString(QStringLiteral("dd.MM. hh:mm:ss"));
    case AreaRole:   return e.area;
    case TextRole:   return e.text;
    case DetailRole: return e.detail;
    case RepeatRole: return e.repeat;
    }
    return QVariant();
}

/* Neueste oben. Wiederholt sich derselbe Eintrag - der Wiederholer beim
   ausgeschalteten Fernseher tut das im Takt -, wird nur mitgezaehlt: sonst
   verschuettet ein Dauerfehler alles andere. */
void ErrorLog::add(const QString &area, const QString &text, const QString &detail)
{
    qWarning() << "Protokoll:" << area << "-" << text << detail;

    if (!m_rows.isEmpty()) {
        Entry &top = m_rows.first();
        if (top.area == area && top.text == text && top.detail == detail) {
            ++top.repeat;
            top.when = QDateTime::currentDateTime();
            emit dataChanged(index(0), index(0));
            return;
        }
    }

    beginInsertRows(QModelIndex(), 0, 0);
    Entry e;
    e.when = QDateTime::currentDateTime();
    e.area = area;
    e.text = text;
    e.detail = detail;
    m_rows.prepend(e);
    endInsertRows();

    if (m_rows.size() > kMax) {
        beginRemoveRows(QModelIndex(), kMax, m_rows.size() - 1);
        m_rows.remove(kMax, m_rows.size() - kMax);
        endRemoveRows();
    }
    emit countChanged();
}

void ErrorLog::clear()
{
    if (m_rows.isEmpty())
        return;
    beginResetModel();
    m_rows.clear();
    endResetModel();
    emit countChanged();
}

QString ErrorLog::asText() const
{
    QStringList zeilen;
    for (const Entry &e : m_rows) {
        QString z = e.when.toString(QStringLiteral("dd.MM. hh:mm:ss"))
                    + QStringLiteral("  ") + e.area + QStringLiteral(": ") + e.text;
        if (!e.detail.isEmpty())
            z += QStringLiteral("  [") + e.detail + QLatin1Char(']');
        if (e.repeat > 1)
            z += QStringLiteral("  (") + QString::number(e.repeat) + QStringLiteral("x)");
        zeilen << z;
    }
    return zeilen.join(QLatin1Char('\n'));
}
