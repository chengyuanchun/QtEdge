#include "QtEdgeFrameLessHelper.h"
#include "QtEdgeNativeEventFilter.h"
#include <windows.h>
#include <windowsx.h>
#include <QtWin>

using namespace QtEdge;

QtEdgeFrameLessHelper::QtEdgeFrameLessHelper(QObject *parent) : QObject(parent)
  , m_window(Q_NULLPTR)
  , m_titleHeight(0)
  , m_leftMargin(6)
  , m_topMargin(6)
  , m_rightMargin(6)
  , m_bottomMargin(6)
{

}

QtEdgeFrameLessHelper::~QtEdgeFrameLessHelper()
{
    QtEdgeNativeEventFilter::instance()->uninstall(m_window);
}

bool QtEdgeFrameLessHelper::nativeEventFilter(void *message, long *result)
{
    LPMSG lpMsg = reinterpret_cast<LPMSG>(message);
    WId winId = reinterpret_cast<WId>(lpMsg->hwnd);

    if (m_window && m_window->winId() == winId)
    {
        switch (lpMsg->message)
        {
        case WM_NCHITTEST:
        {
            int x = GET_X_LPARAM(lpMsg->lParam) - m_window->x();
            int y = GET_Y_LPARAM(lpMsg->lParam) - m_window->y();
            *result = hitTest(x, y);
            return true;
        }
        case WM_NCACTIVATE:
        {
            *result = 1;
            return true;
        }
        case WM_NCCALCSIZE:
        {
            *result = 0;
            return true;
        }
        default:
            break;
        }
    }

    return false;
}

void QtEdgeFrameLessHelper::appendTitleObject(QObject *object)
{
    m_titleObjects.append(object);
}

void QtEdgeFrameLessHelper::appendTitleObjects(const QObjectList &objects)
{
    m_titleObjects.append(objects);
}

int QtEdgeFrameLessHelper::titleHeight() const
{
    return m_titleHeight;
}

int QtEdgeFrameLessHelper::leftMargin() const
{
    return m_leftMargin;
}

int QtEdgeFrameLessHelper::topMargin() const
{
    return m_topMargin;
}

int QtEdgeFrameLessHelper::rightMargin() const
{
    return m_rightMargin;
}

int QtEdgeFrameLessHelper::bottomMargin() const
{
    return m_bottomMargin;
}

void QtEdgeFrameLessHelper::setTitleHeight(int height)
{
    m_titleHeight = height;
    emit titleHeightChanged(m_titleHeight);
}

void QtEdgeFrameLessHelper::setLeftMargin(int margin)
{
    m_leftMargin = margin;
    emit leftMarginChanged(m_leftMargin);
}

void QtEdgeFrameLessHelper::setTopMargin(int margin)
{
    m_topMargin = margin;
    emit topMarginChanged(m_topMargin);

}

void QtEdgeFrameLessHelper::setRightMargin(int margin)
{
    m_rightMargin = margin;
    emit rightMarginChanged(m_rightMargin);
}

void QtEdgeFrameLessHelper::setBottomMargin(int margin)
{
    m_bottomMargin = margin;
    emit bottomMarginChanged(m_bottomMargin);
}

bool QtEdgeFrameLessHelper::isCaption(int x, int y)
{
    Q_UNUSED(x)
    Q_UNUSED(y)

    return false;
}

int QtEdgeFrameLessHelper::hitTest(int x, int y)
{
    int width = m_window->width();
    int height = m_window->height();

    bool isLeft = (x >= 0 && x <= m_leftMargin);
    bool isTop = (y >= 0 && y <= m_topMargin);
    bool isRight = (x >= width - m_rightMargin && x <= width);
    bool isBottom = (y >= height - m_bottomMargin && y <= height);
    bool isCap = (y > 0 && y < m_titleHeight && isCaption(x, y));

    int direction = HTCLIENT;

    if (isLeft && isTop)
        direction = HTTOPLEFT;
    else if (isLeft && isBottom)
        direction = HTBOTTOMLEFT;
    else if (isRight && isTop)
        direction = HTTOPRIGHT;
    else if (isRight && isBottom)
        direction = HTBOTTOMRIGHT;
    else if (isLeft)
        direction = HTLEFT;
    else if (isTop)
        direction = HTTOP;
    else if (isRight)
        direction = HTRIGHT;
    else if (isBottom)
        direction = HTBOTTOM;
    else if (isCap)
        direction = HTCAPTION;

    return direction;
}


