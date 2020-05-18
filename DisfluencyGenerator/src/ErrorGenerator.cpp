#include "pch.h"
#include "System.h"
#include "ErrorGenerator.h"

std::vector<std::string> const INTERJECTIONS = { "um", "uh", "oh" };
std::vector<std::string> const PHRASES = { "yeah but like", "hot diggity dog", "jeepers creepers" };

std::string ErrorGenerator(const std::string &s, bool isVerbose)
{
	int r;
	//Split input sentence into words
	std::vector<word> words;
	word w;
	std::string out = "";

	for (char ch : s)
	{
		if (ch == ' ' || isPunctuation(ch))
		{
			if (!out.empty())
			{
				w.s = out;
				words.push_back(w);
			}
			out.clear();
		}
		else
			out += ch;
	}

	//Randomly pick what error to introduce into the sentence
	r = rand() % 3;

	//Stutter
	if (r == 0 || r == 2)
	{
		//Picks how much stuttering to add based on length of sentence
		r = words.size() % 4 + 1;
		for (int i = 0; i < r; i++)
		{
			do
			{
				r = rand() % words.size();
				w = words[r];
			}
			while (w.type != GEN_TYPE_DEFUALT);

			w.type = GEN_TYPE_STUTTER;
			words.insert(words.begin() + r, w);
		}
	}
	//Interjection
	if (r == 1 || r == 2)
	{
		//Picks how many interjections to add based on length of sentence
		r = words.size() % 4 + 1;
		for (int i = 0; i < r; i++)
		{
			w.s = INTERJECTIONS[rand() % INTERJECTIONS.size()];
			w.type = GEN_TYPE_INTERJECTION;
			words.insert(words.begin() + (rand() % words.size()), w);
		}
	}

	//Display the vector of words and highlight the intentional errors
	if (isVerbose)
	{
		SetColor(GetColor(GEN_TYPE_DEFUALT));

		std::cout << '[';
		for (int i = 0; i < words.size(); i++)
		{
			SetColor(GetColor(words[i].type));
			std::cout << '[' + words[i].s + "]";
			SetColor(GetColor(GEN_TYPE_DEFUALT));
			if (i < words.size() - 1)
				std::cout << ',';
		}
		println("]");

		SetColor(0x7);
		println("------");
	}

	out = "";

	for (int i = 0; i < words.size(); i++)
	{
		out += words[i].s;
		if (i < words.size() - 1)
			out += ' ';
	}

	return out;
}