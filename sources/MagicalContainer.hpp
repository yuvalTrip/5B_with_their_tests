#include <iostream>
#include <vector>
#include <cmath>

namespace ariel {
// The class MagicalContainer contains
// three nested classes: AscendingIterator, SideCrossIterator, and PrimeIterator.
    class MagicalContainer {
    private:
        std::vector<int> elements; //A vector to store integer elements.
        std::vector<int> primeIndexIterator;//iterate over elements and save the index to a prime number
        std::vector<int>::size_type primeIndex=0;//Define index to prime numbers in elements vector
    public:
        int contains(int number) const
        {//checks if a given number is present in the container. Returns 0 if found, 1 otherwise.
            for (std::vector<int>::size_type i=0;i<elements.size();i++) {
                if (elements[i]==number){return 0;}
            }
            return 1;
        }

//Adds an element to the container, sorts the elements vector, and updates the primeIndexIterator.
        void addElement(int element) {
            elements.push_back(element);
            //Sort 'elements' vector
            std::sort(elements.begin(), elements.end());

            // Reset the primeIndexIterator
            primeIndexIterator.clear();
            //std::cout<<" N E W  A D D ********"<<std::endl;
            //For each element we will check if this is prime number
            for (std::vector<int>::size_type i = 0; i< elements.size(); i++) {
                // std::cout<<"primeIndex: "<<primeIndex<<std::endl;

                // Access each item in the elements vector
                if (PrimeIterator::isPrime(elements[i]))//if this is a prime number
                {
                    //   std::cout<<"i: "<<i<<std::endl;
                    // std::cout<<"elements[i]: "<<elements[i]<<std::endl;
                    // Store the index in primePointerIterator
                    primeIndexIterator.push_back(static_cast<std::vector<int>::value_type>(i));//change from just i because of an error in tidy
                }
                // Increase the prime index
                primeIndex++;
            }
        }
//removes an element from the container.
        void removeElement(int element) {
            //Check if element exist in the container
            if (contains(element)==1)
            {
                throw std::runtime_error("Element is not in the container!");
            }
            // Delete from general vector
            elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
        }

        std::vector<int>::size_type size() const {
            //Return the size of the elements vector
            return elements.size();
        }

        class AscendingIterator {
        private:
            MagicalContainer& container;//A reference to the MagicalContainer object.
            std::vector<int>::size_type index;//An index to keep track of the current position in the elements vector.

        public:
            //Constructor
            AscendingIterator(MagicalContainer& container) : container(container), index(0) {}
            //Copy Constructor:
            AscendingIterator(const AscendingIterator& other) : container(other.container), index(other.index) {}
            // Move Constructor
            AscendingIterator(AscendingIterator&& other) noexcept
                    : container(other.container), index(other.index) {
                other.index = 0;
            }//-added because of TIDY errors

            // Default Destructor
            ~AscendingIterator() = default;

            // move assignment operator-This assignment operator is used to perform a move operation instead of a copy.
            AscendingIterator& operator=(AscendingIterator&& other) noexcept{
                { //Case  if (&container != &other.container) handle in the next operator =

                    container = other.container;
                    index = other.index;
                    return *this;
                }
            }
            // Move Assignment Operator-added because of TIDY errors
            // This assignment operator is used to perform a deep copy of the object's state from one instance to another.
            AscendingIterator& operator=(const AscendingIterator& other)
            {
                if (&container != &other.container)
                {
                    throw std::runtime_error("this is not the same AscendingIterator !");
                }
                // if (this != &other) {
                container = other.container;
                index = other.index;
                // }
                return *this;
            }
//compare two iterators for equality.
            bool operator==(const AscendingIterator& other) const {
                return index == other.index;
            }

            bool operator!=(const AscendingIterator& other) const {
                return index != other.index;
            }
// compare two iterators for greater than and less than.
            bool operator>(const AscendingIterator& other) const {
                return index > other.index;
            }

            bool operator<(const AscendingIterator& other) const {
                return index < other.index;
            }
//dereference operator, returns the value at the current index in the elements vector.
            int operator*() const {
                return container.elements[index];
            }
// increment the iterator to the next position.
            AscendingIterator& operator++() {
                //  std::cout << "index: "<< index <<std::endl;
        //if we are out of bounds
                if (index>container.elements.size()-1)
                {
                    //std::cout << "FALL HERE ="<<std::endl;

                    throw std::runtime_error("Out of bounds!");
                }
                //else- we will increase the index by one
                ++index;
                //return the iterator
                return *this;
            }
//returns a new iterator pointing to the beginning of the container.
            AscendingIterator begin() {
                return AscendingIterator(container);
            }
//returns a new iterator pointing to the end of the container.
            AscendingIterator end() {
                AscendingIterator iter(container);
                iter.index = container.size();
                return iter;
            }
        };

