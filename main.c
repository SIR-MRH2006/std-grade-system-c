#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------make {STUDENT}'s {STRUCTURE}-----
//students struct
struct grades{
    char book[30];
    float grade;
};
struct courceInTerm{
    int numOfTerm;
    struct grades cource[5];
    int countOfCorses;
};
struct studentform{
    char firstName[255];
    char lastName[255];
    char fullName[255];
    int birthDate[3];
    int studentNumber;
    int gender;
    int currentTerm;
    struct courceInTerm term[10];
};

//------make {TEACHER}'s {STRUCTURE}-----
typedef struct{
    char name[30];
    int addressOfClass;
} varOfCorse;
typedef struct{
    char firstName[50];
    char lastName[50];
    int countOfCours;
    varOfCorse cource[10];
} varOfTeacher;

//------make {COURSE}'s {STRUCTURE}-----
struct courceForm{
    char semesterName[30];
    int credits;
};
struct courcesofTerm{
    struct courceForm cource[10];
    int countOfCource;
};
typedef struct courcesofTerm storeSemester;


//-----make {ENUMERATE} of month-----
enum month_of_a_year{
    farvardin,
    ordibehesht,
    khordad,
    tir,
    mordad,
    shhrivar,
    mehr,
    aban,
    azar,
    dey,
    bahman,
    esfand,
};
typedef enum month_of_a_year monthes;

//====================================={ AUXILIRARY FUNCTION }===================================//
//add {STUDENT} to a {FILE}
void addStudentInfoToFile (FILE *ptrToStudenstFile,struct studentform student[],int *count){
    ptrToStudenstFile = fopen("studentFile.txt","w");
    if(ptrToStudenstFile == NULL){
        printf("file isnot defind \n");
    }else{                                   

        fprintf(ptrToStudenstFile,"%d \n",*count);
        for(int i = 0 ; i< *count; i++){
            fprintf(ptrToStudenstFile,"%s %s %s %d %d %d %d %d %d\n",
            student[i].firstName,
            student[i].lastName,
            student[i].fullName,
            student[i].birthDate[0],
            student[i].birthDate[1],
            student[i].birthDate[2],
            student[i].studentNumber,
            student[i].gender,
            student[i].currentTerm);
            for(int t = 0 ; t<student[i].currentTerm;t++){
                fprintf(ptrToStudenstFile,"%d",t+1);
                fprintf(ptrToStudenstFile,"\n%d\n",student[i].term[student[i].currentTerm].countOfCorses);
                for(int j = 0; j<student[i].term[student[i].currentTerm].countOfCorses;j++){
                    fprintf(ptrToStudenstFile,"%s %.1f\n",
                    student[i].term[student[i].currentTerm].cource[j].book,
                    student[i].term[student[i].currentTerm].cource[j].grade);   
                }
                printf("\t");
            }
            fprintf(ptrToStudenstFile,"\n");
        }
        fclose(ptrToStudenstFile);
    }
}

// COURSES TO FILE
void addCorceInfoToFile(storeSemester courceOfTerm[],int count,FILE *ptrToCourceFile){
    ptrToCourceFile = fopen("courcesFile.txt","w");
    if(ptrToCourceFile == NULL){
        printf("-----------file is not defind-------------- \n");
    }else{
        fprintf(ptrToCourceFile,"%d\n",count);
        for(int i = 0;i<count;i++){
            fprintf(ptrToCourceFile,"%d\n",courceOfTerm[i].countOfCource);
            for(int j = 0;j<courceOfTerm[i].countOfCource;j++){
                fprintf(ptrToCourceFile,"%s %d\n",courceOfTerm[i].cource[j].semesterName,courceOfTerm[i].cource[j].credits);
            }
        }
        fclose(ptrToCourceFile);
    }
}

// TEACHERS TO FILE

void addTeacherInfoToFile(varOfTeacher teacher[],int *count,FILE *ptrToTeacherFile){
    printf("aaaaaaaaaaa");
    ptrToTeacherFile = fopen("techerFile.txt","wb");
    if(ptrToTeacherFile != NULL){
        printf("bbbbbbbbbbbbbbbbb");
        fwrite(count,sizeof(int),1,ptrToTeacherFile);
        printf("dddddddddddddddd");
        fwrite(teacher,sizeof(varOfTeacher),*count,ptrToTeacherFile);
        printf("ccccccccccccccccc");
        fclose(ptrToTeacherFile);
        printf("ccccccccccccccccc2");
    }else{
        printf("---");
    }
}

