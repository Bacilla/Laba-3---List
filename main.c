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

// Структура элемента двусвязного списка
typedef struct SList List;
struct SList {
    List *next;
    List *prev;
    Film data;
};


// Прототипы функций
int get_int();
void add_to_end(List **ppEnd);
void add_first(List **ppStart, List **ppEnd);
void add_to_front(List **ppStart);
void add_after(List **ppAdded, List **ppEnd);
Film fill_film_data();
void show_commands();
void remove_end(List **ppStart, List **ppEnd);
void remove_front(List **ppStart, List **ppEnd);
void remove_found(List **ppFound);
void search_struct(List *pStart, List **ppFound);
void print_search_res(int res);
void print_search_fields();
void print_all_data(List *start_p);
List *find_prev(List *pFound, List *pStart);


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
                printf("remove_end in progress...\n");
                remove_end(&pStart, &pEnd);
                break;
            case 4:
                printf("remove_front in progress...\n");
                remove_front(&pStart, &pEnd);
                break;
            case 5:
                // Сразу проверяем не пустой ли список
                if(pStart == NULL) {
                    printf("Error, List is empty.\n");
                    break;
                }

                List *pFound = NULL; // указатель на найденную структуру
                printf("search_struct in progress...\n");
                search_struct(pStart, &pFound);
                if(pFound == NULL) { // если структуру не удалось найти - не выполнять код дальше
                    break;
                }
                // делаем следующие действия: вставляем элемент после найденной или удаляем найденную..

                // После того, как элемент списка найден, выбор следующего действия
                printf("\"1\": add after found\n");
                printf("\"2\": removing found\n");
                printf("command:");
                // Ввод и обработка команды
                int command2 = get_int();
                if(command2 < 1 || command2 > 2) {
                    printf("Incorrect command.\n");
                    break;
                }
                switch (command2) {
                    case 1:
                        add_after(&pFound, &pEnd); // добавляем новый элемент после найденного
                        break;
                    case 2:
                        // Проверяем, не является ли найденный указатель указателем на первый или последний элемент в списке                             
                        if(pFound == pStart) { // Если надо удалить первый элемент из списка
                            remove_front(&pStart, &pEnd);
                            break;
                        }
                        if(pFound == pEnd) { // Если надо удалить последний элемент из списка
                            remove_end(&pStart, &pEnd);
                            break;
                        }
                        // Если элемент не является ни первым, ни последним в списке
                        remove_found(&pFound); // удаление найденного элемента
                        break;
                }
                break;
            case 6:
                print_all_data(pStart);
                break;
            case 7:
                printf("goodbye ^W^\n");
                exit(0);
            default:
                printf("Incorrect command.\n");
                break;
        }
    }
    return 0;
}


// Функция удаляет последний элемент с конца списка
void remove_end(List **ppStart, List **ppEnd) {
    if((*ppEnd) == NULL) { // Если список пустой - выходим из функции
        printf("Error, List is empty.\n");
        return;
    }
  
    // Если указатели первого и последнего элемента списка указывают 
    // на один и тот же элемент, значит список имеет всего один элемент
    if((*ppEnd) == (*ppStart)) {
        free(*ppEnd); // В данном случае очищается по факту и *ppStart, т.к. они указывают на один объект
        *ppEnd = NULL;
        *ppStart = NULL;
        return;
    }

    // Кейс когда в списке есть 2+ элементов
    *ppEnd = (*ppEnd)->prev; // передвигаем указатель на новый последний элемент
    free((*ppEnd)->next); 
    (*ppEnd)->next = NULL;
}

// Функция удаляет первый элемент из начала списка
void remove_front(List **ppStart, List **ppEnd) {
    // Если список пустой - выходим из функции
    if((*ppStart) == NULL) { 
        printf("Error, List is empty.\n");
        return;
    }

    // Случай, когда в списке один элемент
    if((*ppEnd) == (*ppStart)) {
        free(*ppStart);
        *ppStart = NULL;
        *ppEnd = NULL;
        return;
    }

    // Кейс когда в списке есть 2+ элементов
    *ppStart = (*ppStart)->next;
    free((*ppStart)->prev); 
    (*ppStart)->prev = NULL;
}

// Функция находит предыдущий, перед найденным, элемент
List *find_prev(List *pFound, List *pStart) {
    List *result = NULL;
    List *temp = pStart;
    while(temp != NULL) {
        // Если следующий элемент это найденный элемент
        if(temp->next == pFound) {
            result = temp;
            break;
        }
        temp = temp->next;
    }
    
    return result;
}

