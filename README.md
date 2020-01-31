# Binary Search

After exploring all the sorting algorithms, now it's time to look for some advantage that is worth all the work done. Sorting things out, giving an index or another way to classify the elements makes it easier to search for one of them. When the elements of our set are sorted this allows us to implement the logic of the binary search algorithm. First, we need to take an element from the list to make a comparison, to simplify the steps, we could use some parameter to choose that element. I chose to use the mean value **(firstIndex + finalIndex)/2**, among the positions within the matrix. If the element in the average index, array[average], is what we are looking for, the algorithm stops and delivers the element as a result. If it doesn't, we need to keep investigating, as we already knew, the array is ​​classified, so we can predict the region of the array that is likely to be our element. We need to evaluate the input value (x) with the mean value, if the mean value is greater than x, x must be to the left of the mean position, otherwise, if the mean value is less than the input value, x must be to the right of the mean position.

After obtaining one of these information, we need to repeat the steps above, recursively or not, until we find the desired value. In each loop, we divide the search space in half, so that the time complexity of this algorithm is **O(logn)**.

Analysing the algorithms output, we can see an excelent performance, taking millionth of seconds to accomplish the search.
