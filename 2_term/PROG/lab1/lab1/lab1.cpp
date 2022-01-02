#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstring>
#include "D:\c++\2_term\lab1\lab1\md5.h"
#include <stdio.h>
#include <cstdio>
#include <ctime>

using namespace std;

struct User
{
    int id;
    char login[20] = { '\0' };
    char password[50] = {'\0'};
    int role; // 0-клиент, 1-букмекер
};

struct Horse
{
    int id;
    int speed;
    float win_coefficient;
};

struct Race
{
    int id;
    float price;
    int horse_id;
    float cash;
    int user_id;
    bool win_flag=false;
};

int enter();
void registration();
int for_user();
int for_bookmaker();
int change_list();
int changes();
void show_horses();
bool check(int& a, int& b);
void del_user();
void del_horse();
void show_users();

int main()
{
    int answer;
    int ind = 0;
    setlocale(LC_ALL, "Russian");
    do
    {
        system("cls");
        answer = enter();
        switch (answer)
        {
            case 0:
            {
                int i = 0;
                int who = 0;
                int WINNER_ID=0;
                if (check(who, WINNER_ID))
                {
                    if (who == 0)
                    {
                        do
                        {
                            answer = for_user();
                            switch (answer)
                            {
                            case 0:
                            {
                                show_horses();
                                break;
                            }
                            case 1:
                            {
                                Race new_race;
                                long int race_ind = 0;
                                long z = sizeof(Race);
                                z = -z;
                                FILE* fp = fopen("races.dat", "rb");
                                fseek(fp, z, SEEK_END);
                                if (fread(&race_ind, sizeof(int), 1, fp))
                                    new_race.id = race_ind + 1;
                                else
                                    new_race.id = 1;
                                fclose(fp);
                                cout << "Сколько вы хотите поставить?"<<endl;
                                cin >> new_race.price;
                                cout << "На кого вы хотите поставить?(ID)" << endl;
                                cin >> new_race.horse_id;
                                new_race.user_id = WINNER_ID;
                                FILE* win = fopen("horses.dat", "rb");
                                int i = 0;
                                while (true)
                                {
                                    Horse horse;
                                    fseek(win, (sizeof(Horse)) * i, SEEK_SET);
                                    fread(&horse, sizeof(Horse), 1, win);
                                    if (feof(fp)) break;
                                    int trk = (time(NULL)/5) % horse.speed;
                                    if ((horse.id == new_race.horse_id)&&( trk==0))
                                    {
                                        new_race.cash = new_race.price * horse.win_coefficient;
                                        new_race.win_flag = true;
                                    }
                                    else
                                    {
                                        new_race.cash = -new_race.cash;
                                        new_race.win_flag = false;
                                    }
                                    i++;
                                }
                                fclose(win);
                                FILE* wr = fopen("races.dat", "ab");
                                fwrite(&new_race, sizeof(Race), 1, wr);
                                fclose(wr);
                                if (new_race.win_flag) cout << "Поздравляем!!! Вы выиграли " << new_race.cash << " голд." << endl;
                                else cout << "К сожалению вы проиграли. Удачи в следующий раз." << endl;
                                system("pause");
                                break;
                                }
                            }
                        } while (answer != 2);
                        answer = 10;
                    }
                    else if(who==1)
                    {
                        do
                        {
                            answer = for_bookmaker();
                            switch (answer)
                            {
                                case 0:
                                {
                                    show_horses();
                                    break;
                                }
                                case 1:
                                {
                                    long int horse_ind = 0;
                                    FILE* fp = fopen("horses.dat", "rb");
                                    long z1 = sizeof(Horse);
                                    z1 = -z1;
                                    fseek(fp, z1, SEEK_END);
                                    fread(&horse_ind, sizeof(long int), 1, fp);
                                    int id_check;
                                    cout << "Введите ID для поиска:"<<endl;
                                    cin >> id_check;
                                    if (id_check <= horse_ind)
                                    {
                                        for (int i = 0; i < horse_ind; i++)
                                        {
                                            Horse horse;
                                            fseek(fp, (sizeof(Horse)) * i, SEEK_SET);
                                            fread(&horse, sizeof(Horse), 1, fp);
                                            if (id_check == horse.id)
                                            {
                                                cout << endl << "Скорость лошади: " << horse.speed << endl;
                                                cout << "Коэффициент выиграша: " << horse.win_coefficient << endl<<endl;
                                                i = horse_ind + 1;
                                            }
                                        }
                                        system("pause");
                                        answer = change_list();
                                        switch (answer)
                                        {
                                            case 0:
                                            {
                                                FILE* fp = fopen("horses.dat", "rb");
                                                FILE* temp = fopen("temp.dat", "wb");
                                                for (int i = 0; i < horse_ind; i++)
                                                {
                                                    Horse horse;
                                                    fseek(fp, (sizeof(Horse)) * i, SEEK_SET);
                                                    fread(&horse, sizeof(Horse), 1, fp);
                                                    if (id_check != horse.id)
                                                    {
                                                        fwrite(&horse, sizeof(Horse), 1, temp);
                                                    }
                                                    else if (id_check == horse.id)
                                                    {
                                                        cout << "Введите новое значение скорости: ";
                                                        cin >> horse.speed;
                                                        fwrite(&horse, sizeof(Horse), 1, temp);
                                                    }
                                                }
                                                fclose(temp);
                                                fclose(fp);
                                                FILE* kr = fopen("horses.dat", "wb");
                                                FILE* rk = fopen("temp.dat", "rb");
                                                for (int i = 0; i < horse_ind; i++)
                                                {
                                                    Horse horse;
                                                    fseek(rk, (sizeof(Horse)) * i, SEEK_SET);
                                                    fread(&horse, sizeof(Horse), 1, rk);
                                                    fwrite(&horse, sizeof(Horse), 1, kr);
                                                }
                                                fclose(rk);
                                                fclose(kr);
                                                remove("temp.dat");
                                                break;
                                            }
                                            case 1:
                                            {
                                                FILE* fp = fopen("horses.dat", "rb");
                                                FILE* temp = fopen("temp.dat", "wb");
                                                for (int i = 0; i < horse_ind; i++)
                                                {
                                                    Horse horse;
                                                    fseek(fp, (sizeof(Horse)) * i, SEEK_SET);
                                                    fread(&horse, sizeof(Horse), 1, fp);
                                                    if (id_check != horse.id)
                                                    {
                                                        fwrite(&horse, sizeof(Horse), 1, temp);
                                                    }
                                                    else if (id_check == horse.id)
                                                    {
                                                        cout << "Введите новое значение коэффициента выиграша: ";
                                                        cin >> horse.win_coefficient;
                                                        fwrite(&horse, sizeof(Horse), 1, temp);
                                                    }
                                                }
                                                fclose(temp);
                                                fclose(fp);
                                                FILE* kr = fopen("horses.dat", "wb");
                                                FILE* rk = fopen("temp.dat", "rb");
                                                for (int i = 0; i < horse_ind; i++)
                                                {
                                                    Horse horse;
                                                    fseek(rk, (sizeof(Horse)) * i, SEEK_SET);
                                                    fread(&horse, sizeof(Horse), 1, rk);
                                                    fwrite(&horse, sizeof(Horse), 1, kr);
                                                }
                                                fclose(rk);
                                                fclose(kr);
                                                remove("temp.dat");
                                                break;
                                            }
                                            case 2:
                                            {
                                                FILE* fp = fopen("horses.dat", "rb");
                                                FILE* temp = fopen("temp.dat", "wb");
                                                for (int i = 0; i < horse_ind; i++)
                                                {
                                                    Horse horse;
                                                    fseek(fp, (sizeof(Horse)) * i, SEEK_SET);
                                                    fread(&horse, sizeof(Horse), 1, fp);
                                                    if (id_check != horse.id)
                                                    {
                                                        fwrite(&horse, sizeof(Horse), 1, temp);
                                                    }
                                                    else if (id_check == horse.id)
                                                    {
                                                        cout << "Введите новое значение скорости: ";
                                                        cin >> horse.speed;
                                                        cout << "Введите новое значение коэффициента выиграша: ";
                                                        cin >> horse.win_coefficient;
                                                        fwrite(&horse, sizeof(Horse), 1, temp);
                                                    }
                                                }
                                                fclose(temp);
                                                fclose(fp);
                                                FILE* kr = fopen("horses.dat", "wb");
                                                FILE* rk = fopen("temp.dat", "rb");
                                                for (int i = 0; i < horse_ind; i++)
                                                {
                                                    Horse horse;
                                                    fseek(rk, (sizeof(Horse)) * i, SEEK_SET);
                                                    fread(&horse, sizeof(Horse), 1, rk);
                                                    fwrite(&horse, sizeof(Horse), 1, kr);
                                                }
                                                fclose(rk);
                                                fclose(kr);
                                                remove("temp.dat");
                                                break;
                                            }
                                        }
                                    }
                                    else cout << "Лошади с таким ID не существует." << endl << "Максимальный ID: " << horse_ind << endl;
                                    fclose(fp);
                                    system("pause");
                                    break;
                                }
                                case 2:
                                {
                                    Horse new_horse;
                                    long int horse_ind = 0;
                                    FILE* fp = fopen("horses.dat", "r+b");
                                    long z1 = sizeof(Horse);
                                    z1 = -z1;
                                    fseek(fp, z1, SEEK_END);
                                    fread(&horse_ind, sizeof(long int), 1, fp);
                                    if (fread(&ind, sizeof(int), 1, fp))
                                        new_horse.id = horse_ind + 1;
                                    else
                                        new_horse.id = 1;
                                    cout << "Введите скорость" << endl;
                                    cin >> new_horse.speed;
                                    cout << "Введите коэфициент при победе" << endl;
                                    cin >> new_horse.win_coefficient;
                                    fseek(fp, 0, SEEK_END);
                                    fwrite(&new_horse, sizeof(Horse), 1, fp);
                                    fclose(fp);
                                    system("pause");
                                    break;
                                }
                                case 3:
                                {
                                    del_horse();
                                    break;
                                }
                                case 4:
                                {
                                    show_users();
                                    break;
                                }
                                case 5:
                                {
                                    long int user_ind = 0;
                                    FILE* fp = fopen("users.dat", "rb");
                                    long z1 = sizeof(User);
                                    z1 = -z1;
                                    fseek(fp, z1, SEEK_END);
                                    fread(&user_ind, sizeof(long int), 1, fp);
                                    int id_check;
                                    cout << "Введите ID для поиска:" << endl;
                                    cin >> id_check;
                                    if (id_check > user_ind) cout << "Пользователя с таким ID не существует. Максимальный ID: "<<user_ind<<endl;
                                    else
                                    {
                                        int i = 0;
                                        while (true)
                                        {
                                            User user;
                                            fseek(fp, (sizeof(User))* i, SEEK_SET);
                                            fread(&user, sizeof(User), 1, fp);
                                            if (feof(fp)) break;
                                            if (id_check == user.id)
                                            {
                                                cout << endl << "Логин: " << user.login << endl;

                                                cout << "Пароль: " << user.password << endl;
                                                if (user.role == 0)
                                                    cout << "Роль: клиент" << endl << endl;
                                                else
                                                    cout << "Роль: букмекер" << endl << endl;
                                            }
                                            i++;
                                        }
                                        system("pause");
                                        int question = changes();
                                        switch (question)
                                        {
                                            case 0:
                                            {
                                                FILE* temp = fopen("temp.dat", "wb");
                                                int i = 0;
                                                while (true)
                                                {
                                                    User user;
                                                    fseek(fp, (sizeof(User)) * i, SEEK_SET);
                                                    fread(&user, sizeof(User), 1, fp);
                                                    if (feof(fp)) break;
                                                    if (id_check != user.id)
                                                    {
                                                        fwrite(&user, sizeof(User), 1, temp);
                                                    }
                                                    else if (id_check == user.id)
                                                    {
                                                        cout << "Введите новый логин: " << endl;
                                                        cin >> user.login;
                                                        fwrite(&user, sizeof(User), 1, temp);
                                                    }
                                                    i++;
                                                }
                                                fclose(temp);
                                                fclose(fp);
                                                remove("users.dat");
                                                rename("temp.dat", "users.dat");
                                                break;
                                            }
                                            case 1:
                                            {
                                                FILE* temp = fopen("temp.dat", "wb");
                                                int i = 0;
                                                while (true)
                                                {
                                                    User user;
                                                    fseek(fp, (sizeof(User)) * i, SEEK_SET);
                                                    fread(&user, sizeof(User), 1, fp);
                                                    if (feof(fp)) break;
                                                    if (id_check != user.id)
                                                    {
                                                        fwrite(&user, sizeof(User), 1, temp);
                                                    }
                                                    else if (id_check == user.id)
                                                    {
                                                        string pas;
                                                        cout << "Введите новый пароль: " << endl;
                                                        cin >> pas;
                                                        pas = md5(pas);
                                                        for (int i = 0; i < pas.size(); i++) user.password[i] = pas[i];
                                                        fwrite(&user, sizeof(User), 1, temp);
                                                    }
                                                    i++;
                                                }
                                                fclose(temp);
                                                fclose(fp);
                                                remove("users.dat");
                                                rename("temp.dat", "users.dat");
                                                break;
                                            }
                                            case 2:
                                            {
                                                FILE* temp = fopen("temp.dat", "wb");
                                                int i = 0;
                                                while (true)
                                                {
                                                    User user;
                                                    fseek(fp, (sizeof(User)) * i, SEEK_SET);
                                                    fread(&user, sizeof(User), 1, fp);
                                                    if (feof(fp)) break;
                                                    if (id_check != user.id)
                                                    {
                                                        fwrite(&user, sizeof(User), 1, temp);
                                                    }
                                                    else if (id_check == user.id)
                                                    {
                                                        cout << "Введите новую роль(0-клиент, 1-букмекер): " << endl;
                                                        cin >> user.role;
                                                        fwrite(&user, sizeof(User), 1, temp);
                                                    }
                                                    i++;
                                                }
                                                fclose(temp);
                                                fclose(fp);
                                                remove("users.dat");
                                                rename("temp.dat", "users.dat");
                                                break;
                                            }
                                            case 3:
                                            {
                                                FILE* temp = fopen("temp.dat", "wb");
                                                int i = 0;
                                                while (true)
                                                {
                                                    User user;
                                                    fseek(fp, (sizeof(User)) * i, SEEK_SET);
                                                    fread(&user, sizeof(User), 1, fp);
                                                    if (feof(fp)) break;
                                                    if (id_check != user.id)
                                                    {
                                                        fwrite(&user, sizeof(User), 1, temp);
                                                    }
                                                    else if (id_check == user.id)
                                                    {
                                                        cout << "Введите новый логин: " << endl;
                                                        cin >> user.login;
                                                        string pas;
                                                        cout << "Введите новый пароль: " << endl;
                                                        cin >> pas;
                                                        pas = md5(pas);
                                                        for (int i = 0; i < pas.size(); i++) user.password[i] = pas[i];
                                                        cout << "Введите новую роль(0-клиент, 1-букмекер): " << endl;
                                                        cin >> user.role;
                                                        fwrite(&user, sizeof(User), 1, temp);
                                                    }
                                                    i++;
                                                }
                                                fclose(temp);
                                                fclose(fp);
                                                remove("users.dat");
                                                rename("temp.dat", "users.dat");
                                                break;
                                            }
                                        }
                                    }
                                    fclose(fp);
                                    system("pause");
                                    break;
                                }
                                case 6:
                                {
                                    registration();
                                    break;
                                }
                                case 7:
                                {
                                    del_user();
                                    break;
                                }
                                case 8:
                                {
                                    long int race_ind = 0;
                                    FILE* fp = fopen("races.dat", "rb");
                                    long z1 = sizeof(Race);
                                    z1 = -z1;
                                    fseek(fp, z1, SEEK_END);
                                    fread(&race_ind, sizeof(long int), 1, fp);
                                    for (int i = 0; i < race_ind; i++)
                                    {
                                        Race race;
                                        fseek(fp, (sizeof(Race)) * i, SEEK_SET);
                                        fread(&race, sizeof(Race), 1, fp);
                                        cout << "ID гонки: " << race.id << endl;
                                        cout << "Размер ставки: " << race.price << " голд." << endl;
                                        cout << "ID лошади: " << race.horse_id << endl;
                                        cout << "ID пользователя: " << race.user_id << endl;
                                        if(race.win_flag)
                                            cout << "Клиент выиграл"<< endl;
                                        else cout << "Клиент проиграл" << endl;
                                        cout << "Итог денег: " << race.cash << endl << endl;
                                    }
                                    fclose(fp);
                                    system("pause");
                                    break;
                                }
                            }
                        } while (answer != 9);
                    }
                    system("pause");
                }
                else
                {
                    cout << "Такого пользователя не существует или данные введены неверно!" << endl;
                    cout << "Пожалуйста, зарегистрируйтесь или попробуйте зайти снова." << endl;
                    system("pause");
                    system("cls");
                    int c;
                    cout << "Введите 0, если вы хотите зарегистрироваться, или 1, если хотите попробовать войти снова." << endl;
                    cin >> c;
                    if(c==0) registration();
                }
                break;
            }
            case 1:
            {
                registration();
                break;
            }
        }
    } while (answer != 2);
	return 0;
}

