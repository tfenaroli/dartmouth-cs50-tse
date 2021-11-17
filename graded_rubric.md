# Lab 6

## Thomas Fenaroli

## Kimberley Rangel

Recall the [Assignment](https://github.com/cs50spring2021/tse-labs/tree/main/querier).

**Total: 90/100 points**


## (10) Overall

9/10 points:

* -1 Executable in indexer

## (8) Makefiles

8/8 points:

* 

## (15) Documentation

15/15 points:

* 

## (7) Testing

7/7 points:

* 

## (20) Coding Style

19/20 points:

* -1 Code needs to be more rigorous when checking if memory was properly allocated

## (30) Functionality

24/30 points:

* -1 Seg fault when dealing with non-readable index file
* -3 Seg faults when given the following directories from the shared folder (due to whitespace):
`letters-3`, `toscrape-2`, `wikipedia-1`

This command works
```
./querier ~/cs50-dev/shared/tse/output/letters-3 ~/cs50-dev/shared/tse/output/letters-3.index < "valid_queries copy.txt"
```

This gives a core dump

```
./querier ~/cs50-dev/shared/tse/output/letters-3 ~/cs50-dev/shared/tse/output/letters-3.index < "valid_queries.txt"
```


## (10) Memory leaks, according to valgrind

6/10 points:

* -2 Memory errors
* -2 Lost memory blocks


```
valgrind --leak-check=full --show-leak-kinds=all ./querier ~/cs50-dev/shared/tse/output/toscrape-2 ~/cs50-dev/shared/tse/output/toscrape-2.index < "valid_queries copy.txt"

==22074== Memcheck, a memory error detector
==22074== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==22074== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==22074== Command: ./querier /thayerfs/home/f003f9c/cs50-dev/shared/tse/output/toscrape-2 /thayerfs/home/f003f9c/cs50-dev/shared/tse/output/toscrape-2.index
==22074== 
Query: here is tokenized query:
dartmouth 

no documents match the query



Query: here is tokenized query:
dartmouth 

no documents match the query



Query: here is tokenized query:
dartmouth 

no documents match the query



Query: here is tokenized query:
lab 

docID: 203, score: 8, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/lab-girl_595/index.html
docID: 196, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/category/books/autobiography_27/index.html
docID: 197, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/a-heartbreaking-work-of-staggering-genius_115/index.html
docID: 198, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/life-without-a-recipe_188/index.html
docID: 199, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/lust-wonder_191/index.html
docID: 200, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/me-talk-pretty-one-day_193/index.html
docID: 201, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/running-with-scissors_215/index.html
docID: 202, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/approval-junkie-adventures-in-caring-too-much_363/index.html



Query: here is tokenized query:
dartmouth college 

no documents match the query



Query: here is tokenized query:
dartmouth college 

no documents match the query



Query: here is tokenized query:
dartmouth and college 

no documents match the query



Query: here is tokenized query:
dartmouth and college 

no documents match the query



Query: here is tokenized query:
dartmouth college and computer science 

no documents match the query



Query: here is tokenized query:
dartmouth college or computer science 

docID: 380, score: 4, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/algorithms-to-live-by-the-computer-science-of-human-decisions_880/index.html



Query: here is tokenized query:
dartmouth and college and computer and science 

no documents match the query



Query: here is tokenized query:
dartmouth and college or computer and science 

docID: 380, score: 4, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/algorithms-to-live-by-the-computer-science-of-human-decisions_880/index.html



Query: here is tokenized query:
dartmouth or computer science or programming or unix or doug mcilroy 

docID: 380, score: 4, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/algorithms-to-live-by-the-computer-science-of-human-decisions_880/index.html



Query: here is tokenized query:
europe and travel 

docID: 575, score: 3, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/neither-here-nor-there-travels-in-europe_198/index.html
docID: 91, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/the-travelers_285/index.html
docID: 573, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/category/books/travel_2/index.html
docID: 574, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/1000-places-to-see-before-you-die_1/index.html
docID: 576, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/the-road-to-little-dribbling-adventures-of-an-american-in-britain-notes-from-a-small-island-2_277/index.html
docID: 577, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/a-year-in-provence-provence-1_421/index.html
docID: 578, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/the-great-railway-bazaar_446/index.html
docID: 579, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/a-summer-in-europe_458/index.html



Query: here is tokenized query:
european travel 

no documents match the query



Query: here is tokenized query:
france and spain 

no documents match the query



Query: here is tokenized query:
france or spain 

docID: 543, score: 4, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/the-constant-princess-the-tudor-court-1_493/index.html
docID: 42, score: 2, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/soumission_998/index.html
docID: 71, score: 2, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/all-the-light-we-cannot-see_660/index.html
docID: 459, score: 2, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/i-had-a-nice-time-and-other-lies-how-to-find-love-sht-like-that_814/index.html
docID: 540, score: 2, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/the-passion-of-dolssa_351/index.html
docID: 545, score: 2, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/a-paris-apartment_612/index.html
docID: 548, score: 2, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/the-marriage-of-opposites_759/index.html
docID: 101, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/benjamin-franklin-an-american-life_460/index.html
docID: 127, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/32-yolks_510/index.html
docID: 143, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/my-paris-kitchen-recipes-and-stories_910/index.html
docID: 312, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/code-name-verity-code-name-verity-1_680/index.html
docID: 441, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/private-paris-private-10_958/index.html
docID: 544, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/lilac-girls_597/index.html
docID: 187, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/dress-your-family-in-corduroy-and-denim_562/index.html
docID: 574, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/1000-places-to-see-before-you-die_1/index.html



Query: here is tokenized query:
members and health 

no documents match the query



Query: here is tokenized query:
england or british and freedom and uses or arabian or universal and brady 

docID: 317, score: 6, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/the-white-queen-the-cousins-war-1_768/index.html
docID: 543, score: 4, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/the-constant-princess-the-tudor-court-1_493/index.html
docID: 104, score: 3, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/louisa-the-extraordinary-life-of-mrs-adams_818/index.html
docID: 576, score: 3, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/the-road-to-little-dribbling-adventures-of-an-american-in-britain-notes-from-a-small-island-2_277/index.html
docID: 17, score: 3, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/aladdin-and-his-wonderful-lamp_973/index.html
docID: 414, score: 2, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/once-was-a-time_724/index.html
docID: 571, score: 2, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/a-murder-in-time_877/index.html
docID: 424, score: 2, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/i-am-pilgrim-pilgrim-1_703/index.html
docID: 16, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/worlds-elsewhere-journeys-around-shakespeares-globe_972/index.html
docID: 101, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/benjamin-franklin-an-american-life_460/index.html
docID: 155, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/brilliant-beacons-a-history-of-the-american-lighthouse_515/index.html
docID: 267, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/library-of-souls-miss-peregrines-peculiar-children-3_816/index.html
docID: 305, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/the-midnight-watch-a-novel-of-the-titanic-and-the-californian_640/index.html
docID: 370, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/kill-em-and-leave-searching-for-james-brown-and-the-american-soul_528/index.html



Query: here is tokenized query:
ccd and homme or cheap and hero or sunset and sunrise or china 

docID: 574, score: 1, URL: http://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/1000-places-to-see-before-you-die_1/index.html



Query: ==22074== 
==22074== HEAP SUMMARY:
==22074==     in use at exit: 104 bytes in 13 blocks
==22074==   total heap usage: 3,332,302 allocs, 3,332,289 frees, 69,553,121 bytes allocated
==22074== 
==22074== 104 bytes in 13 blocks are definitely lost in loss record 1 of 1
==22074==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==22074==    by 0x10B3C0: mem_malloc (mem.c:69)
==22074==    by 0x10AAB4: counters_new (counters.c:45)
==22074==    by 0x109F06: parseQuery (querier.c:280)
==22074==    by 0x109772: query (querier.c:143)
==22074==    by 0x10A0D0: main (querier.c:325)
==22074== 
==22074== LEAK SUMMARY:
==22074==    definitely lost: 104 bytes in 13 blocks
==22074==    indirectly lost: 0 bytes in 0 blocks
==22074==      possibly lost: 0 bytes in 0 blocks
==22074==    still reachable: 0 bytes in 0 blocks
==22074==         suppressed: 0 bytes in 0 blocks
==22074== 
==22074== For counts of detected and suppressed errors, rerun with: -v
==22074== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```