// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#define _XOPEN_SOURCE 500
#include "view.h"
// ./view filecount
int main(int argc, char const *argv[]) {

    int fd;
    char *ptr_read;
    struct stat shm_st;
    int fileCount= 0;

    //sem_t * semaphore = sem_open(SEM,O_CREAT,SEM_FLAGS);

    if(argc == 2){
        fileCount = atoi(argv[1]);
    }
    else if( argc == 1){
        char buffer[SHM_SIZE];
        read(STDIN_FILENO, buffer, SHM_SIZE);
        fileCount = atoi(buffer); 
    }
    else{
        error("Cantidad incorrecta de argumentos");
    }

    fd = shm_open (SHM_NAME,  O_RDONLY  , 00400); /* open s.m object*/
    if(fd == -1)
    {
        error("Shared Memory open fallo");
    }
    
    if(fstat(fd, &shm_st) == -1)
    {
        perror("fstat fallo");
    }
  
    ptr_read = mmap(NULL, shm_st.st_size, PROT_READ, MAP_SHARED, fd, 0);

    if(ptr_read == MAP_FAILED)
    {
        error("Fallo el mapeo de la shared memory");
    }

    int i=0;
    while (i < fileCount){
       
    // //    if(sem_wait(semaphore) < 0){
    // //     error("Semaphore View Error");
    // //    };

       printf("%s \n", ptr_read);
       ptr_read += SHM_SIZE;
       i++;
    }

    close(fd);
    
    return 0;
}