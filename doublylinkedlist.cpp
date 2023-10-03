#include<iostream>
#include<fstream>

using namespace std;

struct node
{
    char data;
    node *next;
    node *prev;
};

node *start = NULL;

void putItem(char item) // Adding a node
{
    node *temp = new node;
    temp->data = item;

    if (start == NULL) {
        start = temp;
        temp->next = temp->prev = temp;
    } else {
        node *toAdd = start->prev;
        toAdd->next = temp;
        temp->prev = toAdd;
        temp->next = start;
        start->prev = temp;
    }
}

void displayUtil(int sequence, node *ptr) {
    if (sequence == 0) {
        cout << ptr->data;
    } else if (sequence > 0) {
        displayUtil(sequence - 1, ptr->next);
    } else if (sequence < 0) {
        displayUtil(sequence + 1, ptr->prev);
    }
}

void display(int sequence) {
    displayUtil(sequence, start);
}

int main()
{
    char letters[26] = "Letters.txt";
    char sequence[26] = "Sequence-1.txt";

    ifstream lettersFile, sequenceFile;

    // Open both files
    lettersFile.open(letters);
    sequenceFile.open(sequence);

    if (!lettersFile || !sequenceFile) {
        cout << "Unable to open input files." << endl;
        return 1;
    }

    string line;
    int n, last = 0;

    // Read letters from the "Letters.txt" file and add them to the linked list
    while (lettersFile >> line) {
        putItem(line[0]);
    }

    // Read sequence numbers from the "Sequence-1.txt" file and display corresponding letters
    while (sequenceFile >> n) {
        cout << "Letter at " << n << ": ";
        display(n + last);

        // Remove the comma from the input file
        if (sequenceFile.peek() == ',') {
            sequenceFile.ignore();
        }
        last = n + last;
        cout << endl;
    }

    // Close the input files
    lettersFile.close();
    sequenceFile.close();

    return 0;
}
