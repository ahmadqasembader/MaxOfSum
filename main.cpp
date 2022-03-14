#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <iterator>

//maximum capacity of storing
#define MAX_NUMBERS 1000

using std::cout;
using std::endl;
using std::cerr;


/*

    In order to solve the problem, I created a coordinate point system,
    where the numbers are stored in a vector of integers, and based on the given rules,
    the movement should be only downwards and diagonally, we start from the top of the trangle and 
    then, we apply this equation to determine the next index that the program is allowed to move to: 
    
    pseudo code:
    index -- > i
    row --> j
    i (can go to) --> max((i, i + j), (i, i + (j++))); 

    In code:
    index = max(arr[index + row], arr[index + (row + 1)]);

    And, in the case of a prime number, the program basically will not add it up to the sum variable.


*/


//Functions signatures
bool isPrimeNumber(int);
int getNumberOfLines();
void maxSum(std::vector<int>, int, int);
void printVector(std::vector<int>);

int main(){

    //int input[MAX_NUMBERS];
    std::vector<int> input;

    std::ifstream filename("input.txt");

    //opening the file and checking for errors
    if(!filename.is_open()){
        cerr << "File: could not open!" <<  endl;
        exit(-1);
    }

    int lines = getNumberOfLines();

    int index = 0, value;

    //reading from the file to vector
    while (filename >> value){
        input.push_back(value);
    }

    //Displaying the content of the file - (optional)
    //printVector(input);


    //finding the maximum sum of the numbers
    maxSum(input, lines, input.size());
    
    filename.close();   
    return 0;
}


//finding the maximum sum of the numbers
void maxSum(std::vector<int> arr, int lines, int arrSize){
    int index = 0, row = 1;
    int sum = arr[index], temp;
    int num_1, num_2;

    //loop over how many lines are there in the file
    for(int i = 1; i < lines; i++){
        
        num_1 = arr[index + row];
        num_2 = arr[index + (row + 1)];
        
        temp = std::max(num_1, num_2);
        

        //set the new index
        index = num_1 > num_2 ? (index + row) : (index + (row + 1));

        //only add the number to the summation if it's not primary number
        if(!isPrimeNumber(temp))
            sum += temp;
        else
            cout << "A prime numer got detected! - " << temp << endl;
        
        row++;
        
        //A trace console program to help tracing the chosen indexes
        /*
        cout << "Comparing " << num_1 << " and " << num_2 << endl;
        cout << "The chosen index is: " << index << " and its value is: " << arr[index] << ", from row: " << row << endl;
        */
    }
    cout << "The sum: " << sum << endl;
}


//checking if a number is a prime number or not
bool isPrimeNumber(int num){
    bool flag = true;

    for(int i = 2; i <= num / 2; i++) {
       if(num % i == 0) {
          flag = false;
          break;
       }
    }
    return flag;
}

//calculating number of lines in the file
int getNumberOfLines(){
    std::ifstream filename("input.txt");

    if(!filename.is_open()){
        cout << "Something went wrong! " << endl;
        exit(-1);
    }

    int lines;
    std::string line;
    while(getline(filename, line)){
        lines++;
    }

    return lines;
}


void printVector(std::vector<int> vec){
    //Displaying the content of the input vector
    cout << "The input: ";
    for(auto i : vec)
        cout << i << " ";
    cout << endl << endl;
}