/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#define WIN32_LEAN_AND_MEAN
#include "mousemove.h"
#include <windows.h>
#include <QDebug>

MouseMove::MouseMove() {
    qDebug()<<"MouseMove on Windows start";
}

void MouseMove::moveMouse(const int& x, const int& y, const int& click) {
    POINT p;
    GetCursorPos(&p);
    qDebug()<<"Mouse "<<p.x<<" "<<p.y;

    HWND hWnd = GetDesktopWindow();
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEX miex;
    miex.cbSize = sizeof(miex);
    GetMonitorInfo(hMonitor, &miex);
    int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
    DEVMODE dm;
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;
    EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
    int cxPhysical = dm.dmPelsWidth;
    double scale = ((double)cxPhysical / (double)cxLogical);

    int m_x = p.x + x * scale;
    int m_y = p.y + y * scale;
    if (m_x < 0) m_x = 0;
    if (m_y < 0) m_y = 0;
    qDebug()<<"New Mouse "<<m_x<<" "<<m_y;
    SetCursorPos(m_x, m_y);

    if (click == 1) {
        INPUT click[2] = {};
        click[0].type = INPUT_MOUSE;
        click[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        click[1].type = INPUT_MOUSE;
        click[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(2, click, sizeof(INPUT));
    } else if (click == -1) {
        INPUT click[2] = {};
        click[0].type = INPUT_MOUSE;
        click[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        click[1].type = INPUT_MOUSE;
        click[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        SendInput(2, click, sizeof(INPUT));
    } else if (click ==2) {
        INPUT click[2] = {};
        click[0].type = INPUT_MOUSE;
        click[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        click[1].type = INPUT_MOUSE;
        click[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(2, click, sizeof(INPUT));
        SendInput(2, click, sizeof(INPUT));
    }
}