int enter()
{
    cout << "-> Вход" << endl;
    int key = 0;
    int code;
    do {
        system("cls");
        key = (key + 3) % 3;
        if (key == 0) cout << "-> Вход" << endl;
        else  cout << "   Вход" << endl;
        if (key == 1) cout << "-> Регистрация" << endl;
        else  cout << "   Регистрация" << endl;
        if (key == 2) cout << "-> Выход" << endl;
        else  cout << "   Выход" << endl;
        code = _getch();
        if (code == 224)
        {
            code = _getch();
            if (code == 80) key++;
            if (code == 72) key--;
        }
    } while (code != 13);
    system("cls");
    return key;
}

void registration()
{
    system("cls");
    User new_user;
    string temp;
    long int ind = 0;
    FILE* fp = fopen("users.dat", "r+b");
    long z = sizeof(User);
    z = -z;
    fseek(fp, z, SEEK_END);
    if (fread(&ind, sizeof(int), 1, fp))
        new_user.id = ind + 1;
    else
        new_user.id = 1;
    cout << "Придумайте логин:" << endl;
    cin >> new_user.login;
    cout << "Придумайте пароль:" << endl;
    cin >> temp;
    temp = md5(temp);
    for (int i = 0; i < temp.size(); i++) new_user.password[i] = temp[i];
    cout << "Выберите роль(0-клиент, 1-букмекер):" << endl;
    cin >> new_user.role;
    fseek(fp, 0, SEEK_END);
    fwrite(&new_user, sizeof(User), 1, fp);
    fclose(fp);
}

