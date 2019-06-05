#ifndef QTEDGEFRAMELESSWIDGETHELPER_H
#define QTEDGEFRAMELESSWIDGETHELPER_H

#include "QtEdgeFrameLessHelper.h"

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

namespace QtEdge {

class QtEdgeFrameLessWidgetHelper : public QtEdgeFrameLessHelper
{
    Q_OBJECT

public:
    explicit QtEdgeFrameLessWidgetHelper(QWidget *parent = Q_NULLPTR);
    virtual ~QtEdgeFrameLessWidgetHelper();

    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_FINAL;
    bool nativeEventFilter(void *message, long *result) Q_DECL_FINAL;

protected:
    bool isCaption(int x, int y) Q_DECL_OVERRIDE;

private:
    QWidget *m_widget;
};

}

#endif // QTEDGEFRAMELESSWIDGETHELPER_H
