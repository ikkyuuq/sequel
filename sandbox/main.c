#include <define.h>
#include <core.h>
#include <stdlib.h>

int main(void)
{
  Application *app = create_app("sandbox", 800, 600, WINDOW_RESIZABLE);
  if (!app) return EXIT_FAILURE;

  run_app(app);

  destroy_app(app);

  return EXIT_SUCCESS;
}
