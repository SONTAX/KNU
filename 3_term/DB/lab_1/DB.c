#define _CRT_SECURE_NO_WARNINGS
#define ERR_OPEN_FILE 1

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>

struct Garbage {
    int are_any_empty = 0;
    char available_numbers[100] = { '\0' };
    int last_position = 0;
};

struct Forms {
    int ID_F = 0;
    char name[5] = { '\0' };
    char form_master[50];
    int fixed_classroom = 0;
    bool present_F = true;
};

struct Pupils {
    int ID_P = 0;
    char full_name[50] = { '\0' };
    int Class_ID = 0;
    bool present_P = true;
};

const int G = sizeof(struct Garbage);

void checker() {

    FILE* check_p;
    check_p = fopen("pupils.dat", "rb+");

    if (!check_p) {
        if (!(check_p = fopen("pupils.dat", "wb+"))) {
            exit(ERR_OPEN_FILE);
            printf("%s", "Unexpected behavior");
        }
        struct Garbage gp;
        fseek(check_p, 0, SEEK_SET);
        fwrite(&gp, sizeof(struct Garbage), 1, check_p);
    }
    fclose(check_p);

    FILE* check_f;
    check_f = fopen("forms.dat", "rb+");

    if (!check_f) {
        if (!(check_f = fopen("forms.dat", "wb+"))) {
            exit(ERR_OPEN_FILE);
            printf("%s", "Unexpected behavior");
        }
        struct Garbage gf;
        fseek(check_f, 0, SEEK_SET);
        fwrite(&gf, sizeof(struct Garbage), 1, check_f);
    }
    fclose(check_f);
}

void insert_m() {
    struct Forms form;
    int index = 0;
    FILE* fp = fopen("forms.dat", "r+b");
    long z1 = sizeof(struct Forms);
    z1 = -z1;
    fseek(fp, z1, SEEK_END);
    if (fread(&index, sizeof(int), 1, fp)) {
        index++;
        form.ID_F = index;
    }
    else {
        index = 1;
        form.ID_F = index;
    }
    printf("Input form master`s full name: ");
    scanf(" %[^\n]s", form.form_master);
    printf("Input form name(<=4 symbols; e.g. '11-A'): ");
    scanf("%4s", form.name);
    printf("Input fixed classroom number (<=3 numbers): ");
    scanf("%3d", &form.fixed_classroom);
    fseek(fp, 0, SEEK_END);
    fwrite(&form, sizeof(struct Forms), 1, fp);
    fclose(fp);
}

void index_insert_m() {
    struct Forms form;
    struct Garbage garbage;
    FILE* fm = fopen("forms.dat", "r+b");
    fseek(fm, 0, SEEK_SET);
    fread(&garbage, G, 1, fm);
    if (garbage.are_any_empty) {
        printf("Input ID (available: ");
        for (int i = 0; i < garbage.last_position; i++) {
            int ID = (int)garbage.available_numbers[i];
            if (ID)printf("%d ", ID);
        }
        printf("): ");
        scanf("%d", &form.ID_F);
        fseek(fm, G + (form.ID_F - 1) * sizeof(struct Forms), SEEK_SET);
        fread(&form, sizeof(struct Forms), 1, fm);
        if ((!feof(fm)) && (!form.present_F)) {
            printf("Input form master`s full name: ");
            scanf(" %[^\n]s", form.form_master);
            printf("Input form name(<=4 symbols; e.g. '11-A'): ");
            scanf("%4s", form.name);
            printf("Input fixed classroom number (<=3 numbers): ");
            scanf("%3d", &form.fixed_classroom);
            form.present_F = true;
            fseek(fm, G + (form.ID_F - 1) * sizeof(struct Forms), SEEK_SET);
            fwrite(&form, sizeof(struct Forms), 1, fm);
            for (int i = 0; i < garbage.last_position; i++) {
                int check = (int)garbage.available_numbers[i];
                if (check == form.ID_F) {
                    garbage.available_numbers[i] = '\0';
                    garbage.are_any_empty--;
                }
            }
            fseek(fm, 0, SEEK_SET);
            fwrite(&garbage, G, 1, fm);
        }
        else {
            printf("\n\nIncorrect ID! Please, try again\n\n");
        }
    }
    else {
        printf("\nThere are no empty positions. The insert will be made at the end\n\n");
        insert_m();
    }
    fclose(fm);
}

