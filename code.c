#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#define MAX_LIMIT 100

//ALARM FUNCTION
void timer(int H, int M, int S)
{
    printf("Your alarm will ring in\n");
    while (H >= 0 && M >= 0 && S >= 0)
    {
        if (M == 0 && H > 0)
        {
            M += 60;
            H--;
        }
        if (S == 0 && M > 0)
        {
            S += 60;
            M--;
        }
        printf("\r");
        printf("%2d:%2d:%2d", H, M, S);
        S--;
        Sleep (1000);
    }
    Beep(500,500);
    return;
}

//BLOOD GLUCOSE LEVEL FUNCTION
void GluCheck(int typ, int dat, FILE *od)
{
    if(typ==1)
    {
        if (dat<70)
        {
            fprintf(od, "Blood Glucose Level: %d\n", dat);
            fprintf(od, "Low blood glucose level. Please take more sugar!\n\n");
            printf("Low blood glucose level. Please take more sugar!\n\n");
            fprintf(od, "\n");
        }
        else if (dat>=70&&dat<131)
        {
            fprintf(od, "Blood Glucose Level: %d\n", dat);
            fprintf(od, "Normal blood glucose level. Keep it up!\n\n");
            printf("Normal blood glucose level. Keep it up!\n\n");
            fprintf(od, "\n");
        }
        else if (dat>=131)
        {
            fprintf(od, "Blood Glucose Level: %d\n", dat);
            fprintf(od, "High blood glucose level. Please take less sugar!\n");
            printf("High blood glucose level. Please take less sugar!\n");
            fprintf(od, "\n");
        }
    }
    else
    {
       if (dat<180)
        {
            fprintf(od, "Blood Glucose Level: %d\n", dat);
            fprintf(od, "Blood glucose level is in range. Keep it up!\n\n");
            printf("Blood glucose level is in range. Keep it up!\n\n");
            fprintf(od, "\n");
            return;
        }
        else if (dat>=180)
        {
            fprintf(od, "Blood Glucose Level: %d\n", dat);
            fprintf(od, "High blood glucose level. Please take less sugar!\n\n");
            printf("High blood glucose level. Please take less sugar!\n\n");
            fprintf(od, "\n");
            return;
        }
        else if (dat>=200)
        {
            fprintf(od, "Blood Glucose Level: %d\n", dat);
            fprintf(od, "Too high blood glucose level. Please find doctor ASAP!\n\n");
            printf("Too high blood glucose level. Please find doctor ASAP!\n\n");
            fprintf(od, "\n");
            return;
        }
    }
    printf("**********\n");
    return;
}

//CHECKING LEAP YEAR FOR AGE CALCULATION
int LeapYear(int year, int mon)
{
    int flag = 0;
    if (year % 100 == 0)
    {
        if (year % 400 == 0)
        {
            if (mon == 2)
            {
                flag = 1;
            }
        }
    }
    else if (year % 4 == 0)
    {
        if (mon == 2)
        {
                flag = 1;
        }
    }
    return (flag);
}

