# cs3113sp21-project1  
Peter Nguyen - Project 1  
  
How to run:  
make clean  
make all  
./project1 test.txt  
  
If no test file is given, it will read from stdin  
  
Notes:  
-Sources used given in COLLABORATORS file  
-Used a printf for the CPU utilization  
-No known bugs (apart from the 1 test on gradescope that is .01 off from the correct output, but everything else is outputting as it should be)  
-Only assumptions that were made were given in the project description (p and N <= 2^15, etc)  
-My program has get functions corresponding to each of the needed outputs  
  * round_double() rounds the double argument to two decimal places  
  * compare_priority() compares the priority of each process, but wasn't needed  
  * get_throughput() finds the throughput by dividing the total burst time by p  
  * voluntary_switches() loops through to find the number of unique PIDs and also sets struct variables repeated and has_later to help with calculating involuntary switches, response time, turnaround time, and waiting time
  * involuntary_switches() finds the number of involuntary switches by looping through the array of processes (structs), and counts the number of involuntary switches by finding the last PIDs that end and never run again (if has_later is 0, then the process doesn't run again after)  
  * get_turnaround() uses the formula turnaround = completion time - arrival time (which is 0). It finds the total completion time of each unique PID and divides it by p to get average turnaround time  
  * get_response_time() uses the struct variable "repeated" to find the average time for a PID to first appear and divide by num unique PIDs to find average  
  * get_waiting_time() uses the formula waiting time = turnaround time - total burst time. I use the total turnaround time and subtract the total burst time and divide by the number of unique PIDs to get the average waiting time  
