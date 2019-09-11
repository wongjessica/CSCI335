// Jessica Wong | CSCI 335 | September 10th, 2019
// The class Chain will store a certain number of numbers in the user inputted order. 
// It can be any size. 
// This is an implementation of Chain class using a dynamic array.

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_

#include <iostream>
#include <cstddef>
#include <sstream>
#include <string>

namespace teaching_project {

template<typename Object>

class Chain 
{
public:
  // Zero-parameter constructor.
  Chain() : size_(0), array_(nullptr) {};

  // Copy-constructor.
  Chain(const Chain &rhs) : size_(rhs.size_), array_(new Object[rhs.size_]) {
    for(size_t i = 0; i < rhs.size_; ++i) {
      array_[i] = Object(rhs.array_[i]);
    }
  };

  // Copy-assignment
  Chain& operator=(const Chain &rhs) {
    Chain copy = rhs; 
    std::swap(*this, copy);
    return *this;
  };

  // Move-constructor. 
    Chain(Chain &&rhs) : size_{rhs.size_}, array_{rhs.array_} {
      rhs.size_ = 0;
      rhs.array_ = nullptr;
      delete[] rhs.array_;
  }

  // Move-assignment.
    Chain &operator=(Chain &&rhs) {
      std::swap(size_, rhs.size_);
      std::swap(array_, rhs.array_);
      rhs.size_ = 0;
      delete[] rhs.array_;
      rhs.array_ = nullptr;
      return *this;
  }

  ~Chain() {  
    delete [] array_;
    array_ = nullptr;   
    size_ = 0;
  }

  // End of big-five.

  // One parameter constructor.
  Chain(const Object& item) {
    array_ = new Object(item);
    size_ = 1;
  }

  // Read a chain from standard input.
  void ReadChain() {
    std::string line; 
    std::getline (std::cin, line); //reads a chain of type string from a standard input

    line = line.substr(1,line.size()-2); //disregards the opening and closing brackets [] from the string
    std::stringstream str_stream(line);  

    std::string chain_size;
    std::getline(str_stream, chain_size,':');  
    size_t c_size;
    std::stringstream size_converter(chain_size); //concerts the first character into the size
    size_converter >> c_size;
    size_ = c_size;

    array_ = new Object [size_];  

    for (size_t i = 0; i < size_; i++) {
      str_stream >> array_[i]; //input is read from string->array
    }
  }

  // @param No Parameters
  // @return the Size of the chain
  size_t size() const { 
    return size_; //returns size of the chain
  }

  // @location: an index to a location in the chain.
  // @returns the Object at @location.
  // const version.
  // abort() if out-of-range.
  const Object& operator[](size_t location) const{ 
    if(location > size_-1) {
       abort();
     }
     return *(array_[location]);
  }

   // @location: an index to a location in the range.
   // @returns the Object at @location.
   // non-const version.
   // abort() if out-of-range.
   Object& operator[](size_t location) { 
    if (location < 0 && location > size_-1) {
      abort();
    }
    return array_[location];
   }

   //  @c1: A chain.
   //  @c2: A second chain.
   //  @return the concatenation of the two chains.
  friend Chain operator+(const Chain &c1, const Chain &c2) {
    Chain temp_object; //new object to store values from the Chain parameters c1 and c2

    temp_object.size_ = c1.size() + c2.size();

    temp_object.array_ = new Object[temp_object.size()];   

    for (size_t i = 0; i < temp_object.size(); i++) {
      if (i < c1.size()) {
        temp_object.array_[i] = c1.array_[i]; //c1 items added to the temp_object
      }
      else {
        temp_object.array_[i] = c2.array_[i-c2.size()+1]; 
      }
    }
    return temp_object;
  }

  //  @a_chain: A chain.
  //  @obj: New element.
  //  @return A chain with a new element added to the end.
  friend Chain operator+(const Chain &a_chain, const Object & obj) {
    Chain temp_object; 
    temp_object.size_ = a_chain.size_ + 1; //increases the size of the array by 1
    temp_object.array_ = new Object [temp_object.size_];

    for (size_t i = 0; i < a_chain.size_; i++)
      temp_object.array_[i] = a_chain.array_[i];

    temp_object.array_[temp_object.size_-1] = obj; 

    return temp_object;
  }
  
  // Overloading the << operator.
  friend std::ostream &operator<<(std::ostream &out, const Chain &a_chain) {
    out << "[";

    for (size_t i = 0; i < a_chain.size();i++)
    {
      if (i != a_chain.size()-1)
        out << a_chain.array_[i] << " "; 
      else
        out << a_chain.array_[i];
    }
    out << "]" << std::endl;

    return out;
  }
  
private:  
  size_t size_;    
  Object *array_;   
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_CHAIN_