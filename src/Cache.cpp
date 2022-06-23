#include <string>
#include <list>
#include <unordered_map>
#include <queue>
#include <cmath>
using namespace std;
#pragma once

// LRU Cache
class Cache
{
protected:								//sorry :(
	// Static meta-data
	int setcount;
	int blockcount;
	int blocksize;
	
	// Dynamic meta-data
	int hitcount;
	int accesscount;

public:
	//Default Constructor
	Cache() {}

	//Actual Constructor
	Cache(int sc, int bc, int bs)
	{
		setcount = sc;
		blockcount = bc;
		blocksize = bs;
		hitcount = 0;
		accesscount = 0;
	}

	virtual void Access(string& addy) {}

	// =====ACCESSORS===== //

	// Parameters:	None
	// Return:		INT number of total hits 
	int GetHitCount()
	{
		return hitcount;
	}

	// Parameters:	None
	// Return:		INT number of total accesses
	int GetAccessCount()
	{
		return accesscount;
	}

	// ======HELPERS====== //

	// Parameters:	STRING binary memory address
	// Return:		pair<INT set number index, STRING binary tag>
	pair<int, string> GetSetNumAndTag(string& addy)
	{
		int offsetwidth = log2(blocksize);
		int setwidth = log2(setcount);

		// Fully Associative
		if (setcount == 1)
			return { 0, addy.substr(0, addy.length() - offsetwidth) };

		// Direct Mapped & Set Associative
		string set = addy.substr(addy.length() - offsetwidth - setwidth, setwidth);
		string tag = addy.substr(0, addy.length() - offsetwidth - setwidth);
		return { BinaryToDecimal(set), tag };

	}


	// Parameters:	STRING binary value
	// Return:		INT decimal value
	int BinaryToDecimal(string binary)
	{
		int decimal = 0;
		for(int i = binary.length() - 1; i > -1; i--)
		{
			int digit = int(binary[i]);
			decimal += pow(2, i) * digit;
		}
		return decimal;
	}
};



class LRUCache : public Cache
{
	// Key: set number, Value: tags/block numbers
	unordered_map<int, list<string>> sets;

public:
	LRUCache() : Cache() {}

	LRUCache(int sc, int bc, int bs) : Cache(sc, bc, bs) {}

	// Parameters:	STRING binary memory address
	// Accesses memory stored in cache
	// Return:		None
	void Access(string& addy)
	{
		// Step 1: Grab tag and set number index from address
		pair<int, string> tokens = GetSetNumAndTag(addy);
		int setnum = tokens.first;
		string tag = tokens.second;

		// Step 2: Parse set for tag
		bool isHit = false;
		for (auto it = sets[setnum].begin(); it != sets[setnum].end(); ++it)
		{
			if (*it == tag)
			{
				isHit = true;
				break;
			}
		}

		// Step 3: Update dynamic meta-data 
		hitcount += (isHit) ? 1 : 0;
		accesscount++;

		// Step 4: Process hit with LRU method
		if (isHit)
		{
			// Step 4.1: Remove accessed tag and add it back at head
			sets[setnum].remove(tag);
			sets[setnum].push_front(tag);
			return;
		}

		// Step 5: Process miss with LRU method
			// Step 5.1: If no empty blocks, remove LRU at tail
		if (sets[setnum].size() >= blockcount)
			sets[setnum].pop_back();
		// Step 5.2: Add new tag at head
		sets[setnum].push_front(tag);
	}
};



class FIFOCache : public virtual Cache
{
	// Key: set number, Value: tags/block numbers
	unordered_map<int, vector<string>> sets;

public:
	FIFOCache() : Cache() {}

	FIFOCache(int sc, int bc, int bs) : Cache(sc, bc, bs) {}

	// Parameters:	STRING binary memory address
	// Accesses memory stored in cache
	// Return:		None
	void Access(string& addy)
	{
	// Step 1: Grab tag and set number index from address
		pair<int, string> tokens = GetSetNumAndTag(addy);
		int setnum = tokens.first;
		string tag = tokens.second;

	// Step 2: Parse set for tag
		bool isHit = false;
		for (auto it = sets[setnum].begin(); it != sets[setnum].end(); ++it)
		{
			if (*it == tag)
			{
				isHit = true;
				break;
			}
		}

	// Step 3: Update dynamic meta-data 
		hitcount += (isHit) ? 1 : 0;
		accesscount++;

	// Step 4: Process hit with FIFO method (aka do nothing)
		if (isHit)
			return;

	// Step 5: Process miss with LRU method
		// Step 5.1: If no empty blocks, remove first element of queue
		if (sets[setnum].size() >= blockcount)
			sets[setnum].erase(sets[setnum].begin());
		// Step 5.2: Add new tag at end of queue
		sets[setnum].push_back(tag);
	}
};
