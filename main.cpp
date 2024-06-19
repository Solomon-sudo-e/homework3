#include <iostream>
#include <fstream>

using namespace std;
int pick_file() {
    string option;
    cout << "Which template would you like to use." << endl;
    cout << "Options are: 1. 'fairytale_long.txt', 2. 'fairytale_short.txt', 3. 'custom_fairytale.txt'" << endl;
    cin >> option;
    try{
        int int_option = stoi(option);
        if(int_option == 1 || int_option == 2 || int_option == 3) {
            return int_option;
        } else {
            cout << "The option must be an integer within 1-3." << endl;
        }
    } catch(exception &e) {
        cout << "The answer must be an integer." << endl;
        throw e;
    }
}

int recursive_or_iterative() {
    string answer;
    cout << "Would you like your madlib to be solved: 1. Recursively, 2. Iteratively." << endl;
    cout << "Please type the number associated with the way you would like the file to be solved" << endl;
    cin >> answer;
    try{
        int int_answer = stoi(answer);
        if(int_answer == 1) {
            return 1;
        } else if (int_answer == 2) {
            return 2;
        } else {
            cout << "This is not a valid answer. Please try again. It must be either 1 or 2" << endl;
        }
    } catch(exception &e) {
        cout << "The answer must be an integer." << endl;
        throw e;
    }
}

void recursive(ifstream &infile, string &typings) {
    /* Go through each index. If "<" begin appending typing.
     * If typing has more than 1 chacter and last character is not ">" go through again.
     * If typing is "< something >", check what is inside of the "< >" and find a word to fill in the spot.
     * Repeat until done.
    */
}

void iterative(ifstream &infile) {
    /*
     * Iterate through entire size of file, if index "<" being appending typing.
     * If typing has more than 1 chacter and last character is not ">" go through again.
     * If typing is "< something >", check what is inside of the "< >" and find a word to fill in the spot.
     */
}

void call_menu(int int_option, int strategy, ifstream &infile) {
    switch(int_option) {
        case 1:
            infile.open("fairytale_long.txt");
            if(infile.is_open()) {
                cout << "File opened" << endl;
                if(strategy == 1) {
                    string typings;
                    recursive(infile, typings);
                } else if(strategy == 2) {
                    iterative(infile);
                }
            } else {
                cout << "File not opened";
            }
            break;
        case 2:
            infile.open("fairytale_short.txt");
            if(infile.is_open()) {
                cout << "File opened" << endl;
                if(strategy == 1) {
                    string typings;
                    recursive(infile, typings);
                } else if(strategy == 2) {
                    iterative(infile);
                }
            } else {
                cout << "File not opened";
            }
            break;
        case 3:
            infile.open("fairytale_custom.txt");
            if(infile.is_open()) {
                cout << "File opened" << endl;
                if(strategy == 1) {
                    string typings;
                    recursive(infile, typings);
                } else if(strategy == 2) {
                    iterative(infile);
                }
            } else {
                cout << "File not opened";
            }
            break;
        case 4:
            cout << "You picked an invalid option, please try again.";
            // make it do something.
            break;
        default:
            break;
    }
}


/*
 * Make global arrays to fill verbs, noun, adjectives to call them.
 */

int main() {

    ifstream infile;
    int option = pick_file();
    int strategy = recursive_or_iterative();

    call_menu(option, strategy, infile);

    return 0;
}
