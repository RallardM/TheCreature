#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>

#include "DebugMessageSystem.h"
#include "ScenesManager.h"

//ScenesManager::ScenesManager() :
//	m_userCurrentScene(E_SceneSequence::INTRO_SCENE)
//{
//}


void ScenesManager::PrintMenuFromScene(E_UserInput userInput)
{
    E_SceneSequence scene = GetPlayerCurrentScene();
    //short int gameMenuLine = 0;
    //short int selectedMenuLine = GetSelectedMenuLine();
    //short int startingMenuLine = GetGameMenuLine(E_SceneSequence::INTRO_SCENE);
    //short int currentPlainMenu = GetCurrentPlainMenu();
    //std::string currentSceneMenuText = GetCurrentSceneMenuText();
    //std::ifstream& menuFilePath = GetMenuFilePath();

    switch (scene)
    {
    case E_SceneSequence::INTRO_SCENE:
        if (userInput != E_UserInput::EMPTY)
        {
            ClearConsolePreviousLine();
            if (userInput == E_UserInput::LEFT)
            {
                std::cout << GetMenuAtLine(GetMenuFilePath(), m_introHighlightedMenu[0]) << std::endl;
                SetIsMenuCleared(false);
                SetSelectedMenuLine(m_introHighlightedMenu[0]);
            }
            else if (userInput == E_UserInput::RIGHT)
            {
                std::cout << GetMenuAtLine(GetMenuFilePath(), m_introHighlightedMenu[1]) << std::endl;
                SetIsMenuCleared(false);
                SetSelectedMenuLine(m_introHighlightedMenu[1]);
            }
        }
        else
        {
            std::cout << GetMenuAtLine(GetMenuFilePath(), m_introHighlightedMenu[0]) << std::endl;
        }
        break;

    case E_SceneSequence::MOVING_SCENE:
        //std::cout << GetMenuAtLine(m_narrationManager->GetMenuFilePath(), 7) << std::endl;

        break;

    default:
        break;
    }
    //std::string newCurrentSceneMenuText = GetMenuAtLine(m_narrationManager->GetMenuFilePath(), gameMenuLine);
    //std::cout << newCurrentSceneMenuText << std::endl;
    //std::cout << GetCurrentSceneMenuText();
}

std::string ScenesManager::GetLastLineInConsole()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);

    COORD position;
    position.X = 0;
    position.Y = screenBufferInfo.dwCursorPosition.Y;

    SetConsoleCursorPosition(consoleHandle, position);

    std::string lastLine;
    // DEBUG_MSG("#R Last line:");
     //std::cout << "\n" << lastLine << std::endl;
     //DEBUG_MSG("#R :Last line");

     // Check if the last line is empty
    if (screenBufferInfo.dwCursorPosition.X == 0)
    {
        return "";
    }

    getline(std::cin, lastLine);

    return lastLine;
}

std::string ScenesManager::GetMenuAtLine(std::string& filePathStr, unsigned short int atLine)
{
    std::ifstream filePath(filePathStr);
    std::string text;

    // Check if file opens
    if (!filePath.is_open())
    {
        // File could not be opened, so return an empty string
        DEBUG_MSG("#R ERROR: Could not open the game text file.");
        exit(EXIT_FAILURE);
    }
    else
    {
        std::string line;
        unsigned short int currentLine = 0;

        // Read the file line by line
        while (getline(filePath, line))
        {
            // Increment the current line number
            currentLine++;

            // If the current line number matches the specified line number, 
            // store the line in the output string and break out of the loop
            if (currentLine == atLine)
            {
                text = line;
                break;
            }
        }

        // Close the file
        filePath.close();
    }

    // Return the output string.
    return text;
}

void ScenesManager::PrintLinesFromScene()
{
    E_SceneSequence scene = GetPlayerCurrentScene();
    const unsigned short int ASCII_IMAGE_HEIGHT = 33;
    const unsigned short int STORY_TEXT_HEIGHT = 4;
    const unsigned short int MENU_TEXT_HEIGHT = 5;

    unsigned short int gameImageFirstLine = 0;
    unsigned short int gameImageLastLine = 0;
    unsigned short int gameTextFirstLine = 0;
    unsigned short int gameTextLastLine = 0;

    switch (scene)
    {
    case E_SceneSequence::INTRO_SCENE:
        gameImageFirstLine = GetSceneImageLines(E_SceneSequence::INTRO_SCENE);
        gameImageLastLine = gameImageFirstLine + ASCII_IMAGE_HEIGHT;

        gameTextFirstLine = GetSceneTextLines(E_SceneSequence::INTRO_SCENE);
        gameTextLastLine = gameTextFirstLine + STORY_TEXT_HEIGHT;

        break;

    case E_SceneSequence::MOVING_SCENE:
        gameImageFirstLine = GetSceneImageLines(E_SceneSequence::MOVING_SCENE);
        gameImageLastLine = gameImageFirstLine + ASCII_IMAGE_HEIGHT;

        gameTextFirstLine = GetSceneTextLines(E_SceneSequence::MOVING_SCENE);
        gameTextLastLine = gameTextFirstLine + STORY_TEXT_HEIGHT;

        break;

    default:
        break;
    }

    std::string scenePicture = GetTextBetweenLines(GetPictureFilePath(), gameImageFirstLine, gameImageLastLine);
    std::string sceneText = GetTextBetweenLines(GetTextFilePath(), gameTextFirstLine, gameTextLastLine);


    std::cout << scenePicture;
    std::cout << sceneText;

}

