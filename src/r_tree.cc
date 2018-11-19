#include "r_tree.h"

template<class Storage, int Dismensions, 
         int MaxNodeCellNum, int HASHSIZE>
void Rtree::Search(const RtreeCell &cell) {
  RtreeNodeType *p_leaf = nullptr;
  
  // 获取对应的根节点
  int hash_index = Hash(cell);
  RtreeNodeType *p_root = GetRootNode(hash_index);
  if (p_root = nullptr) {
    return;  
  } 

  // 找到对应的叶子结点
  FindLeaf(p_root, cell, &p_leaf);
}

template<class Storage, int Dismensions, 
         int MaxNodeCellNum, int HASHSIZE>
void Rtree::Insert(const RtreeCell &cell) {
  RtreeNodeType *p_leaf = nullptr;

  // 先哈希看看落在那个桶里
  int hash_index = Hash(cell);  
  RtreeNodeType *p_root = nullptr;

  NodeAcquire(&p_root);
  if (p_root = nullptr) {
    std::string root_key = GenRootKey(hash_index); 
    std::string value;
    if (db_.GetNodeValue(root_key, value)) {
      do {
        p_root = new RtreeNodeType;
        // 反序列化失败, 可能是数据出了问题
        // 可以从下层恢复，这里暂时不处理
        if (Deserialize2Node(value, p_root)) {
          // 插入到内存中去
          NodeHashInsert(p_root);
          break;
        }
        delete p_root;
      } while (0);
    } else {
      // 根节点本身为空
      p_root = new RtreeNodeType;
      

      NodeHashInsert(p_root);
    } 
  }

  // 当根节点不为空时，选择一个合适的叶子结点进行插入
  ChooseLeaf(p_root, cell, &p_leaf); 
  
  if (p_leaf) {
    // 是否需要分裂
    int s_node_num = DecodeInt32(p_leaf->z_data); 
  }
}




































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
