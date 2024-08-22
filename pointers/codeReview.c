#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void get_sky_team_name(char* name) // passed a pointer called name pointing to a block of memory holding a char
{
   char* ptr = (char*) malloc(10); //not allocated enough memory.
   
   //copy team name to pointer
   strcpy(ptr, "Home Comms SW Team");
   
   //return team name
   name = ptr; // both of these variables are memory addresses.

   free(ptr); //freeing this memory will mean that name will not be accesible from the main method
}
  
int main(void)
{
   char name[10];
   char* pTeamName = NULL;    
   
   strcpy(name, "Sky UK");   //name is not declared in this method so is not in scope.  
   
   while(1)
   {
       get_sky_team_name(pTeamName);        
       
       //print team name
       printf("%s: %s\n", skyName, pTeamName); 
       
       sleep(1);
   }
   
  return 0;
}