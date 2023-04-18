#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TrieNode TrieNode;

// Struct we will use for the nodes
struct TrieNode {
    TrieNode * children[26];
    int subtreeSum;
    int nodeTotal;
};

// Prototype functions
int computeTreeSum(TrieNode *);
TrieNode * incrementNode(TrieNode *, int, char *);
TrieNode * createNode();

// Function to create a new node with the values initialized to 0
TrieNode * createNode() 
{
  TrieNode * result = (TrieNode *) malloc(sizeof(TrieNode));

  for (int i = 0; i < 26; i++)
    result->children[i] = NULL;

  result->subtreeSum = 0;
  result->nodeTotal = 0;
  return result;
}

// Function that creates a node if a name doesn't exist yet or increments a node if it does
TrieNode * incrementNode(TrieNode * root, int value, char * name)
{
    int tmp = (name[0] - 'A') - 32;

    // if a name doesn't exist, create a node for it
    if (root == NULL) 
    {
        root = createNode();
        root->children[tmp] = createNode();
        root->children[tmp]->nodeTotal = value;
        root->children[tmp]->subtreeSum += value;
    }

    if (root != NULL) 
    {
        if (root->children == NULL) 
        {
            root->children[tmp] = createNode();
            root->children[tmp]->nodeTotal = value;
            root->children[tmp]->subtreeSum += value;
        }
        
        // if a name exists, increment the node total and sum of the subtree
        if (root->children != NULL) 
        {
            root->children[tmp]->nodeTotal = value;
            root->children[tmp]->subtreeSum += value;
        }
    }

    return root;
}

int main() 
{

    int numOrangutans, numEvents, event, numMangos;

    // assign memory for the names, which will be at most a size of 20
    char * newName = (char *) malloc(sizeof(char) * 20);
    char * oldName = (char *) malloc(sizeof(char) * 20);
    char * name = (char *) malloc(sizeof(char) * 20);

    // read in the number of orangutans and how many events to process
    scanf("%d%d", &numOrangutans, &numEvents);

    // Main loop to process inputs
    for (int i = 0; i < numEvents; i++) 
    {
        // Take in an event and process it based on switch case below
        scanf("%d", &event);

        switch (event)
        {
        // Increment the number of mangoes that belongs to the monkey who has the inputted name
        case 1:
            scanf("%s%d", name, &numMangos);

            TrieNode * ans = createNode();
            ans->nodeTotal = numMangos;
            ans->subtreeSum += numMangos;
            continue;
        
        // Rename an orangutan, remove their mangoes from the total of their subtree
        // and create a new node for them
        case 2:
            scanf("%s%s", oldName, newName);
            break;

        // Print the number of mangos that the orangutan has in their subtree total
        case 3:
            scanf("%s", name);
            printf("%d\n", ans->subtreeSum);
            break;
        }
    }
}