#include <stdio.h>

struct Protty {
    unsigned int type : 6;
    unsigned int prio : 3;
    unsigned int ID : 7;
};

int main(void) {
    //unsigned short Prot = 0xB7B2;
    unsigned short Prot = 0xB7B3; //- This will make it say wronf

    struct Protty p;
    p.type = (Prot >> 10) & 0x3F;
    p.prio = (Prot >> 7) & 0x07;   
    p.ID = Prot & 0x7F;      

    if(p.type == 45 && p.prio == 7 && p.ID == 50){
        printf("Type: %d\n", p.type);
        printf("Priority: %d\n", p.prio);
        printf("ID: %d\n", p.ID);
    }else{
        printf("Wrong\n");
    }

    return 0;
}
