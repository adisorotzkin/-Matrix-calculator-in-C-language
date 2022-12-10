
#include "mat.h"

void read_mat(matrix, char*);
void print_mat(char *, matrix);
int getIndex(char *);
char * read_word(char *, char*);
char * get_comma(char *);
int emptyLine(char *);
int check_mat_name(char*);
int check_extraneous(char *);
void matrix_algebra(char *, char, matrix*[]);

int main(void){

    double num;
    char *s;
    int index1, index2;
    int stop = 0;
    char input[100] ; 				
    char cmd[30];
    char *ptr;    
    char opnd1[30];

	matrix MAT_A={0}, 
           MAT_B={0}, 
           MAT_C={0}, 
           MAT_D={0}, 
           MAT_E={0}, 
           MAT_F={0};	
	
    matrix *mArr[6];
    mArr[0] = &MAT_A;
	mArr[1] = &MAT_B;
	mArr[2] = &MAT_C;
	mArr[3] = &MAT_D;
	mArr[4] = &MAT_E;
	mArr[5] = &MAT_F;

    while (!stop) {
		
		printf ("\nPlease enter a command:\n");
		if (fgets(input, sizeof(input), stdin) == NULL){  /* reached EOF */
			printf ("\nERROR: Reached EOF with no stop command.\n");
            break;
		}
        printf ("\nYour input is: %s\n", input);

 		ptr = read_word(input, cmd);

        if (strcmp(cmd, "read_mat") == 0) {
			ptr = read_word(ptr, opnd1);  
        	if (check_mat_name(opnd1)){
          		ptr = get_comma(ptr); 
          		if (ptr == NULL)
            		printf ("ERROR:  Missing comma\n");				
          		else {
            		index1 = getIndex(opnd1);
            		read_mat(*mArr[index1], ptr); 
                }          		  
        	}  		

        } else if (strcmp(cmd, "print_mat") == 0) {
			       ptr = read_word(ptr, opnd1);
               	   if (check_mat_name(opnd1)) {    
			 	   	   index1 = getIndex(opnd1);                    
			 	       print_mat(opnd1, *mArr[index1]); 
                   }               

        } else if (strcmp(cmd, "mul_mat") == 0) {
			  matrix_algebra(ptr, 'm', mArr);

        } else if (strcmp(cmd, "add_mat") == 0) {
              matrix_algebra(ptr, 'a', mArr);             

	    } else if (strcmp(cmd, "sub_mat") == 0) {
			  matrix_algebra(ptr, 's', mArr);

		} else if (strcmp(cmd, "trans_mat") == 0) {
				 ptr = read_word(ptr, opnd1);
				 if (check_mat_name(opnd1)) {    
			 	  	index1 = getIndex(opnd1);
					ptr = get_comma(ptr);
   			       	if (ptr == NULL)
       			     	printf("ERROR:  Missing comma\n");						
					else {
                         ptr = read_word(ptr, opnd1);
				         if (check_mat_name(opnd1)) {    
			 	  	         index2 = getIndex(opnd1);
					         check_extraneous(ptr);				  
                             trans_mat(*mArr[index1],*mArr[index2]);
                         }
                    }
                  }

		} else if (strcmp(cmd, "mul_scalar") == 0) {
				 ptr = read_word(ptr, opnd1);
				 if (check_mat_name(opnd1)) {    
			 	  	index1 = getIndex(opnd1);
					ptr = get_comma(ptr);
   			       	if (ptr == NULL)
       			     	printf("ERROR:  Missing comma\n");	
					else {
                         ptr = read_word(ptr, opnd1);
					     num = strtod(opnd1, &s);
 					     if (!(s != opnd1))
       			        	printf("ERROR:  Argument is not a scalar\n");
					     else {
                              ptr = get_comma(ptr);
   			          	      if (ptr == NULL)
       			        	     printf("ERROR:  Missing comma\n");					 
						     else {
                                  ptr = read_word(ptr, opnd1);
					              if (check_mat_name(opnd1)) {    
			 	  		             index2 = getIndex(opnd1);
					                 check_extraneous(ptr);
                                     mul_scalar(*mArr[index1], num, *mArr[index2]);
                                  }
                             }
                         }
                     }
                 }

        } else if (strcmp(cmd, "stop") == 0) {
             if (!check_extraneous(ptr))                       
		         stop = 1;

        } else if (!emptyLine(input))
		     printf("Undefined command name.\n"); 
       
    }  /*while loop*/

    printf("\n*finished*\n");
    return 0;
}   /*main*/


char* read_word(char *ptr, char* word) {
   int i=0;
   while (*ptr == ' ' || *ptr == '\t')
      ptr++;
   /* we are pointing to the first character in the word */ 

   while (*ptr != ' ' && *ptr != '\t' && *ptr != ',' && *ptr != '\0' && *ptr != '\n') {
      word[i] = *ptr;
      i++;
      ptr++;
   }  

   word[i] = '\0';
   return ptr;   /*pointer to the next character in the kelet (after the word we read) */
}

