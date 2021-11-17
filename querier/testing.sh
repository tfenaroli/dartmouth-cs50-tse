# ## testing script

# # testing with invalid number of arguments
echo -e "testing with no arguments\n"
./querier
echo -e "-----------------------------------------------"

# testing with invalid number of arguments
echo -e "testing with one argument\n"
./querier ../../shared/tse/output/crawler/pages-letters-depth-2
echo -e "-----------------------------------------------"

# testing with invalid number of arguments
echo -e "testing with three arguments\n"
./querier ../../shared/tse/output/crawler/pages-letters-depth-2 ../../shared/tse/output/indexer/index-letters-2 faultyargument
echo -e "-----------------------------------------------"

# testing with invalid pageDirectory
echo -e "testing with invalid pageDirectory (non-existent path)\n"
./querier ../../shared/tse/output/crawlertypo/pages-letters-depth-2 ../../shared/tse/output/indexer/index-letters-2
echo -e "-----------------------------------------------"

# testing with invalid pageDirectory
echo -e "testing with invalid pageDirectory (not a crawler directory)\n"
./querier ../data/readonlydirectory ../../shared/tse/output/indexer/index-letters-2
echo -e "-----------------------------------------------"

echo -e "testing with valid inputs and valid queries\n"
./querier ../../shared/tse/output/crawler/pages-letters-depth-2 ../../shared/tse/output/indexer/index-letters-2 < testfile1.txt
echo -e "-----------------------------------------------"

echo -e "-----------------------------------------------"
./querier ../../shared/tse/output/crawler/pages-letters-depth-2 ../../shared/tse/output/indexer/index-letters-2 < testfile2.txt
echo -e "-----------------------------------------------"

echo -e "-----------------------------------------------"
./querier ../../shared/tse/output/crawler/pages-letters-depth-2 ../../shared/tse/output/indexer/index-letters-2 < testfile3.txt
echo -e "-----------------------------------------------"

echo -e "-----------------------------------------------"
./querier ../../shared/tse/output/crawler/pages-letters-depth-2 ../../shared/tse/output/indexer/index-letters-2 < testfile4.txt
echo -e "-----------------------------------------------"

echo -e "-----------------------------------------------"
./querier ../../shared/tse/output/crawler/pages-toscrape-depth-1 ../../shared/tse/output/indexer/index-toscrape-1 < testfile5.txt
echo -e "-----------------------------------------------"

echo -e "valgrind shows no memory leaks or other errors on querier, except for a few queries (mentioned in README.md file)\n"
echo -e "-----------------------------------------------"
