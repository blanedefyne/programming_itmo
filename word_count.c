#include <stdio.h>
#include <stdlib.h>


int strings_compare(char *first, char *second);
int counter(FILE *file, char *what_to_count);


int main(int argc, char* argv[]){

    FILE *file;
    file = fopen(argv[2], "r");

    if (argc < 3){                              /* проверка на корректный ввод */
        if (strings_compare(argv[1], "EXIT"))   /* посчитав все нужное, можно завершить программу, написав EXIT */
            exit(0);
        else
            printf("Invalid input");
    }
    else {
        if ((strings_compare(argv[1], "-l")) || (strings_compare(argv[1], "--lines")))
            printf("%d", counter(file, "lines"));
        else if ((strings_compare(argv[1], "-w")) || (strings_compare(argv[1], "--words")))
            printf("%d", counter(file, "words"));
        else if ((strings_compare(argv[1], "-c")) || (strings_compare(argv[1], "--bytes")))
            printf("%d", counter(file, "bytes"));
}
    
return 0;    

}


int strings_compare(char *first, char *second){                  /*функция, сравнивающая строки - возвращает 1, если строки равны, иначе 0 */
    for (int i = 0 ;first[i] != '\0' || second[i] != '\0'; ++i){
        if (first[i] != second[i]) {
            return 0;
        }
    }
    return 1;
}

int counter(FILE *file, char *what_to_count){                    /* функция counter, считающая сразу все (байты, строки, слова)*/
    int ch, words, bytes, lines;                                 /* но выводящая только то, что нужно (2-ой параметр) */
    words = lines = bytes = 0;
    int flag = -1;   /*чтобы не срабатывала 67 строка */


    while ((ch = fgetc(file)) != EOF){
        if (ch == '\n') {
            ++lines;
            ++bytes;
        }
        if (ch == '\n' || ch == '\t' || ch == ' ') {
            if (flag == 1) {
                ++words;
                flag = 0;
            }
        }
        else
            flag = 1;

        ++bytes;

    }

    if (flag == 1){
        ++words;
        ++lines;
    }

    if (strings_compare(what_to_count, "lines"))
        return lines;
    else if (strings_compare(what_to_count, "words"))
        return words;
    else
        return bytes;

}
