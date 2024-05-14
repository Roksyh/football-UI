#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <random>

class player
{
public:
    int x = 0;
    int y = 0;
    bool have_ball = false;
    bool selected = false;

    player(int xt, int yt)
    {
        x = xt;
        y = yt;
    }
};

player* players1[10] = { new player(0,3), new player(1,1), new player(1,5),
        new player(3,1), new player(3,3), new player(3,5),new player(3,7) ,
        new player(5,1) , new player(5,4), new player(5,7) };
player* players2[10] = { new player(7,4),new player(6,2),new player(6,6),
    new player(4,0),new player(4,2),new player(4,4),new player(4,6),
    new player(2,0),new player(2,3), new player(2,6) };

void printBoard() {
    system("cls"); // очистка консоли
    printf("\n");
    printf("  1 2 3 4 5 6 7 8\n");// Граффика поля
    printf(" -----------------\n");
    for (int i = 0; i < 8; i++) {
        printf("%d", i + 1);
        for (int j = 0; j < 8; j++) {
            int t = 0;
            player* tp;
            for (int k = 0; k < 10; k++)
            {

                if (players1[k]->x == i && players1[k]->y == j)
                {
                    if (players1[k]->have_ball)
                    {
                        printf("{1");
                        t = 1;

                    }
                    else if (players1[k]->selected)
                    {
                        printf("[1");
                        t = 2;
                    }
                    else
                    {
                        printf("|1");
                        t = 3;
                    }
                    tp = players1[k];
                    break;
                }
                if (players2[k]->x == i && players2[k]->y == j)
                {
                    if (players2[k]->have_ball)
                    {
                        printf("{2");
                        t = 1;
                    }
                    else if (players2[k]->selected)
                    {
                        printf("[2");
                        t = 2;
                    }
                    else
                    {
                        printf("|2");
                        t = 3;
                    }
                    tp = players2[k];
                    break;
                }
            }

            if (t == 0)
            {
                printf("| ");

            }
            else if (t == 1)
            {
                printf("} ");
                j++;
            }
            else if (t == 2)
            {
                printf("] ");
                j++;
            }
            else
            {
                printf("| ");
                j++;
            }
            if (j == 7)
            {
                printf("| ");
            }
        }
        printf("\n");
        printf(" -----------------\n");
    }
}

void printRules()
{
    system("cls");
    printf("Добро пожаловать в игру футбол!\n");
    printf("1) Игра для двоих людей! Режима с ботом нет.\n");
    printf("2) Игрок у которого сейчас мяч помечается { }\n");
    printf("3) Управление осуществляется с помощью стрелочек numpad\n");
    printf("4) Игрок, которому вы хотите передать мяч помечается [ ]\n");
    printf("5) Удачной игры:)\n");
    printf("\nНажмите любую клавишу для возврата в меню...");
    _getch();
}

