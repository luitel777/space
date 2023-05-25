#include "space.hpp"
#include "render.hpp"

class Boulder : public RenderObjects {
private:
  RenderObjects *boulder = new RenderObjects;
  ObjectProperties *boulder_property = new ObjectProperties;
public:
  void add_unique_boulder(int a);
  ObjectProperties *return_property();
  void set_speed(int score);
  void reset_property();
  void render_boulder();
  void update_boulder();
};


void unique_boulder();

static Boulder *b1 = new Boulder;
static Boulder *b2 = new Boulder;
static Boulder *b3 = new Boulder;
static Boulder *b4 = new Boulder;