int for_user()
{
    int key = 0;
    int code;
    do {
        system("cls");
        key = (key + 3) % 3;
        cout << "Добро пожаловать!" << endl;
        cout << "Вы вошли как клиент" << endl;
        cout << "________________________________________________" << endl<<endl;
        cout << "Выберите действие, которое хотите совершить:" << endl << endl;
        if (key == 0) cout << "-> Просмотреть всех коней" << endl;
        else  cout << "   Просмотреть всех коней" << endl;
        if (key == 1) cout << "-> Сделать ставку" << endl;
        else  cout << "   Сделать ставку" << endl;
        if (key == 2) cout << "-> Завершить сессию и выйти в главное меню" << endl;
        else  cout << "   Завершить сессию и выйти в главное меню" << endl;
        code = _getch();
        if (code == 224)
        {
            code = _getch();
            if (code == 80) key++;
            if (code == 72) key--;
        }
    } while (code != 13);
    system("cls");
    return key;
}

int for_bookmaker()
{
    int key = 0;
    int code;
    do {
        system("cls");
        key = (key + 10) % 10;
        cout << "Добро пожаловать!" << endl;
        cout << "Вы вошли как букмекер" << endl;
        cout << "________________________________________________" << endl << endl;
        cout << "Выберите действие, которое хотите совершить:" << endl << endl;
        if (key == 0) cout << "-> Просмотреть всех коней" << endl;
        else  cout << "   Просмотреть всех коней" << endl;
        if (key == 1) cout << "-> Найти коня по ID и изменить информацию о нём" << endl;
        else  cout << "   Найти коня по ID и изменить информацию о нём" << endl;
        if (key == 2) cout << "-> Добавить коня" << endl;
        else  cout << "   Добавить коня" << endl;
        if (key == 3) cout << "-> Удалить коня по ID" << endl;
        else  cout << "   Удалить коня по ID" << endl;
        if (key == 4) cout << "-> Просмотреть всех пользователей" << endl;
        else  cout << "   Просмотреть всех пользователей" << endl;
        if (key == 5) cout << "-> Пайти пользователя по ID и изменить информацию о нём" << endl;
        else  cout << "   Найти пользователя по ID и изменить информацию о нём" << endl;
        if (key == 6) cout << "-> Добавить пользователя" << endl;
        else  cout << "   Добавить пользователя" << endl;
        if (key == 7) cout << "-> Удалить пользователя по ID" << endl;
        else  cout << "   Удалить пользователя по ID" << endl;
        if (key == 8) cout << "-> Просмотреть проведённые гонки" << endl;
        else  cout << "   Просмотреть проведённые гонки" << endl;
        if (key == 9) cout << "-> Завершить сессию и выйти в главное меню" << endl;
        else  cout << "   Завершить сессию и выйти в главное меню" << endl;
        code = _getch();
        if (code == 224)
        {
            code = _getch();
            if (code == 80) key++;
            if (code == 72) key--;
        }
    } while (code != 13);
    system("cls");
    return key;
}

