#include <iostream>
#include <string>
#include <map>
#include <vector>

int main(int argc, char const *argv[])
{
	std::string str, str_code("0");
	std::map<char, int> map;
	std::map<char, std::string> map_code;

	std::cin >> str;
	auto it = map.end();
	for(auto index = str.begin(); index != str.end(); index++) {
		it = map.find(*index);

		//std::cout << *index <<std::endl;
		if(it != map.end()) {
			(it->second)++;
		}
		else {
			map[*index] = 1;
		}
	}

/*	for(auto &elem : map) {
		std::cout << 
					elem.first << " " <<
					elem.second << " " <<
		std::endl;
	}*/

	while(!map.empty()) {
		//std::cout << "while\n";
		int max = 0;
		auto it_max_map = map.end();
		for(it = map.begin(); it != map.end(); it++) {
			if(max < (*it).second) {
				max = (*it).second;
				it_max_map = it;
			}
		}
		map_code[(*it_max_map).first] = str_code;
		str_code.pop_back();
		str_code.push_back('1');
		str_code.push_back('0');
		//std::cout << "(*it_max_map).first = " << (*it_max_map).first << std::endl;
		map.erase(it_max_map);
		//std::cout << "while 3\n";
		if(map.size() == 1) {
			it_max_map = map.begin();
			str_code.pop_back();
			//str_code.push_back('1');
			map_code[(*it_max_map).first] = str_code;
			break;
		}
	}
	map.clear();
/*	for(auto &elem : map_code) {
		std::cout << 
					elem.first << ": " <<
					elem.second << " " <<
		std::endl;
	}*/

//std::cout << std::endl;
	long int size = 0;
	std::vector<std::string> res_vec;
	for(auto &elem : str) {
		res_vec.push_back(map_code[elem]);
		size += map_code[elem].size();
		///std::cout << map_code[elem] << std::endl;
	}


	std::cout << map_code.size() << " " << size << std::endl;
	for(auto &elem : map_code) {
		std::cout << 
					elem.first << ": " <<
					elem.second << " " <<
		std::endl;
	}
	for(auto &elem : res_vec) {
		std::cout << elem;
	}
std::cout << std::endl;
	return 0;
}


#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <queue>
#include <iterator>

using namespace std;

using HuffCode = typename std::vector<bool>;
using HuffCodeMap = typename std::map<char, HuffCode>;

class INode {
 public:
  const int f;

  virtual ~INode() {}

 protected:
  INode(int f) : f{f} {}
};

class InternalNode : public INode {
 public:
  INode * const left;
  INode * const right;

  InternalNode(INode *c0, INode *c1) : INode{c0->f + c1->f}, left{c0}, right{c1} {}
  InternalNode(INode *c) : INode{c->f}, left{c}, right{nullptr} {}

  ~InternalNode() {
    delete left;
    delete right;
  }
};

class LeafNode : public INode {
 public:
  const char c;

  LeafNode(int f, char c) : INode{f}, c{c} {}
};

struct NodeCmp {
  bool operator()(const INode* lhs, const INode* rhs) const { return lhs->f > rhs->f; }
};

INode* BuildTree(const map<char, int>& freq) {
  std::priority_queue<INode *, std::vector<INode *>, NodeCmp> trees;

  for (auto cit = freq.cbegin(); cit != freq.end(); ++cit) {
    trees.push(new LeafNode(cit->second, cit->first));
  }

  if (trees.size() == 1) {
    INode *childR = trees.top();
    trees.pop();

    INode *parent = new InternalNode(childR);
    trees.push(parent);
  }
  else {
    while (trees.size() > 1) {
      INode *childR = trees.top();
      trees.pop();

      INode *childL = trees.top();
      trees.pop();

      INode *parent = new InternalNode(childR, childL);
      trees.push(parent);
    }
  }

  return trees.top();
}

void GenerateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes) {
  if (const LeafNode *lf = dynamic_cast<const LeafNode *>(node)) {
    outCodes[lf->c] = prefix;
  }
  else if (const InternalNode *in = dynamic_cast<const InternalNode *>(node)) {
    HuffCode leftPrefix = prefix;
    leftPrefix.push_back(false);
    if (in->left) {
      GenerateCodes(in->left, leftPrefix, outCodes);
    }

    HuffCode rightPrefix = prefix;
    rightPrefix.push_back(true);
    if (in->right) {
      GenerateCodes(in->right, rightPrefix, outCodes);
    }
  }
}

map<char, int> count_freq(string& s) {
  map<char, int> freq_map;

  for (auto& c : s) {
    ++freq_map[c];
  }

  return freq_map;
}

int main() {
  string s;
  vector<bool> code_string;
  vector<bool> prefix;

  cin >> s;
  auto frequencies = count_freq(s);

  INode *root = BuildTree(frequencies);
  HuffCodeMap codes;
  GenerateCodes(root, prefix, codes);
  delete root;

  for (auto &i : s) {
      for (const auto &code : codes[i]) {
        code_string.push_back(code);
      }
  }

  cout << frequencies.size() << ' ' << code_string.size() << endl;
  for (auto cit = codes.cbegin(); cit != codes.cend(); ++cit) {
    std::cout << cit->first << ": ";
    std::copy(cit->second.begin(), cit->second.end(),
              std::ostream_iterator<bool>(std::cout));
    std::cout << std::endl;
  }
  for (int i = 0; i < code_string.size(); ++i) {
    cout << code_string[i];
  }
  cout << endl;

  return 0;
}
