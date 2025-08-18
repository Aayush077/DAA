/*
Define a struct person as follows:
struct person
{
       int id;
       char *name;
       int age;
       int height;
       int weight;
};

Write a menu driven program to read the data of ‘n’ students from a file and store them in a dynamically allocated array of struct person. Implement the min-heap or max-heap and its operations based on the menu options.

Sample Input/Output:

MAIN MENU (HEAP)

1. Read Data
2. Create a Min-heap based on the age
3. Create a Max-heap based on the weight
4. Display weight of the youngest person
5. Insert a new person into the Min-heap
6. Delete the oldest person
7. Exit

 

Enter option: 1

Id         Name                          Age   Height      Weight(pound)

0          Adarsh Hota                39        77                    231

1          Levi Maier                  56        77                    129

2          Priya Kumari              63        78                    240

3          Dorothy Helton           47        72                    229

4          Florence Smith           24        75                    171

5          Erica Anyan                38        73                    102

6          Norma Webster          23        75                    145

 

Enter option: 4

Weight of youngest student: 65.77 kg

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight; // in pounds
};

// ---------- Swap ----------
void swap(struct person *a, struct person *b)
{
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

// ---------- Min-heapify (by age) ----------
void minHeapify(struct person heap[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].age < heap[smallest].age)
        smallest = left;
    if (right < n && heap[right].age < heap[smallest].age)
        smallest = right;

    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

// ---------- Max-heapify (by weight) ----------
void maxHeapify(struct person heap[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].weight > heap[largest].weight)
        largest = left;
    if (right < n && heap[right].weight > heap[largest].weight)
        largest = right;

    if (largest != i)
    {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, n, largest);
    }
}

// ---------- Build Min-heap ----------
void buildMinHeap(struct person heap[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(heap, n, i);
}

// ---------- Build Max-heap ----------
void buildMaxHeap(struct person heap[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(heap, n, i);
}

// ---------- Insert new person into Min-heap ----------
void insertMinHeap(struct person heap[], int *n, struct person p)
{
    int i = (*n)++;
    heap[i] = p;

    while (i != 0 && heap[(i - 1) / 2].age > heap[i].age)
    {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// ---------- Delete oldest person (max age) ----------
void deleteOldest(struct person heap[], int *n)
{
    if (*n == 0)
    {
        printf("Heap is empty.\n");
        return;
    }

    int idx = 0;
    for (int i = 1; i < *n; i++)
    {
        if (heap[i].age > heap[idx].age)
            idx = i;
    }

    printf("Deleted oldest person: %s (Age: %d)\n", heap[idx].name, heap[idx].age);

    heap[idx] = heap[--(*n)];
    buildMinHeap(heap, *n);
}

// ---------- Display youngest student’s weight ----------
void display_YWeight(struct person *students, int n)
{
    if (n == 0)
    {
        printf("Heap is empty!\n");
        return;
    }

    int minAge = students[0].age;
    int weight = students[0].weight;

    for (int i = 1; i < n; i++)
    {
        if (students[i].age < minAge)
        {
            minAge = students[i].age;
            weight = students[i].weight;
        }
    }

    printf("Weight of youngest student: %.2f kg\n", weight * 0.453592);
}

// ---------- Read Data from file ----------
struct person *readData(const char *filename, int *n)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: File not found.\n");
        *n = 0;
        return NULL;
    }

    fscanf(fp, "%d", n);
    struct person *students = (struct person *)malloc((*n) * sizeof(struct person));

    for (int i = 0; i < *n; i++)
    {
        students[i].name = (char *)malloc(50 * sizeof(char));
        fscanf(fp, "%d %s %d %d %d", &students[i].id, students[i].name,
               &students[i].age, &students[i].height, &students[i].weight);
    }

    fclose(fp);

    printf("\nId\tName\t\tAge\tHeight\tWeight(pound)\n");
    for (int i = 0; i < *n; i++)
    {
        printf("%d\t%-15s\t%d\t%d\t%d\n", students[i].id, students[i].name,
               students[i].age, students[i].height, students[i].weight);
    }

    return students;
}

int main()
{
    struct person *students = NULL;
    struct person *minHeap = NULL, *maxHeap = NULL;
    int n = 0, minSize = 0, maxSize = 0;
    int choice;

    while (1)
    {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");

        printf("\nEnter option: ");
        scanf("%d", &choice);

        if (choice == 7)
            break;

        switch (choice)
        {
        case 1:
            students = readData("students.txt", &n);
            break;

        case 2:
            if (students)
            {
                minHeap = (struct person *)malloc(n * sizeof(struct person));
                for (int i = 0; i < n; i++)
                    minHeap[i] = students[i];
                minSize = n;
                buildMinHeap(minHeap, minSize);
                printf("Min-heap created based on age.\n");
            }
            else
                printf("Load data first!\n");
            break;

        case 3:
            if (students)
            {
                maxHeap = (struct person *)malloc(n * sizeof(struct person));
                for (int i = 0; i < n; i++)
                    maxHeap[i] = students[i];
                maxSize = n;
                buildMaxHeap(maxHeap, maxSize);
                printf("Max-heap created based on weight.\n");
            }
            else
                printf("Load data first!\n");
            break;

        case 4:
            if (minHeap)
                display_YWeight(minHeap, minSize);
            else
                printf("Create Min-heap first!\n");
            break;

        case 5:
        {
            struct person newP;
            newP.name = (char *)malloc(50 * sizeof(char));
            printf("Enter Id Name Age Height Weight: ");
            scanf("%d %s %d %d %d", &newP.id, newP.name,
                  &newP.age, &newP.height, &newP.weight);

            minHeap = (struct person *)realloc(minHeap, (minSize + 1) * sizeof(struct person));
            insertMinHeap(minHeap, &minSize, newP);
            printf("Inserted new person into Min-heap.\n");
            break;
        }

        case 6:
            if (minHeap)
                deleteOldest(minHeap, &minSize);
            else
                printf("Create Min-heap first!\n");
            break;

        default:
            printf("Invalid option!\n");
        }
    }

    return 0;
}
