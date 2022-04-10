#include "AVL.h"
AVL::AVL () : root_ ()
{}
AVL::AVL (const AVL &other) : root_ ()
{
  if (!other.root_) return;
  root_ = new AVL::node (other.root_->data_);
  add_nodes (other.root_, root_);
}
AVL::AVL (const std::vector<std::pair<double, double>> &coordinates) : root_ ()
{
  for (const auto &pair: coordinates)
  {
    insert (Apartment (pair));
  }
}
AVL::node *insertnode (AVL::node *node, const Apartment &apartment)
{
  // Find the correct postion and insert the node
  if (node == nullptr)
    return new AVL::node (apartment);
  if (apartment < node->data_)
    node->left_ = insertnode (node->left_, apartment);
  else if (apartment > node->data_)
    node->right_ = insertnode (node->right_, apartment);
  else
    return node;

  node->height_ = 1 + std::max (node->left_ ? node->left_->height_ : 0,
                                node->right_ ? node->right_->height_ : 0);

  RotationType r_type = get_rotation_type (node, apartment);
  if (r_type != NONE) return do_rotation (r_type, node);
  return node;
}

void AVL::insert (const Apartment &apartment)
{
  if (root_ == nullptr)
  {
    root_ = new AVL::node (apartment);
    return;
  }
  /*
   * insert:
   */
  root_ = insertnode (root_, apartment);

}
void AVL::erase (const Apartment &apartment)
{
  if (!root_) return;
  root_ = delete_node (root_, apartment);
}
AVL &AVL::operator= (const AVL &other)
    {
  if (this != &other)
  {
    delete_nodes ((this->root_));
    if (!other.root_)
    {
      root_ = nullptr;
    }
    else
    {
      root_ = new AVL::node (other.root_->data_);
      add_nodes (other.root_, root_);
    }
}
return *this;
}
AVL::~AVL ()
{
  delete_nodes ((this->root_));
}
void AVL::delete_nodes (AVL::node *node)
{
  if (!node) return;
  delete_nodes (node->left_);
  delete_nodes (node->right_);
  delete node;
}

AVL::node *right_rotation (AVL::node *node)
{
  if(!node->right_ && !node->left_) return node;
  AVL::node *x = node->left_;
  AVL::node *lr = x->right_;
  x->right_ = node;
  node->left_ = lr;
  node->height_ = std::max (node->left_ ? node->left_->height_ : 0,
                            node->right_ ? node->right_->height_ : 0) + 1;
  x->height_ = std::max (x->left_ ? x->left_->height_ : 0,
                         x->right_ ? x->right_->height_ : 0) + 1;
  return x;
}

AVL::node *left_rotation (AVL::node *node)
{
  if(!node->right_ && !node->left_) return node;
  AVL::node *y = node->right_;
  AVL::node *rl = y->left_;
  y->left_ = node;
  node->right_ = rl;
  node->height_ = std::max (node->left_ ? node->left_->height_ : 0,
                            node->right_ ? node->right_->height_ : 0) + 1;
  y->height_ = std::max (y->left_ ? y->left_->height_ : 0,
                         y->right_ ? y->right_->height_ : 0) + 1;
  return y;
}

std::ostream &operator<< (std::ostream &os, const AVL &avl)
{
  preorder_output (os, avl.root_);
  return os;
}

void preorder_output (std::ostream &os, AVL::node *node)
{
  if (!node) return;
  os << node->data_;
  preorder_output (os, node->left_);
  preorder_output (os, node->right_);
}

AVL::iterator AVL::begin ()
{
  return {root_};
}

