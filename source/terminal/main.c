#include <stdio.h>
#include <string>
int main(){
    char command[] = {'\0'};
    do {
        printf(":");
        scanf("%s", command);
        printf("you wrote: %s", command);
        command[] = {"\0"};
    }
}