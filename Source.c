#import "struct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#define filename "flights.txt"

void input()

{

    FILE *f;

    flights data;

    int n, i;

    char str[30];

    f = fopen(filename, "wb");

    printf("Enter the number of flights: ");

    scanf("%d", &n);

    for (i = 0; i < n; ++i)

    {

        gets(str);

        printf("\nFlight №%d. Entering following features:\n", i + 1);

        printf("Enter airline: ");

        gets(data.airline);

        printf("Enter target airport: ");

        gets(data.airport);

        printf("Enter type of aircraft: ");

        gets(data.aircraft);

        printf("Enter flight's ID: ");

        if (!scanf("%d", &data.ID))
        {
            printf("No pasaran!");
            fclose(f);
            exit(1);
        }
        if ( 0 > data.ID)
        {
            printf("Wrong ID!");
            return;
        }


        printf("Enter the number of passengers: ");

        if (!scanf("%d", &data.passengers))
        {
            printf("No pasaran!");
            fclose(f);
            exit(1);
        }

        if ( 0 > data.passengers || data.passengers > 300)
        {
            printf("We all live in a Yellow Submarine!");
        }

        printf("Enter arriving time:\nSchedule hours: ");

        if (! scanf("%d", &data.schedule_hours))
        {
            printf("No pasaran!");
            fclose(f);
            exit(1);
        }

        if (0 > data.schedule_hours || data.schedule_hours > 24)
        {
            printf("It was a long-long day!");
            fclose(f);
            return;
        }

        printf("Schedule minutes: ");

        if (!scanf("%d", &data.schedule_minutes))
        {
            printf("No pasaran!");
            fclose(f);
            exit(1);
        }

        if (0 > data.schedule_minutes || data.schedule_minutes > 60)
        {
            printf("Mom? Dad? Friends? Why one chapter of Game of Thrones became a season?");
            return;
        }

        printf("Estimated hours:");

        if (!scanf("%d", &data.estimated_hours))
        {
            printf("No pasaran!");
            fclose(f);
            exit(1);
        }

        if (0 > data.schedule_hours || data.schedule_hours > 24)
        {
            printf("It was a long-long day!");
            fclose(f);
            return;
        }

        printf("Estimated minutes:");

        if (! scanf("%d", &data.estimated_minutes))
        {
            printf("No pasaran!");
            fclose(f);
            exit(1);
        }

        if (0 > data.schedule_minutes || data.schedule_minutes > 60)
        {
            printf("Mom? Dad? Friends? Why one chapter of Game of Thrones became a season?");
            return;
        }

        fwrite(&data, sizeof(flights), 1, f);

    }

    printf("\n");

    fclose(f);

    printf("Data is fulfilled.\n\n");

}

void add()

