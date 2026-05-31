#include "SDL3/SDL_error.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_log.h"
#include <da.h>
#include <renderer.h>

void clear_color(Renderer *ctx, Color color)
{
  SDL_GPUCommandBuffer *command_buf = SDL_AcquireGPUCommandBuffer(ctx->device);
  if (!command_buf)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_AcquireGPUCommandBuffer failed: %s", SDL_GetError());
    return;
  }

  SDL_GPUTexture *swapchain_texture;
  if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buf, ctx->window, &swapchain_texture, NULL, NULL))
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_WaitAndAcquireGPUSwapchainTexture failed: %s", SDL_GetError());
    return;
  }

  SDL_GPUColorTargetInfo color_target_info = {0};
  color_target_info.clear_color = (SDL_FColor){color.r, color.g, color.b, color.a};
  color_target_info.load_op = SDL_GPU_LOADOP_CLEAR;
  color_target_info.store_op = SDL_GPU_STOREOP_STORE;
  color_target_info.texture = swapchain_texture;

  if (swapchain_texture)
  {

    SDL_GPURenderPass *render_pass = SDL_BeginGPURenderPass(command_buf, &color_target_info, 1, NULL);
    if (!render_pass)
    {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_BeginGPURenderPass failed: %s", SDL_GetError());
      return;
    }
    SDL_EndGPURenderPass(render_pass);
  }

  SDL_SubmitGPUCommandBuffer(command_buf);
}

void submit_render_command(Renderer *ctx, SDL_GPUGraphicsPipeline *pipeline)
{
  RenderCommand render_command = {0};
  render_command.pipeline = pipeline;

  da_append(RenderCommand, ctx->command_queue, &render_command);
}

void swap_buffer(Renderer *ctx)
{
  if (ctx->command_queue->size <= 0)
    return;

  SDL_GPUCommandBuffer *command_buf = SDL_AcquireGPUCommandBuffer(ctx->device);
  if (!command_buf)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_AcquireGPUCommandBuffer failed: %s", SDL_GetError());
    return;
  }

  SDL_GPUTexture *swapchain_texture;
  if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buf, ctx->window, &swapchain_texture, NULL, NULL))
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_WaitAndAcquireGPUSwapchainTexture failed: %s", SDL_GetError());
    return;
  }

  SDL_GPUColorTargetInfo color_target_info = {0};
  color_target_info.clear_color = (SDL_FColor){0, 0, 0, 0};
  color_target_info.load_op = SDL_GPU_LOADOP_CLEAR;
  color_target_info.store_op = SDL_GPU_STOREOP_STORE;
  color_target_info.texture = swapchain_texture;

  if (swapchain_texture)
  {
    SDL_GPURenderPass *render_pass = SDL_BeginGPURenderPass(command_buf, &color_target_info, 1, NULL);
    if (!render_pass)
    {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_BeginGPURenderPass failed: %s", SDL_GetError());
      return;
    }

    SDL_GPUGraphicsPipeline *prev_graphic_pipeline = NULL;
    for (size_t i = 0; i < ctx->command_queue->size; i++)
    {
      SDL_GPUGraphicsPipeline *current_graphic_pipeline = ctx->command_queue->data[i]->pipeline;
      if (current_graphic_pipeline != prev_graphic_pipeline)
      {
        SDL_BindGPUGraphicsPipeline(render_pass, current_graphic_pipeline);
        prev_graphic_pipeline = current_graphic_pipeline;
      }
    }
    SDL_EndGPURenderPass(render_pass);
  }

  SDL_SubmitGPUCommandBuffer(command_buf);

  da_clear(ctx->command_queue);
  if (!ctx->command_queue->data)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to clear and allocate memory for ctx->command_queue->data");
  }
}
