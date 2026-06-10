#include "KaraokeText.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <direct.h>

KaraokeText::KaraokeText()
{
    m_text = GetCurrentWorkingDir() + "\\assets\\Adele-Hello.txt"; // Convert raw string to std::string for concatenation
    ParseLyrics();
}

KaraokeText::~KaraokeText()
{
    m_lyrics.clear();
}

int KaraokeText::ParseLyrics()
{
    std::ifstream file(m_text); // Assuming m_text contains the file path

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << m_text << std::endl;
        return -1; // Return an error code instead of lines
    }

    std::string str;

    while (std::getline(file, str))
    {
        std::stringstream ss(str);

        Line line = {};

        std::string token;

        std::getline(ss, token, '|');
        line.m_id = std::stoi(token);

        std::getline(ss, token, '|');
        line.timeStampStart = std::stoi(token);

        std::getline(ss, token, '|');
        line.timeStampEnd = std::stoi(token);

        //std::getline(ss, line.text);
        std::getline(ss, token, '|');
        line.text = token;
        m_lyrics.push_back(line);
    }

    file.close();
    return 0;
}

std::string KaraokeText::GetCurrentWorkingDir()
{
    char cwd[FILENAME_MAX + 1]; // Use a char array instead of std::string  
    if (_getcwd(cwd, sizeof(cwd)) != nullptr) // Use _getcwd for Windows compatibility  
    {
        return std::string(cwd); // Convert char array to std::string  
    }
    else
    {
        std::cerr << "Error: Unable to get current working directory" << std::endl;
        return "";
    }
}