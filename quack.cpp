/**
 * @file quack.cpp
 * Implementation of the Quack class.
 *
 */

template <class T>
Quack<T>::Quack() {
    n1 = 0; // index of leftmost element
}

/**
 * Adds the parameter object to the right of the Quack.
 *
 * @param newItem object to be added to the Quack.
 */
template <class T>
void Quack<T>::pushR(T newItem) {    
    data.push_back(newItem);
}

/**
 * Removes the object at the left of the Quack, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Quack.
 */
template <class T>
T Quack<T>::popL() {
    T popped_ele = data[n1];
    if (n1 >= (data.size()-1)/2) {
        vector<T> newVec(data.size() / 2);
        int x = 0;
        for (unsigned int i = n1 + 1; i < data.size(); i++) {
            newVec[x] = data[i];
            x++;
        }
        data.clear();
        for (unsigned int i = 0; i < newVec.size(); i++) {
            data.push_back(newVec[i]);
        }     
        n1 = 0;
    } else {
    
        n1 += 1;
    } 

    return popped_ele;
}
/**
 * Removes the object at the right of the Quack, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Quack.
 */
template <class T>
T Quack<T>::popR() {
    T popped_ele = data.back();
    if (n1 >= (int)((data.size()-1)/2)) {
        
        vector<T> newVec(data.size() / 2);
        int x = 0;
        for (unsigned int i = n1; i < data.size() - 1; i++) {
            newVec[x] = data[i];
            x++;
        }
        data.clear();
        for (unsigned int i = 0; i < newVec.size(); i++) {
            data.push_back(newVec[i]);
        }
        n1 = 0;
    } else {
        data.pop_back();
    } 

    return popped_ele;
}

/**
 * Finds the object at the left of the Quack, and returns it to the
 * caller. Unlike popL(), this operation does not alter the quack.
 *
 * @return The item at the front of the quack.
 */
template <class T>
T Quack<T>::peekL() {
    return data[n1];
}

/**
 * Finds the object at the right of the Quack, and returns it to the
 * caller. Unlike popR(), this operation does not alter the quack.
 *
 * @return the value of The item at the right of the quack.
 */
template <class T>
T Quack<T>::peekR() {
    return data[data.size() - 1];
}

/**
 * Determines if the Quack is empty.
 *
 * @return bool which is true if the Quack is empty, false otherwise.
 */
template <class T>
bool Quack<T>::isEmpty() const {
    return data.size() == 0;
}
