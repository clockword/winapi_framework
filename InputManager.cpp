#include "InputManager.h"

InputManager::InputManager()
{
    m_xDown = 0;
    m_xUp = 0;
    m_yDown = 0;
    m_yUp = 0;
    m_x = 0;
    m_y = 0;
    m_mouseClicked = false;
    m_shockOff = false;
}

InputManager* InputManager::GetInstance()
{
    static InputManager instance;

    return &instance;
}

void InputManager::RegisterButton(Button* button)
{
    buttons.push_back(button);
}

void InputManager::RegisterTextBox(TextBox* textbox)
{
    textboxes.push_back(textbox);
}

void InputManager::ClearRegistered()
{
    buttons.clear();
    textboxes.clear();
}

void InputManager::SetMouseDownPos(int x, int y)
{
    m_xDown = x;
    m_yDown = y;
    Buttons::iterator bIt = buttons.begin();
    for (;bIt != buttons.end(); bIt++)
    {
        if((*bIt)->GetActive())
            (*bIt)->OnMouseButtonDown(x, y);
        if (m_shockOff)
        {
            m_shockOff = false;
            return;
        }
    }
    TextBoxes::iterator tIt = textboxes.begin();
    for (;tIt != textboxes.end(); tIt++)
    {
        if((*tIt)->GetActive())
            (*tIt)->OnMouseButtonDown(x, y);
        if (m_shockOff)
        {
            m_shockOff = false;
            return;
        }
    }
}

void InputManager::SetMouseUpPos(int x, int y)
{
    m_xUp = x;
    m_yUp = y;
    Buttons::iterator bIt = buttons.begin();
    for (;bIt != buttons.end(); bIt++)
    {
        (*bIt)->OnMouseButtonUp(x, y);
        if (m_shockOff)
        {
            m_shockOff = false;
            return;
        }
    }
    TextBoxes::iterator tIt = textboxes.begin();
    for (;tIt != textboxes.end(); tIt++)
    {
        (*tIt)->OnMouseButtonUp(x, y);
        if (m_shockOff)
        {
            m_shockOff = false;
            return;
        }
    }
}

void InputManager::KeyBoardInput(char ch)
{
    TextBoxes::iterator tIt = textboxes.begin();
    for (;tIt != textboxes.end(); tIt++)
    {
        (*tIt)->OnKeyboardInput(ch);
        if (m_shockOff)
        {
            m_shockOff = false;
            return;
        }
    }
}
