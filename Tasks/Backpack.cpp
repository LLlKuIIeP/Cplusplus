#include <iostream>
#include <list>
#include <vector>
#include <iomanip>

using List_Vector = std::list<std::vector<double> >;

List_Vector::iterator find_max(List_Vector &list_vector) {
    double max = 0;
    auto iter = list_vector.begin();
    for(auto it = list_vector.begin(); it != list_vector.end(); it++) {
        if((*it)[2] > max) {
            max = (*it)[2];
            iter = it;
        }
    }
    return iter;
}



int main()
{
    double n, W, c, w;
    std::cin >> n >> W;
    List_Vector list_vector(n);
    
    for(auto &elem : list_vector) {
        std::cin >> c >> w;
        elem.push_back(c);
        elem.push_back(w);
        elem.push_back(c/w);
    }
    /*
    for(auto &elem : list_vector) {
        std::cout <<
                    elem[0] << " " <<
                    elem[1] << " " <<
                    elem[2] <<
        std::endl;
    }
    */
    double count_c = 0;
    double weight_w = 0;
    double weight = 0;
    /*
    double max = 0;
    auto iter = list_vector.begin();
    for(auto it = list_vector.begin(); it != list_vector.end(); it++) {
        if((*it)[2] > max) {
            max = (*it)[2];
            iter = it;
        }
    }
    */
    while(!list_vector.empty()) {
        auto iter = find_max(list_vector);
        
        //std::cout << (*iter)[2] << std::endl;
        
        weight = (*iter)[1];
        if(weight_w + weight <= W) {
            weight_w += weight;
            count_c += (*iter)[0];
            list_vector.erase(iter);
        }
        else {
            double delta = (W - weight_w) / weight;
            count_c += (*iter)[0] * delta;
            break;
        }
    }
    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(3) << count_c << std::endl;
    /*
    for(auto &elem : list_vector) {
        std::cout <<
                    elem[0] << " " <<
                    elem[1] << " " <<
                    elem[2] <<
        std::endl;
    }
    */
   // = {1, 2, 3};
    
   /* 
   for(auto i = 0; i < n; i++) {
        std::vector<double> v = {1+i, 2+i, 3+i};
        list_vector.push_back(v); 
    }
    
    for(auto &elem : list) {
        //std::cout << elem << " " << elem << " " << elem << std::endl;
    }
    
    for(auto i = list_vector.begin(); i != list_vector.end(); i++) {
        std::cout << (*i)[0] << " " << (*i)[1] << " " << (*i)[2] << std::endl;
    }
    
    list_vector.erase(list_vector.begin());
    for(auto i = list_vector.begin(); i != list_vector.end(); i++) {
        std::cout << (*i)[0] << " " << (*i)[1] << " " << (*i)[2] << std::endl;
    }
    */
    return 0;
}


/*#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

struct Item final {
  int weight;
  int value;
};

double get_max_knapsack_value(int capacity, std::vector <Item> items) {
  double value = 0.0;

  // take items while there is empty space in knapsack
  for (auto &item:items) {
    if (capacity > item.weight) {
      // can take full item and continue
      capacity -= item.weight;
      value += item.value;
    } else {
      value += item.value * (static_cast <double>(capacity) / item.weight);
      break;
    }
  }

  return value;
}

int main(void) {
  int number_of_items;
  int knapsack_capacity;
  std::cin >> number_of_items >> knapsack_capacity;
  std::vector <Item> items(number_of_items);
  for (int i = 0; i < number_of_items; i++) {
    std::cin >> items[i].value >> items[i].weight;
  }

  double max_knapsack_value = get_max_knapsack_value(knapsack_capacity, std::move(items));

  std::cout.precision(10);
  std::cout << max_knapsack_value << std::endl;
  return 0;
}*/
