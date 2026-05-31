#pragma once

#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_video.h"
#include "define.h"
#include <assert.h>
#include <stdlib.h>

typedef struct RenderCommand RenderCommand;
typedef struct RenderCommands RenderCommands;
typedef struct Renderer Renderer;

typedef struct RenderCommands
{
  RenderCommand **data;
  size_t size;
  size_t capacity;
} RenderCommands;

typedef struct RenderCommand
{
  SDL_GPUGraphicsPipeline *pipeline;
} RenderCommand;

typedef struct Renderer
{
  SDL_Window *window;
  SDL_GPUDevice *device;
  RenderCommands *command_queue;
} Renderer;

typedef struct Color
{
  f32 r, g, b, a;
} Color;

void clear_color(Renderer *ctx, Color color);

void submit_render_command(Renderer *ctx, SDL_GPUGraphicsPipeline *pipeline);
void swap_buffer(Renderer *ctx);
