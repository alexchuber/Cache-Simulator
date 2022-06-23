#pragma once
#include "Cache.cpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

class CacheSimulator
{
public:
	Cache* cache;
	ifstream infile;

    //Constructor
    CacheSimulator(string file, int sc, int bc, int bs, string rp)
    {
        if (rp == "LRU")
            cache = new LRUCache(sc, bc, bs);
        else
            cache = new FIFOCache(sc, bc, bs);

	    infile.open(file);

        int i = 0;
	    string line;
	    while (getline(infile, line) && i < 10000)
	    {
            string address = ParseLine(line);
            cache->Access(address);
            i++;
	    }
    }

    //Destructor
    ~CacheSimulator()
    {
	    infile.close();
    }

    // Parameters:  None
    // Return:      pair<INT number of total hits, INT number of otal accesses>
    pair<int, int> GetSummaryStats()
    {
        return { cache->GetHitCount(), cache->GetAccessCount() };
    }
    
    // Parameters:  STRING line of .trace file
    // Return:      STRING binary memory address to be accessed
    string ParseLine(string line)
    {
	    stringstream ss(line);
	    string token;

	    getline(ss, token, ' '); // first: don't care
	    getline(ss, token, ' '); // second: memory address!
							     // third: don't care, don't read
	    return HexToBinary(token);
    }

    // Parameters:  STRING hex representation
    // Return:      STRING binary representation of given hex
    string HexToBinary(string hex)
    {
        cout << "Accessing address " << hex;
	    //Remove 0x from beginning
	    hex = hex.substr(2, hex.length()-2);

	    //Convert each character of remaining string
        string binary = "";
	    int i = 0;
	    while (hex[i])
	    {
		    switch (hex[i])
		    {
                case '0':
                    binary += "0000";
                    break;
                case '1':
                    binary += "0001";
                    break;
                case '2':
                    binary += "0010";
                    break;
                case '3':
                    binary += "0011";
                    break;
                case '4':
                    binary += "0100";
                    break;
                case '5':
                    binary += "0101";
                    break;
                case '6':
                    binary += "0110";
                    break;
                case '7':
                    binary += "0111";
                    break;
                case '8':
                    binary += "1000";
                    break;
                case '9':
                    binary += "1001";
                    break;
                case 'A':
                case 'a':
                    binary += "1010";
                    break;
                case 'B':
                case 'b':
                    binary += "1011";
                    break;
                case 'C':
                case 'c':
                    binary += "1100";
                    break;
                case 'D':
                case 'd':
                    binary += "1101";
                    break;
                case 'E':
                case 'e':
                    binary += "1110";
                    break;
                case 'F':
                case 'f':
                    binary += "1111";
                    break;
		    }
		    i++;
	    }

        cout << " as -->  " << binary << endl;
        return binary;
    }
	
};
