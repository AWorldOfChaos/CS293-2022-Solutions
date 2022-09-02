#!/bin/bash

rm exec
g++ automated.cpp -o exec

echo "Insert and Find"
for ((i=0; i<10; i++)); do
    touch output.txt
    echo "$i"
    timeout 30s ./exec < "testCasesInsertAndFind/input$i.txt" > output.txt
    cmp "testCasesInsertAndFind/output$i.txt" output.txt || echo "Not same"
    rm output.txt
done

echo "Insert and getmin"
for ((i=0; i<10; i++)); do
    touch output.txt
    timeout 30s ./exec < "testCasesInsertAndGETMIN/input$i.txt" > output.txt
    cmp "testCasesInsertAndGETMIN/output$i.txt" output.txt || echo "Not same"
    echo "$i"
    rm output.txt
done

echo "Insert and Find and Delete"
for ((i=0; i<10; i++)); do
    touch output.txt
    timeout 30s ./exec < "testCasesInsertFindAndDelete/input$i.txt" > output.txt
    cmp "testCasesInsertFindAndDelete/output$i.txt" output.txt || echo "Not same"
    echo "$i"
    rm output.txt
done

echo "Complete"
for ((i=0; i<10; i++)); do
    touch output.txt
    timeout 30s ./exec < "completeTestCases/input$i.txt" > output.txt
    cmp "completeTestCases/output$i.txt" output.txt || echo "Not same"
    echo "$i"
    rm output.txt
done