void insert_s() {
    struct Pupils pupil;
    int index = 0;
    FILE* fp = fopen("pupils.dat", "r+b");
    long z1 = sizeof(struct Pupils);
    z1 = -z1;
    fseek(fp, z1, SEEK_END);
    if (fread(&index, sizeof(int), 1, fp)) {
        index++;
        pupil.ID_P = index;
    }
    else {
        index = 1;
        pupil.ID_P = index;
    }
    printf("Input pupil`s full name: ");
    scanf(" %[^\n]s", pupil.full_name);
    FILE* f_id = fopen("forms.dat", "rb");
    printf("Choose form ID (available: ");
    int i = 0;
    bool was_any = false;
    struct Forms form_index;
    while (true) {
        fseek(f_id, ((sizeof(struct Forms)) * i) + G, SEEK_SET);
        fread(&form_index, sizeof(struct Forms), 1, f_id);
        if (feof(f_id)) break;
        if (form_index.present_F) {
            printf("%d", form_index.ID_F);
            printf(" ");
            was_any = true;
        }
        i++;
    }
    if (!was_any) {
        printf("any form record doesn`t exist)\n");
        printf("\n\nPlease enter at least one Form record and try again!\n\n");
        fclose(f_id);
        fclose(fp);
        return;
    }
    printf("): ");
    scanf("%3d", &pupil.Class_ID);
    fseek(f_id, (pupil.Class_ID - 1) * sizeof(struct Forms) + G, SEEK_SET);
    fread(&form_index, sizeof(struct Forms), 1, f_id);
    if ((!feof(f_id)) && (form_index.present_F) && (pupil.Class_ID > 0)) {
        fseek(fp, 0, SEEK_END);
        fwrite(&pupil, sizeof(struct Pupils), 1, fp);
    }
    else {
        printf("\n\nIncorrect Form ID!\nPlease, try again!\n\n");
    }
    fclose(f_id);
    fclose(fp);
}

void index_insert_s() {
    struct Garbage garbage;
    struct Pupils pupil;
    FILE* fs = fopen("pupils.dat", "r+b");
    fseek(fs, 0, SEEK_SET);
    fread(&garbage, G, 1, fs);
    if (garbage.are_any_empty) {
        printf("Input ID (available: ");
        for (int i = 0; i < garbage.last_position; i++) {
            int ID = (int)garbage.available_numbers[i];
            if (ID)printf("%d ", ID);
        }
        printf("): ");
        scanf("%d", &pupil.ID_P);
        fseek(fs, G + (pupil.ID_P - 1) * sizeof(struct Pupils), SEEK_SET);
        fread(&pupil, sizeof(struct Pupils), 1, fs);
        if ((!feof(fs)) && (!pupil.present_P)) {
            FILE* f_id = fopen("forms.dat", "rb");
            printf("Input pupil`s full name: ");
            scanf(" %[^\n]s", pupil.full_name);
            printf("Choose form ID (available: ");
            int i = 0;
            bool was_any = false;
            struct Forms form_index;
            while (true) {
                fseek(f_id, ((sizeof(struct Forms)) * i) + G, SEEK_SET);
                fread(&form_index, sizeof(struct Forms), 1, f_id);
                if (feof(f_id)) break;
                if (form_index.present_F) {
                    printf("%d", form_index.ID_F);
                    printf(" ");
                    was_any = true;
                }
                i++;
            }
            if (!was_any) {
                printf("any form record doesn`t exist)\n");
                printf("\n\nPlease enter at least one Form record and try again!\n\n");
                fclose(f_id);
                fclose(fs);
                return;
            }
            printf("): ");
            scanf("%3d", &pupil.Class_ID);
            fseek(f_id, (pupil.Class_ID - 1) * sizeof(struct Forms) + G, SEEK_SET);
            fread(&form_index, sizeof(struct Forms), 1, f_id);
            if ((!feof(f_id)) && (form_index.present_F) && (pupil.Class_ID > 0)) {
                pupil.present_P = true;
                fseek(fs, G + (pupil.ID_P - 1) * sizeof(struct Pupils), SEEK_SET);
                fwrite(&pupil, sizeof(struct Pupils), 1, fs);
                for (int i = 0; i < garbage.last_position; i++) {
                    int check = (int)garbage.available_numbers[i];
                    if (check == pupil.ID_P) {
                        garbage.available_numbers[i] = '\0';
                        garbage.are_any_empty--;
                    }
                }
                fseek(fs, 0, SEEK_SET);
                fwrite(&garbage, G, 1, fs);
            }
            else {
                printf("\n\nIncorrect Form ID!\nPlease, try again!\n\n");
            }
            fclose(f_id);
        }
        else {
            printf("\n\nIncorrect ID! Please, try again\n\n");
        }
    }
    else {
        printf("\nThere are no empty positions. The insert will be made at the end\n\n");
        insert_s();
    }
    fclose(fs);
}

