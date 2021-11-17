## README.md file for querier

# No assumptions

# My implementation satisfies the full specs outlined in the REQUIREMENTS.md and README.md

# Note: program is free of memory leaks according to myvalgrind, except for one query I found. For example, the query "home and the or tse and biology" leaks 8 bytes in one block, but all other queries I tested do not have memory leaks.
# Note: for testing script to work, must have data directory parallel to indexer directory. Data directory must contain (empty) directories: readonlydirectory (must have chmod -rwx) and readonlyfile.txt (must have chmod -rwx).
# Note: compiler warning for index.c file, which is not a part of this lab... no compiler warnings for what is due for this lab