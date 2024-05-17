
// (c) 2024 R.Hasaranga

#include "src/Console/WSHat.h"
#include "src/Console/NView.h"
#include "src/Tic-Tac-Toe/TicTac.h"
#include "src/Sokoban/Sokoban.h"
#include "src/WaterSort/WaterSort.h"

WSHat hat;
GameListView gameListView;
MainMenuView mainMenuView;
SettingsView settingsView;
AboutView aboutView;
TicTacGameView ticTacGameView;
SokobanGameView sokobanGameView;
WaterSortGameView waterSortGameView;

NView* currentView = nullptr;
unsigned long lastTimeViewExit = 0;

NView* getViewByID(uint8_t viewID)
{
  if(viewID == MAINMENU_VIEW_ID)
    return &mainMenuView;
  else if(viewID == GAMELIST_VIEW_ID)
    return &gameListView;
  else if(viewID == SETTINGS_VIEW_ID)
    return &settingsView;
  else if(viewID == ABOUT_VIEW_ID)
    return &aboutView;
  else if(viewID == TIC_TAC_GAME_VIEW)
    return &ticTacGameView;
  else if(viewID == SOKOBAN_GAME_VIEW)
    return &sokobanGameView;   
  else if(viewID == WATERSORT_GAME_VIEW)
    return &waterSortGameView;
  else
    return &mainMenuView;    
}

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");
  
  SettingsStore::init();
  hat.init();

  gameListView.init(&hat);
  mainMenuView.init(&hat);
  settingsView.init(&hat);
  aboutView.init(&hat);
  ticTacGameView.init(&hat);
  sokobanGameView.init(&hat);
  waterSortGameView.init(&hat);

  mainMenuView.start(false);
  currentView = &mainMenuView;
  lastTimeViewExit = millis();
}

void loop() {
  if(currentView){
    currentView->loop((millis() - lastTimeViewExit) < BUTTON_DELAY);
    if(currentView->shouldStop()){
      currentView->stop();
      const uint8_t nextViewID = currentView->getNextViewID();
      const bool resetLastItemIndex = !currentView->showLastMenuItem();
      NView* nextView = getViewByID(nextViewID);
      nextView->start(resetLastItemIndex);
      currentView = nextView;
      lastTimeViewExit = millis();
    }
  }
}
