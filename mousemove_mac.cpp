/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#include "mousemove.h"
#include <QDebug>

using namespace std;

MouseMove::MouseMove() {
    system("/opt/homebrew/bin/cliclick p");
}

void MouseMove::moveMouse(const int& x, const int& y, const int& click) {
    FILE * p_file = NULL;

    p_file = popen("/opt/homebrew/bin/cliclick p", "r");
    fgets(buf, 21, p_file);
    pclose(p_file);

    sscanf(buf, "%d,%d", &m_x, &m_y);

    qDebug()<<m_x<<" "<<m_y;
    m_x = max(m_x + x, 0);
    m_y = max(m_y + y, 0);

    if (click == 1) tmp="/opt/homebrew/bin/cliclick c:.";
    else if (click == -1) tmp="/opt/homebrew/bin/cliclick rc:.";
    else if (click == 2) tmp="/opt/homebrew/bin/cliclick dc:.";
    else tmp = "/opt/homebrew/bin/cliclick m:"+to_string(m_x)+","+to_string(m_y);

    strcpy(cmd, tmp.c_str());
    system(cmd);
}