//get {COURCES}
void getCources(struct studentform student[],int *count,storeSemester courceOfTerm[]){
    int userCource;
    int i = 0;
    do{
        printf("\n\nplease choose one of them =>\n____________________________________________________________________________________________________________\n\n");
        int j;
        for(j = 0;j<courceOfTerm[(student[*count].currentTerm)-1].countOfCource;j++){
            printf("%d)=> %s (%d credits)\n",j+1,courceOfTerm[(student[*count].currentTerm)-1].cource[j].semesterName,courceOfTerm[(student[*count].currentTerm)-1].cource[j].credits);
        }
        printf("%d)0 to exit\n",j+1);
        printf("____________________________________________________________________________________________________________\n");

        scanf("%d",&userCource);
        //====================
        if(userCource>0 && userCource<=courceOfTerm[(student[*count].currentTerm)-1].countOfCource){
            strcpy(student[*count].term[student[*count].currentTerm].cource[i].book,courceOfTerm[(student[*count].currentTerm)-1].cource[userCource-1].semesterName);
            i++;
        }
    }while(userCource != 0);
    student[*count].term[student[*count].currentTerm].countOfCorses = i;
    for(int j = 0;j<student[*count].term[student[*count].currentTerm].countOfCorses;j++){
        student[i].term[student[i].currentTerm].cource[j].grade = 0;
    }
}
//find STUDENT {INDEX}
int findStudentIndex(int userSecondChoice,struct studentform student[],int count){
    if(userSecondChoice == 1){  // edit with {FULLNAME}
        char firstName[50];
        printf("please enter user fullNAme => ");
        scanf("%s",firstName);
        int resultFlag = 0;
        for(int i = 0; i<count; i++){
            int result = strcmp(firstName,student[i].fullName);
            if(result == 0){
                resultFlag = 1;
                return i;
            }
        }
        if(resultFlag == 0){
            printf("-------------we cant find it--------------- \n");
            return -1;
        }
    }else if(userSecondChoice == 2){   /// edit with {STUDENT-NUMBER}
        int resultFlag = 0;
        int studentNumber;
        printf("please enter student-number=> ");
        scanf("%d",&studentNumber);
        for(int i = 0;i<count;i++){
            if(studentNumber == student[i].studentNumber){
                resultFlag = 1;
                return i;
            }
        }
        // resultFlag == 0 ? printf("----------------we cant find it--------------- \n") : printf("\n");
        if(resultFlag == 0){
            printf("----------------we cant find it--------------- \n");
            return -1;
        }
    }else{
        findStudentIndex(userSecondChoice,student,count);
    }
}
//find COURCE {INDEX}
int findCourceIndex(char *courceName,struct studentform student[],int count,int indexOfStudent){
    if(strcmp(courceName,"exit")==0){
        printf("\n--------------------changes succesfuly change------------------- \n");
        return -1;
    }
    int resultFlag = 0;
    for(int i = 0;i<student[indexOfStudent].term[student[indexOfStudent].currentTerm].countOfCorses;i++){
        int result = strcmp(student[indexOfStudent].term[student[indexOfStudent].currentTerm].cource[i].book,courceName);
        if(result == 0){
            resultFlag = 1;
            return i;
        }
    }
    if(resultFlag == 0){
        printf("-------------this book is not defined------------- \n");
        return -1;
    }
}


void showStudentdCourses(struct studentform student[],int indexOfStudent){
    int count = student[indexOfStudent].term[student[indexOfStudent].currentTerm].countOfCorses;
    printf("\nplease choose one of these courses\n___________________________________________________________________\n");
    for(int i = 0;i<count;i++){
        printf("-%d) %s\n",i+1,student[indexOfStudent].term[student[indexOfStudent].currentTerm].cource[i].book);
    }
    printf("___________________________________________________________________\n");
}

