#include "GAME.h"


// returns Width
int GAME::getWidth() const
{
    return m_windowWidth;
}


// returns Height
int GAME::getHeight() const
{
   
    return m_windowHeight;
}


GAME::GAME(short int width, short int height,Home state=Home())
    :m_windowWidth(width),
    m_windowHeight(height),
    m_state(state)
{

}

void GAME::run()
{
    InitWindow(m_windowWidth, m_windowWidth, m_Title);
    SetTargetFPS(60);
    while (!WindowShouldClose)
    {
        update();
        render();
    }
    CloseWindow();
}


void GAME::render()
{

    BeginDrawing();
    // Rendering code here
    //ClearBackground();

    
    EndDrawing();
}


void GAME::update()
{
    events();
}


void GAME::events()
{
    // TODO: Add your implementation code here.
}
