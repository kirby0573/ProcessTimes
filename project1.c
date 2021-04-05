#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
    // <pid> <burst> <priority>	
    int p_info[3];
    int repeated;
    int has_later;

}process;

float round_float(float f){

    return ((int)(f * 100 + .5) / 100.0);
}

// method not needed for this proj ** 
int compare_priority(const void* p1, const void* p2){
    const process *proc1 = p1;
    const process *proc2 = p2;
    if (proc1->p_info[2] > proc2->p_info[2])
        return -1;
    else if (proc1->p_info[2] < proc2->p_info[2])
        return 1;
    else
        return 0;
}

// method to find the throughput
float get_throughput(process* p_arr, int size, int p){
    float total_burst_time = 0;
    for(int i=0; i < size; i++){
	total_burst_time += p_arr[i].p_info[1];
    }
    float rounded = round_float((p/total_burst_time));
    return rounded;
}

// method to find the number of voluntary switches
int voluntary_switches(process* p_arr, int size, int p){
    // want to look for number of unique elements
    int num_unique = 0;
    for(int i = 0; i < size; i++){
	for(int j = i+1; j < size; j++){
	    if(p_arr[i].p_info[0] == p_arr[j].p_info[0]){
		p_arr[j].repeated = 1;
	    }
	}
	if(p_arr[i].repeated < 1){
	    num_unique++;
	}
    }
    return num_unique;
}

// method to find the number of involuntary switches
int involuntary_switches(process* p_arr, int size, int p){
    int i_s = 0;

    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            if(p_arr[i].p_info[0] == p_arr[j].p_info[0] && p_arr[i].p_info[0] != p_arr[i+1].p_info[0]){
                p_arr[i].has_later = 1;
            }
        }
    }
    for(int k = 0; k < size; k++){
	if(p_arr[k].has_later > 0){
	    i_s++;
	}
    }
    return i_s;
}

// method to find the turnaround time
float get_turnaround(process* p_arr, int size, int p, int burst_time){
    int current_time=0;
    float total_waiting_time=0;
    for(int i = 0; i < size-1; i++){
        if(p_arr[i].p_info[0] != p_arr[i+1].p_info[0]){
            current_time += p_arr[i].p_info[1];
            total_waiting_time+=current_time;  
        } else {
	    current_time+=p_arr[i].p_info[1];
	}
    }

    //turnaround time = total waiting time + total burst time
    total_waiting_time+=burst_time;
    float rounded = round_float(total_waiting_time/p);
    return rounded;
}

// method to find the average response time
float get_response_time(process* p_arr, int size, int p){
    float r = 0;
    for(int i = 1; i < size; i++){
	r += p_arr[i-1].p_info[1];
    }
    float rounded = ((int)((r/(size-1)) * 100 + .5) / 100.0);
    return rounded;
}

// method to find the average waiting time
float get_waiting_time(process* p_arr, int size, int p, int unique){
    int current_time=0;
    float total_waiting_time=0;
    for(int i = 0; i < size-1; i++){
	if(p_arr[i].p_info[0] != p_arr[i+1].p_info[0]){
	    current_time += p_arr[i].p_info[1];
	    total_waiting_time+=current_time;
	}
	else {
            current_time+=p_arr[i].p_info[1];
        }
    }
    // 
    float rounded = round_float((total_waiting_time/unique));
    return rounded;
}

int main(int argc, char *argv[]){
    
    int P,p,n;
    FILE *input;
    if(argc > 1){
	input = fopen(argv[1], "r");
    } else{
	input = stdin;
    }
    fscanf(input, "%d",&P);
    fscanf(input, "%d",&p);
    fscanf(input, "%d",&n);
    int next;
    int idx = 0;
    process* all_processes = calloc(33000, sizeof(process));

    while(fscanf(input,"%d",&next) == 1){
	process p;
	p.repeated = 0;
	p.has_later = 0;
	for(int i = 0; i < 3; i++){
	    p.p_info[i] = next;
	    if(i < 2){
	        fscanf(input, "%d",&next);
	    }
	}
	all_processes[idx++] = p;
    }
    int total_burst = 0;
    for(int i=0; i < n; i++){
        total_burst += all_processes[i].p_info[1];
    }
    int unique_occurrences = voluntary_switches(all_processes, n, p);
    
    printf("%i\n", unique_occurrences);
    printf("%i\n", involuntary_switches(all_processes, n, p));
    //printf("%i\n", n - unique_occurrences-1);
    printf("100.0\n");
    printf("%.2f\n", get_throughput(all_processes, n, p));
    printf("%.2f\n", get_turnaround(all_processes, n, p, total_burst));
    printf("%.2f\n", get_waiting_time(all_processes, n, p, unique_occurrences));
    printf("%.2f\n", get_response_time(all_processes, n, p));
}
