#pragma once
#include "pch.h"

#define println(x) std::cout << x << std::endl

#define HIGHLIGHT_DEFAULT		0x8
#define HIGHLIGHT_STUTTER		0xC
#define HIGHLIGHT_INTERJECTION	0xA

#define GEN_TYPE_DEFUALT		0
#define GEN_TYPE_STUTTER		1
#define GEN_TYPE_INTERJECTION	2

std::string const PUNCTUATION = ".,!?";

int GetColor(int type);
void SetColor(int c);
std::string StrToLower(const std::string &s);
bool isPunctuation(char ch);