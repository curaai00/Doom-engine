#pragma once

#include "Drawable.h"
#include "Fragment.h"
#include "zbuffer.h"

#include <cstdint>
#include <string>

using namespace std;

class Window
{
public:
    Window(const string name, const int width, const int height);
    ~Window();

    void render(const std::vector<Fragment>& fragments);
    void update(void);
    bool running(void) { return is_running; }

    const Mat44& screenMatrix(void) const { return _screen_mat; }
    SDL_Color pixel(uint x, uint y);

public:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    bool is_running;

private:
    std::string name;
    const int w;
    const int h;

    // about screen_mat
    const int min_x = 0;
    const int min_y = 0;
    const float min_z = 0.0f;
    const float max_z = 1.0f;
    Mat44 _screen_mat;

    // drawing elements
    ZBuffer _zbuffer;
};
