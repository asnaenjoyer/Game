#include "Game.h"
#include <windows.h>

int main(int argc, char *argv[]) {

}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const auto game = new Game("Game", 400, 400);
    game->run();
    delete game;
    return 0;
}