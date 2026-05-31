#include <core.h>
#include <define.h>
#include <renderer.h>
#include <da.h>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>

#include <stdlib.h>

Application *create_app(cstring title, i32 width, i32 height, SDL_WindowFlags flags)
{
  Application *app = malloc(sizeof(Application));
  if (!app)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to allocate memory for Application");
    return NULL;
  }

  app->renderer = malloc(sizeof(Renderer));
  if (!app->renderer)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to allocate memory for Renderer");
    free(app);
    return NULL;
  }

  app->renderer->command_queue = malloc(sizeof(RenderCommands));
  if (!app->renderer->command_queue)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to allocate memory for Vector(Command Queue)");
    free(app->renderer);
    free(app);
    return NULL;
  }

  da_init(app->renderer->command_queue, RenderCommand, 32);
  if (!app->renderer->command_queue->data)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to allocate memory for RenderCommand(Initial)");
    free(app->renderer->command_queue);
    free(app->renderer);
    free(app);
    return NULL;
  }

  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init failed: %s", SDL_GetError());
    free(app->renderer->command_queue->data);
    free(app->renderer->command_queue);
    free(app->renderer);
    free(app);
    return NULL;
  }

  app->renderer->device = SDL_CreateGPUDevice(
      SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true, NULL);
  if (!app->renderer->device)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateGPUDevice failed: %s", SDL_GetError());
    free(app->renderer->command_queue->data);
    free(app->renderer->command_queue);
    free(app->renderer);
    free(app);
    return NULL;
  }

  app->renderer->window = SDL_CreateWindow(title, width, height, flags);
  if (!app->renderer->window)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow failed: %s", SDL_GetError());
    SDL_DestroyGPUDevice(app->renderer->device);
    free(app->renderer->command_queue->data);
    free(app->renderer->command_queue);
    free(app->renderer);
    free(app);
    return NULL;
  }

  if (!SDL_ClaimWindowForGPUDevice(app->renderer->device, app->renderer->window))
  {
    SDL_DestroyGPUDevice(app->renderer->device);
    SDL_DestroyWindow(app->renderer->window);
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow failed: %s", SDL_GetError());
    free(app->renderer->command_queue->data);
    free(app->renderer->command_queue);
    free(app->renderer);
    free(app);
    return NULL;
  }

  app->is_running = false;
  return app;
}

void destroy_app(Application *app)
{
  if (!app || !app->renderer || !app->renderer->command_queue || !app->renderer->command_queue->data)
    return;

  if (app->renderer->device && app->renderer->window)
  {
    SDL_ReleaseWindowFromGPUDevice(app->renderer->device, app->renderer->window);
    SDL_DestroyGPUDevice(app->renderer->device);
    SDL_DestroyWindow(app->renderer->window);
  }

  free(app->renderer->command_queue->data);
  free(app->renderer->command_queue);
  free(app->renderer);
  free(app);
  SDL_Quit();
}

void run_app(Application *app)
{
  app->is_running = true;

  while (app->is_running)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_EVENT_QUIT:
        app->is_running = false;
        break;
      }
    }

    // update
    // render
  }
}
