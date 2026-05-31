#pragma once

#include <define.h>
#include <renderer.h>

typedef struct Application
{
  Renderer *renderer;
  bool is_running;
} Application;

Application *create_app(cstring title, i32 width, i32 height, SDL_WindowFlags flags);

void run_app(Application *app);

void destroy_app(Application *app);