        class SideCrossIterator {
        private:
            MagicalContainer& container;//a reference to the MagicalContainer object.
            std::vector<int>::size_type frontIndex;//an index to keep track of the current position in the front of the elements vector.
            std::vector<int>::size_type backIndex;//an index to keep track of the current position in the back of the elements vector.
            bool frontTurn;//a flag to indicate whether the iterator is currently iterating over the front or back of the elements vector.

        public:
            //Constructors
            SideCrossIterator(MagicalContainer& container)
                    : container(container), frontIndex(0), backIndex(container.size() - 1), frontTurn(true) {}
            //Copy constructor
            SideCrossIterator(const SideCrossIterator& other)
                    : container(other.container), frontIndex(other.frontIndex), backIndex(other.backIndex),
                      frontTurn(other.frontTurn) {}
            // Move Constructor-added because of TIDY errors
            SideCrossIterator(SideCrossIterator&& other) noexcept
                    : container(other.container), frontIndex(other.frontIndex), backIndex(other.backIndex),
            frontTurn(other.frontTurn) {
                other.frontIndex = 0;
                other.backIndex = 0;
            }
            // Default Destructor
            ~SideCrossIterator() = default;

            // Move Assignment Operator-added because of TIDY errors
            SideCrossIterator& operator=( SideCrossIterator&& other)noexcept {
                container = other.container;
                frontIndex = other.frontIndex;
                backIndex = other.backIndex;
                frontTurn = other.frontTurn;
                return *this;
            }
            // Move Assignment Operator-added because of TIDY errors
            SideCrossIterator& operator=(const SideCrossIterator& other)  {
                if (&container != &other.container)
                {
                    throw std::runtime_error("this is not the same SideCrossIterator !");
                }
//                if (this != &other) {
                container = other.container;
                frontIndex = other.frontIndex;
                backIndex = other.backIndex;
                frontTurn = other.frontTurn;
//                }
                return *this;
            }
            //compare two iterators for equality.
            bool operator==(const SideCrossIterator& other) const {
//                std::cout << "frontIndex ="<<frontIndex<<" other.frontIndex="<<other.frontIndex << " backIndex="<<backIndex<<" other.backIndex="<<other.backIndex<<std::endl;
                return frontIndex == other.frontIndex && backIndex == other.backIndex;

//                return frontIndex == other.frontIndex && backIndex == other.backIndex && frontTurn == other.frontTurn;

            }

            bool operator!=(const SideCrossIterator& other) const {
                return !(*this == other);
            }
//compare two iterators for greater than and less than.
            bool operator>(const SideCrossIterator& other) const {

                return (!(other<*this) && other!=*this );//using operator I have already implemented
            }

            bool operator<(const SideCrossIterator& other) const {
                return (frontIndex < other.frontIndex && backIndex < other.backIndex) ||
                       (frontIndex < other.frontIndex && other.frontTurn) ||
                       (frontTurn && backIndex < other.backIndex);
            }
//dereference operator, returns the value at the current index in the elements vector.
            std::vector<int>::value_type operator*() const {
                if (frontTurn) {
                    return container.elements[frontIndex];
                }
                return container.elements[backIndex];

            }
// increment the iterator to the next position.
            SideCrossIterator& operator++() {
//                    std::cout << "frontIndex ="<<frontIndex<<std::endl;
//                    std::cout << "backIndex ="<<backIndex<<std::endl;
//                    std::cout << "container.size ="<<container.size()<<std::endl;
//                    std::cout << "frontIndex = container.size()/2+container.size()%2 "<< container.size()/2+container.size()%2 <<std::endl;
//                    std::cout << "backIndex = container.size()/2-(1-container.size()%2) "<< container.size()/2-(1-container.size()%2) <<std::endl;
    // Check if the indices are out of bounds
                if(frontIndex == container.size()/2+container.size()%2 && backIndex == container.size()/2-(1-container.size()%2))
                {
                    throw std::runtime_error("Out of bounds!");
                }
                    // Increment or decrement the indices based on the current state
                    //This alternation allows the iterator to traverse the container in a side-to-cross pattern.
                if (frontTurn  ) {
                    ++frontIndex;

                } else {
                    --backIndex;

                }
                // Toggle the state of frontTurn to alternate between frontIndex and backIndex
                frontTurn = !frontTurn;
                // Return a reference to the updated iterator
                return *this;
            }
//returns a new iterator pointing to the beginning of the container.
            SideCrossIterator begin() {
                return SideCrossIterator(container);
            }
// returns a new iterator pointing to the end of the container.
            SideCrossIterator end() {
                SideCrossIterator iter(container);
                iter.frontIndex = container.size()/2+container.size()%2;
                iter.backIndex = container.size()/2-(1-container.size()%2);
                return iter;
            }
        };
        class PrimeIterator {
            MagicalContainer& container;//a reference to the MagicalContainer object.
            std::vector<int>::size_type index;//an index to keep track of the current position in the primeIndexIterator.

