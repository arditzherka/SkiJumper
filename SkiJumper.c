#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct SkiJumper
{
    char name[30];
    char surname[30];
    int yobirth;
    float jump;

};
typedef struct SkiJumper SkiJumper;

void readSkiJumper(SkiJumper *s);
void writeSkiJumper(SkiJumper s);
void removeEnter(char *text);
void formatSurname(char *text);
void formatName(char *text);
void averageOfBestJump(SkiJumper *s,int size);
void youngestSkiJumper(SkiJumper youngest,SkiJumper *array,int size);
void jumpSort(SkiJumper s,SkiJumper *array,int size);
void putSkiJumpersToFile(SkiJumper s, FILE *f);

int main()
{
    FILE *myfile;

    int n;
    char answer;
    do
    {
        printf("The number of skijumpers:\n");
        scanf("%d",&n);
        myfile=fopen("SkiJumper.txt","a");
        if(n>0)
        {
            SkiJumper s;
            SkiJumper array[n];
            for(int i=0; i<n; i++)
            {
                readSkiJumper(&array[i]);
                printf("\n\n");
            }

            averageOfBestJump(array,n);

            for(int i=0; i<n; i++)
            {
                //writeSkiJumper(array[i]);
                // printf("\n\n");
                putSkiJumpersToFile(array[i],myfile);   /* (h)append all information about ski jumpers to the text file located in the current directory.*/

            }
            /*(f) find the youngest ski jumper in the array of nth ski jumpers*/
            youngestSkiJumper(s,array,n);

            /*(g) sort all ski jumpers from an array of nth ski jumpers in non-decreasing order with respect to the best jump*/

            printf("Skijumpers sorted in non-decreasing order with respect to the best jump:\n\n");

            jumpSort(s,array,n);

            printf("\nOnce again? (y/n) ");

        }
        scanf(" %c",&answer);
        fflush(stdin);
    }
    while (answer=='Y' || answer=='y');
    printf("\n\nEnd of program!\n\n");
    return 0;
}

void readSkiJumper(SkiJumper *s)
{
    fflush(stdin);
    fputs("Skijumper name:\n",stdout);
    fgets(s->name,sizeof(s->name),stdin);
    fflush(stdin);
    fputs("Skijumper surname:\n",stdout);
    fgets(s->surname,sizeof(s->surname),stdin);
    removeEnter(s->name);
    removeEnter(s->surname);
    formatSurname(s->surname);
    formatName(s->name);
    printf("Skijumper year of birth:\n");
    scanf("%d",&s->yobirth);
    printf("Skijumper length of best jump:\n");
    scanf("%f",&s->jump);
}

void writeSkiJumper(SkiJumper s)
{
    printf("Skijumper name:%s\nSkijumper surname:%s\nSkijumper year of birth:%d\nSkijumper best jump length:%g\n\n",s.name,s.surname,s.yobirth,s.jump);

}
void removeEnter(char *text)
{
    int n=strlen(text);
    if(text[n-1]=='\n')
        text[n-1]='\0';
}
void formatSurname(char *text)
{
    int i=0;
    while(text[i])
    {
        text[i]=toupper(text[i]);

        ++i;
    }
}
void formatName(char *text)
{
    text[0]=toupper(text[0]);
    int i=1;

    while(text[i])
    {
        text[i]=tolower(text[i]);
        if(text[i]==' ')

            text[++i]=toupper(text[i]);
        i++;
    }
}

void putSkiJumpersToFile(SkiJumper s, FILE *f)
{
    fprintf(f,"Skijumper name:%s\nSkijumper surname:%s\nSkijumper year of birth:%d\nSkijumper best jump length:%g\n\n",s.name,s.surname,s.yobirth,s.jump);
}
/*(e) find the average of best jumps of all ski jumpers from an array of nth ski jumpers*/
void averageOfBestJump(SkiJumper *array,int size)
{
    float sum=0.0;
    float average;
    for(int i = 0; i<size; i++)
    {
        sum+=array[i].jump;
    }

    average=sum/(float)size;
    printf("Average of best jumps:%g \n",average);
}
void jumpSort(SkiJumper s,SkiJumper *array,int size)
{

    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (array[i].jump < array[j].jump)
            {
                s = array[i];
                array[i] = array[j];
                array[j] = s;
            }
        }
    }
    for(int i=0; i<size; i++)
    {
        s=array[i];
        writeSkiJumper(s);
    }
}

void youngestSkiJumper(SkiJumper youngest,SkiJumper *array,int size)
{

    youngest = array[0];
    for(int i =1 ; i<size; i++)
    {
        if(youngest.yobirth<array[i].yobirth)
        {
            youngest=array[i];
        }

    }

    printf("The youngest skijumper is:\n\n");
    writeSkiJumper(youngest);
}