void printMenu()
{
    system("cls");
    printf("Football\n");
    printf("1. Play\n");
    printf("2. Rules\n");
    printf("3. Exit\n");
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));
    int currentPlayer = rand() % 2 + 1;
    int gameState = 0;
    int ts = 0;
    int menuOption = 0;

    while (true)
    {
        printMenu();

        switch (menuOption)
        {
        case 0:
            printf(" <-");
            break;
        case 1:
            printf("\n <-");
            break;
        case 2:
            printf("\n\n <-");
            break;
        }

        int key = _getch();

        switch (key)
        {
        case 72: // вверх
            menuOption--;
            if (menuOption < 0)
                menuOption = 2;
            break;
        case 80: // Вниз
            menuOption++;
            if (menuOption > 2)
                menuOption = 0;
            break;
        case 13: // enter (подтверждение)
            switch (menuOption)
            {
            case 0:
                gameState = 0;
                ts = 0;
                if (currentPlayer == 1)
                {
                    players1[4]->have_ball = 1;
                }
                else
                {
                    players2[4]->have_ball = 1;
                }
                while (gameState == 0) {

                    printBoard();

                    printf("Ходит игрок %d", currentPlayer);
                    int key = _getch();
                    printf("%d", key);

                    switch (key) {
                    case 52:  // Стрелочка влево(4 нум пад)
                        ts--;
                        if (ts < 0)
                        {
                            ts = 10;
                        }
                        if (ts > 10)
                        {
                            ts = 0;
                        }
                        if (ts < 10) {
                            if (currentPlayer == 1 && players1[ts]->have_ball == 1)
                            {
                                ts--;
                            }
                            else if (currentPlayer == 2 && players2[ts]->have_ball == 1)
                            {
                                ts--;
                            }
                        }
                        break;
                    case 54:  // Стрелочка вправо(6 нум пад)
                        ts++;
                        if (ts < 0)
                        {
                            ts = 10;
                        }
                        if (ts > 10)
                        {
                            ts = 0;
                        }
                        if (ts < 10) {
                            if (currentPlayer == 1 && players1[ts]->have_ball == 1)
                            {
                                ts++;
                            }
                            else if (currentPlayer == 2 && players2[ts]->have_ball == 1)
                            {
                                ts++;
                            }
                        }

                        break;
                    case '\r':// Подтверждение действия (enter)
                        int xt;
                        int yt;
                        float d = 0;
                        for (int i = 0; i < 10; i++)
                        {
                            if (ts < 10)
                            {
                                if (players1[i]->have_ball == 1)
                                {
                                    xt = players1[i]->x;
                                    yt = players1[i]->y;
                                    d = (float)(abs(yt - players1[ts]->y) + abs(xt - players1[ts]->x)) / 12;
                                }
                                else if (players2[i]->have_ball == 1)
                                {
                                    xt = players2[i]->x;
                                    yt = players2[i]->y;
                                    d = (float)(abs(yt - players2[ts]->y) + abs(xt - players2[ts]->x)) / 12;
                                }
                            }
                            else
                            {
                                if (players1[i]->have_ball == 1)
                                {
                                    xt = players1[i]->x;
                                    yt = players1[i]->y;
                                    d = (float)(abs(yt - players2[0]->y) + abs(xt - players2[0]->x)) / 12;
                                }
                                else if (players2[i]->have_ball == 1)
                                {
                                    xt = players2[i]->x;
                                    yt = players2[i]->y;
                                    d = (float)(abs(yt - players1[0]->y) + abs(xt - players1[0]->x)) / 12;
                                }
                            }

                        }
                        float rd = (float)(rand() % 100) / 100;
                        if (1 - d > rd)
                        {
                            for (int i = 0; i < 10; i++)
                            {
                                if (currentPlayer == 1)
                                {
                                    players1[i]->selected = 0;
                                    players1[i]->have_ball = 0;
                                }
                                else
                                {
                                    players2[i]->selected = 0;
                                    players2[i]->have_ball = 0;
                                }
                            }
                            if (ts < 10)
                            {
                                if (currentPlayer == 1)
                                {
                                    players1[ts]->have_ball = 1;
                                }
                                else
                                {
                                    players2[ts]->have_ball = 1;
                                }
                            }
                            else
                            {
                                if (currentPlayer == 1)
                                {
                                    players2[0]->have_ball = 1;
                                }
                                else
                                {
                                    players1[0]->have_ball = 1;
                                }
                            }

                        }
                        else
                        {
                            for (int i = 0; i < 10; i++)
                            {
                                if (currentPlayer == 1)
                                {
                                    players1[i]->selected = 0;
                                    players1[i]->have_ball = 0;
                                }
                                else
                                {
                                    players2[i]->selected = 0;
                                    players2[i]->have_ball = 0;
                                }
                            }
                            if (currentPlayer == 2)
                            {
                                players1[rand() % 10]->have_ball = 1;
                                currentPlayer = 1;
                            }
                            else
                            {
                                players2[rand() % 10]->have_ball = 1;
                                currentPlayer = 2;
                            }
                        }

                        break;
                    }

                    if (ts < 0)
                    {
                        ts = 10;
                    }
                    if (ts > 10)
                    {
                        ts = 0;
                    }
                    for (int i = 0; i < 10; i++)
                    {
                        players1[i]->selected = 0;

                        players2[i]->selected = 0;

                    }
                    if (ts < 10)
                    {
                        if (currentPlayer == 1)
                        {
                            players1[ts]->selected = 1;
                        }
                        else
                        {
                            players2[ts]->selected = 1;
                        }
                    }
                    else
                    {
                        if (currentPlayer == 1)
                        {
                            players2[0]->selected = 1;
                        }
                        else
                        {
                            players1[0]->selected = 1;
                        }
                    }

                    printBoard(); // вывод результатов игры
                    if (players1[0]->have_ball == 1 && currentPlayer == 2)
                    {
                        gameState = 1;
                    }
                    if (players2[0]->have_ball == 1 && currentPlayer == 1)
                    {
                        gameState = 1;
                    }

                }
                if (currentPlayer == 1)
                {
                    printf("Выйграл игрок 1");
                }
                else
                {
                    printf("Выйграл игрок 2");
                }
                _getch();
                break;
            case 1:
                printRules();
                break;
            case 2:
                return 0;
            }
            break;
        }
    }

    return 0;
}