//====================================================={ KEY FUNCTIONS }================================================//
void addStudent(struct studentform student[],int *count,FILE *ptrToStudenstFile,storeSemester courceOfTerm[]){
    printf("\nFirstName : ex(mohammad) => "); 
    scanf("%30s",student[*count].firstName);
    printf("LastName : ex(hazrati) => ");
    scanf("%30s",student[*count].lastName);
    //creat a {FULLNAME}
    char copyFirstName[30];
    strcpy(copyFirstName,student[*count].firstName);
    strcpy(student[*count].fullName,strcat(copyFirstName,student[*count].lastName));
    int auxiliryCount;
    auxiliryCount = *count;
    do{
        printf("BirthYear : ex(1385) => ");
        scanf("%d",&student[auxiliryCount].birthDate[0]);
        if(student[auxiliryCount].birthDate[0]>=1300 && student[auxiliryCount].birthDate[0]<=1385){
            do{
                printf("Number of birth month: ex(1-12) => ");
                scanf("%d",&student[auxiliryCount].birthDate[1]);
                if(student[auxiliryCount].birthDate[1] >= 1 && student[auxiliryCount].birthDate[1] <= 12){
                    do{
                        printf("Number of birth day: ex(1-31) => ");
                        scanf("%d",&student[auxiliryCount].birthDate[2]);
                        if(student[auxiliryCount].birthDate[2]>=1 && student[auxiliryCount].birthDate[2]<=31){
                                    do{
                                        printf("gender : ex(male:1/female:0) => ");
                                        scanf("%d",&student[auxiliryCount].gender);
                                        if(student[auxiliryCount].gender==1 || student[auxiliryCount].gender==0){
                                            do{
                                                printf("current term : ex(1-10) => ");
                                                scanf("%d",&student[auxiliryCount].currentTerm);
                                                if(student[auxiliryCount].currentTerm >=1 && student[auxiliryCount].currentTerm<=10){
                                                    student[auxiliryCount].term[student[auxiliryCount].currentTerm].numOfTerm = student[auxiliryCount].currentTerm;
                                                    // get cources
                                                    getCources(student,count,courceOfTerm);
                                                    student[auxiliryCount].studentNumber = (*count)+10000;
                                                    (*count)++;
                                                    //add to a FILE;
                                                    addStudentInfoToFile(ptrToStudenstFile,student,count);                                     ;
                                                }else{
                                                    printf("please enter 1-10 number\n");
                                                }
                                            }while(!(student[auxiliryCount].currentTerm>=1 && student[auxiliryCount].currentTerm<=10));
                                        }else{
                                            printf("if you are female enter zero(0) or enter one(1)\n");
                                        }
                                    }while(!(student[auxiliryCount].gender==1 || student[auxiliryCount].gender==0));
                        }else{
                            printf("please enter 1-31 number\n");
                        }
                    }while(!(student[auxiliryCount].birthDate[2]>=1 && student[auxiliryCount].birthDate[2]<=31));
                }else{
                    printf("please enter 1-12 number\n");
                }
            }while(!(student[auxiliryCount].birthDate[1] >= 1 && student[auxiliryCount].birthDate[1] <= 12));
        }else{
            printf("please enter four-digit number\n");
        }
    }while(!(student[auxiliryCount].birthDate[0]>=1300 && student[auxiliryCount].birthDate[0]<=1385));
}


//----------------------{REMOVE}-----------------------//
void removeStudent(struct studentform student[],int *count,FILE *ptrToStudenstFile){
    printf("which of these info of student do you have? \n1)fullName(without space) \t2)student-number \n");
    int userSecondChoice;
    scanf("%d",&userSecondChoice);
    if(userSecondChoice == 1){        // edit with {FULLNAME}
        char fullName[50];
        printf("please enter user fullName => ");
        scanf("%s",fullName);
        int resultFlag = 0;
        for(int i = 0; i<*count; i++){
            int result = strcmp(fullName,student[i].fullName);
            if(result == 0){
                resultFlag = 1;
                for(int j = i; j<(*count); j++){
                    student[j] = student[j+1];
                }
                printf("---------------sucessfully remove that---------------- \n");
            }
        }
        if(resultFlag == 0){
            printf("-------------we cant find it--------------- \n");
        }
    }else if(userSecondChoice == 2){   // edit with {STUDENT-NUMBER}
        int resultFlag = 0;
        int studentNumber;
        printf("please enter student-number=> ");
        scanf("%d",&studentNumber);
        for(int i = 0;i<*count;i++){
            if(studentNumber == student[i].studentNumber){
                resultFlag = 1;
                for(int j = i; j<(*count); j++){
                    student[j] = student[j+1];
                }
                printf("--------------sucessfully remove that---------------- \n");
            }
        }
        resultFlag == 0 ? printf("-------------we cant find it--------------- \n") : printf("\n");
    }else{
        removeStudent(student,count,ptrToStudenstFile);
    }

    (*count)--;


    addStudentInfoToFile(ptrToStudenstFile,student,count);
}

