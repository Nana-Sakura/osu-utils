#include "utils/core/uic/CommandLine.h"

int menu_select(void){
    int select;
    printf("\n");
    printf("Type in number to select a function.\n");
    printf("1. Get Mapsets from Best Plays of anyone.\n");
    printf("2. Get Bpht of yourself.\n");
    printf("3. Get Score of a specified beatmap of yourself.\n");
    printf("4. Get Score of your recently passed beatmap.\n");
    printf("5. Get Score of your recently played beatmap.\n");
    printf("6. Get Bpht of anyone.\n");
    printf("7. Get Score of a specified beatmap of anyone.\n");
    printf("8. Get Score of other's recently passed beatmap.\n");
    printf("9. Get Score of other's recently played beatmap.\n");
    printf("10.Calculate pp of any beatmap.(Currently mania only)\n");
    printf("99.Set your ID and default game mode.\n");
    printf("0. Quit.\n");
    printf("Your selection: ");
    while((scanf("%d",&select)<1)||(select<0)||(select>99)){
        LOG("Selection error, please type in again.");
        fflush(stdin);
    }
    printf("\n");
    return select;
}
