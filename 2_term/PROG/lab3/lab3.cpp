#include "Header.h"

int main()
{
    SetConsoleOutputCP(1251);
    int answer;
    Matrix* A = new Matrix;
    Matrix* B = new Matrix;
    do
    {
        system("cls");
        answer = menu();
        switch (answer)
        {
            case 0:
            {              
                Get(A);
                Matrix a;
                for (int i = 0; i < A->col.size(); i++)
                {
                    a.col.push_back(A->col[i]);
                    a.row.push_back(A->row[i]);
                    a.val.push_back(A->val[i]);
                }
                FILE* fp = fopen("Matrix_A.dat", "wb");
                fseek(fp, 0, SEEK_END);
                fwrite(&a, sizeof(Matrix), 1, fp);
                fclose(fp);
                break;
            }
            case 1:
            {
                A->col.clear();
                A->row.clear();
                A->val.clear();
                Matrix a;
                FILE* fp = fopen("Matrix_A.dat", "rb");
                fseek(fp, 0, SEEK_SET);
                fread(&a, sizeof(Matrix), 1, fp);
                fclose(fp);
                for (int i = 0; i < a.col.size(); i++)
                {
                    A->col.push_back(a.col[i]);
                    A->row.push_back(a.row[i]);
                    A->val.push_back(a.val[i]);
                }
                break;
            }
            case 2:
            {
                Get(B);
                Matrix b;
                for (int i = 0; i < B->col.size(); i++)
                {
                    b.col.push_back(B->col[i]);
                    b.row.push_back(B->row[i]);
                    b.val.push_back(B->val[i]);
                }
                FILE* fp = fopen("Matrix_B.dat", "wb");
                fseek(fp, 0, SEEK_END);
                fwrite(&b, sizeof(Matrix), 1, fp);
                fclose(fp);
                break;
            }
            case 3:
            {
                B->col.clear();
                B->row.clear();
                B->val.clear();
                Matrix b;
                FILE* fp = fopen("Matrix_B.dat", "rb");
                fseek(fp, 0, SEEK_SET);
                fread(&b, sizeof(Matrix), 1, fp);
                fclose(fp);
                for (int i = 0; i < b.col.size(); i++)
                {
                    B->col.push_back(b.col[i]);
                    B->row.push_back(b.row[i]);
                    B->val.push_back(b.val[i]);
                }
                break;
            }
            case 4:
            {
                Show(A);
                system("pause");
                break;
            }
            case 5:
            {
                Show(B);
                system("pause");
                break;
            }
            case 6:
            {
                Sum(A, B);
                system("pause");
                break;
            }
            case 7:
            {
                Comp(A, B);
                break;
            }
            case 8:
            {
                Comp(B, A);
                break;
            }
            case 9:
            {
                GetRnd(A);
                Matrix a;
                for (int i = 0; i < A->col.size(); i++)
                {
                    a.col.push_back(A->col[i]);
                    a.row.push_back(A->row[i]);
                    a.val.push_back(A->val[i]);
                }
                FILE* fp = fopen("Matrix_A.dat", "wb");
                fseek(fp, 0, SEEK_END);
                fwrite(&a, sizeof(Matrix), 1, fp);
                fclose(fp);
                break;
            }
            case 10:
            {
                GetRnd(B);
                Matrix b;
                for (int i = 0; i < B->col.size(); i++)
                {
                    b.col.push_back(B->col[i]);
                    b.row.push_back(B->row[i]);
                    b.val.push_back(B->val[i]);
                }
                FILE* fp = fopen("Matrix_B.dat", "wb");
                fseek(fp, 0, SEEK_END);
                fwrite(&b, sizeof(Matrix), 1, fp);
                fclose(fp);
                break;
            }
        }
    } while (answer != 11);

    return 0;
}