        public:
            static bool isPrime(int num) {
                if (num <= 1)
                {return false;}
                for (int i = 2; i <= std::sqrt(num); ++i) {
                    if (num % i == 0)
                    { return false;}
                }
                return true;
            }
            //Constructor
            PrimeIterator(MagicalContainer& container) : container(container), index(0) {
//                //print elemets array
//                for (std::vector<int>::size_type i=0;i<container.elements.size();i++) {
//                    std::cout << "elements[i]:" << container.elements[i]<<std::endl;  // 1 2 3 4 5 6
//                }
//                //print prime array
//                for (std::vector<int>::size_type i=0;i<container.primeIndexIterator.size();i++) {
//                    std::cout << "primeIndexIterator[i]:" << container.primeIndexIterator[i]<<std::endl;  // 1 2 3 4 5 6
//                }
            }
            //Copy constructor
            PrimeIterator(const PrimeIterator& other) : container(other.container), index(other.index) {}
            // Move Constructor-Added because of tidy errors
            PrimeIterator(PrimeIterator&& other) noexcept
                    : container(other.container), index(other.index) {
                other.index = 0;
            }
            // Default Destructor
            ~PrimeIterator() = default;

            // Move Assignment Operator-Added because of tidy errors
            PrimeIterator& operator=( PrimeIterator&& other) noexcept{
                container = other.container;
                index = other.index;
                return *this;
            }

            // Move Assignment Operator-Added because of tidy errors
            PrimeIterator& operator=(const PrimeIterator& other) {
                if (&container != &other.container)
                {
                    throw std::runtime_error("this is not the same PrimeIterator !");
                }
//                if (this != &other) {
                container = other.container;
                index = other.index;
//                }
                return *this;
            }

            int operator*() const {
                // std::cout<<"container.elements[index]: "<<container.elements[index]<<std::endl;

                // std::cout<<"[index]: "<<index<<std::endl;
                // std::cout<<"container.primeIndexIterator[index]: "<<container.primeIndexIterator[index]<<std::endl;
                // std::cout<<"container.primeIndexIterator[index]: "<<container.primeIndexIterator[index]<<std::endl;

                // std::cout<<"container.primeIndexIterator[index]: "<<container.primeIndexIterator[index]<<std::endl;
                std::vector<int>::size_type temp_indexPrime = static_cast<std::vector<int>::size_type>(container.primeIndexIterator[index]);
                // std::cout<<"[temp_indexPrime]: "<<temp_indexPrime<<std::endl;
                // std::cout<<"container.elements[temp_indexPrime********: "<<container.elements[temp_indexPrime]<<std::endl;
                return container.elements[temp_indexPrime];
            }
//            compare two iterators for greater than and less than.
            bool operator>(const PrimeIterator& other) const {
                return index > other.index;
            }

            bool operator<(const PrimeIterator& other) const {
                return index < other.index;
            }
//            compare two iterators for equality.
            bool operator==(const PrimeIterator& other) const {
                return index == other.index;
            }

            bool operator!=(const PrimeIterator& other) const {
                return index != other.index;
            }

            PrimeIterator& operator++() {
                // std::cout<<"im in operator ++ "<<std::endl;

                if (index >= container.primeIndexIterator.size()) {
                    throw std::runtime_error("Out of bounds!");
                }
                if (index < container.primeIndexIterator.size()) {
                    ++index;
                }
                //std::cout<<"[index++]: "<<index<<std::endl;
                // std::cout<<"[container.primeIndexIterator.size()]"<<container.primeIndexIterator.size()<<std::endl;
                return *this;//returns a reference to the updated AscendIterator object.
            }

            PrimeIterator begin() {
                PrimeIterator iter(container);
                //std::cout<<"[begin index]: "<<iter.index<<std::endl;
                return iter;
            }

            PrimeIterator end() {
                PrimeIterator iter(container);
                iter.index = container.primeIndexIterator.size();
                // std::cout<<"[end index]: "<<iter.index<<std::endl;
                return iter;
            }

        };

    };

}  // namespace ariel