#include <stdio.h>
#include <stdlib.h>


int strings_compare(char *first, char *second);
int counter(FILE *file, char *what_to_count);


int main(int argc, char* argv[]){

    FILE *file;
    file = fopen(argv[2], "r");

    if (argc < 3){
        if (strings_compare(argv[1], "EXIT"))
            exit(0);
        else
            printf("Invalid input");
    }
    else
        if ((strings_compare(argv[1], "-l")) || (strings_compare(argv[1], "--lines")))
            printf("%d", counter(file, "lines"));
        else if ((strings_compare(argv[1], "-w")) || (strings_compare(argv[1], "--words")))
            printf("%d", counter(file, "words"));
        else if ((strings_compare(argv[1], "-c")) || (strings_compare(argv[1], "--bytes")))
            printf("%d", counter(file, "bytes"));

}


int strings_compare(char *first, char *second){
    for (int i = 0 ;first[i] != '\0' || second[i] != '\0'; ++i){
        if (first[i] != second[i]) {
            return 0;
        }
    }
    return 1;
}

int counter(FILE *file, char *what_to_count){
    int ch, words, bytes, lines;
    words = lines = bytes = 0;
    int flag = -1; /*чтобы не срабатывала 67 строка */


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