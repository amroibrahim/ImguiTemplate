#include "Application.hpp"

int main(int, char**)
{
  Application app;
  if (!app.Init("ImGui Sample (SDL3)"))
    return EXIT_FAILURE;

  app.Run();
  app.Shutdown();

  return EXIT_SUCCESS;
}
