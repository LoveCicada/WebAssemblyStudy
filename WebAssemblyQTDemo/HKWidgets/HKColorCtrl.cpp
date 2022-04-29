#include "HKColorCtrl.h"
#include <QDebug>

HKColorCtrl::HKColorCtrl(QWidget *parent): QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(choiceColor(void)));

    setAutoFillBackground(true);
    setFlat(true);
}

HKColorCtrl::~HKColorCtrl()
{

}

void HKColorCtrl::choiceColor(void)
{
    QColor color = QColorDialog::getColor(Qt::red, this);
    QPalette pal;
    pal.setColor(QPalette::Button, color);
    setPalette(pal);
}

void HKColorCtrl::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QColorDialog* cd = new QColorDialog(this);
        cd->setModal(true);
        QSize size(573, 455);
        cd->setFixedSize(size);
        cd->show();

        connect(cd, SIGNAL(colorSelected(const QColor&)), this, SLOT(recordColor(QColor)));
        connect(cd, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(recordColor(QColor)));
        connect(cd, SIGNAL(accepted()), this, SLOT(setColor()));
    }
}

void HKColorCtrl::setColor()
{
    QPalette pal;
    pal.setColor(QPalette::Button, m_SelectColor);
    setPalette(pal);
}

void HKColorCtrl::setColor(QColor color)
{
    QPalette pal;
    pal.setColor(QPalette::Button, color);
    setPalette(pal);
}

QColor HKColorCtrl::getColor() const
{
    return this->palette().color(QPalette::Button);
}

void HKColorCtrl::recordColor(QColor color)
{
    m_SelectColor = color;
}
