Arguments：

argv[1] = DataFile

*	      formal (timestamp ID1	ID2 Label1 Lable2)

argv[2] = Process Type

*	      -f : only output the running time 
*	      -fo: output the running time and all FBPs


argv[3] = Burstiness threshold 

*	      Between 0.2 and 0.5


argv[4] = pattern_size

*	      Between 4 and 7

argv[5] = time_segment


argv[6] = the number of results one want to examine

*	      Between 10 and 70

1. Run discoveryFBP

The file discoveryFBP should be run as follow:

./discoveryFBP DataFile -f burstiness pattern_size time_segment k

For example: ./discoveryFBP data -f 0.4 4 6 70

where 70 is the number of FBPs one wants to examine

It can only output the running time

2. Result Enumeration

./discoveryFBP DataFile -fo burstiness pattern_size time_segment k

It can output the top-k FBPs 
