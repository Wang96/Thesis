while getopts "f:" OPTION; do
    case $OPTION in
        f)  # file name and its path
            FILE=$OPTARG     # ex) 20702705
            ;;
        \?)
            echo "You must feed file path (-f), number of partitions (-n) and output file name (-o)"
            exit
            ;;
    esac
done

echo "\nPartition 2\n\n"
#./test.sh -f $FILE -n 2

echo "\nPartition 4\n\n"
#./test.sh -f $FILE -n 4

echo "\nPartition 8\n\n"
./test.sh -f $FILE -n 8

echo "\nPartition 16\n\n"
./test.sh -f $FILE -n 16