// Функция удаляет найденный элемент
void remove_found(List **ppFound) {
    // Соединяем следующий элемент от найденного с предыдущим элементом от найденного
    List *temp = (*ppFound)->next;
    temp->prev = (*ppFound)->prev;

    // Соединяем предыдущий элемент от найденного со следующим элементом от найденного
    temp = (*ppFound)->prev;
    temp->next = (*ppFound)->next;

    free(*ppFound);
} 


void search_struct(List *pStart, List **ppFound) {
    // Вывод список возможных полей для поиска
    print_search_fields();
    
    printf("command:");
    // Ввод и обработка команды
    int command = get_int();
    if(command < 1 || command > 4) {
        printf("Incorrect command.\n");
        return;
    }

    
    int res = 0; // Найдено: 1, не найдено: 0
    List *temp; // Временный указатель на элемент списка
    switch (command) {
        // Поиск по полю film name
        case 1:
            printf("film name:");
            char name[NAME_LENGTH] = {0};
            if(fgets(name, NAME_LENGTH, stdin) == NULL) {
                printf("In \"search_struct\" function: Error in fgets()\n");
            }
            // Удаление символа '\n' из полученной строки
            for(int i = 0; i < NAME_LENGTH; i++) {
                if(name[i] == '\n') {
                    name[i] = '\0';
                    break;
                }
            }

            // Поиск строки в полях структурных переменных списка
            temp = pStart;
            while(temp != NULL) {
                if(strcmp(name, temp->data.name) == 0) {
                    *ppFound = temp; // сохраняем указатель на найденный элемент списка
                    res = 1;
                    break;
                }
                temp = temp->next;
            }
        break;
        // Поиск по полю session    
        case 2:
            printf("session:");
            int session_val = get_int();
            
            // Поиск введённого значения
            temp = pStart;
            while(temp != NULL) {
                if(temp->data.session == session_val) {
                    *ppFound = temp; // сохраняем указатель на найденный элемент списка
                    res = 1;
                    break;
                }
                temp = temp->next;
            }
        break;
        // Поиск по полю price      
        case 3:
            printf("price:");
            int price_val = get_int();
            
            // Поиск введённого значения
            temp = pStart;
            while(temp != NULL) {
                if(temp->data.price == price_val) {
                    *ppFound = temp; // сохраняем указатель на найденный элемент списка
                    res = 1;
                    break;
                }
                temp = temp->next;
            }
        break;
        // Поиск по полю num of viewers
        case 4:
            printf("viewers:");
            int viewers_val = get_int();
            
            // Поиск введённого значения
            temp = pStart;
            while(temp != NULL) {
                if(temp->data.num_of_viewers == viewers_val) {
                    *ppFound = temp; // сохраняем указатель на найденный элемент списка
                    res = 1;
                    break;
                }
                temp = temp->next;
            }
        break;
    }

    // вывод сообщения о результатах поиска
    print_search_res(res);
}

// Функция выводит на экран список команд для выбора поля, по которуму будет осуществлёт поиск
void print_search_fields() {
    printf("search field:\n");
    printf("\"1\": film name\n");
    printf("\"2\": session\n");
    printf("\"3\": price\n");
    printf("\"4\": viewers\n");
}

// Функция выводит сообщение о результате поиска
void print_search_res(int res) {
    if(res == 0) {
        printf("the search failed!\n");
    } else {
        printf("the search was successful!\n");
    }
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

// Функция добавляет элемент списка после указанного 
void add_after(List **ppAdded, List **ppEnd) { 
    // Проверка, не собираемся ли мы добавить новый элемент после последнего
    if((*ppAdded) == (*ppEnd)) {
        printf("to end...\n");
        add_to_end(&(*ppEnd));
        return; 
    }

    // Добавляем элемент после найденного
    Film new_film;
    // Заполнение структуры данными
    new_film = fill_film_data();

    // Создание нового элемента
    List *new_element = malloc(sizeof(List));
    // Заполнение структуры данными
    (*new_element).next = (*ppAdded)->next;
    (*new_element).prev = (*ppAdded); 
    (*new_element).data = new_film; // Заполняем элемент списка данными о фильме

    // Говорим, что теперь указатель на следующий элемент (у структуры, которую мы нашли)
    // будет указывать на только что созданный элемент
    (*ppAdded)->next = new_element; 
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
    (*new_element).prev = (*ppEnd); 
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
    (*new_element).prev = NULL; 
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
    (*new_element).prev = NULL;
    (*new_element).data = new_film;

    // говорим что теперь указател на предыдущий элемент (у бывшего первого элемента) указывает на новый элемент
    (*ppStart)->prev = new_element; 

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
    if(fgets(name, NAME_LENGTH, stdin) == NULL) {
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