#include "util.h"

float map_screenspace(int a, int size)
{
    return float(a) * 2 / size - 1;
}

void drawLine(int x1, int y1, int x2, int y2, const glfwWindowHandle& window)
{
    std::cout << "DrawLine Called" << std::endl;
    int m_new = 2 * (y2 - y1);
    int slope_error_new = m_new - (x2 - x1);
    for (int x = x1, y = y1; x <= x2; x++)
    {
        glBegin(GL_POINTS);
        glVertex2f(map_screenspace(x, window.width()), map_screenspace(y, window.height()));
        glEnd();

        slope_error_new += m_new;

        if (slope_error_new >= 0)
        {
            y++;
            slope_error_new -= 2 * (x2 - x1);
        }
    }
}