int change_list()
{
    int key = 0;
    int code;
    do {
        system("cls");
        key = (key + 3) % 3;
        if (key == 0) cout << "-> Изменить скорость" << endl;
        else  cout << "   Изменить скорость" << endl;
        if (key == 1) cout << "-> Изменить коэфициент выиграша" << endl;
        else  cout << "   Изменить коэфициент выиграша" << endl;
        if (key == 2) cout << "-> Изменить все данные" << endl;
        else  cout << "   Изменить все данные" << endl;
        code = _getch();
        if (code == 224)
        {
            code = _getch();
            if (code == 80) key++;
            if (code == 72) key--;
        }
    } while (code != 13);
    system("cls");
    return key;
}

int changes()
{
    int key = 0;
    int code;
    do {
        system("cls");
        key = (key + 4) % 4;
        if (key == 0) cout << "-> Изменить имя" << endl;
        else  cout << "   Изменить имя" << endl;
        if (key == 1) cout << "-> Изменить пароль" << endl;
        else  cout << "   Изменить пароль" << endl;
        if (key == 2) cout << "-> Изменить роль" << endl;
        else  cout << "   Изменить роль" << endl;
        if (key == 3) cout << "-> Изменить все данные" << endl;
        else  cout << "   Изменить все данные" << endl;
        code = _getch();
        if (code == 224)
        {
            code = _getch();
            if (code == 80) key++;
            if (code == 72) key--;
        }
    } while (code != 13);
    system("cls");
    return key;
}

