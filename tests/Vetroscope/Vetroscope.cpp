#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "util.h"

#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

inline float normalize(uint8_t value)
{
    return (float)value/ 255;
}

std::vector<float> tex_to_coords(uint8_t* tex, int width, int height)
{
    std::vector<float> res;
    for (int i = 0; i < width * height; i += 4)
    {
        float y =  0.299 * normalize(tex[i+0]) + 0.587 * normalize(tex[i+1]) + 0.114 * normalize(tex[i+2]);
        float cb =-0.169 * normalize(tex[i+0]) - 0.331 * normalize(tex[i+1]) + 0.500 * normalize(tex[i+2]);
        float cr = 0.500 * normalize(tex[i+0]) - 0.418 * normalize(tex[i+1]) - 0.082 * normalize(tex[i+2]);
        res.push_back(cb);
        res.push_back(cr);
    }
    return res;
}

float map_screenspace(int a, int size)
{
    return float(a) * 2 / size - 1;
}

std::vector<float> get_points_on_line(int x1, int y1, int x2, int y2, const glfwWindowHandle& window)
{
    std::vector<float> points;
    float k = ((float)y2 - y1) / (x2 - x1);
    float d = 2 * k - 1;
    int y = y1;

    points.push_back(map_screenspace(x1, window.width()));
    points.push_back(map_screenspace(y1, window.height()));

    for (int x = x1 + 1; x <= x2; x++)
    {
        if (d > 0)
        {
            d += 2 * k - 2;
            y++;
        }
        else
            d += 2 * k;

        points.push_back(map_screenspace(x, window.width()));
        points.push_back(map_screenspace(y, window.height()));
    }
    return points;
}

std::vector<float> get_points_on_vertical_line(int x, int y1, int y2, const glfwWindowHandle& window)
{
    std::vector<float> points;
    for (int y = y1; y < y2; y++)
    {
        points.push_back(map_screenspace(x, window.width()));
        points.push_back(map_screenspace(y, window.height()));
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
        delta += 2 * (++x - y--);
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
    glfwWindowHandle window{ glfwInitialiser::createWindow(900, 900, "Bresenham's algorithms") };
    glfwMakeContextCurrent(window.get());
    init_glew();

    Shader shader("C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/vetroscope_vertex.shader",
        "C:/Users/1voic/source/repos/OpenGLRenderer/res/shaders/vetroscope_fragment.shader");
    shader.bind();


    stbi_set_flip_vertically_on_load(1);
    int width, height;
    auto texture = stbi_load("C:/Users/1voic/source/repos/OpenGLRenderer/res/textures/original.png",
        &width, &height, nullptr, 4);

    auto vertices(tex_to_coords(texture, width, height));
    shader.set_uniform("u_color", glm::vec4{ 0.2f, 0.8f, 0.2f, 1.f });
    draw_points(vertices.data(), vertices.size());

    shader.set_uniform("u_color", glm::vec4{ 1.f, 0.9f, 0.1f, 1.f });
    auto line1_points(get_points_on_vertical_line(450, 50, 850, window));
    auto line2_points(get_points_on_line(50, 450, 850, 450, window));
    auto circle_points(get_points_on_circle(450, 450, 400, window));
    draw_points(circle_points.data(), circle_points.size());
    draw_points(line1_points.data(), line1_points.size());
    draw_points(line2_points.data(), line2_points.size());

    glfwSwapBuffers(window.get());
    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();
    }
}