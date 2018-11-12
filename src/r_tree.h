#pragma once

namespace ssq {
/**
* @NodeSize 单节点存储的数据长度
**/
template<int NodeSize>
struct RtreeNode {
  RtreeNode() {
    p_parent = nullptr;
    p_next = nullptr;
    z_data = (unsigned char*)malloc(sizeof(unsigned char) * NodeSize);
    i_node = 0;
  }
  ~RtreeNode() {
    p_parent = nullptr;
    p_next = nullptr;
    if (z_data) {
      free(z_data);
      z_data = nullptr;
    }
  }
 
  std::atomic<int> ref;           /* 引用计数 */
  RtreeNode *p_parent;            /* 这个节点的父节点 */
  uint64_t i_node;                /* 节点id */
  bool is_dirty;                  /* 标记这个节点是否已经脏了 */
  unsigned char *z_data;          /* 数据区域, 非叶子结点存放范围，
                                     叶子结点存放具体值, 长度与维度有关 */
  RtreeNode *p_next;
};

template<class RtreeCoord, int MaxDismensions>
struct RtreeCell {
  uint64_t i_id;
  RtreeCoord a_coord[MaxDismensions * 2]; 
};

/**
* @Storage 具体的存储引擎，存储持久化的数据
* @Dismensions 维度数
* @MaxNodeCellNum 单节点最大包含的单元数
**/
template<class Storage, int Dismensions, int MaxNodeCellNum>
class Rtree {
 public: 
  typedef RtreeNode<Dismensions * 2 + 2> RtreeNodeType;
 public:
  Rtree();
  virtual ~Rtree(); 
  void Insert(const RtreeCell &cell);
  void Remove(const RtreeCell &cell);
  int Search();
  int Count(); 
  bool Save();
 private:
  void NodeInsertCell(RtreeCell &cell, 
                      RtreeNodeType *p_node); 
  void NodeRemoveCell(RtreeNodeType *p_node,
                      uint64_t cell_number);
  /**
   * 根据传输进来的 cell 信息，找到合适的叶子结点
   **/
  int ChooseLeaf(RtreeCell &cell, 
                 RtreeNodeType *pLeaf); 
  /**
   * 获得一个节点
   * 这个操作会增加节点的引用计数
   **/
  void NodeAcquire(RtreeNodeType* p_node);

  /**
   * 释放一个节点
   * 此操作会释放节点的引用计数
   * 如果发现某个节点已经脏了的话，会将这个节点回写到持久化存储中
   **/
  void NodeRelease();

  RtreeNodeType* NodeHashLookup(uint64_t i_node);
   
  void NodeHashInsert(RtreeNodeType *p_node);

  void NodeHashRemove(RtreeNodeType *p_node);

  int FindLeafNode(uint64_t node_number, 
                   RtreeNodeType **pp_leaf);

  int AdjustTree(RtreeNodeType *p_node,
                 RtreeCell& cell);

  int SplitNode();

 private:
  Storage *db;                   /* 存储引擎 */
  int n_dim_;                    /* 维度信息 */ 
  RtreeNodeType *hash_map[];     /* 存放所有的在内存中的节点，加速查找 */
};

} // namespace ssq