void get_m(int index) {
    struct Forms form;
    FILE* fm = fopen("forms.dat", "rb");
    fseek(fm, (index - 1) * sizeof(struct Forms) + G, SEEK_SET);
    fread(&form, sizeof(struct Forms), 1, fm);
    if ((form.present_F) && (!feof(fm))) {
        printf("##################\tFORMS\t##################\n\n");
        printf("ID\t");
        printf("Form name\t");
        printf("Form master\t\t");
        printf("Fixed classroom\n");
        printf("%d", form.ID_F);
        printf("\t");
        printf("%s", form.name);
        printf("\t\t");
        printf("%s", form.form_master);
        printf("\t\t");
        printf("%d\n", form.fixed_classroom);
        printf("\n##################################################\n\n");
    }
    else {
        printf("\n\nRecord with such ID doesn`t exist!\n\n");
    }
    fclose(fm);
}

void get_s(int index) {
    struct Pupils pupil;
    FILE* fs = fopen("pupils.dat", "rb");
    fseek(fs, (index - 1) * sizeof(struct Pupils) + G, SEEK_SET);
    fread(&pupil, sizeof(struct Pupils), 1, fs);
    if ((pupil.present_P) && (!feof(fs))) {
        get_m(pupil.Class_ID);
        printf("##################\tPUPILS\t##################\n\n");
        printf("ID\t");
        printf("Full name\t\t\t");
        printf("Form ID\n");
        printf("%d", pupil.ID_P);
        printf("\t");
        printf("%s", pupil.full_name);
        printf("\t\t");
        printf("%d\n", pupil.Class_ID);
        printf("\n##################################################\n\n");
    }
    else {
        printf("\n\nRecord with such ID doesn`t exist!\n\n");
    }
    fclose(fs);
}

void del_s(int index) {
    struct Pupils pupil_index;
    struct Garbage garbage;
    FILE* fp = fopen("pupils.dat", "r+b");
    fseek(fp, ((index - 1) * sizeof(struct Pupils)) + G, SEEK_SET);
    fread(&pupil_index, sizeof(struct Pupils), 1, fp);
    if ((!feof(fp)) && (pupil_index.present_P)) {
        get_s(index);
        fseek(fp, 0, SEEK_SET);
        fread(&garbage, G, 1, fp);
        garbage.are_any_empty++;
        garbage.available_numbers[garbage.last_position] = (char)index;
        garbage.last_position++;
        fseek(fp, 0, SEEK_SET);
        fwrite(&garbage, sizeof(struct Garbage), 1, fp);
        fseek(fp, ((index - 1) * sizeof(struct Pupils)) + G, SEEK_SET);
        fread(&pupil_index, sizeof(struct Pupils), 1, fp);
        pupil_index.present_P = false;
        fseek(fp, ((index - 1) * sizeof(struct Pupils)) + G, SEEK_SET);
        fwrite(&pupil_index, sizeof(struct Pupils), 1, fp);
    }
    else {
        printf("Record with such ID doesn`t exist!");
    }
    fclose(fp);
}

