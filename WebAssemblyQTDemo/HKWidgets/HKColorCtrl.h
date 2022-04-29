#pragma once

#include <QObject>
#include <QPushButton>
#include <QColorDialog>
#include <QMouseEvent>
class HKColorCtrl : public QPushButton
{
    Q_OBJECT

public:
    HKColorCtrl(QWidget* parent);
    ~HKColorCtrl();

    QColor getColor() const;
public slots:
    void choiceColor(void);
    void setColor(QColor color);
    void setColor();
    void recordColor(QColor color);
protected:
    void mousePressEvent(QMouseEvent* event);

private:
    QColor m_SelectColor;
};
