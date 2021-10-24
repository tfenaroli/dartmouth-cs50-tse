### implementation for indexer

## functions

# main
if argc isn't three, error
assign to pageDirectory
assign to indexFilename
call indexBuild with pageDirectory and indexFilename

return 0

# indexBuild
if pagedir isn't valid, error
create new index
while docID file exists, open it and load a webpage
    call indexPage with the webpage
call index save from module
call index delete from module

# indexPage
get every word from webpage
if word is greater than or equal to three characters, normalize the word and insert into index

## testing plan

# testing.sh
test with no arguments, one argument, three arguments
test with different types of invalid pageDirectories
test with different types of invalid indexFilenames
test with valid inputs using given test files in shared folder

test indextest by loading and then saving an index file
