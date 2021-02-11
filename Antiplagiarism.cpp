#include <iostream>

#define ZERO       0
#define THREE      3
#define THIRTY_TWO 32
#define HUNDRED    100
#define CHARACTERS 1024

using namespace std;

void setNormalizeText(char* text);
bool isCapitalLetter(char letter);
void splitString(char* text, int startWordPosition = 0, int count = 1);
bool isMatchString(char* originalText, char* fragment);
void getResult(char* fragment, char* originalText, int matchCount, double& unique);
void strCopy(char firstString[], char secondString[]);
int strLength(char string[]);
int countWords(char* text);
double getUniquePercent(double match, double iterations);

int main()
{
	int shinglesCount = 0;
	double percent = 0.0;
	
	cout << "Input shingles count: ";
	cin >> shinglesCount;
	// check < 1 (for me)
	cout << endl;

	char originalText[] = "The Java Tutorials are practical guides for programmers who want to use the Java programming language to create applications. They include hundreds of complete, working examples, and dozens of lessons. Groups of related lessons are organized into trails.";
	char fragment[] = "The Java programming language are practical guides for programmers. The Java Tutorials are organized into trails. Create applications include hundreds of complete. Groups of dozens of lessons.";

	getResult(fragment, originalText, shinglesCount, percent);
	
	cout << "Text has unique " << percent << " percent" << endl;

	return 0;
}

void setNormalizeText(char* text) {
	for (int i = 0; text[i] != '\0'; i++) {
		if ((text[i] >= 'A' and text[i] <= 'Z') or (text[i] >= 'a' and text[i] <= 'z')) {
			if (isCapitalLetter(text[i]))
				text[i] += THIRTY_TWO;
		}
		else
			text[i] = ' ';
	}
}

bool isCapitalLetter(char letter) {
	if (letter >= 'A' and letter <= 'Z')
		return true;
	return false;
}

void getResult(char* fragment, char* originalText, int matchCount, double& unique) {
	int i = 0, j = 0, iterationCount = 0, numberWord = 0;
	double result = 0.0;

	setNormalizeText(originalText);	
	setNormalizeText(fragment);

	char copyFragment[CHARACTERS];
	char copyFragmentIteration[CHARACTERS];
	char copyOriginalText[CHARACTERS];
	char copyOriginalTextIteration[CHARACTERS];	

	strCopy(copyFragment, fragment);	
	strCopy(copyFragmentIteration, fragment);	
	strCopy(copyOriginalText, originalText);
	splitString(copyOriginalTextIteration);
	
	while (strLength(copyFragmentIteration) > 0) {
		iterationCount++;
		splitString(copyFragment, i, matchCount);
		strCopy(copyOriginalTextIteration, originalText);
		splitString(copyOriginalTextIteration);	
		while (strLength(copyOriginalTextIteration) > 0) {
			splitString(copyOriginalText, j, matchCount);
			if (isMatchString(copyOriginalText, copyFragment))
				result++;
			strCopy(copyOriginalText, originalText);
			strCopy(copyOriginalTextIteration, originalText);
			j++;
			splitString(copyOriginalTextIteration, j);
			numberWord = countWords(originalText) - j;
            if (numberWord < THREE)
                break;
		}
		strCopy(copyFragment, fragment);
		strCopy(copyFragmentIteration, fragment);
		i++;
		j = 0;
		splitString(copyFragmentIteration, i);
		numberWord = countWords(fragment) - i;
		if (numberWord < THREE)
		    break;
	}
	unique = getUniquePercent(result, iterationCount);	
}

void splitString(char* text, int startWordPosition, int count) {
	char buf[CHARACTERS];
	int length = 0, word = 0, i = 0, j = 0;
	bool flag = false;

	count += startWordPosition;	
	while (text[i] != '\0') {
		while (text[i] == ' ') {
			if (!flag)
				word++;
			flag = true;
			i++;
		}
		flag = false;
		if (count == word)
			break;
		if (startWordPosition <= word) {
			buf[j] = text[i];			
			length++;
			j++;
		}
		i++;
	}
	for (i = 0; text[i] != '\0'; i++)	{
		if (i < length)
			text[i] = buf[i];
		else
			text[i] = '\0';
	}
}

int countWords(char* text) {
	int word = 0;
	bool flag = false; 
		
  	for (int i = 0; text[i] != '\0'; i++) {
  		if (text[i] != ' ' and flag == false) {
  			word++;
  			flag = true;
  		}
  		else {
  			if (text[i] == ' ')
  				flag = false;
  		}  			
  	}
  	return word;
}

bool isMatchString(char* originalText, char* fragment) {
	if (strLength(originalText) != strLength(fragment))
		return false;
		
	for (int i = 0; originalText[i] != '\0'; i++) {
		if (originalText[i] != fragment[i])
			return false;
	}
	return true;
}

void strCopy(char firstString[], char secondString[]) {
	int length = strLength(secondString);

	for (int i = 0; i <= length; i++) {
		if (i == length)
			firstString[i] = '\0';
		firstString[i] = secondString[i];
	}
}

int strLength(char string[]) {
	int counter = 0;

	while (string[counter] != '\0')
		counter++;

	return counter;
}

double getUniquePercent(double match, double iteration) {
	double result = 0.0;

	if (!match)
		return HUNDRED;
	if (match > iteration)
	    return ZERO;

	result = (iteration - match) / iteration * HUNDRED;
	return result;
}
