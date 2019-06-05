#include "QtEdgeNativeEventFilter.h"
#include "QtEdgeFrameLessHelper.h"
#include <QCoreApplication>
#include <QtWin>
#include <windows.h>

using namespace QtEdge;

QtEdgeNativeEventFilter *QtEdgeNativeEventFilter::m_instance = Q_NULLPTR;
QMutex QtEdgeNativeEventFilter::m_mutex;

QtEdge::QtEdgeNativeEventFilter *QtEdge::QtEdgeNativeEventFilter::instance()
{
    if (Q_NULLPTR == m_instance)
    {
        QMutexLocker locker(&m_mutex);
        if (Q_NULLPTR == m_instance)
        {
            m_instance = new QtEdgeNativeEventFilter();
            qApp->installNativeEventFilter(m_instance);
        }
    }

    return m_instance;
}

void QtEdgeNativeEventFilter::install(QWindow *window, QtEdgeFrameLessHelper *helper)
{
    if (Q_NULLPTR == window || Q_NULLPTR == helper)
        return;

    if (!m_helpers.contains(window->winId()))
    {
        setWindowStyle(window);
        m_helpers.insert(window->winId(), helper);
    }
}

void QtEdgeNativeEventFilter::uninstall(QWindow *window)
{
    if (Q_NULLPTR == window)
        return;

    m_helpers.remove(window->winId());
}

bool QtEdgeNativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    LPMSG lpMsg = reinterpret_cast<LPMSG>(message);
    WId winId = reinterpret_cast<WId>(lpMsg->hwnd);
    QtEdgeFrameLessHelper *helper = m_helpers.value(winId);
    if (Q_NULLPTR != helper)
        return helper->nativeEventFilter(message, result);

    return false;
}

QtEdgeNativeEventFilter::QtEdgeNativeEventFilter()
{

}

void QtEdgeNativeEventFilter::setWindowStyle(QWindow *window)
{
    HWND hwnd = reinterpret_cast<HWND>(window->winId());
     //设置窗口风格
    DWORD oldWindowStyle = ::GetWindowLong(hwnd, GWL_STYLE);
    DWORD newWindowStyle = oldWindowStyle | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
    SetWindowLong(hwnd, GWL_STYLE, newWindowStyle);
    // 添加窗口阴影
    if (QtWin::isCompositionEnabled())
        QtWin::extendFrameIntoClientArea(window, 1, 1, 1, 1);
}
