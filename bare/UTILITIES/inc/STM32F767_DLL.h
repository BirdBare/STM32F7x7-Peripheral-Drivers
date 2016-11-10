//
//
//
//
//



#ifndef STM32F767_DLL_H
#define STM32F767_DLL_H

#include "BARE_STM32F767.h"
#include "STM32F767_BALLOC.h"
//#include "STM32F767_xxx.h"

struct DLL_Node 
{
  struct DLL_Node *next;
  struct DLL_Node *prev;
  void *data;
};
//Total 12 Bytes



//#define DLL_CreateListLinear(ListPointer, FirstNodeAddress) \
  struct DLL_Node *ListPointer = _DLL_MakeNodeLinear(FirstNodeAddress)

#define DLL_CreateList(ListPointer, FirstNodeAddress) \
  struct DLL_Node *ListPointer = FirstNodeAddress


//CREATE NODE FUNCTION
static struct DLL_Node* DLL_CreateNode(void *DataAddress)
{
  struct DLL_Node *NewNode = balloc(sizeof(struct DLL_Node));

  NewNode->data = DataAddress;
  NewNode->next = NewNode;
  NewNode->prev = NewNode;
  
  return NewNode;
}
//END CREATE NODE

/*//PRIVATE FUNCTIONS
ALWAYS_INLINE struct DLL_Node* _DLL_MakeNodeCircular(
  struct DLL_Node *NodeAddress)
{
  NodeAddress->next = NodeAddress;
  NodeAddress->prev = NodeAddress;
  return NodeAddress;
}
ALWAYS_INLINE struct DLL_Node* _DLL_MakeNodeLinear( 
  struct DLL_Node *NodeAddress)
{
  NodeAddress->next = 0;
  NodeAddress->prev = 0;
  return NodeAddress;
}
//END PRIVATE FUNCTIONS
*/

//ADD NODE FUNCTIONS
static void DLL_AddNodeBefore(void *ListNodeAddress, 
  void *NewNodeAddress)
{
  ((struct DLL_Node*)NewNodeAddress)->next = ListNodeAddress;
  ((struct DLL_Node*)NewNodeAddress)->prev = 
    ((struct DLL_Node *)ListNodeAddress)->prev;
  //NodeAddress pointers

  ((struct DLL_Node *)ListNodeAddress)->prev->next = NewNodeAddress;
  ((struct DLL_Node *)ListNodeAddress)->prev = NewNodeAddress;
  //HeadAddress prev changed
}


static void DLL_AddNodeAfter(void *ListNodeAddress, 
  void *NewNodeAddress)
{
  ((struct DLL_Node*)NewNodeAddress)->prev = ListNodeAddress;
  ((struct DLL_Node*)NewNodeAddress)->next = 
    ((struct DLL_Node *)ListNodeAddress)->next;
  //NodeAddress pointers

  ((struct DLL_Node *)ListNodeAddress)->next->prev = NewNodeAddress;
  ((struct DLL_Node *)ListNodeAddress)->next = NewNodeAddress;
  //HeadAddress prev changed
}
//END ADD FUNCTIONS

static void* DLL_RemoveNode(struct DLL_Node *NodeAddress)
{
  struct DLL_Node *next = NodeAddress->next; 
  struct DLL_Node *prev = NodeAddress->prev; 
  //place in variable to help compiler make it faster

  next->prev = prev;
  prev->next = next;
  //remove NodeAddress

  return NodeAddress->data;
}


#endif
