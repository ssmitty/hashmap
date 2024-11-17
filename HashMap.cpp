

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	mapSize = 1500; // or whatever size is needed
	numKeys=0;
	map = new hashNode*[mapSize];
	for (int i = 0; i < mapSize; i++) {
		map[i] = NULL;
	}
	hashfn=false;
	collfn=true;
	//collfn=collision2;
	collisions=0;
	hashcoll=0;

}
void hashMap::addKeyValue(string k, string v) {
	int x= getIndex(k);
	if (map[x]==NULL) {
		map[x]=new hashNode(k,v);
		numKeys++;
	}
	else{
		map[x]->addValue(v);

	}
	if(double(numKeys/mapSize)>.70) {
		reHash();
	}
}
int hashMap::getIndex(string k) {
	//return calcHash2(k);
    int h = calcHash2(k);
    int i = h;

    if (map[i] != NULL && map[i]->keyword != k) {
        i = coll1(h, i, k);
    }

    return i;
}


int hashMap::calcHash2(string k){
		unsigned long int h = 0;
		int L = k.length();
		for (int j = 0; j < L; j++) {
			h = (h*11 + ((int)k[L-j-1]));
		}

	return h% mapSize;
}
int hashMap::calcHash1(string k){
	return ((k[0] + (27 * k[1]) + (729 * k[2])) %mapSize);
}
void hashMap::getClosestPrime() {
}
void hashMap::reHash() {
	mapSize=2*mapSize;
	hashNode** newmap= new hashNode*[mapSize];
	for (int i = 0; i < mapSize; i++) {
		newmap[i] = NULL;
	}
	/*for (int i = 0; i < mapSize/2; i++) {
		if(map[i]!=NULL) {
			int x=getIndex(map[i]->keyword);
			newmap[x]=map[i];
		}
	}
delete [] map;
	map=newmap;*/
	for (int i = 0; i < mapSize / 2; i++) {
		if (map[i] != NULL) {
			int hash = calcHash2(map[i]->keyword);
			int index = hash % mapSize;

			// Linear probing to resolve any collisions in newmap
			while (newmap[index] != NULL) {
				index = (index + 1) % mapSize;
			}
			newmap[index] = map[i];
		}
	}

	delete[] map;
	map = newmap;
}
int hashMap::coll1(int h, int i, string k) {
	i=h%mapSize;
	int maximumcap=i;
	while(map[i]!=NULL) {
		if(map[i]->keyword==k) {
			return i;
		}
			i=(i+1)%mapSize;
		if (i==maximumcap) {
			break;
		}
		}
	return i;
	}

int hashMap::coll2(int h, int i, string k) {
	i=h%mapSize;
	int index=0;
	int maximumcap=i;
	while(map[maximumcap]!=NULL) {
		if(map[maximumcap]->keyword==k) {
			return maximumcap;
		}
		index++;
		maximumcap=(i+index*index)%mapSize;
		if (i==maximumcap) {
			break;
		}
	}
	return maximumcap;
}

void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