void show_horses()
{
    FILE* fp = fopen("horses.dat", "rb");
    int i = 0;
    fseek(fp, 0, SEEK_SET);
    while (true)
    {
        Horse horse;
        fseek(fp, (sizeof(Horse)) * i, SEEK_SET);
        fread(&horse, sizeof(Horse), 1, fp);
        if (feof(fp)) break;
        cout << "ID лошади: " << horse.id << endl;
        cout << "Скорость лошади: " << horse.speed << endl;
        cout << "Коэффициент выиграша: " << horse.win_coefficient << endl << endl;
        i++;
    }
    fclose(fp);
    system("pause");
}

bool check(int& a, int& b)
{
    char login[20];
    string password;
    cout << "Введите логин:" << endl;
    cin >> login;
    cout << "Введите пароль" << endl;
    cin >> password;
    system("cls");
    password = md5(password);
    FILE* fp = fopen("users.dat", "rb");
    int i = 0;
    while (true)
    {
        User check_list;
        fseek(fp, (sizeof(User)) * i, SEEK_SET);
        fread(&check_list, sizeof(User), 1, fp);
        if (feof(fp)) break;
        string log_check = string(check_list.login);
        string pas_check = string(check_list.password);
        if ((password == pas_check) && (login == log_check))
        {
            a = check_list.role;
            b = check_list.id;
            return true;
        }
        i++;
    }
    fclose(fp);
    return false;
}

