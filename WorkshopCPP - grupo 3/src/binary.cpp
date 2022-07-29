#include <vector> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream> 		    // manejo de archivos
#include <iostream>	
using namespace std;

#define LEN 50
#define N_STUD 2

struct Tprovincia{
    unsigned int id;
    float average;
    char name[LEN+1];
};
vector <Tprovincia> lstProvincia;
vector <Tprovincia> lstProvinciaR;
vector <Tprovincia> lstProvinciaR1;

int main() {
  FILE *fp;
  //Tprovincia student[N_STUD];
  //int i;
  //char row[LEN+1];
  unsigned int n_stud;
    
    

    for (size_t i = 0; i < 5; i++)
    {
        Tprovincia pro;
        pro.id = i;
        pro.average = 25.5*i;
        strcpy(pro.name, "Loja");
        lstProvincia.push_back(pro);
    }
    



//   strcpy(student[0].name, "Steven");
//   student[0].id = 120000;
//   student[0].average = 25.5;

//   strcpy(student[1].name, "Julia");
//   student[1].id = 120001;
//   student[1].average = 28.5;

  fp = fopen("out.bin", "w"); /* Open the file for writing */
  if (fp == NULL){
    printf("Error: file out.bin cannot be opened\n");
    exit(1);
  }


  /* Write the file */
  /* NOTE 2: a binary file sometimes cannot be readable 
     correctly in a PC that it is not the one which generates it, 
     because, for instance, integer numbers can be coded with a
     different number of bytes.
  */
 
  /* Write in binary all the data contained in the structure   */
  printf("lstProvincia.size() = %i \n ", lstProvincia.size());
  //fwrite(student, sizeof(Tprovincia), N_STUD , fp); 
  fwrite(&lstProvincia, sizeof(Tprovincia), lstProvincia.size() , fp); 
////////////////
   ofstream wf("lstProvincia.dat", ios::out | ios::binary);
   if(!wf) {
      cout << "Cannot open file!" << endl;
      return 1;
   }
   for (auto &&p : lstProvincia)
        wf.write((char *) &p, sizeof(Tprovincia));
   wf.close();
   if(!wf.good()) {
      cout << "Error occurred at writing time!" << endl;
      return 1;
   }
  /* DIMENSION OF THE GENERATED FILE
     The dimension of the generated file will be:
     n_stud*sizeof(Tprovincia)
     in the case of the computer used to test the program:
     2*60 = 120 byte
   */
  
  fclose(fp); /* Close the file */


  
  fp = fopen("out.bin", "r"); /* Open the file for reading */
  if (fp == NULL){
    printf("Error: file out.bin cannot be opened\n");
    exit(1);
  }

  /* Read the file */
  n_stud = 0;
  //while( fread(&student[n_stud], sizeof(Tprovincia), 1, fp) == 1 ) {
    Tprovincia provin;
  while( fread(&lstProvinciaR[n_stud], sizeof(Tprovincia), 1, fp) == 1 ) {
    n_stud++;
    printf("%s",lstProvinciaR[n_stud].name);
   // lstProvinciaR.push_back(provin);
  }
printf("n_stud %i \n ",n_stud);
  fclose(fp); /* Close the file */

  
  
  /* Print the read records */
  //for (int i=0; i<n_stud; i++) {
    //printf("%s %d %f\n", student[i].name, student[i].id, student[i].average);
  //}

ifstream rf("lstProvincia.dat", ios::out | ios::binary);
   if(!rf) {
      cout << "Cannot open file!" << endl;
      return 1;
   }
    
    Tprovincia tp[1];
    while(rf.read((char *) &tp[0], sizeof(Tprovincia)))
        lstProvinciaR1.push_back(tp[0]);
    rf.close();
   
    for (auto &&p : lstProvinciaR1)
    {
        cout<<"id: "        << p.id<<endl;
        cout<<"average: " << p.average<<endl;
        cout<<"name: "   << p.name<<endl;
    }
  return 0;
}