//------------------{EDIT1}--------------------//
void editStudentInfo(struct studentform student[],int *count,FILE *ptrToStudenstFile){
    printf("which of these info of student do you have? \n1)fullName(without space) \t2)student-number \n");
    int userSecondChoice;
    scanf("%d",&userSecondChoice);
    int result = findStudentIndex(userSecondChoice,student,*count);
    int indexOfStudent;
    if(result != -1){
        indexOfStudent = result;
        printf("what info do you want to edit? \n1)firstName \n2)lastName \n3)birthDate \n4)studentNumber \n5)gender \n6)currentTerm \n");
        int userthirdChoice;
        scanf("%d",&userthirdChoice);
        switch(userthirdChoice){
            case 1: printf("first name is : ");
                    char newFirstName[30];
                    scanf("%s",newFirstName);
                    strcpy(student[indexOfStudent].firstName,newFirstName);
                    printf("----------------------------succesfully change------------------------- \n");break;
            case 2: printf("last name is : ");
                    char newLastName[30];
                    scanf("%s",newLastName);
                    strcpy(student[indexOfStudent].lastName,newLastName);
                    printf("----------------------------succesfully change------------------------- \n");break;
            case 3: {        //its a very imporatant key => in switch-case structure we must add varibale in {code-block};
                    int newYearOfBirth;
                    int newmonthOfBirth;
                    int newdayOfBirth;
                    do{
                        printf("year Of birth  is : ");
                        scanf("%d",&newYearOfBirth);
                        if(newYearOfBirth>1300 && newYearOfBirth<1385){
                            student[indexOfStudent].birthDate[0] = newYearOfBirth;
                        }else{
                            printf("---------------------please enter valid year-----------------------\n");
                        }
                    }while(!(newYearOfBirth>1300 && newYearOfBirth<1385));
                    do{
                        printf("month Of birth  is : ");
                        scanf("%d",&newmonthOfBirth);
                        if(newmonthOfBirth>0 && newmonthOfBirth<=12){
                            student[indexOfStudent].birthDate[1] = newmonthOfBirth;
                        }else{
                            printf("------------------------please enter valid month-num--------------------\n");
                        }
                    }while(!(newmonthOfBirth>0 && newmonthOfBirth<=12));
                    do{
                        printf("day Of birth  is : ");
                        scanf("%d",&newdayOfBirth);
                        if(newdayOfBirth>0 && newdayOfBirth<=31){
                            student[indexOfStudent].birthDate[2] = newdayOfBirth;
                        }else{
                            printf("-----------------please enter valid day-num--------------\n");
                        }
                    }while(!(newdayOfBirth>0 && newdayOfBirth<=31));

                    printf("----------------------------succesfully change------------------------- \n");break;}
            case 4:{
                    int newStudentNumber;
                    do{
                        printf("student-number is : ");
                        scanf("%d",&newStudentNumber);
                        if(newStudentNumber>=10000){
                            student[indexOfStudent].studentNumber = newStudentNumber;
                        }else{
                            printf("---------------the student-number cant be less than 10000-----------------\n");
                        }
                    }while(!(newStudentNumber>=10000));
                    printf("----------------------------succesfully change------------------------- \n");break;}
            case 5:{
                    int newGender;
                    do{
                        printf("gender is :(male:1)/(female:0) ");
                        scanf("%d",&newGender);
                        if(newGender==1 || newGender==0){
                            student[indexOfStudent].gender = newGender;
                        }else{
                            printf("--------------please enter only 0 or 1-------------\n");
                        }
                    }while(!(newGender==1 || newGender==0));

                    printf("----------------------------succesfully change------------------------- \n");break;}
            case 6:{
                    int newcurrentTerm;
                    do{
                        printf("currentTerm name is : ");
                        scanf("%d",&newcurrentTerm);
                        if(newcurrentTerm>=1 && newcurrentTerm<=10){
                            student[indexOfStudent].currentTerm = newcurrentTerm;
                        }else{
                            printf("------------please enter a number between 1 til 10-------------\n");
                        }
                    }while(!(newcurrentTerm>=1 && newcurrentTerm<=10));
                    printf("----------------------------succesfully change------------------------- \n");break;}
            default : editStudentInfo(student,count,ptrToStudenstFile);break;
        }
        char fullName[50];
        strcpy(fullName,student[indexOfStudent].firstName);
        strcat(fullName,student[indexOfStudent].lastName);
        strcpy(student[indexOfStudent].fullName,fullName);
        //add to a file;
        addStudentInfoToFile(ptrToStudenstFile,student,count);
        }
}

