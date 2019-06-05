#include "QtEdgeIconHelper.h"
#include <QLabel>
#include <QAbstractButton>
#include <QFontDatabase>

using namespace QtEdge;

QtEdgeIconHelper *QtEdgeIconHelper::m_instance = 0;
QMutex QtEdgeIconHelper::m_mutex;

QtEdge::QtEdgeIconHelper *QtEdge::QtEdgeIconHelper::instance()
{
    if (Q_NULLPTR == m_instance)
    {
        QMutexLocker locker(&m_mutex);
        if (Q_NULLPTR == m_instance)
        {
            m_instance = new QtEdgeIconHelper();
        }
    }

    return m_instance;
}

void QtEdgeIconHelper::setIcon(QLabel *label, QChar ch, int size)
{
    m_iconFont.setPointSize(size);
    label->setFont(m_iconFont);
    label->setText(ch);
}

void QtEdgeIconHelper::setIcon(QAbstractButton *button, QChar ch, int size)
{
    m_iconFont.setPointSize(size);
    button->setFont(m_iconFont);
    button->setText(ch);
}

QtEdgeIconHelper::QtEdgeIconHelper(QObject *parent) : QObject(parent)
{
    initFont();
}

void QtEdgeIconHelper::initFont()
{
    int fontID = QFontDatabase::addApplicationFont(":/resouce/font/fontawesome-webfont.ttf");
    QStringList fontNames = QFontDatabase::applicationFontFamilies(fontID);

    if (fontNames.size() > 0)
        m_iconFont = QFont(fontNames[0]);
}
