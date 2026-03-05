#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct{
    char *question;
    char *choices[4];
    char correct;
    unsigned char points;
    unsigned char choice_count;
}Test;

void runQuiz(const Test[], const int);
void printQuestion(const Test[], const int);
char getInput(const Test[], const int);
bool checkAnswer(const Test[], const int, char);

int main()
{
    Test quiz[] = {
        {
            "What's the largest planet?",
            {"Mercury", "Jupiter", "Saturn", "Neptune"},
            'B',
            5,
            4
        },
        {
            "What's the smallest planet?",
            {"Earth", "Venus", "Mercury", "Mars"},
            'C',
            10,
            4
        },
        {
            "Which of the below is red?",
            {"The Sun", "An apple", "The sea", "Coffee"},
            'B',
            5,
            4
        },
        {
            "Is a person who is 20 an adult?",
            {"Yes", "No"},
            'A',
            5,
            2
        },
        {
            "What is the capital of Germany?",
            {"Berlin", "Munich", "Frankfurt", "Hamburg"},
            'A',
            5,
            4
        },
        {
            "Is the Earth flat?",
            {"Yes", "No"},
            'B',
            5,
            2
        },
        {
            "How many bits are in one byte?",
            {"4", "8", "16", "32"},
            'B',
            5,
            4
        }
    };
    
    int quiz_size = sizeof(quiz) / sizeof(quiz[0]);

    runQuiz(quiz, quiz_size);
    
    return 0;
}

void runQuiz(const Test quiz[], const int quiz_size)
{
    int max_score = 0;
    for(int i = 0; i < quiz_size; i++)
        max_score += quiz[i].points;
    int score = 0;

    printf("\n*** QUIZ GAME ***\n\n");
    for(int i = 0; i < quiz_size; i++)
    {
        printQuestion(quiz, i);

        char answer = getInput(quiz, i);

        if(checkAnswer(quiz, i, answer))
        {
            printf("CORRECT!\n\n");
            score += quiz[i].points;
        }
        else printf("WRONG!\n\n");
    };
    printf("You scored %d out of %d", score, max_score);
}

void printQuestion(const Test quiz[], const int i)
{
    printf("%d. %s\n", i + 1, quiz[i].question);
    for(int j = 0; j < quiz[i].choice_count; j++)
    {
        printf("%c. %s", 'A' + j, quiz[i].choices[j]);
        if(j < quiz[i].choice_count - 1)
            printf(" | ");
    }
    printf("\n");
}

char getInput(const Test quiz[], const int i)
{
    char answer;
    do
    {
        scanf(" %c", &answer);
        printf("\n");
        answer = toupper((unsigned char)answer);

        if(answer < 'A' || answer >= 'A' + quiz[i].choice_count)
            printf("Invalid Choice, Choose Again: ");

    }while(answer < 'A' || answer >= 'A' + quiz[i].choice_count);
    return answer;
}

bool checkAnswer(const Test quiz[], const int i, char answer)
{
    return (quiz[i].correct == answer);
}