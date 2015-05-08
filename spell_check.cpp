#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

#include "weight.h"

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

        ~Node(){ }

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

        vector<Node*> get_children()
        {
            return children;
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

        vector<string> all_words_that_start_with(char c)
        {
            Node * subroot = (root->get_children())[c - 97];
            vector<string> words;
            traverse_sub_tree(subroot, "", words);
            return words;
        }

    private:
        Node* root;

        void traverse_sub_tree(Node * curr, string word, vector<string> & words)
        {
            if(curr == NULL)
                return;

            word += curr->content();
            if(curr->wordMarker())
                words.push_back(word);
            for(int i = 0; i < 26; i++)
            {
                Node * ch = (curr->get_children())[i];
                traverse_sub_tree(ch, word, words);
            }
        }
};


inline int min(int a, int b, int c)
{
    if (a < b)
        return a < c ? a : c;
    else
        return b < c ? b : c;
}

int edit_distance(string & A, string & B, int (&weights)[26][26])
{
    int len_A = A.size();
    int len_B = B.size();

    int M[len_A + 1][len_B + 1];

    for (int i = 0; i <= len_A; i++)
        M[i][0] = i;

    for (int j = 0; j <= len_B; j++)
        M[0][j] = j;

    for (int a = 1; a <= len_A; a++)
    {
        for (int b = 1; b <= len_B; b++)
        {
            int x = M[a-1][b] + 2;
            int y = M[a][b-1] + 2;
            int z_1 = M[a-1][b-1] + (A[a-1] == B[b-1] ? 0 : weights[A[a - 1] - 97][B[b - 1] - 97]);
            int z_2 = M[a-1][b-1] + (A[a-1] == B[b-1] ? 0 : 2);
            int z = (z_1 + z_2)/2;
            M[a][b] = min(x,y,z);
        }
    }   

    return M[len_A][len_B];
}


int main()
{
    map<string,int> dict;
    Trie* trie = new Trie();
    weight* w = new weight();
    string s;
    string sl;
    ifstream f("english_words.txt");
    ifstream big("cleaned_big.txt");
    vector<vector<string> > sorted;

    //loop to populate trie with all words in the english dictionary
    while(getline(f, s))
    {
        trie->addWord(s);
        dict[s] = 0;
    }

    //loop to give appropriate frequencies to the words
    while(getline(big, s, ' '))
        dict[s]++;

    //loop to smooth words with 0 frequencies by assigning them a frequency of 1
    for(map<string, int>::iterator it = dict.begin(); it != dict.end(); it++)
    {
        if(it->second == 0)
            it->second = 1;
    }

    //loop to store in vector all words in the english dictionary with a particular letter
    for(int i = 0; i < 26; i++)
    {
        vector<string> words = trie->all_words_that_start_with(char(i + 97));
        sorted.push_back(words);
    }

    cout<<"\n";
    while(1)
    {
        int threshold = 0;
        int best = 100000;
        string best_string = "";
        cout<<"Enter a word: ";
        cin >> s;
        vector<string> words = sorted[s[0] - 97];
        if(trie->searchWord(s)) //if the word exists in the english language
            cout<<"Closest Word: "<<s<<endl;
        else
        {
            for(int i = 0; i < words.size(); i++)
            {
                int dist = edit_distance(words[i], s, w->weights);
                if(dist < best)
                    best = dist;
            }
            for(int i = 0; i < words.size(); i++)
            {
                int dist = edit_distance(words[i], s, w->weights);
                if(best == dist)
                {
                    //cout<<words[i]<<"\t"<<dist<<" "<<dict[words[i]]<<endl;
                    if(dict[words[i]] * dist >= threshold)
                    {
                        if(dict[words[i]] * dist == threshold)
                            best_string += " " + words[i];
                        else
                            best_string = words[i];
                        threshold = dict[words[i]] * dist;
                    }
                }
            }
            cout<<"Closest Word(s): "<<best_string<<endl;
        }
        cout<<"\n";
    }
}