void del_m(int index) {
    struct Forms form_index;
    struct Garbage garbage;
    FILE* fm = fopen("forms.dat", "r+b");
    fseek(fm, (index - 1) * sizeof(struct Forms) + G, SEEK_SET);
    fread(&form_index, sizeof(struct Forms), 1, fm);
    if ((!feof(fm)) && (form_index.present_F)) {
        get_m(index);
        fseek(fm, 0, SEEK_SET);
        fread(&garbage, G, 1, fm);
        garbage.are_any_empty++;
        garbage.available_numbers[garbage.last_position] = (char)index;
        garbage.last_position++;
        fseek(fm, 0, SEEK_SET);
        fwrite(&garbage, sizeof(struct Garbage), 1, fm);
        fseek(fm, (index - 1) * sizeof(struct Forms) + G, SEEK_SET);
        fread(&form_index, sizeof(struct Forms), 1, fm);
        form_index.present_F = false;
        fseek(fm, (index - 1) * sizeof(struct Forms) + G, SEEK_SET);
        fwrite(&form_index, sizeof(struct Forms), 1, fm);
        struct Pupils pupil;
        FILE* fs = fopen("pupils.dat", "rb");
        int i = 0;
        while (true) {
            fseek(fs, G + i * sizeof(struct Pupils), SEEK_SET);
            fread(&pupil, sizeof(struct Pupils), 1, fs);
            if (feof(fs)) {
                break;
            }
            if (pupil.Class_ID == index) {
                del_s(pupil.ID_P);
            }
            i++;
        }
        fclose(fs);
    }
    else {
        printf("Record with such ID doesn`t exist!");
    }
    fclose(fm);
}

void update_m() {
    int index;
    struct Forms form;
    printf("%s", "Input ID to update: ");
    scanf("%d", &index);
    FILE* fp = fopen("forms.dat", "r+b");
    fseek(fp, (index - 1) * sizeof(struct Forms) + G, SEEK_SET);
    fwrite(&form, sizeof(struct Forms), 1, fp);
    if ((!feof(fp) && (form.present_F))) {
        printf("\n\n");
        get_m(index);
        printf("\n\n\n");
        form.ID_F = index;
        printf("Input new form master`s full name: ");
        scanf(" %[^\n]s", form.form_master);
        printf("Input new form name(<=4 symbols; e.g. '11-A'): ");
        scanf("%4s", form.name);
        printf("Input new fixed classroom number (<=3 numbers): ");
        scanf("%3d", &form.fixed_classroom);
        fseek(fp, (index - 1) * sizeof(struct Forms) + G, SEEK_SET);
        fwrite(&form, sizeof(struct Forms), 1, fp);
    }
    else {
        printf("Record with such ID doesn`t exist!");
    }
    fclose(fp);
}

void update_s() {
    int index;
    struct Pupils pupil;
    FILE* fp = fopen("pupils.dat", "r+b");
    printf("%s", "Input ID to update: ");
    scanf("%d", &index);
    fseek(fp, (index - 1) * sizeof(struct Pupils) + G, SEEK_SET);
    fread(&pupil, sizeof(struct Pupils), 1, fp);
    if ((!feof(fp)) && (pupil.present_P)) {
        printf("\n\n");
        get_s(index);
        printf("\n\n\n");
        pupil.ID_P = index;
        printf("Input new pupil`s full name: ");
        scanf(" %[^\n]s", pupil.full_name);
        FILE* f_id = fopen("forms.dat", "rb");
        printf("Choose new form ID (available: ");
        int i = 0;
        struct Forms form_index;
        bool was_any = false;
        while (true) {
            fseek(f_id, ((sizeof(struct Forms)) * i) + G, SEEK_SET);
            fread(&form_index, sizeof(struct Forms), 1, f_id);
            if (feof(f_id)) break;
            if (form_index.present_F) {
                printf("%d", form_index.ID_F);
                printf(" ");
                was_any = true;
            }
            i++;
        }
        if (!was_any) {
            printf("any form record doesn`t exist):");
            fclose(f_id);
            return;
        }
        printf("): ");
        scanf("%d", &pupil.Class_ID);
        fclose(f_id);
        FILE* fp = fopen("pupils.dat", "r+b");
        fseek(fp, (index - 1) * sizeof(struct Pupils) + G, SEEK_SET);
        fwrite(&pupil, sizeof(struct Pupils), 1, fp);
        fclose(fp);
    }
    else {
        printf("Record with such ID doesn`t exist!");
    }
    fclose(fp);
}

