#ifndef QTEDGEICONHELPER_H
#define QTEDGEICONHELPER_H

#include <QObject>
#include <QMutex>
#include <QFont>

QT_BEGIN_NAMESPACE
class QLabel;
class QAbstractButton;
QT_END_NAMESPACE

namespace QtEdge {

class QtEdgeIconHelper : public QObject
{
    Q_OBJECT

public:
    static QtEdgeIconHelper* instance();

    void setIcon(QLabel *label, QChar ch, int size = 9);
    void setIcon(QAbstractButton *button, QChar ch, int size = 9);

protected:
    explicit QtEdgeIconHelper(QObject *parent = 0);

private:
    void initFont();

private:
    static QtEdgeIconHelper *m_instance;
    static QMutex m_mutex;
    QFont m_iconFont;
};

}

#endif // QTEDGEICONHELPER_H
