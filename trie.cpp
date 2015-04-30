#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Node {
    public:
        Node() 
        {  
            node_char = '\0'; 
            end_word = false; 
            for(int i = 0; i < 26; i++)
                children.push_back(NULL);
        }

        ~Node()
        {

        }

        char content() 
        { 
            return node_char; 
        }

        void setContent(char c) 
        { 
            node_char = c; 
        }

        bool wordMarker() 
        { 
            return end_word; 
        }
        void setWordMarker() 
        { 
            end_word = true; 
        }

        Node* findChild(char c)
        {
            return children[c - 97];
        }

        void insertChild(int index, Node * child) 
        { 
            children[index] = child; 
        }

        private:
            char node_char;
            bool end_word;
            vector<Node*> children;
};

class Trie {
    public:
        Trie()
        {
            root = new Node();
        }

        ~Trie();

        void addWord(string s)
        {
            Node* current = root;
            for(int i = 0; i < s.length(); i++)
            {       
                Node* child = current->findChild(s[i]);
                if (child != NULL)
                    current = child;
                else
                {
                    Node* tmp = new Node();
                    tmp->setContent(s[i]);
                    current->insertChild(s[i] - 97, tmp);
                    current = tmp;
                }
                if (i == s.length() - 1)
                    current->setWordMarker();
            }            
        }

        bool searchWord(string s)
        {
            Node* current = root;
            while(current != NULL)
            {
                for(int i = 0; i < s.length(); i++)
                {
                    Node* tmp = current->findChild(s[i]);
                    if (tmp == NULL)
                        return false;
                    current = tmp;
                }
                if (current->wordMarker())
                    return true;
                else
                    return false;
            }
            return false;
        }

    private:
        Node* root;
};


inline int min(int x, int y, int z)
{
    if (x < y)
        return x < z ? x : z;
    else
        return y < z ? y : z;
}

int edit_distance(const string& A, const string& B)
{
    int NA = A.size();
    int NB = B.size();

    vector<vector<int> > M(NA + 1, vector<int>(NB + 1));

    for (int a = 0; a <= NA; ++a)
        M[a][0] = a;

    for (int b = 0; b <= NB; ++b)
        M[0][b] = b;

    for (int a = 1; a <= NA; ++a)
        for (int b = 1; b <= NB; ++b)
        {
            int x = M[a-1][b] + 1;
            int y = M[a][b-1] + 1;
            int z = M[a-1][b-1] + (A[a-1] == B[b-1] ? 0 : 2);
            M[a][b] = min(x,y,z);
        }

    return M[A.size()][B.size()];
}


int main()
{
    Trie* trie = new Trie();
    
    ifstream f("words.txt");
    string s;
    int num_words = 0;
    while(getline(f, s))
    {
        trie->addWord(s);
        num_words++;
    }
    while(1)
    {
        cout<<"Enter a word: ";
        cin >> s;
        if(trie->searchWord(s))
            cout<<s<<" was found!"<<endl;
        else
            cout<<s<<" was not found!"<<endl;
    }
}