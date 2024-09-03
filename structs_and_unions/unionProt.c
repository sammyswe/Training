#include <stdio.h>
//idk why this is not working?
int main(void){

    struct person {
        unsigned int ID : 7;
        unsigned int prio : 3;
        unsigned int type : 6;
        
    };

    union Prot {
        unsigned short data;
        struct person p;
    }varprot;


    varprot.data = 0xB7B2;
    unsigned short a = varprot.p.type;
    unsigned short b = varprot.p.prio;   
    unsigned short c = varprot.p.ID;

    if(a == 45 && b == 7 && c == 50){
        printf("Type: %d\n", a);
        printf("Priority: %d\n", b);
        printf("ID: %d\n", c);
    }else{
        printf("Wrong\n");
    }

    return 0;
}

