# Implementation of Starve free Readers Writers Problem using C++
### <div align = "right"> Maram Sumanth, 17116038 </div>


# Introduction
In this repository, we will be implementing the starve free solution of classical readers writers problem using C++ by using semaphores. In this problem we have a shared resource/database which is accessed by two processes namely reader and writer. Any number of readers can read from the shared resource simultaneously, but only one writer can write to the shared resource. So, when a writer is writing the data to the shared resource, no other process is allowed to access the resource. This solution can tackle the concurrent use of shared resources.

# Implementation using semaphores
## Count Variables to be declared initially
**rc** - Abbreviation for read count, It used to maintain the number of readers currently accessing the resource.

**wc** - Abbreviation for write count, It used to maintain the number of writers currently accessing the resource.

## Method
Initally the writer process requests for its entry, it waits wait() until it is allowed. It performs the write operation and exits. Similarly, the reader process requests for its entry. If it is allowed then firstly rc is incremented and then semaphore is signalled to allow other readers. Finally it exits.

## Reader Code
```
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

```


## Writer Code
```
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
```

## Sample output of the C++ code using 7 Readers and 2 Writers
![Screenshot from 2021-05-17 17-19-30](https://user-images.githubusercontent.com/32808381/118484366-c2d73c00-b734-11eb-9c85-3e70ce06a1a5.png)