//--------------------{EDIT2}--------------------//
void editStudentGrade(struct studentform student[],int *count,FILE *ptrToStudenstFile,storeSemester courceOfTerm[],int countOfCorcesOfTerm,void (*showCources)(storeSemester[],int)){
    printf("which of these info of student do you have? \n1)fullName(without space) \t2)student-number \n");
    int userSecondChoice;
    scanf("%d",&userSecondChoice);
    int indexOfStudent = findStudentIndex(userSecondChoice,student,*count);
    //
    if(indexOfStudent != -1){
        char courceName[30];
        do{
            printf("\n");
            //we can show all of courses in student term(i just use callback func);
            // showCources(courceOfTerm,student[indexOfStudent].currentTerm);
            showStudentdCourses(student,indexOfStudent);
            printf("please enter cource name (write exit to exit) ");
            scanf("%s",courceName);
            int indexOfCource = findCourceIndex(courceName,student,*count,indexOfStudent);
            if(indexOfCource != -1){
                printf("please enter the grade ");
                float newgrade;
                scanf("%f",&newgrade); 
                if(newgrade >= 0 && newgrade<= 20){
                    student[indexOfStudent].term[student[indexOfStudent].currentTerm].cource[indexOfCource].grade = newgrade;
                }else{
                    printf("-------------your grade is not valid-------------- \n");
                }
                addStudentInfoToFile(ptrToStudenstFile,student,count);
            }
            while(getchar() != '\n'){
                //empty
            }
        }while(strcmp(courceName,"exit") != 0);
    }else{
        editStudentGrade(student,count,ptrToStudenstFile,courceOfTerm,countOfCorcesOfTerm,showCources);
    }
}

//------------------{SHOW-STUDENTS}--------------------//
void showAllStudentInfo(struct studentform student[],int count){
    if(count != 0){
        printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________\n\n\n");
        printf("--------------------------------------------------------------------------------------------------------------------\n");      
        int i;
        for(i = 0;i<count;i++){
            printf("name : %s %s \t",student[i].firstName,student[i].lastName);
            if((student[i].birthDate[1])/10 == 0){
                printf("birhDate : %d/0%d/%d\t",student[i].birthDate[0],student[i].birthDate[1],student[i].birthDate[2]);
            }else if((student[i].birthDate[2])/10 == 0){
                printf("birhDate : %d/%d/0%d\t",student[i].birthDate[0],student[i].birthDate[1],student[i].birthDate[2]);
            }else{
                printf("birhDate : %d/%d/%d\t",student[i].birthDate[0],student[i].birthDate[1],student[i].birthDate[2]);
            }
            printf("student-Number : %d \t",student[i].studentNumber);
            if(student[i].gender == 1){
                printf("gender : male \t");
            }else{
                printf("gender : female \t");
            }
            printf("term%d\n",student[i].currentTerm);
            // 
            for(int t = 1;t<=student[i].currentTerm;t++){
                printf("term %d => ",t);
                for(int j = 0;j<student[i].term[t].countOfCorses;j++){
                    printf("%s %.1f / ",student[i].term[t].cource[j].book,student[i].term[t].cource[j].grade);
                }
                printf("\n");
            }
            printf("--------------------------------------------------------------------------------------------------------------------\n");    
        }
        printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________\n");
    }else{
        printf("------------------ {we dont have any students} ------------------\n");
    }
}

//------------------{SHOW-STUDENT}--------------------//
void showStudentInfo(struct studentform student[],int count){
    printf("which of these info of student do you have? \n1)fullName(without space) \t2)student-number \n");
    int userSecondChoice;
    scanf("%d",&userSecondChoice);
    int indexOfStudent = findStudentIndex(userSecondChoice,student,count);
    if(indexOfStudent != -1){
        // show student personal info
        printf("______________________________________________________________________________________________\nSTUDENT PERSONAL INFO=>\n");
        printf("name : %s %s \t",student[indexOfStudent].firstName,student[indexOfStudent].lastName);
        if((student[indexOfStudent].birthDate[1])/10 == 0){
            printf("birhDate : %d/0%d/%d\t",student[indexOfStudent].birthDate[0],student[indexOfStudent].birthDate[1],student[indexOfStudent].birthDate[2]);
        }else if((student[indexOfStudent].birthDate[2])/10 == 0){
            printf("birhDate : %d/%d/0%d\t",student[indexOfStudent].birthDate[0],student[indexOfStudent].birthDate[1],student[indexOfStudent].birthDate[2]);
        }else{
            printf("birhDate : %d/%d/%d\t",student[indexOfStudent].birthDate[0],student[indexOfStudent].birthDate[1],student[indexOfStudent].birthDate[2]);
        }
        printf("student-Number : %d \t",student[indexOfStudent].studentNumber);
        if(student[indexOfStudent].gender == 1){
            printf("gender : male \t");
        }else{
            printf("gender : female \t");
        }
        printf("term%d\n",student[indexOfStudent].currentTerm);
        // show student Courses
        printf("-------------------------------------------------\nSTUDENT COURSES INFO=>\n");
        for(int j = 1;j<(student[indexOfStudent].currentTerm)+1;j++){
            printf("term%d=> ",j);
            for(int i = 0;i<student[indexOfStudent].term[student[indexOfStudent].currentTerm].countOfCorses;i++){
            printf("%s %.1f\t",
            student[indexOfStudent].term[j].cource[i].book,
            student[indexOfStudent].term[j].cource[i].grade);
            }
            if(j==(student[indexOfStudent].currentTerm)){
            printf("{{current-term}}");
            }
            printf("\n");
        }
        printf("______________________________________________________________________________________________\n");
    }else{
        showStudentInfo(student,count);
    }
}

