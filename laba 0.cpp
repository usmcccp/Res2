#include <iostream>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

char too(char s, int K)
{
    s += K + 4;
    if (K > 2)
        return s - 1;
    return s;
}

void too(char* str, int K)
{
    for (int i = 0; i < strlen(str); i++)
        str[i] = too(str[i], K);
}

//Вывод матрицы
void output(int M, int N, float** A)
{
    std::cout << endl << "Матрица:" << endl << "\n";
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            cout << A[i][j] << "  ";
        cout << endl;
    }
}

//Заполнение матрицы
int fuller(int M, int N, float** A, int K, char* str)
{
    int NN = N / 2;
    int MM = M / 2;
    int O = 0;

    int min = -100;
    int max = 100;
    float r;

    time_t sec;

    sec = time(NULL);

    srand(time(0));

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = ((rand() % (max - min + 1)) + min) * 0.001; //Для точности до 3 знаков после запятой
            while (A[i][j] == 0)
                A[i][j] = ((rand() % (max - min + 1)) + min) * 0.001; //Исключаем ноль

            if (N % 2 == 0) //Перевод: при чётном значении количества столбцов мы ищем два "серединных" (побочный пояс) и заполняем их минус номером варианта 
                if (j == NN or j == NN - 1) // "NN" - половина количества столбцов в матрице (NN = N/2)
                    A[i][j] = -K;

            if (N % 2 != 0) //Перевод: при нечётном значении количества столбцов мы ищем один "серединный" (побочный пояс) и заполняем его минус номером варианта 
                if (j == NN)
                    A[i][j] = -K;

            if (M % 2 == 0) // По той же логике, что и со столбцами
                if (i == MM or i == MM - 1)
                    A[i][j] = K;

            if (M % 2 != 0)
                if (i == MM)
                    A[i][j] = K;

            if (N % 2 == 0 and M % 2 != 0) // Здесь мы перебираем 4 возможных варианта развития событий: 1) нечётное количество строк и чётное количество столбцов; 2) Чётное количество и того и того, и т д
                if (i == MM and (j == NN - 1 or j == NN))
                    A[i][j] = O;

            if (N % 2 == 0 and M % 2 == 0)
                if ((i == MM or i == MM - 1) and (j == NN - 1 or j == NN))
                    A[i][j] = O;

            if (N % 2 != 0 and M % 2 != 0)
                if (i == MM and j == NN)
                    A[i][j] = O;

            if (N % 2 != 0 and M % 2 == 0)
                if ((i == MM or i == MM - 1) and j == NN)
                    A[i][j] = O;
        }
    return *str; //Возврат нужной строки по условию задания
}

void packing(char* str) //"Упаковка" нужной строки в файл
{
    ofstream file("out.txt");
    if (file.is_open())
    {
        file << str[0] << str[1];
        file.close();
    }
    else cout << "Запись не удалась :(";
}

void packingE()
{
    ofstream file("out.txt");
    if (file.is_open())
    {
        file << "Ёё";
        file.close();
    }
    else cout << "Запись не удалась :(";
}

int main()
{
    setlocale(0, "");

    int M, N, K;

    char str[100] = "Аа";
    //Вариант
    K = 5;//

    if (K != 2)
    {
        too(str, K);
        packing(str);
    }
    else
        packingE();
    
    int min = 3;
    int max = 3 + K;

    N = (rand() % (max - min + 1)) + min; //Задаём размеры матрицы
    M = (rand() % (max - min + 1)) + min;

    cout << "Значения переменных успешно созданы" << endl << endl;

    float** A = new float* [M];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            A[i] = new float[N];

    cout << "Матрица успешно создана" << endl << endl;

    fuller(M, N, A, K, str);

    cout << endl << endl << "Матрица успешно заполнена" << endl << endl;

    output(M, N, A);

    cout << endl << "Строка успешно передана в файл _out.txt_" << endl << endl;

    return 0;

}