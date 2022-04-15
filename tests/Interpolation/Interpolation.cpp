#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "util.h"

#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

constexpr uint32_t width = 1280;
constexpr uint32_t height = 720;

constexpr glm::vec4 red{ 1.0, 0.0, 0.0, 1.0 };
constexpr glm::vec4 green{ 0.0, 1.0, 0.0, 1.0 };
constexpr glm::vec4 blue{ .0, 0.0, 1.0, 1.0 };

struct Point
{
    glm::vec2 pos;
    glm::vec4 color;
};


inline glm::vec2 to_screenspace(glm::vec2 pos)
{
    float x = (pos.x * 2 / width) - 1;
    float y = (pos.y * 2 / height) - 1;
    return { x, y };
}

auto bounding_points(Point const& a, Point const& b, Point const& c)
{
    auto min_x = fminf(a.pos.x, fminf(b.pos.x, c.pos.x));
    auto min_y = fminf(a.pos.y, fminf(b.pos.y, c.pos.y));
    auto max_x = fmaxf(a.pos.x, fmaxf(b.pos.x, c.pos.x));
    auto max_y = fmaxf(a.pos.y, fmaxf(b.pos.y, c.pos.y));
    return std::make_pair( glm::vec2{min_x, min_y}, glm::vec2{ max_x, max_y} );
}

inline bool in_bounds(glm::vec2 pos, glm::vec2 min, glm::vec2 max)
{
    return min.x <= pos.x && pos.x <= max.x && min.y <= pos.y&& pos.y <= max.y;
}

glm::vec4 interpolate_color(glm::vec2 pos, Point const& a, Point const& b, Point const& c)
{

    return glm::vec4{ 1.0f };
}

bool in_triangle(glm::vec2 pos, Point const& a, Point const& b, Point const& c)
{
    if ((a.pos.x - pos.x) * (b.pos.y - pos.y) - (a.pos.y - pos.y) * (b.pos.x - pos.x) > 0) return false;
    if ((b.pos.x - pos.x) * (c.pos.y - pos.y) - (b.pos.y - pos.y) * (c.pos.x - pos.x) > 0) return false;
    if ((c.pos.x - pos.x) * (a.pos.y - pos.y) - (c.pos.y - pos.y) * (a.pos.x - pos.x) > 0) return false;
    return true;
}


std::vector<Point> make_trianlge(Point const& a, Point const& b, Point const& c)
{
    std::vector<Point> trianlge_points{ a,b,c };
    auto b_points = bounding_points(a, b, c);
    auto& [min, max] = b_points;

    for (glm::vec2 pos = min; in_bounds(pos, min, max); pos.x++)
    {
        for (pos; in_bounds(pos, min, max); pos.y++)
        {
            if (in_triangle(pos, a, b, c))
                trianlge_points.push_back(Point{ pos, interpolate_color(pos, a, b, c) });
        }
        pos.y = min.y;
    }

    std::for_each(trianlge_points.begin(), trianlge_points.end(), [](Point& p) { p.pos = to_screenspace(p.pos); });
    return trianlge_points;
}

void draw_points(const float* points, uint32_t len)
{
    assert(len * sizeof(Point) % 4 == 0);
    VertexBuffer vb(points,len * sizeof(Point)/4);
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(4);
    VertexArray va(vb, layout);

    glDrawArrays(GL_POINTS, 0, len );
}

int main()
{

    glfwInitialiser::getInstance();
    glfwWindowHandle window{ glfwInitialiser::createWindow(width, height, "Bresenham's algorithms") };
    glfwMakeContextCurrent(window.get());
    init_glew();


    Shader shader("../../../res/shaders/Interpolation_Vertex.shader",
        "../../../res/shaders/Interpolation_Fragment.shader");
    shader.bind();

    Point a{ glm::vec2{250, 100}, red };
    Point b{ glm::vec2{width/2, height - 100}, green };
    Point c{ glm::vec2{ width - 250, 100}, blue };
    auto vec = make_trianlge(a, b, c);

    draw_points((float*) &vec[0], vec.size());

    glfwSwapBuffers(window.get());
    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();
    }
}


