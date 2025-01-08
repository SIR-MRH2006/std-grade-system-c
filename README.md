# ``Student Adding Info System`` #

</br>

## Description ##
This Is a system for adding,removing,editing,setting grad and ets.that is writting by c languge.
</br></br>

## Languages that had uses for this project ##
![](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
- c(libarary)
    - <stdio.h>
    - <string.h>
    - <stdlib.h>

</br>


### e.g CODE ###
```c
    switch(userFirstChoice){
        //studentInfo function
        case 1 : addStudent(student,&countOfStudent,ptrToStudenstFile,courceOfTerm);break;
        case 2 : removeStudent(student,&countOfStudent,ptrToStudenstFile);break;
        case 3 : editStudentInfo(student,&countOfStudent,ptrToStudenstFile);break;
        case 4 : editStudentGrade(student,&countOfStudent,ptrToStudenstFilecourceOfTercountOfCorcesOfTerm,showCources);break;
        case 5 : showAllStudentInfo(student,countOfStudent);break;
        //Cources function;
        case 6 : addCource(courceOfTerm,&countOfCorcesOfTerm,ptrToCourceFile);break;
        case 7 : ;break;
        case 8 : showCources(courceOfTerm,countOfCorcesOfTerm);break;
        //Tarkibi Porro...
        case 9 : addCourcesToStudent(student,&countOfStudent,ptrToStudenstFilecourceOfTercountOfCorcesOfTerm);break;
        case 10 : removeCourcesToStudent(student,&countOfStudent,ptrToStudenstFile);break;
        case 11 : showStudentInfo(student,countOfStudent);break;
        case 0 : return 0;
        default : printf("-----------please enter a valid number-------------- \n");break;
    }
```