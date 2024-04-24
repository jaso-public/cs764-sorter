git clone https://github.com/jaso-public/cs764-sorter.git
cd cs764-sorter/
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./generate -f lots-of-dups  -s1000 -c50000 -p1 -r999 -n 
./sort -i lots-of-dups -j no-dups-sorted  -s 1000 -d 
./verify -i no-dups-sorted -s 1000
