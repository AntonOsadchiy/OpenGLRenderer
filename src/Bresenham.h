#pragma once 

#include "util.h"
#include <iostream>

inline float map_screenspace(int a, int size);

inline void drawLine(int x1, int y1, int x2, int y2, const glfwWindowHandle& window);
