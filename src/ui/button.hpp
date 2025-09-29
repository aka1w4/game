#ifndef BUTTON
#define BUTTON

#include <functional>
#include <raylib.h>
#include "../db/db.hpp"

/// @brief Representasi Button
class Button {
  private:
    const char* text;                            // text button 
    int x, y, w, h, w2, h2, fontsize, screenX, screenY;  // posisi x y, lebar tinggi ukuran frame, fontsize ukuran text, screenX screenY posisi yang akan di gambar 
    Texture2D* img;                              // pointer texture image 
    std::function<void()> action;                // aksi yang akan di jalankan di Action()

  public:
    // @brief membuat button baru
    Button(int x, int y, int w, int h, int fontsize, const char* text, Texture2D& img, std::function<void()> action);
    // @brief Draw button
    void Draw(int offScrollY = 0);
    // @brief kondisi jika button di click
    bool isClicked();
    // @brief aksi yang akan di jalankan
    void Action();
    virtual ~Button() = default;
};

/// @brief Representasi tombol khusus untuk memilih world
class WorldButton : public Button {
  private:
    std::string path;                   // lokasi folder 
    int x, y, h, screenX, screenY;      // posisi x y, lebar tinggi ukuran frame, dan screenX screenY posisi yang akan di gambar
    Texture2D* imgicon;                 // texture image 
    std::function<void()> actionDelete; // aksi yang akan di jalankan di ActionDelete()

  public:
    /// @brief membuat world button baru
    WorldButton(int x, int y, int w, int h, int fontsize, Texture2D& img, Texture2D& imgicon, const WorldInfo& wi, std::function<void(const WorldInfo&)> action, std::function<void()> actionDelete) : 
      Button(x, y, w, h, fontsize, wi.name.c_str(), img, [=](){action(wi); }), 
      path(wi.path), imgicon(&imgicon), x(x), y(y), h(h), actionDelete(actionDelete) {}
    /// @brief Draw delete button
    void DrawDelete(int offScrollY);
    // @brief kondisi jika button di click
    bool isClickedDele();
    // @brief aksi yang akan di jalankan
    void ActionDelete();
};
#endif // !BUTTON