//AGE CALCULATION FUNCTION
void AgeCalc (int days, int month, int year, FILE *od)
{
    int DaysInMon[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char dob[100];
    time_t ts;
    struct tm *ct;
    //AGE CALCULATION
    ts = time(NULL);
    ct = localtime(&ts);

    days = DaysInMon[month - 1] - days + 1;

    //checking leap year
    if (LeapYear(year, month))
    {
        days = days + 1;
    }

    //calculating age in days, months, and years
    days = days + ct -> tm_mday;
    month = (12 - month) + (ct -> tm_mon);
    year = (ct -> tm_year + 1900) - year - 1;

    //for leap year age
    if (LeapYear((ct -> tm_year + 1900), (ct -> tm_mon + 1)))
    {
        if (days >= (DaysInMon[ct -> tm_mon] + 1))
        {
            days = days - (DaysInMon[ct -> tm_mon] + 1);
            month = month + 1;
        }
    }
    else if (days >= DaysInMon[ct -> tm_mon])
    {
        days = days - (DaysInMon[ct -> tm_mon]);
        month = month + 1;
    }

    printf("AGE: %d years %d months %d days\n", year, month, days);
    fprintf(od,"AGE: %d years %d months %d days\n", year, month, days);
}

int main()
{
    int hr, mn, s;
    FILE *od;
    od = fopen("result.txt", "w");
    if (od == NULL)
    {
        printf("ERROR! FILE COULD NOT BE OPENED! \n");
        return 0;
    }
    char name[MAX_LIMIT];
    int sex, inp, dat;
    int bday, bmon, byear;
    time_t ts;
    struct tm *ct;

    printf("****************************************************************\n");
    printf("*            KEEP YOUR BLOOD GLUCOSE LEVEL IN CHECK            *\n");
    printf("****************************************************************\n\n");
    fprintf(od, "****************************************************************\n");
    fprintf(od, "*            KEEP YOUR BLOOD GLUCOSE LEVEL IN CHECK            *\n");
    fprintf(od, "****************************************************************\n\n");

    //TODAY'S DATE
    ts = time(NULL);
    ct = localtime(&ts);
    printf("Today's Date: %d/%d/%d\n", ct -> tm_mday, ct -> tm_mon + 1, ct -> tm_year + 1900);
    fprintf(od, "Today's Date: %d/%d/%d\n\n", ct -> tm_mday, ct -> tm_mon + 1, ct -> tm_year + 1900);

    //PROFILE TITLE
    printf("\n**************************PROFILE PAGE**************************\n");
    fprintf(od, "**************************PROFILE PAGE**************************\n");

    //NAME
    printf("Please enter your name: ");
    scanf("%[^\n]%*c", name);
    printf("\n");
    fprintf(od, "NAME: %s\n", name);

    //GENDER
    printf("1 for Female \n2 for Male\n");
    printf("Please enter your sex assigned at birth: ");
    scanf("%d", &sex);
    printf("\n");

    if(sex != 1 && sex != 2)
    {
        while (sex!=1&&sex!=2)
        {
            printf("INVALID INPUT! \n");
            printf("1 for Female \n2 for Male\n");
            printf("Please enter your sex assigned at birth: ");
            scanf("%d", &sex);
            printf("\n");
        }
    }

    if(sex==1)
    {
        fprintf(od, "SEX ASSIGNED AT BIRTH: FEMALE\n");
    }
    else
    {
        fprintf(od, "SEX ASSIGNED AT BIRTH: MALE\n");
    }

    //BIRTHDAY
    printf("Please enter your birthday (DD/MM/YYYY): ");
    scanf("%d/%d/%d",&bday,&bmon, &byear);

    //invalid birthday
    if (bmon > 12 || bmon < 1)
    {
        while (bmon > 12 || bmon < 1)
        {
            printf("INVALID DATE! PLEASE REENTER YOUR BIRTHDAY!\n");
            printf("Please enter your birthday (DD/MM/YYYY): ");
            scanf("%d/%d/%d",&bday,&bmon, &byear);
        }
    }
    else if (bmon == 1 || bmon == 3 || bmon == 5 || bmon == 7 || bmon == 8 || bmon == 10|| bmon == 12)
    {
        while (bday > 31 || bday < 1)
        {
            printf("INVALID DATE! PLEASE REENTER YOUR BIRTHDAY!\n");
            printf("Please enter your birthday (DD/MM/YYYY): ");
            scanf("%d/%d/%d",&bday,&bmon, &byear);
        }
    }
    else if (bmon == 4 || bmon == 6 || bmon == 9 || bmon == 11)
    {
        while (bday > 30 || bday < 1)
        {
            printf("INVALID DATE! PLEASE REENTER YOUR BIRTHDAY!\n");
            printf("Please enter your birthday (DD/MM/YYYY): ");
            scanf("%d/%d/%d",&bday,&bmon, &byear);
        }
    }
    else if (bmon == 2)
    {
        if (LeapYear(byear, bmon))
        {
            while (bday > 29 || bday < 1)
            {
                printf("INVALID DATE! PLEASE REENTER YOUR BIRTHDAY!\n");
                printf("Please enter your birthday (DD/MM/YYYY): ");
                scanf("%d/%d/%d",&bday,&bmon, &byear);
            }
        }
        else
        {
            while (bday > 28 || bday < 1)
            {
                printf("INVALID DATE! PLEASE REENTER YOUR BIRTHDAY!\n");
                printf("Please enter your birthday (DD/MM/YYYY): ");
                scanf("%d/%d/%d",&bday,&bmon, &byear);
            }
        }
    }
    fprintf(od, "Birthday: %d/%d/%d\n", bday, bmon, byear);
    //age calculation
    AgeCalc(bday, bmon, byear, od);

    int cho;
    while(cho!=3)
    {
        printf("\n*****************************MENU*******************************\n");
        printf("SERVICE OPTIONS:\n\n");
        printf("GLUCOSE LEVEL CHECKER \t\t[1]\n");
        printf("SET AN ALARM \t\t\t[2]\n");
        printf("EXIT \t\t\t\t[3]\n\n");
        printf("SELECT YOUR CHOICE: ");
        scanf("%d", &cho);

        //GLUCOSE LEVEL CHECKER
        if (cho==1)
        {
            fprintf(od, "\n**********************GLUCOSE LEVEL CHECKER**********************\n");
            while(inp != 3)
            {
                printf("\n*********************GLUCOSE LEVEL CHECKER**********************\n");
                printf("SERVICE OPTIONS:\n\n");
                printf("FASTING GLUCOSE LEVEL \t\t[1]\n");
                printf("POST-MEAL GLUCOSE LEVEL \t[2]\n");
                printf("EXIT \t\t\t\t[3]\n\n");
                printf("ENTER YOUR CHOICE: ");
                scanf("%d", &inp);
                if (inp != 3 && inp != 1 && inp != 2)
                {
                    while (inp != 3 && inp != 1 && inp != 2)
                    {
                        printf("INVALID INPUT\n");
                        printf("Please Enter 0 to stop the program\n");
                        printf("Please Enter 1 if you are fasting\n");
                        printf("or Enter 2 if you have just eaten\n");
                        scanf("%d", &inp);
                    }
                }
                if (inp != 3)
                {
                    if (inp == 1)
                    {
                        printf("\nFASTING BLOOD GLUCOSE LEVEL\n");
                        fprintf(od, "FASTING BLOOD GLUCOSE LEVEL\n");
                    }
                    else if (inp == 2)
                    {
                        printf("\nPOST-MEAL BLOOD GLUCOSE LEVEL\n");
                        fprintf(od, "POST-MEAL BLOOD GLUCOSE LEVEL\n");
                    }
                    printf("Please enter your blood glucose level in mg/dL: ");
                    scanf("%d", &dat);
                    GluCheck(inp, dat, od);
                }
                if (inp == 3)
                {

                }
            }
        }

        //ALARM
        else if (cho == 2)
        {
            printf("*****************************ALARM******************************\n");
            printf("Please enter how long would you like your timer to run before the alarm rings (hh:mm:ss): ");
            scanf("%d:%d:%d", &hr, &mn, &s);
            timer (hr, mn, s);
        }

        //EXIT
        else if (cho == 3)
        {
            printf("THANK YOU FOR USING OUR SERVICE!\n");
        }
    }
    fclose(od);
}