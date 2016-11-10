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
//  struct DLL_Node *ListPointer = _DLL_MakeNodeLinear(FirstNodeAddress)

#define DLL_CreateList(ListPointer, FirstNodeAddress) \
  struct DLL_Node *ListPointer = FirstNodeAddress



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


#endif
