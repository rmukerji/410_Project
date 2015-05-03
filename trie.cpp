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


inline int min(int x, int y, int z)
{
    if (x < y)
        return x < z ? x : z;
    else
        return y < z ? y : z;
}

int edit_distance(const string& A, const string& B, int (&weights)[26][26])
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
            int x = M[a-1][b] + 2;
            int y = M[a][b-1] + 2;
            int z_1 = M[a-1][b-1] + (A[a-1] == B[b-1] ? 0 : weights[A[a - 1] - 97][B[b - 1] - 97]);
            int z_2 = M[a-1][b-1] + (A[a-1] == B[b-1] ? 0 : 2);
            int z = (z_1 + z_2)/2;
            M[a][b] = min(x,y,z);
        }

    return M[A.size()][B.size()];
}


int main()
{
    std::map<string,int> dict;
    Trie* trie = new Trie();
    string s;

    weight* weights = new weight();

    ifstream f("words.txt");
    int num_words = 0;
    while(getline(f, s))
    {
        trie->addWord(s);
        num_words++;
        dict[s] = 0;
    }

    //Time to read big.txt and fill in frequencies
    ifstream big("cleaned_big.txt");
    while(getline(big, s, ' '))
        dict[s]++;

    for(map<string, int>::iterator it = dict.begin(); it != dict.end(); it++)
    {
        if(it->second == 0)
            it->second = 1;
    }

    vector<vector<string> > sorted;
    for(int i = 0; i < 26; i++)
    {
        vector<string> words = trie->all_words_that_start_with(char(i + 97));
        sorted.push_back(words);
    }
    ifstream test("test.txt");
    ifstream sol("solution.txt");
    string sl;
    while(1)
    {
        int correct = 0;
        int total = 0;
        while(getline(test, s, '\n'))
        {
            getline(sol, sl, '\n');
            int best = 100000;
            string best_string = "";
            int freq = 0;
            total++;
            // cout<<"Enter a word: ";
            // cin >> s;
            vector<string> words = sorted[s[0] - 97];
            if(trie->searchWord(s)) {
                //cout<<"In Dictionary: "<<s<<endl;
                correct++;
            }
            else
            {
                for(int i = 0; i < words.size(); i++)
                {
                    int dist = edit_distance(words[i], s, weights->weights);
                    if(dist < best)
                        best = dist;
                }

                for(int i = 0; i < words.size(); i++)
                {
                    int dist = edit_distance(words[i], s, weights->weights);
                    if(best == dist)
                    {
                        //cout<<words[i]<<"\t"<<dict[words[i]]<<endl;
                        if(dict[words[i]] > freq)
                        {
                            freq = dict[words[i]];
                            best_string = words[i];
                        }
                    }
                }
                if(best_string.compare(sl) == 0)
                {
                    //cout<<"Query: "<<s<<" Output: "<<best_string<<" Solution: "<<sl<<" Correct: YES"<<endl;
                    correct++;
                }
                else
                    cout<<"Query: "<<s<<" Output: "<<best_string<<" Solution: "<<sl<<" INCORRECT"<<endl;
            }
        }
        cout<<float(correct)/total<<endl;
        break;
    }
}
