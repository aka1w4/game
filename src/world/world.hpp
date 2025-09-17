#ifndef WORLD
#define WORLD

#include "../ui/textinput.hpp"
#include "../ui/button.hpp"
#include <memory>
#include <raylib.h>
#include <string>

class NewWorld {
  private:
    std::string name;
    std::unique_ptr<Textinput> textinput_name;
    std::unique_ptr<Button> submit;

  public:
    NewWorld(Texture2D& inputT, Texture2D& buttonT);
    void Draw();
    void Update();
    void ClearText();
};

#endif // !WORLD