//------------------{ADD-{COURCES}}--------------------//
void addCource(storeSemester courceOfTerm[],int *count,FILE *ptrToCourceFile){
    for(int i = 9;i>(*count-1);i--){
        courceOfTerm[i].countOfCource = 0;
    }

    printf("please enter term of cource that you want add to it (1-10) : ");
    int numOfTerm;
    scanf("%d",&numOfTerm);
    printf("please enter your new cource : ");
    char nameOfCource[30];
    scanf("%s",nameOfCource);
    printf("please enter your credits Of new Corce : ");
    int CreditOfNewCource;
    scanf("%d",&CreditOfNewCource);
    strcpy(courceOfTerm[numOfTerm-1].cource[courceOfTerm[numOfTerm-1].countOfCource].semesterName,nameOfCource);
    courceOfTerm[numOfTerm-1].cource[courceOfTerm[numOfTerm-1].countOfCource].credits = CreditOfNewCource;
    // add count of term and countofCorce
    if(courceOfTerm[numOfTerm-1].countOfCource == 0){
        (*count)++;
    }
    (courceOfTerm[numOfTerm-1].countOfCource)++;

    //add to courceFile =>
    addCorceInfoToFile(courceOfTerm,*count,ptrToCourceFile);
}

//------------------{SHOW-{COURCES}}--------------------//
void showCources(storeSemester courceOfTerm[],int count){
    printf("____________________________________________________________________________________________________________\n");
    for(int i = 0;i<count;i++){
        printf("\nterm%d => \t",i+1);
        for(int j = 0;j<courceOfTerm[i].countOfCource;j++){
            printf("%s %d  |  ",courceOfTerm[i].cource[j].semesterName,courceOfTerm[i].cource[j].credits);
        }
    }
    printf("\n____________________________________________________________________________________________________________\n");
}

//------------------{ADD-COURCE --> STUDENT}--------------------//
void addCourcesToStudent(struct studentform student[],int *count,FILE *ptrToStudenstFile,storeSemester courceOfTerm[],int countOfCorcesOfTerm){
        printf("which of these info of student do you have? \n1)fullName(without space) \t2)student-number \n");
    int userSecondChoice;
    scanf("%d",&userSecondChoice);
    int studentIndex = findStudentIndex(userSecondChoice,student,*count);
    if(studentIndex != -1){
        // show cources to student=>
        printf("\n\nplease choose one of them =>\n____________________________________________________________________________________________________________\n\n");
        int j;
        for(j = 0;j<courceOfTerm[(student[studentIndex].currentTerm)-1].countOfCource;j++){
            printf("%d)=> %s (%d credits)\n",j+1,courceOfTerm[(student[studentIndex].currentTerm)-1].cource[j].semesterName,courceOfTerm[(student[studentIndex].currentTerm)-1].cource[j].credits);
        }
        printf("____________________________________________________________________________________________________________\n");
        // 
        int userChoiceCource;
        scanf("%d",&userChoiceCource);
        if(userChoiceCource >=1 && userChoiceCource<=courceOfTerm[(student[studentIndex].currentTerm)-1].countOfCource){
            int isexist = 0;
            for(int i = 0;i<(student[studentIndex].term[student[studentIndex].currentTerm].countOfCorses);i++){
                int result = strcmp(student[studentIndex].term[student[studentIndex].currentTerm].cource[i].book,courceOfTerm[student[studentIndex].term[student[studentIndex].currentTerm].numOfTerm].cource[userChoiceCource-1].semesterName);
                if(result == 0){
                    isexist = 1;
                }
            }
            if(isexist == 0){
                strcpy(student[studentIndex].term[student[studentIndex].currentTerm].cource[(student[studentIndex].term[student[studentIndex].currentTerm].countOfCorses)].book,courceOfTerm[(student[studentIndex].currentTerm)-1].cource[userChoiceCource-1].semesterName);
                student[studentIndex].term[student[studentIndex].currentTerm].cource[student[studentIndex].term[student[studentIndex].currentTerm].countOfCorses].grade = 0;
                (student[studentIndex].term[student[studentIndex].currentTerm].countOfCorses)++;
                printf("you added %s to %s %s\n",
                courceOfTerm[student[studentIndex].term[student[studentIndex].currentTerm].numOfTerm].cource[userChoiceCource-1].semesterName,
                student[studentIndex].firstName,
                student[studentIndex].lastName);
                printf("-----------succesfully add cource to %s %s------------------ \n",student[studentIndex].firstName,student[studentIndex].lastName);
                addStudentInfoToFile(ptrToStudenstFile,student,count);
            }else{
                printf("----------------this cource is exist in student Cources!-------------------- \n");
            }
        }else{
            printf("----------------------this cource is not exist in this term----------------\n");
            addCourcesToStudent(student,count,ptrToStudenstFile,courceOfTerm,countOfCorcesOfTerm);
        }
    }else{
        printf("-----------------this student doesnt exist in this university--------------------- \n");
        addCourcesToStudent(student,count,ptrToStudenstFile,courceOfTerm,countOfCorcesOfTerm);
    }
}

