#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstring>

using namespace std;

void editSpaces(char* text)
{
    bool spaceWas = false;
    int i = 0, j = 0;

    while (text[i] != '\0')
    {
        if (isspace(text[i]))
        {
            if (!spaceWas)
            {
                text[j++] = text[i];
            }
            spaceWas = true;
        }
        else
        {
            text[j++] = text[i];
            spaceWas = false;
        }
        i++;
    }

    text[j] = '\0';
}
void editPunctuation(char* text)
{
    bool punctWas = false;
    int i = 0, j = 0;

    while (text[i] != '\0')
    {
        if (ispunct(text[i]))
        {
            if (!punctWas)
            {
                if (text[i] == '.' && text[i + 1] == '.' && text[i + 2] == '.')
                {
                    text[j++] = text[i];
                    text[j++] = text[i + 1];
                    text[j++] = text[i + 2];
                }
                else
                {
                    text[j++] = text[i];
                }
            }
            punctWas = true;
        }
        else
        {
            text[j++] = text[i];
            punctWas = false;
        }
        i++;
    }

    text[j] = '\0';
}
void editCase(char* text)
{
    bool startOfWord = true;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (startOfWord && isalpha(text[i]))
        {
            text[i] = toupper(text[i]);
            startOfWord = false;
        }
        else
        {
            text[i] = tolower(text[i]);
        }

        if (ispunct(text[i]) || isspace(text[i]))
        {
            startOfWord = true;
        }
    }
}
void deletePattern(char* text, const char* pattern)
{
    int lenText = strlen(text);
    int lenPattern = strlen(pattern);
    int i = 0, j = 0;

    while (i < lenText)
    {

        if (strncmp(&text[i], pattern, lenPattern) == 0)
        {
            i += lenPattern;
        }
        else
        {
            text[j++] = text[i++];
        }
    }

    text[j] = '\0';
}

void linearSearch(char* text, char* pattern)
{
    char result[999] = "";
    int lenText = strlen(text);
    int lenPat = strlen(pattern);

    for (int i = 0; i < lenText; i++)
    {
        int j;
        for (j = 0; j < lenPat; j++)
        {
            if (text[i + j] != pattern[j])
            {
                break;
            }
        }

        if (j == lenPat)
        {
            strncat_s(result, "[", 1);
            strncat_s(result, &text[i], lenPat);
            strncat_s(result, "]", 1);
            i += lenPat - 1;
        }
        else
        {
            strncat_s(result, &text[i], 1);
        }
    }

    cout << "Найденные последовательности: " << result << endl;
}

void task1(char* text)
{
    int answer;


    cout << "Каким способом ввести строку?" << endl << "1. С клавиатуры" << endl << "2. C файла" << endl << ">";
    cin >> answer;
    cin.ignore();

    switch (answer)
    {
    case 1:
    {
        cout << "Введите строку: ";
        cin.getline(text, 999);
        break;
    }
    case 2:
    {
        ifstream file("text3.txt");

        if (!file)
        {
            cout << "Не удалось открыть файл((" << endl;
            return;
        }

        file.getline(text, 999);

        file.close();
        break;

    }
    }
}
void task2(char* text)
{
    editSpaces(text);
    editPunctuation(text);
    editCase(text);
}
void task3(char* text)
{
    //Вывести на экран слова последовательности, не содержащие цифр.
    char word[50];
    int indexWord = 0;

    cout << "Слова без цифр: ";

    for (int i = 0; text[i] != '\0' || indexWord > 0; i++)
    {
        if (isalnum(text[i]))
        {
            word[indexWord++] = text[i];
        }
        else
        {
            if (indexWord > 0)
            {
                word[indexWord] = '\0';
                bool numberWas = false;

                for (int j = 0; word[j] != '\0'; j++)
                {
                    if (isdigit(word[j]))
                    {
                        numberWas = true;
                        break;
                    }
                }

                if (!numberWas)
                {
                    cout << word << " ";
                }
                indexWord = 0;
            }
        }
    }

    cout << endl << endl;
}
void task4(char* text)
{
    //Вывести на экран ту же последовательность, удалив из всех слов заданный набор букв и (или) цифр.
    char pattern[100];
    cout << "Введите последовательность, которую нужно удалить: ";
    cin >> pattern;

    char word[50];
    int indexWord = 0;
    bool firstWord = true;

    for (int i = 0; text[i] != '\0' || indexWord > 0; i++)
    {
        if (isalnum(text[i]))
        {
            word[indexWord++] = text[i];
        }
        else
        {
            if (indexWord > 0)
            {
                word[indexWord] = '\0';
                deletePattern(word, pattern);

                if (indexWord > 0)
                {
                    if (!firstWord)
                    {
                        cout << " ";
                    }
                    cout << word;
                    firstWord = false;
                }
                indexWord = 0;
            }
            if (text[i] != '\0' && !isspace(text[i]))
            {
                cout << text[i];
            }
        }
    }

    cout << endl << endl;
}
void task5(char* text)
{
    char pattern[50];

    cout << "Введите последовательность, которую нужно найти: ";
    cin >> pattern;

    linearSearch(text, pattern);
}

int main()
{
    setlocale(0, "");

    char text[999];

    task1(text);
    cout << "Изначальная строка:" << endl << text << endl << endl;
    task2(text);
    cout << "Строка после редактирования:" << endl << text << endl << endl;
    task3(text);
    task4(text);
    task5(text);

    return 0;

}
