// Вариант 15
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAME_LENGTH 50

// Структура данных о фильме
typedef struct {
    char name[NAME_LENGTH];
    int session;
    int price;
    int num_of_viewers;
} Film;

// Структура элемента односвязного списка
typedef struct SList List;
struct SList {
    List *next;
    Film data;
};


// Прототипы функций
int get_int();
void add_to_end(List **ppEnd);
void add_first(List **ppStart, List **ppEnd);
void add_to_front(List **ppStart);
Film fill_film_data();
void print_all_data(List *start_p);
void show_commands();


int main() {
    // Указатель на первый элемент списка (он всегда будет указывать на начало списка)
    List *pStart = NULL;
    // Указатель на последний элемент списка (он всегда будет смещаться по мере добавления или удаления элементов)
    List *pEnd = NULL;
 
    show_commands();
    // Main loop
    while(1) { 
        printf("\ninput your command: ");
        int command = get_int();
        switch (command) {
            case 1:
                if(pEnd == NULL && pStart == NULL) {
                    printf("add_first in progress...\n");
                    add_first(&pStart, &pEnd);
                } else {
                    printf("add_to_end in progress...\n");
                    add_to_end(&pEnd);
                }
                break;
            case 2:
                if(pEnd == NULL && pStart == NULL) {
                    printf("add_first in progress...\n");
                    add_first(&pStart, &pEnd);
                } else {
                    printf("add_to_front in progress...\n");
                    add_to_front(&pStart);
                }
                break;
            case 3:
                printf("not ready...\n");
                break;
            case 4:
                printf("not ready...\n");
                break;
            case 5:
                printf("not ready...\n");
                break;
            case 6:
                print_all_data(pStart);
                break;
            case 7:
                printf("goodbye ^W^\n");
                exit(0);
        }

    }


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

// Функция добавляет новый элемент в конец списка
void add_to_end(List **ppEnd) {
    // Создание новой структуры Film
    Film new_film;
    // Заполнение структуры данными
    new_film = fill_film_data();

    // Создание нового элемента
    List *new_element = malloc(sizeof(List));
    // Заполнение структуры данными
    (*new_element).next = NULL; // Т.к. элемент добавляется в конец списка
    (*new_element).data = new_film; // Заполняем элемент списка данными о фильме
 
    // Cвязываем бывший последний элемент с новым последним элементом
    (*ppEnd)->next = new_element; // Теперь бывший последний элемент(который хранился по адресу в переменной pEnd) больше не является последним

    // Переприсваиваем указатель на новый последний элемент 
    *ppEnd = new_element;
}

// Функция для добавления первого элемента в список
void add_first(List **ppStart, List **ppEnd) {
    // Создание новой структуры Film
    Film new_film;
    // Заполнение структуры данными
    new_film = fill_film_data();

    // Создание нового элемента
    List *new_element = malloc(sizeof(List));
    // Заполнение структуры данными
    (*new_element).next = NULL; 
    (*new_element).data = new_film;

    // Т.к. добавляется первый элемент в списке - указатели на начало списка и конец это один объект
    *ppStart = new_element;
    *ppEnd = new_element;
}

// Функция добавляет новый элемент в начало списка
void add_to_front(List **ppStart) {
    // Создание новой структуры Film
    Film new_film;
    // Заполнение структуры данными
    new_film = fill_film_data();

    // Создание нового элемента
    List *new_element = malloc(sizeof(List));
    // Заполнение структуры данными
    (*new_element).next = *ppStart; // Указывает на бывший первый элемент в списке
    (*new_element).data = new_film;

    // Переприсваиваем указатель на новый первый элемент 
    *ppStart = new_element;
}

// Функция создаёт новую структру Film и инициализирует её пользовательскими данными
Film fill_film_data() {
    // Создаём новый фильм
    Film f;

    // Заполнение поля name
    printf("film name:");// scanf("%s", &new_film.name);
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

// Функция выводит информацию о каждом фильме
void print_all_data(List *pStart) {
    List *temp = pStart;
    int i = 1; // номер элемента в списке
    printf("--START OF THE LIST--\n");
    while(temp != NULL) {
        printf("\tElement %d:\n", i);
        printf("film name:\t%s\n", (*temp).data.name);
        printf("session:\t%d\n", (*temp).data.session);
        printf("price:\t\t%d\n", (*temp).data.price);
        printf("viewers:\t%d\n", (*temp).data.num_of_viewers);
        temp = (*temp).next;
        i++;
    }
    printf("---END OF THE LIST---\n");
}

// Функция показывает все возможные команды
void show_commands() {
    printf("Commands:\n");
    printf("\"1\": add to the end\n");
    printf("\"2\": add to the front\n");
    printf("\"3\": delete from the end\n");
    printf("\"4\": delete from the front\n");
    printf("\"5\": element search\n");
    printf("\"6\": print all elements\n");
    printf("\"7\": exit\n");
    printf("\n");
}