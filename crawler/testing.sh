## testing script

# testing with improper number of arguments
echo -e "testing with improper number of arguments\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 5 faultyarg
echo -e "-----------------------------------------------"

# testing with depth out of range
echo -e "testing with depth out of range\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 11
echo -e "-----------------------------------------------"

# testing with faulty link (not working)
echo -e "testing with faulty link\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.htmlfaultylink ../data/letters 5
echo -e "-----------------------------------------------"

# testing with improper directory (not working)
echo -e "testing with improper directory\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../faultydirectory/letters 5
echo -e "-----------------------------------------------"

# valgrind test with letters
echo -e "valgrind test with letters\n"
myvalgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 1
echo -e "-----------------------------------------------"

# basic test with letters
echo -e "basic test with letters\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 5
echo -e "samples of first two files:\n"
head -3 ../data/letters/1
head -3 ../data/letters/2
echo -e "-----------------------------------------------"

# basic test with letters with different seedURL
echo -e "basic test with letters with different seedURL\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/G.html ../data/letters 5
echo -e "samples of first two files:\n"
head -3 ../data/letters/1
head -3 ../data/letters/2
echo -e "-----------------------------------------------"

# basic test with toscrape
echo -e "basic test with toscrape\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../data/toscrape 1
echo -e "samples of first two files:\n"
head -3 ../data/toscrape/1
head -3 ../data/toscrape/2
echo -e "-----------------------------------------------"

# basic test with wikipedia
echo -e "basic test with wikipedia\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html ../data/wikipedia 1
echo -e "samples of first two files:\n"
head -3 ../data/wikipedia/1
head -3 ../data/wikipedia/2
echo -e "-----------------------------------------------"