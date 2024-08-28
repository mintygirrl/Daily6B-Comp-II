/**********************************************************************
Program: daily6B.c
Author: Fallon Weiss
Date: 2/9/24
Time spent: 4 and a half days.
Purpose: The purpose of this program is to create two linked lists
and insert numbers into them, then use a list_sum function to
reverse them, add them up digit by digit, and return the sum to a
new linked list, and print out the result.
***********************************************************************/

#include <stdlib.h>
#include <stdio.h>

typedef struct node Node;
struct node
{
    int data;
    Node* next;
};

void head_insert(Node** first, int number);
Node* list_sum(Node* first, Node* second);
Node* reverse_list(Node* head);
void print_list(Node* head);
void destroy_list(Node* head);

int main(int argc, char* argv[])
{
    //add up 189 and 11
    Node* head_1 = NULL;
    Node* head_2 = NULL;
    Node* head_sum = NULL;

    head_insert(&head_1, 9);
    head_insert(&head_1, 8);
    head_insert(&head_1, 1);

    head_insert(&head_2, 1);
    head_insert(&head_2, 1);
    head_insert(&head_2, 8);

    head_sum = list_sum(head_1, head_2);
    printf("The sum of ");
    print_list(head_1);
    printf(" + ");
    print_list(head_2);
    printf("\n");
    printf(" = ");
    print_list(head_sum);
    printf("\n");

    //clean up three lists
    destroy_list(head_1);
    head_1 = NULL;
    destroy_list(head_2);
    head_2 = NULL;
    destroy_list(head_sum);
    head_sum = NULL;
    return 0;
}

void head_insert(Node** first, int number)
{
    Node* temp;
    temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL)
    {
        return;
    }
    temp->data = number;
    temp->next = *first;
    *first = temp;
}

Node* reverse_list(Node* head)
{
    Node* next = head->next;
    Node* prev = NULL;

    while (next != NULL)
    {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    return prev;
}

Node* list_sum(Node* first, Node* second)
{
    int num1;
    int num2;
    int sums;
    int hold;
    hold = 0;
    sums = 0;
  
    Node* temp = NULL;
    Node* firsthead;
    Node* secondhead;

    first = reverse_list(first);
    second = reverse_list(second);

    firsthead = first;
    secondhead = second;



    while (first != NULL || second != NULL)
    {
        if (first != NULL)
        {
            num1 = first->data;
            first = first->next;
        }
        else
        {
            num1 = 0;
        }

        if (second != NULL)
        {
            num2 = second->data;
            second = second->next;
        }
        else
        {
            num2 = 0;
        }
        sums = num1 + num2 + hold;
        hold = sums / 10;
        sums = sums % 10;
        head_insert(&temp, sums);
    }

    if (hold > 0)  // If there's a carry left after the loop
    {
        head_insert(&temp, hold);
    }
    
    first = reverse_list(firsthead);
    second = reverse_list(secondhead);

    return temp;

}

void print_list(Node* head)
{
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
}

void destroy_list(Node* head)
{
    Node* current;
    Node* next;
    current = head;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}