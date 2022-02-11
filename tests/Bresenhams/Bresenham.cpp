#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "util.h"

#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"


float map_screenspace(int a, int size)
{
    return float(a) * 2 / size - 1;
}

std::vector<float> get_points_on_line(int x1, int y1, int x2, int y2, const glfwWindowHandle& window)
{
    std::vector<float> points;
    int m_new = 2 * (y2 - y1);
    int slope_error_new = m_new - (x2 - x1);
    for (int x = x1, y = y1; x <= x2; x++)
    {
        points.push_back(map_screenspace(x, window.width()));
        points.push_back(map_screenspace(y, window.height()));

        slope_error_new += m_new;
        if (slope_error_new >= 0)
        {
            y++;
            slope_error_new -= 2 * (x2 - x1);
        }
    }
    return points;
}

void add_points(std::vector<float>& points, int x1, int x, int y1, int y, int h, int w)
{
    points.push_back(map_screenspace(x1 + x, w));
    points.push_back(map_screenspace(y1 + y, h));
    points.push_back(map_screenspace(x1 + x, w));
    points.push_back(map_screenspace(y1 - y, h));
    points.push_back(map_screenspace(x1 - x, w));
    points.push_back(map_screenspace(y1 + y, h));
    points.push_back(map_screenspace(x1 - x, w));
    points.push_back(map_screenspace(y1 - y, h));
}

std::vector<float> get_points_on_circle(int x1, int y1, int r, const glfwWindowHandle& window)
{
    std::vector<float> points;
    int x = 0;
    int y = r;
    int delta = 1 - 2 * r;
    int error = 0;
    while (y > 0)
    {
        add_points(points, x1, x, y1, y, window.height(), window.width());
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0))
        {
            delta += 2 * ++x + 1;
            continue;
        }
        error = 2 * (delta - x) - 1;
        if ((delta > 0) && (error > 0))
        {
            delta += 1 - 2 * --y;
            continue;
        }
        delta += 2 * (x++ - y--);
    }
    return points;
}


void draw_points(const float* points, uint32_t len)
{
    VertexBuffer vb(points, len);
    VertexBufferLayout layout;
    layout.push<float>(2);
    VertexArray va(vb, layout);

    glDrawArrays(GL_POINTS, 0, len / 2);
}


void main()
{
    glfwInitialiser::getInstance();
    glfwWindowHandle window{ glfwInitialiser::createWindow(1280, 720, "Bresenham's algorithms") };
    glfwMakeContextCurrent(window.get());
    init_glew();

    Shader shader("C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/basic_vertex.shader",
        "C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/basic_fragment.shader");
    shader.bind();

    auto line_points(get_points_on_line(0, 0, 100, 100, window));
    auto circle_points(get_points_on_circle(200, 200, 50, window));


    draw_points(circle_points.data(), circle_points.size());
    draw_points(line_points.data(), line_points.size());
    glfwSwapBuffers(window.get());
    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();
    }
}