int count_m() {
    int i = 0;
    int counter = 0;
    struct Forms form;
    FILE* fp = fopen("forms.dat", "rb");
    while (true) {
        fseek(fp, G + i * sizeof(struct Forms), SEEK_SET);
        fread(&form, sizeof(struct Forms), 1, fp);
        if (feof(fp)) break;
        if (form.present_F)counter++;
        i++;
    }
    fclose(fp);
    return counter;
}

int count_s() {
    int i = 0;
    int counter = 0;
    struct Pupils pupil;
    FILE* fp = fopen("pupils.dat", "rb");
    while (true) {
        fseek(fp, G + i * sizeof(struct Pupils), SEEK_SET);
        fread(&pupil, sizeof(struct Pupils), 1, fp);
        if (feof(fp)) break;
        if (pupil.present_P)counter++;
        i++;
    }
    fclose(fp);
    return counter;
}

void count_s_by_m() {
    int i = 0;
    int counter = 0;
    int g = 0;
    struct Forms form;
    struct Pupils pupil;
    FILE* mf = fopen("forms.dat", "rb");
    FILE* sf = fopen("pupils.dat", "rb");
    while (true) {
        g = 0;
        counter = 0;
        fseek(mf, G + i * sizeof(struct Forms), SEEK_SET);
        fread(&form, sizeof(struct Forms), 1, mf);
        if (feof(mf)) break;
        if (form.present_F) {
            while (true) {
                fseek(sf, G + g * sizeof(struct Pupils), SEEK_SET);
                fread(&pupil, sizeof(struct Pupils), 1, sf);
                if (feof(sf)) break;
                if ((pupil.present_P) && (pupil.Class_ID == form.ID_F)) counter++;
                g++;
            }
            printf("%s", "For master(ID) ");
            printf("%d", form.ID_F);
            printf("%s", " are ");
            printf("%d", counter);
            printf("%s", " slaves\n");
        }
        i++;
    }
    fclose(sf);
    fclose(mf);
}

void ut_m() {
    struct Forms form;
    struct Garbage garbage;
    FILE* fp = fopen("forms.dat", "rb");
    size_t i = 0;
    fseek(fp, 0, SEEK_SET);
    fread(&garbage, sizeof(struct Garbage), 1, fp);
    printf("%d", garbage.are_any_empty);
    printf("\n");
    printf("%s", garbage.available_numbers);
    printf("\n");
    printf("%d", garbage.last_position);
    printf("\n");
    printf("ID\t");
    printf("Form name\t");
    printf("Form master\t\t\t");
    printf("Fixed classroom\t\t");
    printf("Is present\n");
    while (true) {
        fseek(fp, i * sizeof(struct Forms) + G, SEEK_SET);
        fread(&form, sizeof(struct Forms), 1, fp);
        if (feof(fp)) {
            break;
        }
        printf("%d", form.ID_F);
        printf("\t");
        printf("%s", form.name);
        printf("\t\t");
        printf("%s", form.form_master);
        printf("\t\t\t");
        printf("%d", form.fixed_classroom);
        printf("\t\t\t");
        if (form.present_F) {
            printf("true");
        }
        else {
            printf("false");
        }
        printf("\n");
        i++;
    }
    fclose(fp);
}

void ut_s() {
    struct Pupils pupil;
    struct Garbage garbage;
    FILE* fp = fopen("pupils.dat", "rb");
    size_t i = 0;
    fseek(fp, 0, SEEK_SET);
    fread(&garbage, sizeof(struct Garbage), 1, fp);
    printf("%d", garbage.are_any_empty);
    printf("\n");
    printf("%s", garbage.available_numbers);
    printf("\n");
    printf("%d", garbage.last_position);
    printf("\n");
    printf("ID\t");
    printf("Pupil\t\t\t\t");
    printf("Form ID\t\t");
    printf("Is present\n");
    while (true) {
        fseek(fp, i * sizeof(struct Pupils) + G, SEEK_SET);
        fread(&pupil, sizeof(struct Pupils), 1, fp);
        if (feof(fp)) {
            break;
        }
        printf("%d", pupil.ID_P);
        printf("\t");
        printf("%s", pupil.full_name);
        printf("\t\t");
        printf("%d", pupil.Class_ID);
        printf("\t\t");
        if (pupil.present_P) {
            printf("true");
        }
        else {
            printf("false");
        }
        printf("\n");
        i++;
    }
    fclose(fp);
}

