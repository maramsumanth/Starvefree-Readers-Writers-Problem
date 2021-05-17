# include <bits/stdc++.h>
# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>

using namespace std;

// Reader and writer functions
void *reader(void *);
void *writer(void *);

// Initialize readcount and writecount to 0
int rc = 0;
int wc = 0;

// Initialize variables
int sh_var = 5;
sem_t x, y, z, rsem, wsem;
int total_readers = 7;
int total_writers = 2;
pthread_t r[7], w[2];

// Reader code
void *reader(void *i){

    // Entry
    sem_wait(&z); sem_wait(&rsem); sem_wait(&x);
    rc++;
    if (rc == 1) sem_wait(&wsem);
    sem_post(&x); sem_post(&rsem); sem_post(&z);

    // Reader output
    cout << "Reader " << i << " is reading the data: " << sh_var << endl;

    // Exit
    sem_wait(&x);
    rc--;
    if (rc == 0) sem_post(&wsem);
    sem_post(&x);
}


// Writer code
void *writer(void *i){

    // Entry
    sem_wait(&y);
    wc++; 
    if (wc == 1) sem_wait(&rsem);
    sem_post(&y); sem_wait(&wsem);
    sh_var += 50;

    // Writer output
    cout << "Writer " << i << " is writing the data: " << sh_var << endl;

    // Exit
    sem_post(&wsem); sem_wait(&y);
    wc--;
    if (wc == 0) sem_post(&rsem);
    sem_post(&y);
}

// Main function
int main(){

    // Initialize semaphores
    sem_init(&x,0,1);
    sem_init(&y,0,1);
    sem_init(&z,0,1);
    sem_init(&wsem,0,1);
    sem_init(&rsem,0,1);


    // Create threads
    pthread_create(&r[0], NULL, reader, (void *)0);
    pthread_create(&r[1], NULL, reader, (void *)1);
    pthread_create(&r[2], NULL, reader, (void *)2);
    pthread_create(&w[0], NULL, writer, (void *)0);
    pthread_create(&r[3], NULL, reader, (void *)3);
    pthread_create(&r[4], NULL, reader, (void *)4);
    pthread_create(&w[1], NULL, writer, (void *)1);
    pthread_create(&r[5], NULL, reader, (void *)5);
    pthread_create(&r[6], NULL, reader, (void *)6);


    // Finish
    pthread_join(r[0], NULL);
    pthread_join(r[1], NULL);
    pthread_join(r[2], NULL);
    pthread_join(w[0], NULL);
    pthread_join(r[3], NULL);
    pthread_join(r[4], NULL);
    pthread_join(w[1], NULL);
    pthread_join(r[5], NULL);
    pthread_join(r[6], NULL);
 
    return 0;
}    
































// # Implementation of Starve free Readers Writers Problem using C++

// # Introduction
// In this repository, we will be implementing the starve free solution of classical readers writers problem using C++ by using semaphores. In this problem we have a shared resource/database which is accessed by two processes namely reader and writer. Any number of readers can read from the shared resource simultaneously, but only one writer can write to the shared resource. So, when a writer is writing the data to the shared resource, no other process is allowed to access the resource. This solution can tackle the concurrent use of shared resources.

// # Implementation using semaphores
// ## Count Variables to be declared initially
// **rc** - Abbreviation for read count, It used to maintain the number of readers currently accessing the resource.

// **wc** - Abbreviation for write count, It used to maintain the number of writers currently accessing the resource.

// ## Method
// Initally the writer process requests for its entry, it waits wait() until it is allowed. It performs the write operation and exits. Similarly, the reader process requests for its entry. If it is allowed then firstly rc is incremented and then semaphore is signalled to allow other readers. Finally it exits.

// ## Reader Code
// ```
// // Reader code
// void *reader(void *i){

//     // Entry
//     sem_wait(&z); sem_wait(&rsem); sem_wait(&x);
//     rc++;
//     if (rc == 1) sem_wait(&wsem);

//     sem_post(&x); sem_post(&rsem); sem_post(&z);

//     // Reader output
//     cout << "Reader " << i << " is reading the data: " << sh_var << endl;

//     // Exit
//     sem_wait(&x);
//     rc--;
//     if (rc == 0) sem_post(&wsem);
//     sem_post(&x);
// }

// ```


// ## Writer Code
// ```
// // Writer code
// void *writer(void *i){

//     // Entry
//     sem_wait(&y);
//     wc++; 
//     if (wc == 1) sem_wait(&rsem);
//     sem_post(&y); sem_wait(&wsem);
//     sh_var += 50;

//     // Writer output
//     cout << "Writer " << i << " is writing the data: " << sh_var << endl;

//     // Exit
//     sem_post(&wsem); sem_wait(&y);
//     wc--;
//     if (wc == 0) sem_post(&rsem);
//     sem_post(&y);
// }
// ```

// ## Sample output of the C++ code using 7 Readers and 2 Writers
// ![Screenshot from 2021-05-16 20-51-20](https://user-images.githubusercontent.com/32808381/118402881-7be03c80-b689-11eb-8912-684d753b4a92.png)