void del_user()
{
    FILE* fp = fopen("users.dat", "rb");    
    int id_del;
    cout << "Введите ID для удаления:" << endl;
    cin >> id_del;
    FILE* temp = fopen("temp.dat", "ab");
    int i = 0;
    while (true)
    {
        User user;
        fseek(fp, (sizeof(User)) * i, SEEK_SET);
        fread(&user, sizeof(User), 1, fp);
        if (feof(fp)) break;
        if (id_del != user.id) fwrite(&user, sizeof(User), 1, temp);
        i++;
    }
    fclose(temp);
    fclose(fp);
    remove("users.dat");
    rename("temp.dat", "users.dat");
}

void del_horse()
{
    FILE* fp = fopen("horses.dat", "rb");
    int id_del;
    cout << "Введите ID для удаления:" << endl;
    cin >> id_del;
    FILE* temp = fopen("temp.dat", "ab");
    int i = 0;
    while (true)
    {
        Horse horse;
        fseek(fp, (sizeof(Horse)) * i, SEEK_SET);
        fread(&horse, sizeof(Horse), 1, fp);
        if (feof(fp)) break;
        if (id_del != horse.id) fwrite(&horse, sizeof(Horse), 1, temp);
        i++;
    }
    fclose(temp);
    fclose(fp);
    remove("horses.dat");
    rename("temp.dat", "horses.dat");
}

void show_users()
{
    FILE* fp = fopen("users.dat", "rb");
    int i = 0;
    while (true)
    {
        User to_show;
        fseek(fp, (sizeof(User)) * i, SEEK_SET);
        fread(&to_show, sizeof(User), 1, fp);
        if (feof(fp)) break;
        cout << "ID пользователя: " << to_show.id << endl;
        cout << "Логин пользователя: " << to_show.login << endl;
        cout << "Пароль пользователя: " << to_show.password << endl;
        if (to_show.role == 0)
            cout << "Роль пользователя: клиент" << endl << endl;
        else
            cout << "Роль пользователя: букмекер" << endl << endl;
        i++;
    }
    fclose(fp);
    system("pause");
}