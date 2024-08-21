#include <stdio.h>

int main(void){

    union Prot {

    unsigned short type;
    unsigned short prio;
    unsigned short ID;

}varprot;

    //varprot.type = 0xB7B2;
    varprot.type = 0xB7B3;
    unsigned short a = (varprot.type >> 10) & 0x3F;
    unsigned short b = (varprot.prio >> 7) & 0x07;   
    unsigned short c = (varprot.ID) & 0x7F; 

    if(a == 45 && b == 7 && c == 50){
        printf("Type: %d\n", a);
        printf("Priority: %d\n", b);
        printf("ID: %d\n", c);
    }else{
        printf("Wrong\n");
    }

    return 0;
}

