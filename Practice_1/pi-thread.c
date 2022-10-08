#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int npoints = 10000;
double pi = 0;
int circle_count = 0;
pthread_mutex_t lock;

void* monteCarlo(void *arg){
	int points = 0;
	int temp_circle = 0;
        pthread_mutex_lock(&lock);
	
	for(int i= 0; i < 10000, points < npoints/(int)arg; i++, points++){  
		double y_num = (double)(rand()%10000)/10000;
		double x_num = (double)(rand()%10000)/10000;

		if( x_num*x_num + y_num*y_num <= 1){
			circle_count++;
		}
	}
	pthread_mutex_unlock(&lock);
	return NULL;
}
int main(int argc, char *argv[]){
	int nthreads = atoi(argv[1]);
	pthread_t tid[nthreads];
	int i = 0;
	int err;
			    
	if (pthread_mutex_init(&lock, NULL) != 0){
		printf("\n mutex init failed\n");
		return 1;
	}

	while(i < nthreads) {
		err = pthread_create(&(tid[i]), NULL, &monteCarlo,(void*) nthreads);
		if (err != 0)
			printf("\ncan't create thread :[%s]", strerror(err));
		i++;
	}
	i = 0;
	while(i < nthreads){
		pthread_join(tid[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&lock);
	pi = (double)4.0*circle_count/10000.0;
	printf("\n pi value = %f\n", pi);
	return 0;
}
