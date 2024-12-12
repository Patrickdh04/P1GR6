#include "../ProfileSetup/ProfileSetup.h"
#include "../MovieOutput_DAN/CoolName.h"
#include "../MovieSort_JPG/movieSort.h"
#include "../TimeInput_P/input.h"
//missing time limiting choices

int main(void){
    profilesetup();
    coolname();
    moviesort();
    input();

    return 0;
}
