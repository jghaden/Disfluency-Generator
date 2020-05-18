/**
  ******************************************************************************
  * @file    System.cpp
  * @author  Joshua Haden
  * @version V0.0.0
  * @date    18-MAY-2020
  * @brief   Adds support to highlight changes when executed at the command line
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "pch.h"
#include "System.h"

int GetColor(int type)
{
	int c;

	switch (type)
	{
	case GEN_TYPE_STUTTER:
		c = HIGHLIGHT_STUTTER;
		break;
	case GEN_TYPE_INTERJECTION:
		c = HIGHLIGHT_INTERJECTION;
		break;
	case GEN_TYPE_DEFUALT:
		c = HIGHLIGHT_DEFAULT;
		break;
	}

	return c;
}

void SetColor(int c)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
}

std::string StrToLower(const std::string &s)
{
	std::string out = "";

	for (int i = 0; i < s.length(); i++)
	{
		out += tolower(s[i]);
	}

	return out;
}