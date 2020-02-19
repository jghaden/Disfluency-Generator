#include "pch.h"

#define println(x) std::cout << x << std::endl

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

std::string const PUNCTUATION = ".,!?";
std::vector<std::string> const INTERJECTIONS = { "uh", "um", "oh" };

bool isPunctuation(char ch)
{
	return (PUNCTUATION.find(ch) != std::string::npos);
}

std::string ErrorGenerator(const std::string &s)
{
	int r;
	srand(time(NULL));

	//Split input sentence into words
	std::vector<std::string> words;
	std::string word = "";

	for (char ch : s)
	{
		if (ch == ' ' || isPunctuation(ch))
		{
			if(!word.empty())
				words.push_back(word);
			word.clear();
		}
		else
			word += ch;
	}

	/*for (int i = 0; i < words.size(); i++)
	{
		println('\"' + words[i] + '\"');
	}

	println("------");*/
	
	//Randomly pick what error to introduce into the sentence
	r = rand() % 1;

	switch (r)
	{
		//Stutter
		case 0:
			break;
		//Interject
		case 1:

			break;
	}

	return "";
}

int main(int argc, char** argv)
{
	bool flag = false;

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