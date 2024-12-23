//Michael Murgia
//CDA 3100
//Assignment 10: Implementing an Instruction Cache Simulator
//Due date: 11/22/24
//compile:
//	step 1: "g++ -c assign10.cpp"
//	step 2: "g++ assign10.o -o test1"
// 	step 3: "./test1 < trace.dat > trace.stats"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Cache line representation
struct CacheLine {
	bool valid;
	unsigned int tag;
	int last_access_time;
	vector<bool> accessed_offsets;

	CacheLine(int line_size) : valid(false), tag(0), last_access_time(0), accessed_offsets(line_size / 4, false) {}
};

// Cache variables
int num_sets = 0;
int set_size = 0;
int line_size = 0;

vector<vector<CacheLine>> cache;

// Final result variables
int tot_hits = 0;
int tot_temp_hits = 0;
int tot_spat_hits = 0;
int tot_miss = 0;
int tot_acc = 0;

// Function to read the config file
void read_file(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open()) 
	{
		cerr << "Could not open file" << endl;
		exit(EXIT_FAILURE);
	}

	string temp;
	file >> temp >> temp >> temp >> num_sets;
	file >> temp >> temp >> set_size;
	file >> temp >> temp >> line_size;
	file.close();
}

// Function to simulate accessing a cache
void access_cache(unsigned int address, int ref_num)
{
	// log2 for both line size and numsets
	int offset_bits = __builtin_ctz(line_size);
	int index_bits = __builtin_ctz(num_sets);

	unsigned int index = (address >> offset_bits) & ((1 << index_bits) - 1);
	unsigned int tag = address >> (offset_bits + index_bits);
	int offset = (address & (line_size - 1));

	bool hit = false;
	bool temp_hit = false;
	CacheLine* lru_line = nullptr;

	for (auto& line : cache[index])
	{
		if (line.valid && line.tag == tag)
		{
			hit = true;
			if(line.accessed_offsets[offset])
			{
				temp_hit = true;
				tot_temp_hits++;
			} else {
				tot_spat_hits++;
			}
			
			line.accessed_offsets[offset] = true;
			line.last_access_time = ref_num;
			break;
		}

	// 	tracks lru
	//	if (!lru_line || line.last_access_time < lru_line->last_access_time)
	//		lru_line = &line;
	}

	if (hit)
	{
		tot_hits++;
		cout << setw(4) << ref_num << " " << setw(8) << hex << address << " " << setw(7) << tag << " " 
		<< setw(5) << dec << index << " " << setw(6) << offset << setw(13) << (temp_hit ? " temporal hit" : " spatial hit") << endl;

	} else {
		tot_miss++;

		//checks lru
		CacheLine* lru_line = &cache[index][0];
		for (auto& line : cache[index])
		{
			if (!line.valid)
			{
				lru_line = &line;
				break;
			}
			if (line.last_access_time < lru_line->last_access_time)
			{
				lru_line = &line;
			}
		}
		lru_line->valid = true;
		lru_line->tag = tag;
		lru_line->last_access_time = ref_num;

		//resets access
		fill(lru_line->accessed_offsets.begin(), lru_line->accessed_offsets.end(), false);
		lru_line->accessed_offsets[offset] = true;

		cout << setw(4) << ref_num << " " << setw(8) << hex << address << " " << setw(7) << tag << " "
		<< setw(5) << dec << index << " " << setw(6) << offset << setw(13) << " miss" << endl;
	}

	tot_acc++;
}


int main()
{
	read_file("trace.config");

	// Prints results
	cout << "Cache Configuration" << endl;
	cout << setw(4) << num_sets << " " << set_size << "-way set associative entries of line size " << line_size << " bytes" << endl;

	cache.resize(num_sets, vector<CacheLine>(set_size, CacheLine(line_size)));

	cout << "\n\nResults for Each Reference" << endl;
	cout << "\nRef  Address    Tag   Index Offset    Result" << endl;
	cout << "---- -------- ------- ----- ------ ------------" << endl;

	unsigned int address;
	int ref_num = 1;
	while (cin >> hex >> address)
	{
		if (address %4 != 0)
		{
			cerr << "Address " << hex << address << " is not 4-byte aligned" << endl;
			continue;
		}
		
		access_cache(address, ref_num);

		ref_num++;
	}

	cout << "\n\nSimulation Summary Statistics" << endl;
	cout << "-----------------------------" << endl;
	cout << "Total hits          : " << tot_hits << endl;
	cout << "Total temporal hits : " << tot_temp_hits << endl;
	cout << "Total spatial hits  : " << tot_spat_hits << endl;
	cout << "Total misses        : " << tot_miss << endl;
	cout << "Total accesses      : " << tot_acc << endl;
	cout << fixed << setprecision(6);
	cout << "Hit ratio           : " << (static_cast<float>(tot_hits) / tot_acc) << endl;
	cout << "Miss ratio          : " << (static_cast<float>(tot_miss) / tot_acc) << endl << endl;

	return 0;
}
