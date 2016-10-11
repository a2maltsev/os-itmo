./sigusr > tmp & sleep 2; kill -SIGUSR1 $!; wait; cat tmp