int menu() {
    int key = 0;
    int code;
    do {
        system("cls");
        printf("###Database###\n\n");
        key = (key + 16) % 16;
        if (key == 0) printf("-> get-m\n");
        else printf("   get-m\n");
        if (key == 1) printf("-> get-s\n");
        else printf("   get-s\n");
        if (key == 2) printf("-> delete-m\n");
        else printf("   delete-m\n");
        if (key == 3) printf("-> delete-s\n");
        else printf("   delete-s\n");
        if (key == 4) printf("-> update-m\n");
        else printf("   update-m\n");
        if (key == 5) printf("-> update-s\n");
        else printf("   update-s\n");
        if (key == 6) printf("-> insert-m\n");
        else printf("   insert-m\n");
        if (key == 7) printf("-> index-insert-m\n");
        else printf("   index-insert-m\n");
        if (key == 8) printf("-> insert-s\n");
        else printf("   insert-s\n");
        if (key == 9) printf("-> index-insert-s\n");
        else printf("   index-insert-s\n");
        if (key == 10) printf("-> count-m\n");
        else printf("   count-m\n");
        if (key == 11) printf("-> count-s\n");
        else printf("   count-s\n");
        if (key == 12) printf("-> count-s by m\n");
        else printf("   count-s by m\n");
        if (key == 13) printf("-> ut-m\n");
        else printf("   ut-m\n");
        if (key == 14) printf("-> ut-s\n");
        else printf("   ut-s\n");
        if (key == 15) printf("-> exit\n");
        else printf("   exit\n");
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

int main() {

    checker();
    int answer;
    int index;
    while (true) {
        answer = menu();
        switch (answer) {
        case 0: {
            system("cls");
            printf("%s", "Input ID: ");
            scanf("%d", &index);
            if (index > 0)get_m(index);
            else printf("%s", "\n\nIncorrect ID! Please, try again\n");
            break;
        }
        case 1: {
            system("cls");
            printf("%s", "Input ID: ");
            scanf("%d", &index);
            if (index > 0)get_s(index);
            else printf("%s", "\n\nIncorrect ID! Please, try again\n");
            break;
        }
        case 2: {
            system("cls");
            printf("%s", "Input ID: ");
            scanf("%d", &index);
            if (index > 0)del_m(index);
            else printf("%s", "\n\nIncorrect ID! Please, try again\n");
            break;
        }
        case 3: {
            system("cls");
            printf("%s", "Input ID: ");
            scanf("%d", &index);
            if (index > 0)del_s(index);
            else printf("%s", "\n\nIncorrect ID! Please, try again\n");
            break;
        }
        case 4: {
            system("cls");
            update_m();
            break;
        }
        case 5: {
            system("cls");
            update_s();
            break;
        }
        case 6: {
            system("cls");
            insert_m();
            break;
        }
        case 7: {
            system("cls");
            index_insert_m();
            break;
        }
        case 8: {
            system("cls");
            insert_s();
            break;
        }
        case 9: {
            system("cls");
            index_insert_s();
            break;
        }
        case 10: {
            system("cls");
            printf("There are %d master records\n", count_m());
            break;
        }
        case 11: {
            system("cls");
            printf("There are %d slave records\n", count_s());
            break;
        }
        case 12: {
            system("cls");
            count_s_by_m();
            break;
        }
        case 13: {
            system("cls");
            ut_m();
            break;
        }
        case 14: {
            system("cls");
            ut_s();
            break;
        }
        case 15: {
            exit(0);
        }
        }
        system("pause");
    }
    return 0;
}