# ## testing script

# # testing with invalid number of arguments
echo -e "testing with no arguments\n"
./indexer
echo -e "-----------------------------------------------"

# testing with invalid number of arguments
echo -e "testing with one argument\n"
./indexer ../../shared/tse/output/crawler/pages-letters-depth-2
echo -e "-----------------------------------------------"

# testing with invalid number of arguments
echo -e "testing with three arguments\n"
./indexer ../../shared/tse/output/crawler/pages-letters-depth-2 ../data/letters/.index additionalArgument
echo -e "-----------------------------------------------"

# testing with invalid pageDirectory
echo -e "testing with invalid pageDirectory (non-existent path)\n"
./indexer ../../sharedtypo/tse/output/crawler/pages-letters-depth-2 ../data/letters/.index
echo -e "-----------------------------------------------"

# testing with invalid pageDirectory
echo -e "testing with invalid pageDirectory (not a crawler directory)\n"
./indexer ../../tse-tfenaroli ../data/letters/.index
echo -e "-----------------------------------------------"

# testing with invalid indexFile
echo -e "testing with invalid indexFile (non-existent path)\n"
./indexer ../../shared/tse/output/crawler/pages-letters-depth-2 ../datatypo/letters/.index
echo -e "-----------------------------------------------"

# testing with invalid indexFile
echo -e "testing with invalid indexFile (read-only directory)\n"
./indexer ../../shared/tse/output/crawler/pages-letters-depth-2 ../data/lettersreadonlydirectory/.index
echo -e "-----------------------------------------------"

# testing with invalid indexFile
echo -e "testing with invalid indexFile (existing, read-only file)\n"
./indexer ../../shared/tse/output/crawler/pages-letters-depth-2 ../data/readonlyfile.txt
echo -e "-----------------------------------------------"

echo -e "testing with valid inputs\n"
./indexer ../../shared/tse/output/crawler/pages-letters-depth-2 ../data/letters/.index
echo -e "-----------------------------------------------"

echo -e "checking the result of indexer test on pages-toscrape-depth-1 with given func indexcmp... if nothing is printed, then indices are equivalent\n"
./indexer ../../shared/tse/output/crawler/pages-toscrape-depth-1 ../data/toscrape/.index
~/cs50-dev/shared/tse/indexcmp ../../shared/tse/output/indexer/index-toscrape-1 ../data/toscrape/.index
echo -e "-----------------------------------------------"

echo -e "create indextestresults.index with indextest.c using given file index-toscrape-1\n"
./indextest ../../shared/tse/output/indexer/index-toscrape-1 ../data/indextesting/indextestresults.index
echo -e "see if files are different using given func indexcmp... if nothing is printed, then indices are equivalent\n"
~/cs50-dev/shared/tse/indexcmp ../../shared/tse/output/indexer/index-toscrape-1 ../data/indextesting/indextestresults.index
echo -e "-----------------------------------------------"

echo -e "valgrind shows no memory leaks or other errors on indextest or indexer\n"
echo -e "-----------------------------------------------"
