// Вариант 15
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAME_LENGTH 50

// Структура данных о фильме
typedef struct SFilm {
    char name[NAME_LENGTH];
    int session;
    int price;
    int num_of_viewers;
} Film;

// Структура элемента односвязного списка
typedef struct SList {
    struct SList *next;
    Film data;
} List;



void print_film_data() {

}

// Прототипы функций
int get_int();
void add_to_end(List *start_p, List *end_p);
Film fill_film_data();


int main() {
    // Указатель на первый элемент списка
    List *start_p = NULL;
    // Указатель на последний списка
    List *end_p = NULL;

    add_to_end(start_p, end_p);







    // printf("Input your string:");
    // char my_string[NAME_LENGTH];
    // if(fgets(my_string, NAME_LENGTH, stdin) == NULL) {
    //     printf("Error in fgets()\n");
    //     return 0;
    // }
    // printf("%s", my_string);


    return 0;
}


// Функция получает от пользователя число типа int 
int get_int() {
    // Массив символов для вводимого числа
	char strValue[10] = {0}; 
	if(fgets(strValue, 11, stdin) == NULL) {
        printf("In \"get_int\" function: Error in fgets()\n");
    };
    // Преобразуем полученные массив символов в число типа int 
	int value = atoi(strValue);
	return value;
}

void add_to_end(List *start_p, List *end_p) {
    // Создание новой структуры Film
    Film new_film;
    // Заполнение структуры данными
    new_film = fill_film_data();

    printf("%s\n", new_film.name);
    printf("%d\n", new_film.session);
    printf("%d\n", new_film.price);
    printf("%d\n", new_film.num_of_viewers);



}

// Функция создаёт новую структру Film и инициализирует её пользовательскими данными
Film fill_film_data() {
    // Создаём новый фильм
    Film f;

    // Заполнение поля name
    printf("name:");// scanf("%s", &new_film.name);
    char name[NAME_LENGTH] = {0};
    if(fgets(name, NAME_LENGTH + 1, stdin) == NULL) {
        printf("In \"fill_film_data\" function: Error in fgets()\n");
    }
    // Удаление символа '\n' из полученной строки
    for(int i = 0; i < NAME_LENGTH; i++) {
        if(name[i] == '\n') {
            name[i] = '\0';
            break;
        }
    }
    strcpy(f.name, name);

    // Заполнение поля session
    printf("session:");
    f.session = get_int();

    // Заполнение поля price
    printf("price:");
    f.price = get_int();

    // Заполнение поля num_viewers
    printf("num of viewers:");
    f.num_of_viewers = get_int();

    return f;
}