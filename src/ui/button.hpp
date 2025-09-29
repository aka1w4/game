#ifndef BUTTON
#define BUTTON

#include <functional>
#include <raylib.h>
#include "../db/db.hpp"

enum typeButton {
  ExitGame,
  Exit,
  Start,
  Create,
  Setting,
  Resume,
};

class Button {
  private:
    const char* text;
    int x, y, w, h, fontsize, screenX, screenY;
    Texture2D* img;
    std::function<void()> action;

  public:
    Button(int x, int y, int w, int h, int fontsize, const char* text, Texture2D& img, std::function<void()> action);
    void Draw(int offScrollY = 0);
    bool isClicked();
    void Action();
    virtual ~Button() = default;
};

class WorldButton : public Button {
  private:
    std::string path;
    int x, y, h, screenX, screenY;
    Texture2D* imgicon;
    std::function<void()> actionDelete;

  public:
    WorldButton(int x, int y, int w, int h, int fontsize, Texture2D& img, Texture2D& imgicon, const WorldInfo& wi, std::function<void(const WorldInfo&)> action, std::function<void()> actionDelete) : 
      Button(x, y, w, h, fontsize, wi.name.c_str(), img, [=](){action(wi); }), 
      path(wi.path), imgicon(&imgicon), x(x), y(y), h(h), actionDelete(actionDelete) {}
    void DrawDelete(int offScrollY);
    bool isClickedDele();
    void ActionDelete();
};
#endif // !BUTTON
