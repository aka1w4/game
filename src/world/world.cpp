#include "world.hpp"
#include "../ui/button.hpp"
#include "../ui/textinput.hpp"
#include "../db/db.hpp"
#include <memory>
#include <raylib.h>
#include <filesystem>

NewWorld::NewWorld(Texture2D& inputT, Texture2D& buttonT) : 
  textinput_name(std::make_unique<Textinput>(200, 170, 183, 29, 20, inputT)), 
  submit(std::make_unique<Button>(200, 200, 183, 29, 20, "submit", buttonT, [this]()
        {
        TraceLog(LOG_INFO, "dibuat");

        createNewWorld(textinput_name->GetText(), 1);
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
