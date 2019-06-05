#include "widget.h"
#include "ui_widget.h"
#include "Source/QtEdgeFrameLessWidgetHelper.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include <QWidget>
#include <QStackedWidget>
#include <QFile>
#include "Source/QtEdgeIconHelper.h"

const int TITLE_HEIGHT = 80;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setMinimumSize(400, 300);
    resize(800, 600);

    auto *helper = new QtEdge::QtEdgeFrameLessWidgetHelper(this);
    helper->setTitleHeight(TITLE_HEIGHT);

    QPushButton *minButton = new QPushButton();
    QPushButton *maxButton = new QPushButton();
    QPushButton *closeButton = new QPushButton();
    closeButton->setObjectName("closeButton");
    QSpacerItem *menuSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    QtEdge::QtEdgeIconHelper::instance()->setIcon(minButton, QChar(0xF068));
    QtEdge::QtEdgeIconHelper::instance()->setIcon(maxButton, QChar(0xF067));
    QtEdge::QtEdgeIconHelper::instance()->setIcon(closeButton, QChar(0xF00D));

    QFile file(":/resouce/qss/title.qss");
    file.open(QFile::ReadOnly);
    QString qss = QString::fromLocal8Bit(file.readAll());
    this->setStyleSheet(qss);

    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    connect(minButton, &QPushButton::clicked, this, &QWidget::showMinimized);
    connect(maxButton, &QPushButton::clicked, this, [&]{ isMaximized() ? showNormal() : showMaximized(); });

    helper->appendTitleObject(minButton);
    helper->appendTitleObject(maxButton);
    helper->appendTitleObject(closeButton);

    QGridLayout *menuLayout = new QGridLayout();
    menuLayout->setContentsMargins(0, 0, 0, 0);
    menuLayout->setSpacing(0);
    menuLayout->addWidget(minButton, 0, 1, 1, 1);
    menuLayout->addWidget(maxButton, 0, 2, 1, 1);
    menuLayout->addWidget(closeButton, 0, 3, 1, 1);
    menuLayout->addItem(menuSpacer, 1, 0, 1, 3);

    QWidget *menuWidget = new QWidget();
    menuWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    menuWidget->setLayout(menuLayout);

    QSpacerItem *titleSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->addItem(titleSpacer);
    titleLayout->addWidget(menuWidget);

    QWidget *titleWidget = new QWidget();
    titleWidget->setLayout(titleLayout);
    QPalette palette(titleWidget->palette());
    palette.setColor(QPalette::Background, Qt::green);
    titleWidget->setAutoFillBackground(true);
    titleWidget->setPalette(palette);
    titleWidget->setMaximumHeight(TITLE_HEIGHT);

    QStackedWidget *stackedWidget = new QStackedWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(titleWidget);
    mainLayout->addWidget(stackedWidget);

    this->setLayout(mainLayout);
}

Widget::~Widget()
{
    delete ui;
}
