/**
  ******************************************************************************
  * @file    ErrorGenerator.h
  * @author  Joshua Haden
  * @version V0.0.0
  * @date    18-MAY-2020
  * @brief   Header for ErrorGenerator.cpp
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#pragma once
#include "pch.h"
#include "System.h"

struct word
{
	std::string s;
	int type = GEN_TYPE_DEFUALT;
};

bool isPunctuation(char ch);
std::string ErrorGenerator(const std::string &s, bool isVerbose);