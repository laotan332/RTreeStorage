#include "r_tree.h"

template<class Storage, int Dismensions, 
         int MaxNodeCellNum, int HASHSIZE>
Rtree::Rtree() {

}

template<class Storage, int Dismensions, 
         int MaxNodeCellNum, int HASHSIZE>
RtreeNodeType* Rtree::NodeHashLookup(uint64_t i_ndoe) {
  uint32_t part_num = i_node % HASHSIZE; 
  HashIterator iter(&(hash_[part_num]));
  iter.Seek(i_node);
  if (iter.Valid()) {
    return iter.Key();
  }
  return nullptr;
}

template<class Storage, int Dismensions, 
         int MaxNodeCellNum, int HASHSIZE>
void Rtree::NodeHashInsert(RtreeNodeType *p_node) {
  uint32_t part_num = i_node % HASHSIZE; 

}

template<class Storage, int Dismensions, 
         int MaxNodeCellNum, int HASHSIZE>
void Rtree::NodeHashRemove(RtreeNodeType *p_node) {
  
}
