while getopts "f:n:" OPTION; do
    case $OPTION in
        f)  # file name and its path
            FILE=$OPTARG     # ex) 20702705
            ;;
        n)  # number of partitions
            PARTITION_NUM=$OPTARG   # ex) squared, hinge, logistic, quantile
            ;;
        \?)
            echo "You must feed file path (-f), number of partitions (-n) and output file name (-o)"
            exit
            ;;
    esac
done

# running graph partitioning
cd ./KaHIP
#./compile.sh
start_time=$SECONDS
./deploy/kaffpa ../$FILE --k $PARTITION_NUM --preconfiguration=fastsocial
#./deploy/kaffpaE ../$FILE --k $PARTITION_NUM --preconfiguration=fastsocial --mh_optimize_communication_volume
end_time=$SECONDS
duration_partition=$((end_time-start_time))
#echo "Partitioning graph into $PARTITION_NUM parts in $duration_partition seconds."

loop_num=$((PARTITION_NUM-1))

# construct subgraphs
cd ../
#echo "file name: $FILE"
g++ -std=c++11 subgraph.cpp -o subgraph
for n in `seq 0 $loop_num`
do
  echo "Constructing subgraph $n"
  ./subgraph $n $FILE ./KaHIP/tmppartition$PARTITION_NUM
done

cd ./Thesis
make
./bin/qc --input-file="../$FILE" --algorithm=degeneracy 0 "../../../projects/algo/nwang/partition2.txt" "../../../projects/algo/nwang/backtrack.txt" "../../../projects/algo/nwang/remapping.txt" "./degeneracyOrdering.txt" #> "../../../projects/algo/nwang/origin.graph"

start_time=$SECONDS
for n in `seq 0 $loop_num`
do
  ./bin/qc --input-file="../../../projects/algo/nwang/newgraph$n.graph" --algorithm=degeneracy 1 "../../../projects/algo/nwang/partition$n.txt" "../../../projects/algo/nwang/backtrack$n.txt" "../../../projects/algo/nwang/remapping$n.txt" "./degeneracyOrdering.txt" #> "../../../projects/algo/nwang/$OUTPUT$n.graph"
done
end_time=$SECONDS
duration_partition=$((end_time-start_time))
#echo "Computing all cliques in $duration_partition seconds."
