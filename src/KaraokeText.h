#pragma once
#include <vector>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Line
{
	int m_id;
	int timeStampStart;
	int timeStampEnd;
	std::string text;
};

class KaraokeText
{
	public:
	KaraokeText();
	~KaraokeText();

	int ParseLyrics();
	std::string GetCurrentWorkingDir();
	Line GetTextWithId(int id) {return m_lyrics[id];}

	std::string m_text;

	std::vector<Line> m_lyrics;
};