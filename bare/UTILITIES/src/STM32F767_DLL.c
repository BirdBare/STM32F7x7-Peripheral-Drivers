#include "STM32F767_DLL.h"

//CREATE NODE FUNCTION
struct DLL_Node* DLL_CreateNode(void *DataAddress)
{
  struct DLL_Node *NewNode = balloc(sizeof(struct DLL_Node));

  NewNode->data = DataAddress;
  NewNode->next = NewNode;
  NewNode->prev = NewNode;
  
  return NewNode;
}

//ADD NODE FUNCTIONS
void* DLL_AddNodeBefore(void *NewNodeAddress, 
  void *ListNodeAddress)
{
  ((struct DLL_Node*)NewNodeAddress)->next = ListNodeAddress;
  ((struct DLL_Node*)NewNodeAddress)->prev = 
    ((struct DLL_Node *)ListNodeAddress)->prev;
  //NodeAddress pointers

  ((struct DLL_Node *)ListNodeAddress)->prev->next = NewNodeAddress;
  ((struct DLL_Node *)ListNodeAddress)->prev = NewNodeAddress;
  //HeadAddress prev changed

  return NewNodeAddress;
}


void* DLL_AddNodeAfter(void *NewNodeAddress, 
  void *ListNodeAddress)
{
  ((struct DLL_Node*)NewNodeAddress)->prev = ListNodeAddress;
  ((struct DLL_Node*)NewNodeAddress)->next = 
    ((struct DLL_Node *)ListNodeAddress)->next;
  //NodeAddress pointers

  ((struct DLL_Node *)ListNodeAddress)->next->prev = NewNodeAddress;
  ((struct DLL_Node *)ListNodeAddress)->next = NewNodeAddress;
  //HeadAddress prev changed

  return NewNodeAddress;
}
//END ADD FUNCTIONS

void* DLL_RemoveNode(struct DLL_Node *NodeAddress)
{
  struct DLL_Node *next = NodeAddress->next; 
  struct DLL_Node *prev = NodeAddress->prev; 
  //place in variable to help compiler make it faster

  next->prev = prev;
  prev->next = next;
  //remove NodeAddress

  return NodeAddress->data;
}




