#include <iostream>
#include <stack>
using namespace std;

void merge(int* arr, int l, int m, int r){
    int i, j, k;
    int n1 = m-l+1, n2 = r-m;
    int L[n1], R[n2];

    for (i=0; i<n1; i++)
        L[i] = arr[l+i];
    for(j=0; j<n2; j++)
        R[j] = arr[m+1+j];

    i=0;
    j=0;
    k=l;
    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    //Copy remaining elements
    while(i < n1)
        arr[k++] = L[i++];
    while(j < n2)
        arr[k++] = R[j++];
}


class Node{
public:
    int st{}, m{}, end{};
    bool function{};//0->sort, 1->merge
    Node()= default;
    Node(int st, int m, int end, bool func)
    {
        this->st = st;
        this->m = m;
        this->end = end;
        this->function = func;
    }
};


void mergeSortStack(int arr[], int size)
{

    Node first(0, (size/2)-1, size-1, false);

    stack<Node> myStack;
    myStack.push(first);

    while(!myStack.empty()){
        Node node;
        node = myStack.top();
        myStack.pop();
        int baseCondition = node.end - node.st;
        if(baseCondition == 0)
            continue;
        if(node.function)
            merge(arr, node.st, node.m, node.end);
        else{
            Node mergeNode(node.st, node.m, node.end, true);
            myStack.push(mergeNode);
            Node rightMergeSort(node.m+1, (node.m+1+node.end)/2, node.end, false);
            myStack.push(rightMergeSort);
            Node leftMergeSort(node.st, (node.st+node.m)/2, node.m, false);
            myStack.push(leftMergeSort);
        }
    }
}



int main()
{
    int arr[] = {7,8,6,5,4,1};
    int size = sizeof(arr) / sizeof(arr[0]);
    mergeSortStack(arr, size);

    //Print the sorted array
    for (int i=0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}

