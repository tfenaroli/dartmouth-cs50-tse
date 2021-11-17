# Lab 6

## Thomas Fenaroli

## Kimberley Rangel

Recall the [Assignment](https://github.com/cs50spring2021/tse-labs/tree/main/querier).

**Total: 82/100 points**


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
* -5 Seg faults when given the following directories from the shared folder:

`letters-3`, `toscrape-2`, `wikipedia-1`

## (10) Memory leaks, according to valgrind

0/10 points:

* -4 Memory errors
* -4 Lost memory blocks
* -2 Still reachable memory blocks

```
********************************************************************************
*** Testing student solution memory management...
********************************************************************************
==4407== Memcheck, a memory error detector
==4407== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==4407== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==4407== Command: ./querier /thayerfs/home/f003f9c/cs50-dev/shared/tse/output/toscrape-2 /thayerfs/home/f003f9c/cs50-dev/shared/tse/output/toscrape-2.index
==4407== 
==4407== Use of uninitialised value of size 8
==4407==    at 0x109AD4: tokenizeQuery (querier.c:214)
==4407==    by 0x109D4F: parseQuery (querier.c:250)
==4407==    by 0x109772: query (querier.c:143)
==4407==    by 0x10A0D0: main (querier.c:325)
==4407== 
==4407== Invalid read of size 1
==4407==    at 0x109AC7: tokenizeQuery (querier.c:214)
==4407==    by 0x109D4F: parseQuery (querier.c:250)
==4407==    by 0x109772: query (querier.c:143)
==4407==    by 0x10A0D0: main (querier.c:325)
==4407==  Address 0x7c61661 is 0 bytes after a block of size 81 alloc'd
==4407==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==4407==    by 0x10A5BB: file_readUntil (file.c:66)
==4407==    by 0x10A55F: file_readLine (file.c:49)
==4407==    by 0x1097E0: query (querier.c:141)
==4407==    by 0x10A0D0: main (querier.c:325)
==4407== 
==4407== Invalid read of size 1
==4407==    at 0x109AFE: tokenizeQuery (querier.c:218)
==4407==    by 0x109D4F: parseQuery (querier.c:250)
==4407==    by 0x109772: query (querier.c:143)
==4407==    by 0x10A0D0: main (querier.c:325)
==4407==  Address 0x7c61690 is 32 bytes before a block of size 560 in arena "client"
==4407== 
==4407== Invalid read of size 1
==4407==    at 0x109B1E: tokenizeQuery (querier.c:221)
==4407==    by 0x109D4F: parseQuery (querier.c:250)
==4407==    by 0x109772: query (querier.c:143)
==4407==    by 0x10A0D0: main (querier.c:325)
==4407==  Address 0x7c61691 is 31 bytes before a block of size 560 in arena "client"
==4407== 
==4407== Invalid write of size 1
==4407==    at 0x109B5D: tokenizeQuery (querier.c:228)
==4407==    by 0x109D4F: parseQuery (querier.c:250)
==4407==    by 0x109772: query (querier.c:143)
==4407==    by 0x10A0D0: main (querier.c:325)
==4407==  Address 0x7c61691 is 31 bytes before a block of size 560 in arena "client"
==4407== 

valgrind: m_mallocfree.c:307 (get_bszB_as_is): Assertion 'bszB_lo == bszB_hi' failed.
valgrind: Heap block lo/hi size mismatch: lo = 112, hi = 0.
This is probably caused by your program erroneously writing past the
end of a heap block and corrupting heap metadata.  If you fix any
invalid writes reported by Memcheck, this assertion failure will
probably go away.  Please try that before reporting this as a bug.


host stacktrace:
==4407==    at 0x5804417A: ??? (in /usr/lib/valgrind/memcheck-amd64-linux)
==4407==    by 0x58044294: ??? (in /usr/lib/valgrind/memcheck-amd64-linux)
==4407==    by 0x58044419: ??? (in /usr/lib/valgrind/memcheck-amd64-linux)
==4407==    by 0x58052F80: ??? (in /usr/lib/valgrind/memcheck-amd64-linux)
==4407==    by 0x5803CE8A: ??? (in /usr/lib/valgrind/memcheck-amd64-linux)
==4407==    by 0x5803B593: ??? (in /usr/lib/valgrind/memcheck-amd64-linux)
==4407==    by 0x5803FC5D: ??? (in /usr/lib/valgrind/memcheck-amd64-linux)
==4407==    by 0x5803A88B: ??? (in /usr/lib/valgrind/memcheck-amd64-linux)
==4407==    by 0x580153F4: ??? (in /usr/lib/valgrind/memcheck-amd64-linux)
==4407==    by 0x1002D41B00: ???
==4407==    by 0x1002CA9F2F: ???
==4407==    by 0x1C0F: ???
==4407==    by 0x100200833F: ???
==4407==    by 0x1002CA9F17: ???
==4407==    by 0x1002CA9F2F: ???
==4407==    by 0x5946EB1F: ???
==4407==    by 0x600: ???
==4407==    by 0x47AD: ???

sched status:
  running_tid=1

Thread 1: status = VgTs_Runnable (lwpid 4407)
==4407==    at 0x4C34CF2: strlen (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==4407==    by 0x10A6B5: normalizeWord (word.c:14)
==4407==    by 0x109B6B: tokenizeQuery (querier.c:229)
==4407==    by 0x109D4F: parseQuery (querier.c:250)
==4407==    by 0x109772: query (querier.c:143)
==4407==    by 0x10A0D0: main (querier.c:325)


Note: see also the FAQ in the source distribution.
It contains workarounds to several common problems.
In particular, if Valgrind aborted or crashed after
identifying problems in your program, there's a good chance
that fixing those problems will prevent Valgrind aborting or
crashing, especially if it happened in m_mallocfree.c.

If that doesn't help, please report this bug to: www.valgrind.org

In the bug report, send all the above text, the valgrind
version, and what OS and version you are using.  Thanks.

```