AVL::const_iterator AVL::begin () const
{
  return {root_};
}
AVL::const_iterator AVL::cbegin () const
{
  return {root_};
}
AVL::iterator AVL::end ()
{
  return {nullptr};
}
AVL::const_iterator AVL::end () const
{
  return {nullptr};
}
AVL::const_iterator AVL::cend () const
{
  return {nullptr};
}
AVL::iterator AVL::find (const Apartment &data)
{
  return {find_node (root_, data)};
}
AVL::const_iterator AVL::find (const Apartment &data) const
{
  return {find_node (root_, data)};
}
AVL::node *AVL::find_node (node *node, const Apartment &a) const
{
  if (!node) return nullptr;
  if (a == node->data_) return node;
  if (a < node->data_)
  {
    return find_node (node->left_, a);
  }
  else
  {
    return find_node (node->right_, a);
  }
}
AVL::node *delete_node (AVL::node *node, const Apartment &apartment)
{
  if (node == nullptr)
    return node;
  if (apartment < node->data_)
    node->left_ = delete_node (node->left_, apartment);
  else if (apartment > node->data_)
    node->right_ = delete_node (node->right_, apartment);
  else
  {
    if ((node->left_ == nullptr) ||
    (node->right_ == nullptr))
    {
      AVL::node *temp = node->left_ ? node->left_ : node->right_;
      if (temp == nullptr)
      {
        temp = node;
        node = nullptr;
      }
      else
        *node = *temp;
      delete temp;
    }
    else
    {

      AVL::node *current = node->right_;
      while (current->left_)
        current = current->left_;
      AVL::node *temp = current;
      node->data_ = temp->data_;
      node->right_ = delete_node (node->right_,
                                  temp->data_);
    }
  }

  if (node == nullptr)
    return node;

  node->height_ = 1 + std::max (node->left_ ? node->left_->height_ : 0,
                                node->right_ ? node->right_->height_ : 0);
  RotationType r_type = get_rotation_type (node);
  if (r_type != NONE) return do_rotation (r_type, node);
  return node;
}
RotationType get_rotation_type (AVL::node *node, const Apartment &apartment)
{
  int hl = node->left_ ? node->left_->height_ + 1 : 0;
  int hr = node->right_ ? node->right_->height_ + 1 : 0;
  int balance_factor = hl - hr;
  if (balance_factor > 1)
  {
    return apartment < node->left_->data_ ? LL : LR;
  }
  if (balance_factor < -1)
  {
    return apartment > node->right_->data_ ? RR : RL;
  }
  return NONE;
}
AVL::node *do_rotation (RotationType rt, AVL::node *node)
{
  switch (rt)
  {
    case RR:
      return left_rotation (node);
    case LL:
        return right_rotation (node);
    case RL:
        node->right_ = right_rotation (node->right_);
        return left_rotation (node);
    case LR:
        node->left_ = left_rotation (node->left_);
        return right_rotation (node);
    case NONE:
        break;
  }
  return nullptr;
}
void add_nodes (AVL::node *original_node, AVL::node *new_node)
{
  if (!original_node) return;
  if (original_node->left_) new_node->left_ = new
      AVL::node (original_node->left_->data_);
  if (original_node->right_) new_node->right_ = new
      AVL::node (original_node->right_->data_);
  add_nodes (original_node->left_, new_node->left_);
  add_nodes (original_node->right_, new_node->right_);
    }
    RotationType get_rotation_type (AVL::node *node)
    {
  int hl = node->left_ ? node->left_->height_ + 1 : 0;
  int hr = node->right_ ? node->right_->height_ + 1 : 0;
  int balance_factor = hl - hr;
  if (balance_factor > 1)
  {
    int left_hl = node->left_->left_ ? node->left_->left_->height_ + 1 : 0;
    int left_hr = node->left_->right_ ? node->left_->right_->height_ + 1 : 0;
    int balance_factorl = left_hl - left_hr;
    return balance_factorl >= 0 ? LL : LR;
  }
  if (balance_factor < -1)
  {
    int right_hl = node->right_->left_ ? node->right_->left_->height_ + 1 : 0;
    int right_hr = node->right_->right_ ? node->right_->right_->height_ + 1 : 0;
    int balance_factorr = right_hl - right_hr;
    return balance_factorr <= 0 ? RR : RL;
  }
  return NONE;
}

