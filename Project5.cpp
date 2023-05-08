/* 
This project asks the user to enter a value of 2 or greater as k. This value decides the amount of letters the
program will read as consecutive values. The data will then be read from the file and spaces will be removed.
The program will process this data and then store it as a node in the binary tree. If duplicates are found,
the number of that value is incremented. Once the values are processed the program will traverse the tree
and display output in the users terminal.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

char inputFromFile; // This will store the input from the file.
int k = 2; // The user will select a value for k, however, the default is 2.
int amountOfCharsInFile = 0; // This value is used to hold the amount of characters found in the file.
string tempStr; // This string will hold the data found in the file after some processing.

// The following class defines the binary tree and all its parts.
class BinaryTree
{
    private:
        struct node // This struct is used to design the nodes of the tree.
        {
            int count; // This will hold the amount of times a value has been found in the file.
            string value; // This will hold the value found in the file.
            node *left; 
            node *right;
        };

        node *root; // This creates a pointer to the root node of tree.

        // The following is a member function for inserting new nodes.
        void insert(node *&nodePtr, node *&newNode)
        {
            if (nodePtr == nullptr)
                nodePtr = newNode;
            else if (newNode->value < nodePtr->value)
                insert(nodePtr->left, newNode);
            else 
                insert(nodePtr->right, newNode);
        }

    public:
        // The following acts as a constructor for a binary tree.
        BinaryTree()
            { root = nullptr; }

        node *repeatedValue; // This node can hold repeated values that are found in the file.

        // The following member function inserts nodes into the tree. It uses the insert member function to work.
        void nodeInsert(string letter, int num)
        {  
            node *newNode = nullptr;
            newNode = new node;
            newNode->value = letter;
            newNode->count = num;
            newNode->left = newNode->right = nullptr;

            insert(root, newNode); // Call to insert member function. This public function allows the code to add nodes.
        }

        // This member function searches the tree for specific nodes/values. It allows duplicates to be processed.
        bool searchForValue(string correctValue) 
        {
            node *nodePtr = root; // Points to root of the tree.

            while (nodePtr)
            {
                // Following if statement checks if the pointers value is the same as the value we are looking for.
                if (nodePtr->value == correctValue)
                {
                    repeatedValue = nodePtr; // If it is the same value, it should be labeled that way...
                    return true; // then it needs to return true.
                }
                else if (correctValue < nodePtr->value) // If it is not the same value, it will check the left and right for the value.
                    nodePtr = nodePtr->left;
                else
                    nodePtr = nodePtr->right;
            }
            return false; // If not found, return false.
        }

        // This defines the output function. It will perform inorder traversal of the tree.
        void output() const
        {
            output(root);
        }

        // This defines the output function. It will perform inorder traversal of the tree.
        void output(node *nodePtr) const
        {
            if (nodePtr)
            {
                output(nodePtr->left);
                cout << endl << nodePtr->value << ": " << nodePtr->count << endl; // Prints output onto the console.
                output(nodePtr->right);
            }
        }
        
       
};

int main()
{
    // The following asks the user to enter a value for k.
    cout << "\nPlease enter a value k for the amount of consecutive \nletters you would like to check for (cannot be less than 2 and \nit should be 1 more than the amount of letters in the Project5.txt file): ";
    cin >> k;
    cout << endl;
    if (k < 2) {
        cout << "\n*ERROR: Value CANNOT be less than 2. Please try again.*\n";
        exit(0);
    }

    BinaryTree tree; // This creates an instance of the tree class. It will be used as the binary tree throughout.

    // The code below will open the file and ensure no file related errors occur.
    fstream file("Project5.txt", ios::in); // The file "Project5.txt" contains some text.

    // Check if the file is opened successfully. If so, begin single char processing.
    if (file)
    {
        file.get(inputFromFile); // This will begin to get data from the file.
        while (file)
        {
            if (inputFromFile != ' ') // This if statement checks if the input data is not a space.
            {
                char lowercaseInputFromFile = tolower(inputFromFile); // This forces any values to be stored as lowercase for processing.
                string lowercaseInputFromFile2;
                lowercaseInputFromFile2.append(1, lowercaseInputFromFile); // This value will be converted to a string before processing. A string is needed to be stored in the tree.
                bool isInTree = tree.searchForValue(lowercaseInputFromFile2); // This calls the search member function.

                if (isInTree == false) // If the value is not found in the tree, it is added as a new node.
                {
                    tree.nodeInsert(lowercaseInputFromFile2, 1); // Adds new value as new node into tree.
                } 
                else if (isInTree == true) // If value is found in the tree, the count is incremented for that value.
                {
                    tree.repeatedValue->count++; // Increment value in tree.
                }
                
            }
            file.get(inputFromFile); // This will get the next char from the file.
            amountOfCharsInFile++; // This counts the amount of chars found in the file.
        }

        file.close(); // Closes the open file.

        fstream file("Project5.txt", ios::in); // This reopens the file to begin multi-char processing.

        // Check if the file is opened successfully. If so, begin multi-char processing.
        if (file)
        {
            getline(file, tempStr); // This stores the data from the file into the string "tempStr."
        
            // This for loop iterates over the values and looks for spaces.
            for (int count = 0; count < tempStr.size(); count++)
            {
                if (tempStr[count] == ' ') // If spaces are found, they are removed.
                {
                    tempStr.erase(count, 1);
                } 
                else
                {
                    tempStr[count-1] = tolower(tempStr[count-1]); // Otherwise, the value is converted to lowercase value.
                }
            }

            int kCopy = k; // This will copy k so k is not affected by changes made to the value.
            string tempStr1; // This acts as a copy of tempStr, the var that holds data from the file.
            while (tempStr.size() >= k) // Checks if the size of chars from the file is less than k.
            {
                for (int count = 0; count < k; count++)
                {   
                    tempStr1 += tempStr[k-kCopy]; // Adds chars to new string based on value of k.
                    kCopy--; 
                }

                bool isInTree1 = tree.searchForValue(tempStr1); // This calls the search member function and checks if the value is held in the tree already.

                if (isInTree1 == false) // If the value is not in the tree...
                {
                    tree.nodeInsert(tempStr1, 1); // it is inserted into the tree.
                } 
                else if (isInTree1 == true)
                {
                    tree.repeatedValue->count++; // If it is in the tree, its count is incremented.
                }

                kCopy = k; // This reassigns kCopy's value to k.
                tempStr.erase(0, k); // This clears tempStr and prepares it for more data to be added.
                tempStr1.erase(); // This clears tempStr1 (tempStr's copy) and prepares it for more data to be added.
            }   
        } else // This displays an error if the file cannot be opened. If this error occurs, execution is aborted.
        {
            cout <<  "\n********************************************\n"
                << "*Error: Cannot open file. Please try again.*"
                << "\n********************************************\n" << endl;
            exit(0);
        }

        file.close(); // This closes the file.
        
        tree.output(); // This calls the output function and displays output for the user with inorder traversal.

    } else // This displays an error if the file cannot be opened. If this error occurs, execution is aborted.
        {
            cout <<  "\n********************************************\n"
                << "*Error: Cannot open file. Please try again.*"
                << "\n********************************************\n" << endl;
            exit(0);
        }
    return 0;
}
