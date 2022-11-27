#include <iostream>
#include <fstream>

/**
*   Name: Bemwa Malak
*   ID: 20200116
*   Name: Kevin Marco
*   ID: 20200401
**/

using namespace std;

class FloatArray{
    protected:
        int size_;
        float* array_;
    public:
        FloatArray(const int& size){
            size_ = size;
            array_ = new float[size_];
        }
    //Add method which adds an element to the end of the array
        virtual bool Add(const int& index, const float& element){
            array_[index] = element;
            return true;
        }
        friend ifstream& operator>>(ifstream& file, FloatArray& floatArray){
            int size = floatArray.size_;
            int indexOfArray = 0;        // indexOfArray is purpose to determine the subscript that we will put the entered element in
            for(int i = 0; i < size; i++){
                float element;
                file >> element;
                if(floatArray.Add(indexOfArray, element)){
                    indexOfArray++;
                }
            }
        }
        friend ofstream& operator<<(ofstream& file, const FloatArray& floatArray){
            file << floatArray.size_;
            file << '|';
            file << '\t';
            for(int i = 0; i < floatArray.size_; i++){
                file << floatArray.array_[i];
                file << '\t';
            }
            file << endl;
        }
        ~FloatArray(){
            delete[] array_;
        }

};

class SortedArray : public FloatArray{
    public:
        SortedArray(const int& size) : FloatArray(size){}
    // Add method which adds an element to right place of the array which make the array sorted  
        virtual bool Add(const int& index, const float& element) override{
            bool flag = false;      // flag purpose is to check the entered element is the first element in the whole array or not
            for(int i = index; i > 0; i--){
            // check the element that we want to add is small than the element of subscript [i] in the array or not
                if(element < array_[i-1]){
                    // Shifing the element to the right by 1 place 
                    array_[i] = array_[i-1];
                }else{
                    // Putting the element in the right place 
                    array_[i] = element;
                    flag = true;
                    break;
                }
            }
        // putting the first entered element to the first subscript in the array
            if(!flag){
                array_[0] = element;
            }
            return true;
        }
};

class FrontArray : public FloatArray{
    public:
        FrontArray(const int& size) : FloatArray(size){}
    // Add method which adds an element to the front of the array
        virtual bool Add(const int& index, const float& element) override{
            array_[size_ - index - 1] = element;
            return true;
        }
};

class PositiveArray : public SortedArray{
    public:
        PositiveArray(const int& size) : SortedArray(size){}
    // Add Method which adds the Positive elements in each order that the  array will be sorted
        virtual bool Add(const int& index, const float& element) override{
            static int numberOfElements = 0;    //Determine the number of Positive elements 
        // Checking the Number is positive or Not
            if(element > 0){
                SortedArray::Add(index, element);
                numberOfElements++;
            }else{
                size_--;
                return false;
            }
            // Reallocate the array to the size of entered positive numbers 
            if(numberOfElements == size_){
                float* tmp = new float[size_];
                for(int i = 0; i < size_; i++){
                    tmp[i] = array_[i];
                }
                delete[] array_;
                array_ = new float[size_];
                for(int i = 0; i < size_; i++){
                    array_[i] = tmp[i];
                }
                delete[] tmp;
                tmp = nullptr;
                numberOfElements = 0;
            }
            return true;
        }
};

class NegativeArray : public SortedArray{
    public:
    // Add Method which adds the Negative elements in each order that the  array will be sorted
        NegativeArray(const int& size) : SortedArray(size){}
        virtual bool Add(const int& index, const float& element) override{
            static int numberOfElements = 0;         // Determine the number of Negative elements
        // Checking the number is negative or not 
            if(element < 0){
                SortedArray::Add(index, element);
                numberOfElements++;
            }else{
                size_--;
                return false;
            }
            // Reallocate the array to the size of entered Negative numbers
            if(numberOfElements == size_){
                float* tmp = new float[size_];
                for(int i = 0; i < size_; i++){
                    tmp[i] = array_[i];
                }
                delete[] array_;
                array_ = new float[size_];
                for(int i = 0; i < size_; i++){
                    array_[i] = tmp[i];
                }
                delete[] tmp;
                tmp = nullptr;
                numberOfElements = 0;
            }
            return true;
        }
};


int main(){
    FloatArray* floatArrays[10];
    string inputFileName, outputFileName;
    cout << "Enter the name of the input file:" << endl;
    cin >> inputFileName;
    cout << "Enter the name of the output file:" << endl;
    cin >> outputFileName;
    ifstream inputFile(inputFileName.c_str());
    ofstream outputFile(outputFileName.c_str());
    for(int i = 0; i < 10; i++){
        string arrayType;
        int arraySize;
        inputFile >> arrayType >> arraySize;
    //Detrmine the type of the object that will be created 
        if(arrayType == "Array"){
            floatArrays[i] = new FloatArray(arraySize);
        }else if(arrayType == "Sorted"){
            floatArrays[i] = new SortedArray(arraySize);
        }else if(arrayType == "Front"){
            floatArrays[i] = new FrontArray(arraySize);
        }else if(arrayType == "Positive"){
            floatArrays[i] = new PositiveArray(arraySize);
        }else{
            floatArrays[i] = new NegativeArray(arraySize);
        }
    // Read the Data of the object from the file 
        inputFile >> *floatArrays[i];
    // Write the Data of the object to the file
        outputFile << *floatArrays[i];
    // Freeing Memory of created object
        delete floatArrays[i];
        floatArrays[i] = nullptr;
    }
    inputFile.close();
    outputFile.close();

    return 0;
}