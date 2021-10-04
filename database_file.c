#include <stdio.h>
#include <stdlib.h>
struct employee{
  char name[20];
  int id, salary;
};
void get(struct employee *emp){
  printf("\nEnter employee name\n");
  scanf("%s",emp->name);
  printf("Enter employee id\n");
  scanf("%d",&emp->id);
  printf("Enter employee salary\n");
  scanf("%d",&emp->salary);
  }
void read(FILE *fp){    //reads contents from the file and prints them
  struct employee e;
  while((fread(&e,sizeof(e),1,fp))==1){
    printf("\nEmployee name: %10s\nEmployee ID: %d\t\tEmployee Salary: %d\n\n",e.name,e.id,e.salary);
  }
  fclose(fp);
}
void search(FILE *fp,int id){     //saves one chunk of data into object 'e' using fread, checks if the ID matches, prints if matched
  struct employee e;
  while((fread(&e,sizeof(e),1,fp))==1){
    if(e.id==id){
      printf("\nEmployee name: %10s\nEmployee ID: %d\t\tEmployee Salary: %d\n\n",e.name,e.id,e.salary);
      break;
    }
    else{
      continue;
    }
  }
  fclose(fp);
}
void mod(FILE *fp){   //creates a temporary file, copies everything except the interested chunk of data. asks for modifications, writes them 
  int choice;          //and makes the temporary file into the new permanant file
  struct employee emp;
  printf("Enter the ID of the entry you want to modify\n");
  scanf("%d",&choice);
  FILE *ftemp;
  while((fread(&emp,sizeof(emp),1,fp))==1){
    ftemp=fopen("temp.dat","ab");
    if(emp.id==choice){
      printf("Enter the new name of the employee\n");
      scanf("%s",emp.name);
      printf("Enter the new salary of the employee\n");
      scanf("%d",&emp.salary);
      fwrite(&emp,sizeof(emp),1,ftemp);
    }
    else{
      fwrite(&emp,sizeof(emp),1,ftemp);
    }
    fclose(ftemp);
  }
  fclose(fp);
  system("rm pract.dat");
  system("mv temp.dat pract.dat");
}
void del(FILE *fp, int id){  //similar to 'mod', here we just skip writing the interested chunk into the tmep file, ultimately deleting it.
  struct employee emp;
  FILE *ftemp;
  while((fread(&emp,sizeof(emp),1,fp))==1){
    ftemp=fopen("temp.dat","ab");
    if(emp.id==id){
      printf("Entry deleted...\n");
      continue;
    }
    else{
      fwrite(&emp,sizeof(emp),1,ftemp);
    }
    fclose(ftemp);
  }
  fclose(fp);
  system("rm pract.dat");
  system("mv temp.dat pract.dat");
}
int main(){
  int choice, choice0;
  FILE *fp;
  fp=fopen("pract.dat","a+b");
  if(fp==NULL){
    printf("Cannot open file");
    fclose(fp);
    exit(1);
  }
  struct employee emp;
while(1){
  printf("Please choose an option from below:\n");
  printf("***********************************************************\n");
  printf("1: Add a new entry\t\t2: Display all records\n3: Search existing entry\t4: Modify an existing record\n5: Delete a record\t\t6: Exit\n");
  printf("***********************************************************\n");
  scanf("%d",&choice);
  if(choice==6){
    exit(0);
  }
  switch(choice){
    case 1: get(&emp);
            fwrite(&emp,sizeof(emp),1,fp);
            fclose(fp);
            fp=fopen("pract.dat","a+b");
            printf("\n\n");
            break;
    case 2: read(fp);
            fp=fopen("pract.dat","a+b");
            break;
    case 3: printf("\n\nEnter the ID of the entry you want to search\n");
            scanf("%d",&choice0);
            search(fp,choice0);
            fp=fopen("pract.dat","a+b");
            break;
    case 4: mod(fp);
            fp=fopen("pract.dat","a+b");
            break;
    case 5: printf("\n\nEnter the ID of the entry you want to delete\n");
            scanf("%d",&choice0);
            del(fp,choice0);
            fp=fopen("pract.dat","a+b");
            break;
  }
}
  fclose(fp);
}
