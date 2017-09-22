#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main(int argc, const char * argv[])
{
    bool findArg = false, findC = false, findW = false;
    istream* input;
    ifstream infile;
    string filename;
    string line, word, ch,findWord, findCharacter;
    char  letter, findChar;
    int totalChar = 0, totalWord = 0, totalLine = 0, wordLength=0, searchLength=0;
    int wordCounter=0, charCounter=0;
    
    
    for (int i = 1; i < argc; i++)
    {
        string name = argv[1];
        
        // Checks to see if it starts with a dash
        if (name[0] == '-')
        {
            //If it the arguement has "find"
            findArg = true;
            
            if(name.find("find") != string::npos )
                
                //FindChar
                if(name.find("findchar=") != string::npos && name.length() == 11)
                {
                    
                    findC = true;
                    findChar = name[11];
                    return 0;
                }
            
                //FindWord
                else if(name.find("-findword=") != string::npos )
                {
                    return 0;
                }
                else
                {
                    cout << "Argument "<< name  << " is poorly formed" << endl;
                    return 0;
                }
            
            else
            {
                cout << "Argument "<< name  << " is not recognized" << endl;
                return 0;
            }
        }
    
        
        else
        {
            int charCount = 0, wordCount =0 , lineCount = 0, lineCount2=0;
            int findlineCount = 0, findwordCount = 0;
            infile.open(argv[i]);
            
            if(infile.is_open() == false)
            {
                input = &cin;
                cout << "File " << argv[i] << " is not found" << endl;
                return -1;
            }
            
            else
            {
                
                input = &infile;
                filename = argv[i];
                
                if(input == 0)
                {
                    input = &cin;
                    filename = "stdin";
                }
               
                //Count line
                while(getline(*input, line))
                {
                    //recall -findchar
                    if(findArg == true && findC == true)
                    {
                        while(input->get(letter))
                        {
                            if(letter == findChar)
                                charCounter++;
                        }
                        findlineCount++;
                        
                    }
                    if(findArg == true && findW == true)
                    {
                        
                    }
                    
                    lineCount++;
                    lineCount2++;
                    
                }
                input->clear();
                input->seekg(0,input->beg);
                
                //Count Words
                while(*input >> word){
                    wordCount++;
                    //Recall -findchar
                    if(findArg == true && findC == true)
                    {
                        if(word.find(findCharacter) != string::npos )
                            findwordCount++;
                    }
                }
                
                input->clear();
                input->seekg(0,input->beg);
                //Count Characters
                while(getline(*input, ch))
                    charCount+=ch.length();
                input->clear();
                input->seekg(0,input->beg);
                
                charCount += lineCount2;
                
                totalLine += lineCount;
                totalWord += wordCount;
                totalChar += charCount;
                
                if(findC == true)
                    cout << findChar << ":" << setw(12) << findlineCount << setw(12) << findwordCount << setw(12) << charCounter << setw(10) << filename << endl;
                cout << setw(12) << lineCount << setw(12) << wordCount << setw(12) << charCount << setw(10) << filename << endl;
                
                infile.close();
            }
        }
    }
    
    //Standard Input
    if(argc == 1)
    {
        int charCount = 0, wordCount =0 , lineCount = 0, lineCount2=0, empty =0;
        input=&cin;
        
        while(getline(*input, ch))
        {
            lineCount++;
            lineCount2++;
            charCount+=ch.length();
            
            if(ch.empty())
                empty++;
            for(int a =0; a< ch.length(); a++)
            {
                if(isspace(ch[a]))
                    wordCount++;
            }
            
        }
        charCount += lineCount2;
        wordCount += lineCount2;
        wordCount -= empty;
        
        cout << setw(12) << lineCount << setw(12) << wordCount << setw(12) << charCount << " " << endl;
    }
    
    //Outputs totalCounts for mutliple Files
    if(argc > 2 && findArg == false)
        cout << setw(12) << totalLine << setw(12) << totalWord << setw(12) << totalChar << setw(6) << " totals" << endl;
    
    return 0;
}
