#include<stdio.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>

int main() {
    key_t key;
    key = 1234; //Semaphore Key
    int msgflag = IPC_CREAT | 0666;
    int sem_id =  semget(key, 2, msgflag);
    struct sembuf WAIT[1], SIGNAL[1];
    
    //Defining WAIT
    WAIT[0].sem_num = 0;
    WAIT[0].sem_op = -1;
    WAIT[0].sem_flg = SEM_UNDO;

    //Defining SIGNAL
    SIGNAL[0].sem_num = 0;
    SIGNAL[0].sem_op = 1;
    SIGNAL[0].sem_flg = SEM_UNDO;

    int a,b;
    printf("Program Running\n");
    semop(sem_id, WAIT, 1);
    printf("CRITICAL SECTION RUNNING\n");
    printf("Enter value of 2 numbers : \n");
    scanf("%d%d",&a,&b);
    int c = a+b;
    printf("SUM = %d\n",c);
    semop(sem_id, SIGNAL, 1);
    printf("EXITING CRITICAL SECTION\n");
    semctl(sem_id, 1, IPC_RMID | 0666);
}
