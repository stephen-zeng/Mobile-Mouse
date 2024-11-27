/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#ifndef MOUSEMOVE_H
#define MOUSEMOVE_H

#include <stdlib.h>
#include <string>
#include <cstdio>

using namespace std;

class MouseMove {
public:
    MouseMove();
    void moveMouse(const int&, const int&, const int&);

private:
    int m_x, m_y;
    char buf[21];
    char cmd[1001];
    string tmp;
};

#endif // MOUSEMOVE_H
