#include "world.hpp"
#include "../ui/button.hpp"
#include "../ui/textinput.hpp"
#include "../db/db.hpp"
#include "../player/player.hpp"
#include <memory>
#include <raylib.h>
#include <filesystem>

NewWorld::NewWorld(Texture2D& inputT, Texture2D& buttonT) : 
  textinput_name(std::make_unique<Textinput>(240, 60, 183, 29, 40, inputT)), 
  submit(std::make_unique<Button>(240,120, 183, 29, 40, "submit", buttonT, [this]()
        {
        SavePlayer sp = SavePlayer{Vector2{100, 100}, Down, false};
        createNewWorld(textinput_name->GetText(), 1);
        writeBinPlayer(textinput_name->GetText(), sp);
        })) 
  {
    if(!std::filesystem::exists("world")) {
      std::filesystem::create_directories("world");
    }
  }

void NewWorld::Update() {
  textinput_name->checkPos();

  if (textinput_name->inTextInput()) {
    textinput_name->EditInputText();
  }

  if (textinput_name->GetText().size() >= 5) {
    if (submit->isClicked()) {
      submit->Action();
      textinput_name->ClearText();
    }
  }
 }

void NewWorld::Draw() {
  textinput_name->Draw();
  submit->Draw();
}

void NewWorld::ClearText() {
  textinput_name->ClearText();
}