//------------------{RM-COURCE --> STUDENT}--------------------//
void removeCourcesToStudent(struct studentform student[],int *count,FILE *ptrToStudenstFile){
    printf("which of these info of student do you have? \n1)fullName(without space) \t2)student-number \n");
    int userSecondChoice;
    scanf("%d",&userSecondChoice);
    int studentIndex = findStudentIndex(userSecondChoice,student,*count);
    if(studentIndex != -1){
        printf("student name: %s %s\n",student[studentIndex].firstName,student[studentIndex].lastName);
        int courceIndex;
        // do{
            printf("please enter cource name : ");
            char courceName[30];
            scanf("%s",courceName);
            courceIndex = findCourceIndex(courceName,student,*count,studentIndex);
            printf("student name: %s %s\tstudnt cource name: %s\n",
            student[studentIndex].firstName,
            student[studentIndex].lastName,
            student[studentIndex].term[student[studentIndex].currentTerm].cource[courceIndex]);
            if(courceIndex != -1){
                for(int i = courceIndex;i<(student[studentIndex].term[student[studentIndex].currentTerm].countOfCorses)-1;i++){
                    student[studentIndex].term[student[studentIndex].currentTerm].cource[i] = student[studentIndex].term[student[studentIndex].currentTerm].cource[i+1];
                }
                (student[studentIndex].term[student[studentIndex].currentTerm].countOfCorses)--;
                printf("-------------this cource succesfully delet of that student---------------\n");
                addStudentInfoToFile(ptrToStudenstFile,student,count);
                
            }else{
                printf("this cource is not exist in this student Cources \n");
            }
        // }while(courceIndex != -1);
    }else{
        printf("this student doesnt exist in this university \n");
        removeCourcesToStudent(student,count,ptrToStudenstFile);
    }
}

void addTeacher(varOfTeacher teacher[],int *count,FILE *ptrToTeacherFile){
    getchar();
    puts("teacher firstname ");
    char firstName[50];
    fgets(firstName,sizeof(firstName),stdin);
    strcpy(teacher[*count].firstName,firstName);
    fputs("teacher lastName ",stdout);
    char lastName[50];
    fgets(lastName,sizeof(lastName),stdin);
    strcpy(teacher[*count].lastName,lastName);
    teacher[*count].countOfCours = 0;
    char curseName[20];
    int result;
    do{
        printf("please enter course name ");
        scanf("%s",curseName);
        result = strcmp(curseName,"exit");
        if(result != 0){
            strcpy(teacher[*count].cource[teacher[*count].countOfCours].name,curseName);
            (teacher[*count].countOfCours)++;
        }
    }while(result);

    (*count)++;

    //add in a file
    addTeacherInfoToFile(teacher,count,ptrToTeacherFile);
}

void showteachers(varOfTeacher teacher[],int count){
    printf("_______________________________\n");
    for(int i = 0;i<count;i++){
        puts("firstName : ");
        puts(teacher[i].firstName);
        puts("lastName : ");
        puts(teacher[i].lastName);
        for(int j = 0;j<teacher[i].countOfCours;j++){
            printf("course%d : ",j+1);
            puts(teacher[i].cource[j].name);
        }
    }
    printf("_______________________________\n");
}


