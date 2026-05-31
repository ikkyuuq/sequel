#pragma once

#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_video.h"

typedef struct RenderCommand
{
  SDL_GPUGraphicsPipeline *pipeline;
} RenderCommand;

typedef struct Renderer
{
  SDL_Window *window;
  SDL_GPUDevice *device;
  RenderCommand *command_queue;
} Renderer;
