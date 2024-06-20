#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int ARRAY_SIZE = 50;
string nouns[ARRAY_SIZE];
string verbs[ARRAY_SIZE];
string adjectives[ARRAY_SIZE];

void fill_array(string array[ARRAY_SIZE], string text) {
    ifstream infile;
    infile.open(text);
    if(!infile.is_open()) {
        cout << text << " cant be opened";
    }
    string word;
    for(int i = 0; i < ARRAY_SIZE; i++) {
        infile >> word;
        array[i] = word;
    }
}

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

string new_word(string typings) {
    int random = rand() % ARRAY_SIZE;
    if(typings == "<noun>") {
        return nouns[random];
    } else if(typings == "<verb>") {
        return verbs[random];
    } else if(typings == "<adjective>") {
        return adjectives[random];
    }
}

string read_file(ifstream &infile) {
    stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();
    string file = buffer.str();
    return file;
}

void recursive(string &file, int pos) {
    /* Go through each index. If "<" begin appending typing.
     * If typing has more than 1 chacter and last character is not ">" go through again.
     * If typing is "< something >", check what is inside of the "< >" and find a word to fill in the spot.
     * Repeat until done.
    */
    int max_size = file.size();

    if (pos >= max_size) {
        // Base case: If pos is beyond the file size, return
        cout << file;
        return;
    }

    if (file[pos] == '<') {
        // Begin collecting the placeholder
        string typings;
        typings += file[pos];
        pos++;

        // Continue collecting until '>' is found
        while (pos < max_size && file[pos] != '>') {
            typings += file[pos];
            pos++;
        }

        // Add the closing '>'
        typings += file[pos];

        // Find a word to replace the placeholder
        string word = new_word(typings);

        // Replace the placeholder in the file string
        size_t replace_pos = file.find(typings, pos - typings.size());
        if (replace_pos != string::npos) {
            file.replace(replace_pos, typings.size(), word);
            // Update pos to the end of the replaced word
            pos = replace_pos + word.size();
        } else {
            cout << "Error: Placeholder not found in file!" << endl;
            return;
        }

        // Recursively call to continue replacing placeholders
        recursive(file, pos);
    } else {
        // If not at a placeholder, move to the next character
        pos++;
        recursive(file, pos);
    }
}

void iterative(string &file, string &typings, int pos) {
    /*
     * Iterate through entire size of file, if index "<" being appending typing.
     * If typing has more than 1 character and last character is not ">" go through again.
     * If typing is "< something >", check what is inside of the "< >" and find a word to fill in the spot.
     */
    int max_size = file.size();

    while (pos < max_size) {
        if (file[pos] == '<') {
            // Begin collecting the placeholder
            string typings;
            typings += file[pos];
            pos++;

            // Continue collecting until '>' is found
            while (pos < max_size && file[pos] != '>') {
                typings += file[pos];
                pos++;
            }

            // Add the closing '>'
            typings += file[pos];

            // Find a word to replace the placeholder
            string word = new_word(typings);

            // Replace the placeholder in the file string
            size_t replace_pos = file.find(typings, pos - typings.size());
            if (replace_pos != string::npos) {
                file.replace(replace_pos, typings.size(), word);
                // Move pos past the replaced placeholder
                pos = replace_pos + word.size();
            } else {
                cout << "Error: Placeholder not found in file!" << endl;
                break;
            }
        } else {
            pos++;
        }
    }
    cout << file;
}

void handle_file_pushing(ifstream &infile, string &typings, int pos) {
    string new_file = read_file(infile);
    recursive(new_file, pos);
}

void call_menu(int int_option, int strategy, ifstream &infile) {
    int pos = 0;
    switch(int_option) {
        case 1:
            infile.open("fairytale_long.txt");
            if(infile.is_open()) {
                cout << "File opened" << endl;
                if(strategy == 1) {
                    string typings = "";
                    handle_file_pushing(infile, typings, pos);
                } else if(strategy == 2) {
                    //(infile, "filler", pos);
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
                    string typings = "";
                    handle_file_pushing(infile, typings, pos);
                } else if(strategy == 2) {
                    //iterative(infile, "filler", pos);
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
                    string typings = "";
                    handle_file_pushing(infile, typings, pos);
                } else if(strategy == 2) {
                    //iterative(infile, "filler", pos);
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

int main() {
    fill_array(nouns, "nouns.txt");
    fill_array(verbs, "verbs.txt");
    fill_array(adjectives, "adjectives.txt");

    ifstream infile;
    int option = pick_file();
    int strategy = recursive_or_iterative();

    call_menu(option, strategy, infile);

    return 0;
}

