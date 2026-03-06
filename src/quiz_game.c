#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    char question[100];
    unsigned char choice_count;
    char choices[4][50];
    char correct;
    unsigned char points;
}Test;

void runQuiz(const Test[], const int);
void printQuestion(const Test[], const int);
char getInput(const Test[], const int);
bool checkAnswer(const Test[], const int, char);
int loadQuestions(const char*, Test[]);
void removeNewLine(char[]);

int main()
{
    Test quiz[50];
    int quiz_size = loadQuestions("quiz.txt", quiz);
    if(quiz_size == 0) return 1;
    runQuiz(quiz, quiz_size);
    
    return 0;
}

void removeNewLine(char str[]){
    str[strcspn(str, "\n")] = '\0';
}

int loadQuestions(const char *filename, Test quiz[])
{
    FILE *pFile = fopen(filename, "r");
    if(pFile == NULL){
        printf("Error opening file...");
        return 0;
    }

    int i = 0;
    char buffer[1024];

    while(i < 50)
    {
        /*Read Question from the File*/
        if(fgets(quiz[i].question, sizeof(quiz[i].question), pFile) == NULL)
            break;
        removeNewLine(quiz[i].question);

        /*Read Choice Count from the File*/
        if(fgets(buffer, sizeof(buffer), pFile) == NULL)
            break;
        removeNewLine(buffer);
        sscanf(buffer, "%hhu", &quiz[i].choice_count);

        /*Read Choices from the File for (Choice Count) Times*/
        for(int j = 0; j < quiz[i].choice_count; j++)
        {
            if(fgets(quiz[i].choices[j], sizeof(quiz[i].choices[j]), pFile) == NULL)
                break;
            removeNewLine(quiz[i].choices[j]);
        }

        /*Read the Correct Answer from the File*/
        if(fgets(buffer, sizeof(buffer), pFile) == NULL)
            break;
        removeNewLine(buffer);
        quiz[i].correct = buffer[0];

        /*Read the Point Value of the Question from the File*/
        if(fgets(buffer, sizeof(buffer), pFile) == NULL)
            break;
        removeNewLine(buffer);
        sscanf(buffer, "%hhu", &quiz[i].points);

        /*Read the Separator and Do Nothing with It*/
        if(fgets(buffer, sizeof(buffer), pFile) == NULL)
            break;

        i++;
    }

    fclose(pFile);
    return i;

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
