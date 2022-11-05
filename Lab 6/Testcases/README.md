# Testcases
----
For the purpose of automatic evaluation, we have the following files.
- userXInputs.txt
- adminXInputs.txt

## Guidelines
----

### Case 1
Outputs based on adminXInputs.txt and userXInputs.txt. If your submission compiles, you can run ./a.out logfile.txt and enter the following commands
1. Enter admin user code: 1879
2. Enter input 3 (read admin commands from file)
3. Give input file name as adminXInputs.txt
4. Enter input 5 (to print trie of station names)
    Check if the trie looks ok.  Specifically check if CHHATRAPATI SHIVAJI MAHARAJ TERMINUS appears at four places, corresponding to the words CHHATRAPATI, SHIVAJI, MAHARAJ and TERMINUS.  Similarly, check for NETAJI SC BOSE JUNCTION GOMOH.  Please also check for the word ROAD in the trie -- we should have 13 station names with the word ROAD at the trie node reached for the word ROAD.
5. Enter input 0 (to exit admin user)
6. Enter input 1 (user code for normal user)
7. Enter input 130 (read user commands from file)
8. Give input file name as userXInputs.txt
9. Enter input 120 (Find journeys)
10. Now open the file userXInputs.txt in an editor.  Go to a random line number in the file (it has 11977 lines) and look for a block of 6 lines starting with 110, e.g. lines 11965-11970:
    110
    111
    GOKULPUR
    ONDA GRAM
    1234
    Costly Journey, ticket cost was so high....
11. Enter some prefix of the first station name (say, GOK, in the above example).  The system should automatically choose the complete station name.
12. Now enter some prefix of the second station name (say, OND, in the above example). The system should automatically choose the complete station name.
13. To the query "Do you want to filter reviews by keyword? (y/n)"  enter y
14. Enter a keyword that you found in the review above, say "Costly"
15. Check whether the system returns the review with the match highlighted in green.
16. Next repeat steps 11-13 above and for step 14, enter a modification of the keyword (something that is unlikely to exist in the review, such as "abracadabra")
17. Check whether the system reports no review matching the keyword.

Note that that point 10 involves choosing a block randomly.

### Case 2
For the second code-based evaluation, we check if deletions and completions have been implemented correctly.  If the code compiles, please repeat steps 1, 2, 3, 4 as in the above check.  Check whether RAJ NANDGAON and RAJGANGPUR are inserted at the right place: at the node reached after reading RAJ, we should have RAJ NANDGAON.  Further down the same branch we should have RAJGANGPUR.

Now we will delete RAJ NANDGAON and check if the trie has been correctly updated.
Enter option 1 (enter/delete station name) in admin mode
Enter option 12 (delete station name)
Enter RAJ NANDGAON as complete station name
Enter option 5 to print the trie and see if RAJGANGPUR is still in the trie, but the path leading to RAJGANGPUR must not have RAJ NANDGAON at the node reached after reading RAJ.

Next exit admin user by entering 0.
Enter user code 1 (for normal user)
Enter option 120 (find journeys)
Enter ROAD as prefix of source station name.  You should see 13 station names with ROAD in them listed.
Enter a choice, say 11 (to choose the right source station name)
Enter JUNC as prefix of destination station name.  You should see 34 station names with JUNCTION in them listed.
If the above completions are shown, you can enter Ctrl-C and exit the program.  It means deletion and completions are working fine.