std::string ScenesManager::GetTextBetweenLines(std::string& filePathStr, unsigned int firstLine, unsigned int lastLine)
{
    //std::ifstream filePath("resouce_files/ScenesAsciiArt.txt");
    std::ifstream filePath(filePathStr);
    std::string text;
    std::string line;

    // Check if file opens
    if (!filePath.is_open())
    {
        // File could not be opened, so return an empty string
        DEBUG_MSG("#R ERROR: Could not open the game text file.");
        exit(EXIT_FAILURE);
    }
    else
    {
        //unsigned int currentLine = 1;
        unsigned int currentLine = firstLine;

        // Read each line in the file until we reach the end or the desired line range.
        while (std::getline(filePath, line) && currentLine <= lastLine)
        {
            // If the current line is within the desired range, add it to the output string.
            if (currentLine >= firstLine)
            {
                text += line + "\n";
            }
            currentLine++;
        }

        // Close the file
        filePath.close();
    }

    // Return the output string.
    return text;
}


ScenesManager::E_UserInput ScenesManager::GetInput()
{
    char key = 0;
    while (true)
    {
        //if (_kbhit())
        //{
        key = _getch(); // Read the key
        //std::cout << "Letter " << char(key) << " pressed , number :" << key << std::endl;

        switch (key)
        {
        case 'a':
        case 'A':
        case 75: // Left arrow keya
            return E_UserInput::LEFT;

        case 100: // Letter d
            return E_UserInput::RIGHT;
        case 68: // Letter D
            return E_UserInput::RIGHT;
        case 77: // Right arrow key
            return E_UserInput::RIGHT;

        case 'w':
        case 'W':
        case 72: // Up arrow key
            return E_UserInput::UP;

        case 's':
        case 'S':
        case 80: // Down arrow key
            return E_UserInput::DOWN;

        case 13: // Enter key
            return E_UserInput::ENTER;

        case 27: // Escape key
            return E_UserInput::ESC;

        default: // Default case - returns an empty input
            return E_UserInput::EMPTY;
        }
    }
}

void ScenesManager::SetAction(E_UserInput userInput)
{
    userInput = GetInput();


    if (userInput == E_UserInput::LEFT || userInput == E_UserInput::RIGHT)
    {
        PrintMenuFromScene(userInput);
        SetIsMenuCleared(false);
        SetHasInput(false);
    }
    if (userInput == E_UserInput::UP)
    {
    }
    if (userInput == E_UserInput::DOWN)
    {
    }
    if (userInput == E_UserInput::ENTER)
    {
        std::cout << GetSelectedMenuLine() << std::endl;
    }
    if (userInput == E_UserInput::ESC)
    {

    }
}

bool ScenesManager::HasInput()
{
    return m_hasInput;
}

void ScenesManager::SetHasInput(bool hasInput)
{
    m_hasInput = hasInput;
}

ScenesManager::E_SceneSequence ScenesManager::GetPlayerCurrentScene()
{
	return m_userCurrentScene;
}

void ScenesManager::SetPlayerCurrentScene(E_SceneSequence scene)
{
	m_userCurrentScene = scene;
}

unsigned short int ScenesManager::GetSelectedMenuLine()
{
    return m_selectedMenuLine;
}

void ScenesManager::SetSelectedMenuLine(unsigned short int selectedMenuLine)
{
    m_selectedMenuLine = selectedMenuLine;
}

void ScenesManager::ClearConsolePreviousLine()
{
    std::cout << "\033[1A\033[0K";
    SetIsMenuCleared(true);
}

bool ScenesManager::GetIsMenuCleared()
{
    return m_isMenuCleared;
}

void ScenesManager::SetIsMenuCleared(bool isMenuCleared)
{
    m_isMenuCleared = isMenuCleared;
}

std::string& ScenesManager::GetPictureFilePath()
{
    return m_pictureFilePath;
}

std::string& ScenesManager::GetTextFilePath()
{
    return m_textFilePath;
}

std::string& ScenesManager::GetMenuFilePath()
{
    return m_menuFilePath;
}

unsigned short int ScenesManager::GetSceneImageLines(E_SceneSequence fromLine)
{
    return m_sceneImageLines[static_cast<int>(fromLine)];
}

unsigned short int ScenesManager::GetSceneTextLines(E_SceneSequence fromLine)
{
    return m_sceneTextLines[static_cast<int>(fromLine)];
}

unsigned short int ScenesManager::GetSceneMenuLine(E_SceneSequence fromLine)
{
    return m_sceneMenuLines[static_cast<int>(fromLine)];
}
