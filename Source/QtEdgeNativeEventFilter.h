#ifndef QTEDGENATIVEEVENTFILTER_H
#define QTEDGENATIVEEVENTFILTER_H

#include <QAbstractNativeEventFilter>
#include <QMutex>
#include <QHash>
#include <QWindow>

namespace QtEdge {

class QtEdgeFrameLessHelper;

class QtEdgeNativeEventFilter : public QAbstractNativeEventFilter
{
public:
    static QtEdgeNativeEventFilter* instance();

    void install(QWindow *window, QtEdgeFrameLessHelper *helper);
    void uninstall(QWindow *window);

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;

protected:
    QtEdgeNativeEventFilter();

private:
    void setWindowStyle(QWindow *window);

private:
    static QtEdgeNativeEventFilter *m_instance;
    static QMutex m_mutex;

    QHash<WId, QtEdgeFrameLessHelper *> m_helpers;
};

}

#endif // QTEDGENATIVEEVENTFILTER_H
