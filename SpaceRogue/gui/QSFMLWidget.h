#ifndef QSFMLWIDGET_H
#define QSFMLWIDGET_H
/*
#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11\Xlib.h>
#endif*/

#include <QTimer>
#include <QObject>
#include <QWidget>
#include <SFML/Graphics.hpp>

class QSFMLWidget : public QWidget, public sf::RenderWindow
{
    Q_OBJECT

public:
    explicit QSFMLWidget(QWidget* parent = 0);
    // �����, ������������ ������ ��������� Qt
    virtual QPaintEngine* paintEngine() const override;
    // ����� ������� �������� � �������� �������, ����������� ��� �������������� �������������
    virtual void showEvent(QShowEvent *event) override;
    // ����� ���������, ����������� ��� ��� ����������� �������
    virtual void paintEvent(QPaintEvent *event) override;

    // ����� �������������� ������������� �������
    virtual void onInit();
    // ����� ���������� ����������� �������
    virtual void onUpdate();

private:
    QTimer m_timer;
    bool   m_initialized;
};

#endif // QSFMLWIDGET_H
