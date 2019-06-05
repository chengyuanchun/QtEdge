#include "QtEdgeFrameLessWidgetHelper.h"
#include "QtEdgeNativeEventFilter.h"
#include <windows.h>
#include <QWidget>
#include <QScreen>

using namespace QtEdge;

QtEdgeFrameLessWidgetHelper::QtEdgeFrameLessWidgetHelper(QWidget *parent)
    : QtEdgeFrameLessHelper(parent)
    , m_widget(parent)
{
    if (parent && (parent->windowFlags() & Qt::FramelessWindowHint))
        parent->installEventFilter(this);
}

QtEdgeFrameLessWidgetHelper::~QtEdgeFrameLessWidgetHelper()
{

}

bool QtEdge::QtEdgeFrameLessWidgetHelper::eventFilter(QObject *watched, QEvent *event)
{
    // The window system identifer for this native widget has changed.
    // The WId should get only this event changed
    if (event->type() == QEvent::WinIdChange && m_widget) {
        // Our purpose has been reached, so remove event filter
        m_widget->removeEventFilter(this);
        // set parent m_widow for WM_NCHITTEST event
        m_window = m_widget->windowHandle();

        QtEdgeNativeEventFilter::instance()->install(m_window, this);
    }

    return QObject::eventFilter(watched, event);
}

bool QtEdge::QtEdgeFrameLessWidgetHelper::nativeEventFilter(void *message, long *result)
{
    if (QtEdgeFrameLessHelper::nativeEventFilter(message, result))
        return true;

    // widget will large than screen size when maximized, so extend margins for it
    LPMSG lpMsg = reinterpret_cast<LPMSG>(message);
    if (lpMsg->message == WM_GETMINMAXINFO)
    {
        static QMargins margins = m_widget->contentsMargins();

        QScreen *screen = m_window->screen();
        QRect frameRect = screen->availableVirtualGeometry();
        LPMINMAXINFO lpMinMaxInfo = reinterpret_cast<LPMINMAXINFO>(lpMsg->lParam);

        lpMinMaxInfo->ptMinTrackSize.x = m_window->minimumWidth();
        lpMinMaxInfo->ptMinTrackSize.y = m_window->minimumHeight();
        lpMinMaxInfo->ptMaxTrackSize.x = frameRect.width();
        lpMinMaxInfo->ptMaxTrackSize.y = frameRect.height();

        if (IsZoomed(lpMsg->hwnd))
        {
            RECT frame = { 0, 0, 0, 0 };
            AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
            frame.left = abs(frame.left);
            frame.top = abs(frame.bottom);
            m_widget->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
        }
        else
        {
            m_widget->setContentsMargins(margins);
        }

        return true;
    }

    return false;
}

bool QtEdgeFrameLessWidgetHelper::isCaption(int x, int y)
{
    if (m_widget)
        return !m_titleObjects.contains(m_widget->childAt(x, y));

    return true;
}
