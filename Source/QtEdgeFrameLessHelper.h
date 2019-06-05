#ifndef QTEDGEFRAMELESSHELPER_H
#define QTEDGEFRAMELESSHELPER_H

#include <QObject>
#include <QWindow>
#include <QMargins>

namespace QtEdge {

class QtEdgeFrameLessHelper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int titleHeight READ titleHeight WRITE setTitleHeight NOTIFY titleHeightChanged)
    Q_PROPERTY(int leftMargin READ leftMargin WRITE setLeftMargin NOTIFY leftMarginChanged)
    Q_PROPERTY(int topMargin READ topMargin WRITE setTopMargin NOTIFY topMarginChanged)
    Q_PROPERTY(int rightMargin READ rightMargin WRITE setRightMargin NOTIFY rightMarginChanged)
    Q_PROPERTY(int bottomMargin READ bottomMargin WRITE setBottomMargin NOTIFY bottomMarginChanged)

public:
    explicit QtEdgeFrameLessHelper(QObject *parent = Q_NULLPTR);
    virtual ~QtEdgeFrameLessHelper();

    virtual bool nativeEventFilter(void *message, long *result);

    Q_INVOKABLE void appendTitleObject(QObject *object);
    Q_INVOKABLE void appendTitleObjects(const QObjectList &objects);

    int titleHeight() const;
    int leftMargin() const;
    int topMargin() const;
    int rightMargin() const;
    int bottomMargin() const;

    void setTitleHeight(int height);
    void setLeftMargin(int margin);
    void setTopMargin(int margin);
    void setRightMargin(int margin);
    void setBottomMargin(int margin);

signals:
    void titleHeightChanged(int);
    void leftMarginChanged(int);
    void topMarginChanged(int);
    void rightMarginChanged(int);
    void bottomMarginChanged(int);

protected:
    virtual bool isCaption(int x, int y);

private:
    int hitTest(int x, int y);

protected:
    QWindow *m_window;
    QObjectList m_titleObjects;
    int m_titleHeight;
    int m_leftMargin;
    int m_topMargin;
    int m_rightMargin;
    int m_bottomMargin;

};

}

#endif // QtEdgeFrameLessHelper_H
