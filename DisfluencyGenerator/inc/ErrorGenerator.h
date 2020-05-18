#pragma once
#include "pch.h"
#include "System.h"

struct word
{
	std::string s;
	int type = GEN_TYPE_DEFUALT;
};

std::string ErrorGenerator(const std::string &s, bool isVerbose);