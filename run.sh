make clear
make -B main

make a 
make b
./bin/a &
./bin/b &

while true; do
    pa=$(pgrep -x "a")
    pb=$(pgrep -x "b")
    if [ -z "$pa" ] && [ -z "$pb" ]; then
            echo "Done with waiting queue!"
            ./bin/main
        break;
    fi
done