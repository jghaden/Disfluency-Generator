#include "pch.h"

#define println(x) std::cout << x << std::endl

#define HIGHLIGHT_DEFAULT		0x8
#define HIGHLIGHT_STUTTER		0xC
#define HIGHLIGHT_INTERJECTION	0xA

#define GEN_TYPE_DEFUALT		0
#define GEN_TYPE_STUTTER		1
#define GEN_TYPE_INTERJECTION	2

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

constexpr unsigned int hash(const char* s, int off = 0)
{
	return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}

bool isVerbose = false;

std::string const PUNCTUATION = ".,!?";
std::vector<std::string> const INTERJECTIONS = { "um", "uh", "oh" };
std::vector<std::string> const PHRASES = { "yeah but like", "hot diggity dog", "jeepers creepers" };

bool isPunctuation(char ch)
{
	return (PUNCTUATION.find(ch) != std::string::npos);
}

struct word
{
	std::string s;
	int type = GEN_TYPE_DEFUALT;
};

std::string ErrorGenerator(const std::string &s)
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
			} while (w.type != GEN_TYPE_DEFUALT);

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

	return "";
}

int main(int argc, char** argv)
{
	srand(time(NULL));

	std::string s, tmp;
	
	std::string inputFileName;
	std::string outputFileName;

	for (int i = 1; i < argc; i++)
	{
		s = argv[i];
		s = StrToLower(s);

		//std::cout << hash(s.c_str()) << ":\t" << s << std::endl;
		switch (hash(s.c_str()))
		{
			case hash("-i"):
			case hash("-in"):
				if(argv[i + 1] != '\0' && argv[i + 1][0] != '-')
					inputFileName = argv[i + 1];
				break;
			case hash("-o"):
			case hash("-out"):
				if (argv[i + 1] != '\0' && argv[i + 1][0] != '-')
					outputFileName = argv[i + 1];
				break;
			case hash("-h"):
			case hash("-help"):
				println("\t-h,-help\tDisplays this help screen");
				println("\t-i,-in\t\tInput file for parsing");
				println("\t-o,-out\t\tOutput file after parsing");
				exit(0);
				break;
			case hash("-v"):
			case hash("-verbose"):
				isVerbose = true;
				break;
		}
	}

	if (argv[1] != '\0')
	{
		if (!inputFileName.empty() && !outputFileName.empty())
		{
			std::ifstream inFile;
			std::ofstream outFile;

			inFile.open(inputFileName);
			outFile.open(outputFileName);
			if (inFile.is_open())
			{
				while (!inFile.eof())
				{
					getline(inFile, tmp);
					outFile << '[' << ErrorGenerator(tmp) << "], [" << tmp << ']' << std::endl;
				}
			} else
			{
				println("ERROR::MISSING::INPUT_FILE: " + inputFileName);
			}

			inFile.close();
		} else
		{
			if (inputFileName.empty())
				println("ERROR::MISSING::INPUT_FILE_NAME");
			if (outputFileName.empty())
				println("ERROR::MISSING::OUTPUT_FILE_NAME");
		}
	}

	return 0;
}