{

    FILE *f;

    flights data;

    char str[30];

    f = fopen(filename, "rb+");

    printf("Enter features of the new flight:\n");

    gets(str);

    printf("Enter airline: ");

    gets(data.airline);

    printf("Enter target airport: ");

    gets(data.airport);

    printf("Enter type of aircraft: ");

    gets(data.aircraft);

    printf("Enter flight's ID: ");

    if (!scanf("%d", &data.ID))
    {
        printf("No pasaran!");
        fclose(f);
        exit(1);
    }

    printf("Enter the number of passengers: ");

    if (!scanf("%d", &data.passengers))
    {
        printf("No pasaran!");
        fclose(f);
        exit(1);
    }

    printf("Enter arriving time:\nSchedule hours: ");

    if (!scanf("%d", &data.schedule_hours))
    {
        printf("No pasaran!");
        fclose(f);
        exit(1);
    }

    printf("Schedule minutes: ");

    if (!scanf("%d", &data.schedule_minutes))
    {
        printf("No pasaran!");
        fclose(f);
        exit(1);
    }

    printf("Estimated hours:");

    if (!scanf("%d", &data.estimated_hours))
    {
        printf("No pasaran!");
        fclose(f);
        exit(1);
    }

    printf("Estimated minutes:");

    if (!scanf("%d", &data.estimated_minutes))
    {
        printf("No pasaran!");
        fclose(f);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    fwrite(&data, sizeof(flights), 1, f );

    fclose(f);

    printf("\nNew flight added.\n\n");

}

void del()

{

    FILE *f;

    flights data;

    int i, ind, size;

    f = fopen(filename, "rb+");

    printf("Enter the flight number: ");

    if (!scanf("%d", &ind))
    {
        printf("No pasaran!");

        return;
    }

    fseek(f, 0, SEEK_END);

    size = ftell(f) / sizeof(flights);

    while ((ind > size) || (ind < 1))

    {

        printf("\nNo such flight. Choose another: ");

        if (!scanf("%d", &ind))
        {
            printf("No pasaran!");

            return;
        }

    }

    --ind;

    for (i = ind; i < size - 1; ++i)

    {

        fseek(f, (i + 1) * sizeof(flights), SEEK_SET);

        fread(&data, sizeof(flights), 1, f);

        fseek(f, i * sizeof(flights), SEEK_SET);

        fwrite(&data, sizeof(flights), 1, f);

    }

    ftruncate(fileno(f), (size - 1) * sizeof(flights));

    //Unix function - consider using chsize on DOS system instead
    //chsize(fileno(f), (size - 1) * sizeof(flights));

    fclose(f);

    printf("\nFlight removed\n\n");

}

void find()

{

    FILE *f;

    flights data;

    char str[30];

    int ind, num;

    f = fopen(filename, "rb");

    printf("Choose the sorting feature:\n1 - Airline\n2 - Airport\n3 - Aircraft\n4 - ID\n5 - Passengers\n6 - Schedule\n7 - Estimated\n\n");

    if (!scanf("%d", &ind))
    {
        printf("No pasaran!");

        return;
    }

    printf("\n");

    gets(str);

    switch (ind)

    {

        case 1:

            printf("Enter airline: ");

            gets(str);

            printf("\nFound:\n");

            while (!feof(f))

            {

                fread(&data, sizeof(flights), 1, f);

                if (!feof(f))

                {

                    if (!strcmp(data.airline, str))

                        printf("%-10s%-10s%-10s%-5d%-5d%-5d:%d%-5d:%d\n", data.airline, data.airport, data.aircraft, data.ID, data.passengers, data.schedule_hours, data.schedule_minutes, data.estimated_hours, data.estimated_minutes);

                }

            }

            printf("\n");

            break;

        case 2:

            printf("Enter airport: ");

            gets(str);

            printf("\nFound:\n");

            while (!feof(f))

            {

                fread(&data, sizeof(flights), 1, f);

                if (!feof(f))

                {

                    if (!strcmp(data.airport, str))

                        printf("%-10s%-10s%-10s%-5d%-5d%-5d:%d%-5d:%d\n", data.airline, data.airport, data.aircraft, data.ID, data.passengers, data.schedule_hours, data.schedule_minutes, data.estimated_hours, data.estimated_minutes);

                }

            }

            printf("\n");

            break;

        case 3:

            printf("Enter aircraft: ");

            gets(str);

            printf("\nFound:\n");

            while (!feof(f))

            {

                fread(&data, sizeof(flights), 1, f);

                if (!feof(f))

                {

                    if (!strcmp(data.aircraft, str))

                        printf("%-10s%-10s%-10s%-5d%-5d%-5d:%d%-5d:%d\n", data.airline, data.airport, data.aircraft, data.ID, data.passengers, data.schedule_hours, data.schedule_minutes, data.estimated_hours, data.estimated_minutes);

                }

            }

            printf("\n");

            break;

        case 4:

            printf("Enter ID: ");

            if (!scanf("%d", &num))
            {
                printf("No pasaran!");
                return;
            }

            printf("\nFound:\n");

            while (!feof(f))

            {

                fread(&data, sizeof(flights), 1, f);

                if (!feof(f))

                {

                    if (data.ID == num)

                        printf("%-10s%-10s%-10s%-5d%-5d%-5d:%d%-5d:%d\n", data.airline, data.airport, data.aircraft, data.ID, data.passengers, data.schedule_hours, data.schedule_minutes, data.estimated_hours, data.estimated_minutes);

                }

            }

            printf("\n");

            break;

        case 5:

            printf("Enter number of passengers: ");

            if (!scanf("%d", &num))
            {
                printf("No pasaran!");

                return;
            }

            printf("\nFound:\n");

            while (!feof(f))

            {

                fread(&data, sizeof(flights), 1, f);

                if (!feof(f))

                {

                    if (data.passengers == num)

                        printf("%-10s%-10s%-10s%-5d%-5d%-5d:%d%-5d:%d\n", data.airline, data.airport, data.aircraft, data.ID, data.passengers, data.schedule_hours, data.schedule_minutes, data.estimated_hours, data.estimated_minutes);

                }

            }

            printf("\n");

            break;

        case 6:

            printf("Enter schedule hours: ");

            if (!scanf("%d", &num))
            {
                printf("No pasaran!");

                return;
            }

            printf("\nFound:\n");

            while (!feof(f))

            {

                fread(&data, sizeof(flights), 1, f);

                if (!feof(f))

                {

                    if (data.schedule_hours == num)

                        printf("%-10s%-10s%-10s%-5d%-5d%-5d:%d%-5d:%d\n", data.airline, data.airport, data.aircraft, data.ID, data.passengers, data.schedule_hours, data.schedule_minutes, data.estimated_hours, data.estimated_minutes);

                }

            }

            printf("\n");

            break;

        case 7:

            printf("Estimated hours: ");

            if (!scanf("%d", &num))
            {
                printf("No pasaran!");

                return;
            }

            printf("\nFound:\n");

            while (!feof(f))

            {

                fread(&data, sizeof(flights), 1, f);

                if (!feof(f))

                {

                    if (data.estimated_hours == num)

                        printf("%-10s%-10s%-10s%-5d%-5d%-5d:%d%-5d:%d\n", data.airline, data.airport, data.aircraft, data.ID, data.passengers, data.schedule_hours, data.schedule_minutes, data.estimated_hours, data.estimated_minutes);

                }

            }

            printf("\n");

            break;

        default:

            printf("No Pasaran!\n\n");

    }

    fclose(f);

}

void edit()

{

    FILE *f;

    flights data;

    char str[30];

    int i, ind, size;

    f = fopen(filename, "rb+");

    printf("Enter flight: ");

    if (!scanf("%d", &ind))
    {
        printf("No pasaran!");

        return;
    }

    fseek(f, 0, SEEK_END);

    size = ftell(f) / sizeof(flights);

    while ((ind > size) || (ind < 1))

    {

        printf("\nNo such flight. Enter another: ");

        if (!scanf("%d", &ind))
        {
            printf("No pasaran!");

            return;
        }

    }

    --ind;

    fseek(f, ind * sizeof(flights), SEEK_SET);

    fread(&data, sizeof(flights), 1, f);

    fseek(f, -sizeof(flights), SEEK_CUR);

    printf("\nChoose feature:\n1 - Airline\n2 - Airport\n3 - Aircraft\n4 - ID\n5 - Passengers\n6 - Schedule\n7 - Estimated\n\n");

    if (!scanf("%d", &i))
    {
        printf("No pasaran!");

        return;
    }

    printf("\n");

    gets(str);

    switch (i)

    {

        case 1:

            printf("Enter airline: ");

            gets(data.airline);

            printf("\n");

            break;

        case 2:

            printf("Enter airport: ");

            gets(data.airport);

            printf("\n");

            break;

        case 3:

            printf("Enter aircraft: ");

            gets(data.aircraft);

            printf("\n");

            break;

        case 4:

            printf("Enter ID: ");

            if (!scanf("%d", &data.ID))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            break;

        case 5:

            printf("Enter numbers of passengers: ");

            if (!scanf("%d", &data.passengers))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            break;

        case 6:

            printf("Enter schedule hours: ");

            if (!scanf("%d", &data.schedule_hours))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            break;

        case 7:

            printf("Enter schedule minutes: ");

            if (!scanf("%d", &data.schedule_minutes))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            break;

        case 8:

            printf("Enter estimated hours: ");

            if (!scanf("%d", &data.estimated_hours))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            break;

        case 9:

            printf("Enter estimated minutes: ");

            if (!scanf("%d", &data.estimated_minutes))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            break;

        default:

            printf("No pasaran!\n\n");

    }

    fwrite(&data, sizeof(flights), 1, f);

    fclose(f);

}

void sort()

{

    FILE *f;

    flights tmp;

    flights *datas = NULL;

    int i, j, ind1, ind2, size;

    f = fopen(filename, "rb+");

    fseek(f, 0, SEEK_END);

    size = ftell(f) / sizeof(flights);

    fseek(f, 0, SEEK_SET);

    datas = (flights*)malloc(size * sizeof(flights));

    for (i = 0; i < size; ++i)

    {

        fread(&datas[i], sizeof(flights), 1, f);

    }

    printf("\nChoose feature:\n1 - Airline\n2 - Airport\n3 - Aircraft\n4 - ID\n5 - Passengers\n6 - Schedule\n7 - Estimated\n\n");

    if (!scanf("%d", &ind1))
    {
        printf("No pasaran!");

        return;
    }

    printf("\n");

    switch (ind1)

    {

        case 1:

            printf("1 - increasing\n2 - decreasing\n\n");

            if (!scanf("%d", &ind2))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            switch (ind2)

            {

                case 1:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (strcmp(datas[j].airline, datas[j + 1].airline) > 0)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                case 2:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (strcmp(datas[j].airline, datas[j + 1].airline) < 0)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                default:

                    printf("No pasaran!\n\n");

            }

            break;

        case 2:

            printf("1 - increasing\n2 - decreasing\n\n");

            if (!scanf("%d", &ind2))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            switch (ind2)

            {

                case 1:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (strcmp(datas[j].airport, datas[j + 1].airport) > 0)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                case 2:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (strcmp(datas[j].airport, datas[j + 1].airport) < 0)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                default:

                    printf("No pasaran\n\n");

            }

            break;

        case 3:

            printf("1 - increasing\n2 - decreasing\n\n");

            if (!scanf("%d", &ind2))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            switch (ind2)

            {

                case 1:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (strcmp(datas[j].aircraft, datas[j + 1].aircraft) > 0)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;
                case 2:
                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (strcmp(datas[j].aircraft, datas[j + 1].aircraft) < 0)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                default:

                    printf("No pasaran\n\n");

            }

            break;

        case 4:

            printf("1 - increasing\n2 - decreasing\n\n");

            if (!scanf("%d", &ind2))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            switch (ind2)

            {

                case 1:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (datas[j].ID > datas[j + 1].ID)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                case 2:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (datas[j].ID < datas[j + 1].ID)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                default:

                    printf("No pasaran\n\n");

            }

            break;

        case 5:

            printf("1 - increasing\n2 - decreasing\n\n");

            if (!scanf("%d", &ind2))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            switch (ind2)

            {

                case 1:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (datas[j].passengers > datas[j + 1].passengers)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                case 2:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (datas[j].passengers < datas[j + 1].passengers)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                default:

                    printf("No pasaran\n\n");

            }

            break;

        case 6:

            printf("1 - increasing\n2 - decreasing\n\n");

            if (!scanf("%d", &ind2))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            switch (ind2)

            {

                case 1:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (datas[j].schedule_hours*60+datas[j].schedule_minutes > datas[j + 1].schedule_hours*60+datas[j + 1].schedule_minutes)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                case 2:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (datas[j].schedule_hours*60+datas[j].schedule_minutes < datas[j + 1].schedule_hours*60+datas[j + 1].schedule_minutes)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                default:

                    printf("No pasaran\n\n");

            }

            break;

        case 7:

            printf("1 - increasing\n2 - decreasing\n\n");

            if (!scanf("%d", &ind2))
            {
                printf("No pasaran!");

                return;
            }

            printf("\n");

            switch (ind2)

            {

                case 1:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (datas[j].estimated_hours*60+datas[j].estimated_minutes > datas[j + 1].estimated_hours*60+datas[j + 1].estimated_minutes)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                case 2:

                    for (i = size - 1; i >= 0; i--)

                    {

                        for (j = 0; j < i; j++)

                        {

                            if (datas[j].estimated_hours*60+datas[j].estimated_minutes < datas[j + 1].estimated_hours*60+datas[j + 1].estimated_minutes)

                            {

                                tmp = datas[j];

                                datas[j] = datas[j + 1];

                                datas[j + 1] = tmp;

                            }

                        }

                    }

                    break;

                default:

                    printf("No pasaran\n\n");

            }

            break;

        default:

            printf("No pasaran\n\n");

    }

    fseek(f, 0, SEEK_SET);

    for (i = 0; i < size; ++i)

    {

        fwrite(&datas[i], sizeof(flights), 1, f);

    }

    free(datas);

    fclose(f);

}

void output()

{

    FILE *f;

    flights data;

    f = fopen(filename, "rb");

    printf("Data:\n");

    while (!feof(f))

    {

        fread(&data, sizeof(flights), 1, f);

        if (!feof(f))

            printf("Airline - %s\t\t Airport - %s\t\t Aircraft - %s\t\t ID - %d\t Passengers - %d\t Schedule - %d:%d\t Estimated - %d:%d\n", data.airline, data.airport, data.aircraft, data.ID, data.passengers, data.schedule_hours, data.schedule_minutes, data.estimated_hours, data.estimated_minutes);

    }

    printf("\n");

    fclose(f);

}
int main()
{

    int i, check = 0;

    while (check == 0)
    {

        check = 0;

        printf("\n1 - Create database\n2 - Add\n3 - Delete\n4 - Find\n5 - Edit\n6 - Sort\n7 - Show \n0 - Visit canteen\n");

        printf("\nChoose function: ");

        if (!scanf("%d", &i))
        {
            printf("No pasaran!");
            exit(1);
        }

        printf("\n");

        switch (i)

        {

            case 1:

                input();

                break;

            case 2:

                add();

                break;

            case 3:

                del();

                break;

            case 4:

                find();

                break;

            case 5:

                edit();

                break;

            case 6:

                sort();

                break;

            case 7:

                output();

                break;

            case 0:

                check = 1;

                break;

            default:

                printf("No pasaran\n\n");

        }

    }

    return 0;

}
