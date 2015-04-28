#include "driver.h"

char menu()
{
   char ans;
   static string title[13];
   title[0]= " Please make a selection: ";
   title[1]="  S : Select a list";
   title[2]="  D : Change print direction";
   title[3]="  R : Read from a file";
   title[4]="  W : Write to a file";
   title[5]="  P : Print the list";
   title[6]="  + : Add an item";
   title[7]="  - : Delete an item";
   title[8]="  F : Find an item";
   title[9]="  M : Merge List 2 into List 1";
   title[10]=" Q : Quit";
   title[11]="Your selection: ";

   for(int i=0; i<12; i++)
   {
           cout<<title[i]<<endl;
   }
   cin>>ans;
   cin.ignore(100, '\n');
   return ans;
}


void help()
{
     cout<<"/h or /H -- This message"<<endl
         <<"/sn or /Sn -- switch to list n"<<endl
         <<"n=filename -- load list n with data from file named filename"<<endl;
     exit(0);
}