char *get_next_char(char * ptr) 
{   
   /* returns a pointer to the next non-whitespace char or eol or eos */
   while (*ptr == ' ' || *ptr == '\t')
      ptr++;
   /* now we are pointing to a non-whitespace char, or eol or eos */ 
   return ptr; 
}

int getIndex(char* matrixName) {
    return matrixName[4] - 65;   /* map A to 0, B to 1... */
}

int emptyLine(char *str) {  /*check if rest of the line us empty*/
    while (*str == ' ' || *str == '\t')
      str++;
    return (*str == '\0' || *str == '\n');
}

char *get_comma(char * ptr) 
{   
    
   while (*ptr == ' ' || *ptr == '\t')
     ptr++;
     
   if (*ptr == ',')
     return ++ptr;
   else
     return NULL; 
}

void read_mat(matrix m, char *ptr)
{
	int i, j;
        double dnum;
        char *s;
        char strnum[30];
        char errmsg[100] = "";
        bool ccontinue = true;
        matrix temp = {0};

        ptr = read_word(ptr, strnum);

        if (strlen(strnum) > 0) { /*check that there is at least one number */

        	for (i = 0; i < SIZE && ccontinue; i++) {
            	for (j = 0; j < SIZE && ccontinue; j++) {  
            		dnum = strtod(strnum, &s);   
                	if (s != strnum) {  /*we read a number */     
                        temp[i][j] = dnum;
                    	ptr= get_next_char(ptr);
				    	if (*ptr == ',') {   /*we found a comma*/                       
               		   	    if (!emptyLine(++ptr))
                  	        	ptr = read_word(ptr, strnum);
                        	else {  /* remainder of line is blank */
                            	strcpy(errmsg, "ERROR: Extra comma at end of line.\n");
	                            ccontinue = false;
						 	}
               	  	 } else {  /*we did not find a comma */
                           if (!emptyLine(ptr)) { 
                   	           strcpy(errmsg, "ERROR: Missing comma.\n");              		 
    					       ccontinue = false; }                      
                           else /* no comma but we reached the end of the line */
                               ccontinue = false; 
                           }						 
               } else {
                     strcpy(errmsg, "ERROR: Argument is not a real number.\n");
                     ccontinue = false; }		
              }  /* for j */
           }   /* for i */
	  } else /* if strlen(strnum) */
        	strcpy(errmsg, "ERROR: Missing argument.\n");
     

        if (strcmp(errmsg, "") != 0)
            printf("%s\n", errmsg);
        else   /* Kelet takin */
            for (i=0; i<SIZE; i++)
               for (j=0; j<SIZE; j++)
                   m[i][j] = temp[i][j];

        return;
}    


void print_mat(char* name, matrix m)
{
		int i, j;
        printf("Matrix %s\n", name);
        for (i = 0; i < SIZE; i++) {
        	for (j = 0; j < SIZE; j++) {
            	printf("\t%7.2f", m[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return;
}


int check_mat_name(char* name){  /*check matrix name*/
    int valid = 1;
	if ((strcmp(name, "MAT_A") != 0)&&
		(strcmp(name, "MAT_B") != 0)&&
		(strcmp(name, "MAT_C") != 0)&&
		(strcmp(name, "MAT_D") != 0)&&
		(strcmp(name, "MAT_E") != 0)&&
		(strcmp(name, "MAT_F") != 0)) {
			valid = 0;
	        printf("ERROR: Undefined matrix name.\n");
    }
	return valid;
}


int check_extraneous(char *ptr) { /*check extraneous text*/
    int extraneous = 0;
    while (*ptr == ' ' || *ptr == '\t') 
      ptr++;
    if (*ptr != '\n' && *ptr != '\0') {
      printf("ERROR: Extraneous text after end of command.\n");
      extraneous = 1;
    }
    return extraneous;
}

void matrix_algebra(char *ptr, char command, matrix *mArr[])
{

    char opnd1[20];
    int index1, index2, index3;

    ptr = read_word(ptr, opnd1);
	if (check_mat_name(opnd1)) {    
	    index1 = getIndex(opnd1);
		ptr = get_comma(ptr);
   		if (ptr == NULL)
       	   printf("ERROR:  Missing comma\n");						
		else {
              ptr = read_word(ptr, opnd1);
			  if (check_mat_name(opnd1)) {    
			 	 index2 = getIndex(opnd1);
				 ptr = get_comma(ptr);
   			     if (ptr == NULL)
       			    printf("ERROR:  Missing comma\n");						
				 else {
                      ptr = read_word(ptr, opnd1);
				      if (check_mat_name(opnd1)) {    
			 	         index3 = getIndex(opnd1);
					     check_extraneous(ptr); 
						 if (command == 'a')
                 	        add_mat(*mArr[index1],*mArr[index2],*mArr[index3]);
                         else if (command == 's')
                            sub_mat(*mArr[index1],*mArr[index2],*mArr[index3]);
                         else if (command == 'm')
     						mul_mat(*mArr[index1],*mArr[index2],*mArr[index3]);
                      }
                 }
              }
         }
     }

     return;
}
