#include <iostream>
#include "filter.h"

double Filter::value(){
    double sum = 0;
    for(std::deque<double>::iterator it = nums.begin(); it != nums.end(); ++it){
        sum += *it;
    }
    return sum/(double)nums.size();
}

void Filter::update(){
    if(channel("link").nonempty()){
        nums.push_back(channel("link").latest());
        if(nums.size() > 10) nums.pop_front();
    }
}

