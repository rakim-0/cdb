#!bin/sh
make clear
make -B main

make a 
make b
./bin/a &
./bin/b &

# calc(){ awk "BEGIN { print "$*" }"; }

while true; do
    pa=$(pgrep -x "a")
    pb=$(pgrep -x "b")
    if [ -z "$pa" ] && [ -z "$pb" ]; then
            echo "Done with waiting queue!"
            echo "DEPORTES: Sports Club"  >> output.txt
            echo "---------------------" >> output.txt
            echo "Scenario 1:" >> output.txt
            echo "" >> output.txt
            ./bin/main >> output.txt
            echo "" >> output.txt
            time1=$(awk '{ sum += $1 } END { print sum }' log.txt);
            rm log.txt

            echo "Scenario 2:" >> output.txt
            echo "" >> output.txt
            echo "Increased Memory by 20%" >> output.txt
            sed -i -e 's/count >= 5/count >= 6/g' main_memory.c
            make clear2
            make -B main
            ./bin/main >> output.txt
            time2=$(awk '{ sum += $1 } END { print sum }' log.txt);
            rm log.txt

            echo "" >> output.txt
            echo "Increased Memory by 50%" >> output.txt
            sed -i -e 's/count >= 6/count >= 9/g' main_memory.c
            make clear2
            make -B main
            ./bin/main >> output.txt
            time3=$(awk '{ sum += $1 } END { print sum}' log.txt);
            rm log.txt

            sed -i -e 's/count >= 9/count >= 5/g' main_memory.c

            echo "" >> output.txt
            echo "Scenario 3:" >> output.txt 
            echo "" >> output.txt
            echo "Original times: $time1 $time2 $time3" >> output.txt
            echo "Updated times: $((time1 / 2)) $((time2 / 2)) $((time3 / 2))" >> output.txt
            echo ""
            cat output.txt

        break;
    fi
done