//|||||||||||||||||||||||||||||||||||||||||||||||===================={MAIN FUNCTION}==================||||||||||||||||||||||||||||||||||||||||||//
int main(){
    FILE *ptrToStudenstFile;
    FILE *ptrToCourceFile;
    FILE *ptrToTeacherFile;
    struct studentform student[50];
    storeSemester courceOfTerm[10];
    varOfTeacher teacher[10];
    int countOfTeacher = 0;


    ptrToTeacherFile = fopen("techerFile.txt","rb");
    if(ptrToTeacherFile != NULL){
        fread(&countOfTeacher,sizeof(int),1,ptrToTeacherFile);
        fread(teacher,sizeof(varOfTeacher),countOfTeacher,ptrToTeacherFile);
    }else{
        printf("-----teacher------file is not defind-------------- \n");
    }
    fclose(ptrToTeacherFile);


    // read Cources of {FILE}
    ptrToCourceFile = fopen("courcesFile.txt","r");
    if(ptrToCourceFile == NULL){
        printf("-----------file is not defind-------------- \n");
    }else{
        int countOfCorcesOfTerm = 0;
        fscanf(ptrToCourceFile,"%d",&countOfCorcesOfTerm);
        for(int i = 0;i<countOfCorcesOfTerm;i++){
            fscanf(ptrToCourceFile,"%d",&courceOfTerm[i].countOfCource);
            for(int j = 0;j<courceOfTerm[i].countOfCource;j++){
                fscanf(ptrToCourceFile,"%s %d",courceOfTerm[i].cource[j].semesterName,&courceOfTerm[i].cource[j].credits);
            }
        }
        fclose(ptrToCourceFile);

        // read studentsInfo of {FILE}
        ptrToStudenstFile = fopen("studentFile.txt","r");
        if(ptrToStudenstFile == NULL){
            printf("-----------file is not defind-------------- \n");
        }else{
            int countOfStudent;
            fscanf(ptrToStudenstFile,"%d",&countOfStudent);
            for(int i = 0 ; i<countOfStudent; i++){
                fscanf(ptrToStudenstFile,"%s %s %s %d %d %d %d %d %d",
                student[i].firstName,
                student[i].lastName,
                student[i].fullName,
                &student[i].birthDate[0],
                &student[i].birthDate[1],
                &student[i].birthDate[2],
                &student[i].studentNumber,
                &student[i].gender,
                &student[i].currentTerm);
                for(int j=0; j<student[i].currentTerm;j++){
                    int termName;
                    fscanf(ptrToStudenstFile,"%d",&termName);
                    fscanf(ptrToStudenstFile,"%d",&student[i].term[termName].countOfCorses);
                    for(int t = 0;t<student[i].term[termName].countOfCorses;t++){
                        fscanf(ptrToStudenstFile,"%s %f",
                        student[i].term[termName].cource[t].book,
                        &student[i].term[termName].cource[t].grade);
                    }
                }
                fscanf(ptrToStudenstFile,"");
            }
            fclose(ptrToStudenstFile);

            //{MENU}
            int userFirstChoice;
            do{
                printf("\n\n         {~~~~~~~~ Please Choose One Of Them ~~~~~~~~}     \n1)Add student \n2)Remove student \n3)Edit student info \n4)Edit student grade \n5)show all students\n6)add Cource\n7)Edit cource info(incomplete)\n8)Show Cources \n9)add Cources To Student \n10)remove Cources To Student \n11)showStudentInfo\n-----------------\n12)add Teacher\n13)show teachers \n0)Exit \n");
                scanf("%d",&userFirstChoice);
                switch(userFirstChoice){
                    //studentInfo function
                    case 1 : addStudent(student,&countOfStudent,ptrToStudenstFile,courceOfTerm);break;
                    case 2 : removeStudent(student,&countOfStudent,ptrToStudenstFile);break;
                    case 3 : editStudentInfo(student,&countOfStudent,ptrToStudenstFile);break;
                    case 4 : editStudentGrade(student,&countOfStudent,ptrToStudenstFile,courceOfTerm,countOfCorcesOfTerm,showCources);break; //callback funcion//
                    case 5 : showAllStudentInfo(student,countOfStudent);break;
                    //Cources function;
                    case 6 : addCource(courceOfTerm,&countOfCorcesOfTerm,ptrToCourceFile);break;
                    case 7 : ;break;
                    case 8 : showCources(courceOfTerm,countOfCorcesOfTerm);break;
                    //Tarkibi Porro...
                    case 9 : addCourcesToStudent(student,&countOfStudent,ptrToStudenstFile,courceOfTerm,countOfCorcesOfTerm);break;
                    case 10 : removeCourcesToStudent(student,&countOfStudent,ptrToStudenstFile);break;
                    case 11 : showStudentInfo(student,countOfStudent);break;
                    case 12 : addTeacher(teacher,&countOfTeacher,ptrToTeacherFile);break;
                    case 13 : showteachers(teacher,countOfTeacher);break;
                    case 0 : return 0;
                    default : printf("-----------please enter a valid number-------------- \n");break;
                }
            }while(userFirstChoice != 0);
        }
    }
    return 0;
};