#include <engine.hpp>

using namespace qpl;

int main(int, char**) {
  WindowConfig cfg{800, 600, "Hello, World!", false};
  Engine engine(cfg);
  engine.Start();
  return 0;
}
