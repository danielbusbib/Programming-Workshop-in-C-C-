#include <iostream>
#include <algorithm>
#ifndef _VL_VECTOR_H_
#define _VL_VECTOR_H_
#define STAT_CAP 16
template<typename T, size_t C = STAT_CAP>
    class vl_vector {
 private:
  T *arr_d;
  T arr_s[C];
  size_t vl_size;
  size_t vl_capacity;
  friend class iterator;

 public:
  vl_vector () :
  arr_d (), arr_s (), vl_size (0), vl_capacity (C)
  {}

  vl_vector (const vl_vector<T, C> &other) :
  arr_d (), arr_s (), vl_size (other.vl_size), vl_capacity (other.vl_capacity)
  {
    if (other.arr_d)
    {
      arr_d = new T[vl_capacity];
      std::copy (other.arr_d, other.arr_d + vl_size, arr_d);
    }
    else
    {
      std::copy (other.arr_s, other.arr_s + vl_size, arr_s);
    }
  }

  vl_vector (size_t count, T v)
  : arr_d (), arr_s (), vl_size (0), vl_capacity (C)
  {
    T *cur = arr_s;
    if (count > C)
    {
      vl_capacity = (3 * count) / 2;
      arr_d = new T[vl_capacity];
      cur = arr_d;
    }
    for (size_t i = 0; i < count; ++i) cur[vl_size++] = v;
  }

  template<class InputIterator>
      vl_vector (InputIterator first, InputIterator last):
      arr_d (), arr_s (), vl_size (0), vl_capacity (C)
      {
    size_t n = std::distance (first, last);
    T *cur = arr_s;
    if (n > C)
    {
      vl_capacity = (3 * n) / 2;
      arr_d = new T[vl_capacity];
      cur = arr_d;
    }
    while (first != last)
    {
      cur[vl_size++] = *first;
      ++first;
    }
      }

      ~vl_vector ()
      { delete[] arr_d;
        arr_d= nullptr;}
        size_t size ()
        { return vl_size; }

        size_t capacity ()
        { return vl_capacity; }

        bool empty () const
        { return vl_size == 0; }

  T &at (size_t index)
  {
    if (index >= vl_size) throw std::exception ();
    return arr_d ? arr_d[index] : arr_s[index];

  }
  T at (size_t index) const
  {
    if (index >= vl_size) throw std::exception ();
    return arr_d ? arr_d[index] : arr_s[index];

  }

        void push_back (T val)
        {
    if (vl_size + 1 > vl_capacity) arr_d ? re_alloc () : alloc (1);
    data ()[vl_size++] = val;
        }

        void pop_back ()
        {
    if (vl_size == 0)return;
    if (--vl_size <= C && arr_d)
    {
      std::copy (arr_d, arr_d + vl_size, arr_s);
      vl_capacity = C;
      delete[] arr_d;
      arr_d = nullptr;
    }
        }
        void clear ()
        {
    if (arr_d)
    {
      delete[] arr_d;
      arr_d = nullptr;
    }
    vl_size = 0;
    vl_capacity = C;
        }

        T *data ()
        { return arr_d ? arr_d : arr_s; }

        bool contains (const T val) const
        {
    if (vl_size == 0) return false;
    const T *cur = arr_d ? arr_d : arr_s;
    for (size_t i = 0; i < vl_size; ++i)
    {
      if (cur[i] == val) return true;
    }
    return false;
  }

  vl_vector &operator= (const vl_vector<T, C> &other)
      {
    if (this != &other)
    {
      delete[] arr_d;
      arr_d = nullptr;
      vl_size = other.vl_size;
      vl_capacity = other.vl_capacity;
      if (other.arr_d)
      {
        arr_d = new T[vl_capacity];
        std::copy (other.arr_d, other.arr_d + vl_size, arr_d);
      }
      else
      {
        std::copy (other.arr_s, other.arr_s + vl_size, arr_s);
      }
    }
    return *this;
            }

    T operator[] (size_t i) const
    { return (arr_d? arr_d: arr_s)[i]; }

    T &operator[] (size_t i)
    { return (data ())[i]; }

            bool operator== (const vl_vector<T, C> &other) const
            {
    if (vl_size != other.vl_size) return false;
    const T *cur1 = arr_d ? arr_d : arr_s;
    const T *cur2 = other.arr_d ? other.arr_d : other.arr_s;
    return std::equal (cur1, cur1 + vl_size, cur2);
            }

            bool operator!= (const vl_vector<T, C> &other) const
            {
    return !(*this == other);
            }

 private:
  void alloc (int k = 1)
  {
    int new_capacity = (3 * (vl_size + k)) / 2;
    arr_d = new T[new_capacity];
    std::copy (arr_s, arr_s + vl_size, arr_d);
    vl_capacity = new_capacity;
  }
  void re_alloc (int k = 1)
  {
    vl_capacity = (3 * (vl_size + k)) / 2;
    T *tmp = new T[vl_capacity];
    std::copy (data (), data () + vl_size, tmp);
    delete[] arr_d;
    arr_d = tmp;
  }
  void de_alloc ()
  {
    std::copy (arr_d, arr_d + vl_size, arr_s);
    delete[] arr_d;
    arr_d = nullptr;
    vl_capacity = C;
  }
  /**
   * Iterators:
   */
  class const_iterator;
  class Iterator {
    T *arr;
    size_t index, size;
    friend class const_iterator;
   public:
    /* These typedefs are required for STL usage. They are called iterator traits */
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    Iterator () : arr (), index (0)
    {}

    Iterator (T *p, size_t index = 0)
    : arr (p), index (index)
    {}

    pointer operator-> ()
    {
      return &arr[index];
    }
    reference operator* ()
    {
      return arr[index];
    }
    Iterator &operator++ ()
    {
      ++index;
      return *this;
    }
    Iterator operator++ (int)
    {
      Iterator it = *this;
      ++index;
      return it;
    }
    Iterator operator-- ()
    {
      --index;
      return *this;
    }
    Iterator operator-- (int)
    {
      Iterator it = *this;
      --index;
      return it;
    }

    Iterator operator+ (size_t i)
    {
      return {arr, index + i};
    }
    Iterator operator- (size_t i)
    {
      return {arr, index - i};
    }
    size_t  operator-(const Iterator& other)
    {return index - other.index;}

    size_t  operator+(const Iterator& other)
    {return index + other.index;}

    bool  operator<(const Iterator& other)
    {return index < other.index;}

    bool  operator>(const Iterator& other)
    {return index > other.index;}

    Iterator &operator+= (int i)
        {
      index += i;
      return *this;
        }
        Iterator &operator-= (int i)
            {
      index -= i;
      return *this;
            }
            bool operator== (const Iterator &rhs) const
            {
      return arr == rhs.arr && index == rhs.index;
            }
            bool operator!= (const Iterator &rhs) const
            {
      return !(rhs == *this);
            }
  };
  class const_iterator {
    const T *arr;
    size_t index;
   public:
    /* These typedefs are required for STL usage. They are called iterator traits */
    typedef T value_type;
    typedef const T &reference;
    typedef const T *pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    const_iterator (const T *p, size_t index = 0) : arr (p), index (index)
    {}
    const_iterator () : arr (), index (0)
    {}
    pointer operator-> ()
    {
      return &arr[index];
    }
    reference operator* ()
    {
      return arr[index];
    }
    const_iterator &operator++ ()
    {
      ++index;
      return *this;
    }
    const_iterator operator++ (int)
    {
      const_iterator it = *this;
      ++index;
      return it;
    }
    const_iterator operator-- ()
    {
      --index;
      return *this;
    }
    const_iterator operator-- (int)
    {
      const_iterator it = *this;
      --index;
      return it;
    }

    const_iterator operator+ (size_t i)
    {
      return {arr, index + i};
    }
    const_iterator operator- (size_t i)
    {
      return {arr, index - i};
    }
    size_t  operator-(const const_iterator& other)
    {return index - other.index;}

    size_t  operator+(const const_iterator& other)
    {return index + other.index;}

    bool  operator<(const const_iterator& other)
    {return index < other.index;}

    bool  operator>(const const_iterator& other)
    {return index > other.index;}

    const_iterator &operator+= (int i)
        {
      index += i;
      return *this;
        }
        const_iterator &operator-= (int i)
            {
      index -= i;
      return *this;
            }
            bool operator== (const const_iterator &rhs) const
            {
      return arr == rhs.arr && index == rhs.index;
            }
            bool operator!= (const const_iterator &rhs) const
            {
      return !(rhs == *this);
            }
  };
  /**
   * Reverse Iterators:
   */
  class const_reverse_iterator;
  class ReverseIterator {
    T *arr;
    size_t index;
    friend class const_reverse_iterator;
   public:
    /* These typedefs are required for STL usage. They are called iterator traits */
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    ReverseIterator (T *p, size_t index = -1)
    : arr (p), index (index)
    {}
    ReverseIterator () : arr (), index (0)
    {}
    pointer operator-> ()
    { return &arr[index]; }
    reference operator* ()
    { return arr[index]; }

    ReverseIterator &operator++ ()
    {
      --index;
      return *this;
    }
    ReverseIterator operator++ (int)
    {
      ReverseIterator it = *this;
      --index;
      return it;
    }
    ReverseIterator operator-- ()
    {
      ++index;
      return *this;
    }
    ReverseIterator operator-- (int)
    {
      ReverseIterator it = *this;
      ++index;
      return it;
    }

    ReverseIterator operator+ (size_t i)
    { return {arr, index - i}; }

    ReverseIterator operator- (size_t i)
    { return {arr, index + i}; }

    size_t  operator-(const ReverseIterator& other)
    {return index - other.index;}

    size_t  operator+(const ReverseIterator& other)
    {return index + other.index;}

    bool  operator<(const ReverseIterator& other)
    {return index < other.index;}

    bool  operator>(const ReverseIterator& other)
    {return index > other.index;}

    ReverseIterator &operator+= (int i)
        {
      index -= i;
      return *this;
        }
        ReverseIterator &operator-= (int i)
            {
      index += i;
      return *this;
            }
            bool operator== (const ReverseIterator &rhs) const
            { return arr == rhs.arr && index == rhs.index; }

            bool operator!= (const ReverseIterator &rhs) const
            { return !(rhs == *this); }

  };
  class const_reverse_iterator {
    const T *arr;
    size_t index;
   public:
    /* These typedefs are required for STL usage. They are called iterator traits */
    typedef T value_type;
    typedef const T &reference;
    typedef const T *pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    const_reverse_iterator (const T *p, size_t index = -1) : arr (p), index (index)
    {}
    const_reverse_iterator () : arr (), index (0)
    {}
    pointer operator-> ()
    { return &arr[index]; }

    reference operator* ()
    { return arr[index]; }

    const_reverse_iterator &operator++ ()
    {
      --index;
      return *this;
    }
    const_reverse_iterator operator++ (int)
    {
      const_reverse_iterator it = *this;
      --index;
      return it;
    }
    const_reverse_iterator operator-- ()
    {
      ++index;
      return *this;
    }
    const_reverse_iterator operator-- (int)
    {
      const_reverse_iterator it = *this;
      ++index;
      return it;
    }

    const_reverse_iterator operator+ (size_t i)
    { return {arr, index - i}; }

    const_reverse_iterator operator- (size_t i)
    { return {arr, index + i}; }

    size_t  operator-(const const_reverse_iterator& other)
    {return index - other.index;}

    size_t  operator+(const const_reverse_iterator& other)
    {return index + other.index;}

    bool  operator<(const const_reverse_iterator& other)
    {return index < other.index;}

    bool  operator>(const const_reverse_iterator& other)
    {return index > other.index;}

    const_reverse_iterator &operator+= (int i)
        {
      index -= i;
      return *this;
        }
        const_reverse_iterator &operator-= (int i)
            {
      index += i;
      return *this;
            }
            bool operator== (const const_reverse_iterator &rhs) const
            { return arr == rhs.arr && index == rhs.index; }

            bool operator!= (const const_reverse_iterator &rhs) const
            { return !(rhs == *this); }

  };
 public:
  typedef Iterator iterator;
  typedef const_iterator const_iterator;
  typedef ReverseIterator reverse_iterator;
  typedef const_reverse_iterator const_reverse_iterator;
  iterator begin ()
  { return {data ()}; }
  iterator end ()
  { return {data (), vl_size}; }
  const_iterator begin () const
  {
    const T *cur = arr_d ? arr_d : arr_s;
    return {cur};
  }
  const_iterator end () const
  {
    const T *cur = arr_d ? arr_d : arr_s;
    return {cur, vl_size};
  }
  const_iterator cbegin () const
  {
    const T *cur = arr_d ? arr_d : arr_s;
    return {cur};
  }
  const_iterator cend () const
  {
    const T *cur = arr_d ? arr_d : arr_s;
    return {cur, vl_size};
  }

  reverse_iterator rbegin ()
  { return {data (), vl_size - 1}; }
  reverse_iterator rend ()
  { return {data ()}; }
  const_reverse_iterator rbegin () const
  {
    const T *cur = arr_d ? arr_d : arr_s;
    return {cur, vl_size - 1};
  }
  const_reverse_iterator rend () const
  {
    const T *cur = arr_d ? arr_d : arr_s;
    return {cur};
  }
  const_reverse_iterator crbegin () const
  {
    const T *cur = arr_d ? arr_d : arr_s;
    return {cur, vl_size - 1};
  }
  const_reverse_iterator crend () const
  {
    const T *cur = arr_d ? arr_d : arr_s;
    return {cur};
  }

  iterator insert (iterator position, T val)
  {
    T *cur = data ();
    size_t i = 0, index = 0;
    while (cur[i++] != *position) ++index;
    if (vl_size + 1 > vl_capacity)
    {
      (!arr_d) ? alloc () : re_alloc ();

    }
    cur = data ();
    T *tmp = new T[vl_size];
    std::copy (cur, cur + vl_size, tmp);
    std::copy (tmp + index, tmp + vl_size, cur + index + 1);
    cur[index] = val;
    ++vl_size;
    delete[] tmp;
    return {data (), index};
  }

  template<class InputIterator>
      iterator insert (iterator position, InputIterator first, InputIterator last)
      {
    T *cur, *tmp;
    size_t index = 0;
    iterator b = begin ();
    while (b++ != position) ++index;
    int n = std::distance (first, last);
    tmp = new T[n];
    std::copy (first, last, tmp);

    if (vl_size + n > vl_capacity) (!arr_d) ? alloc (n) : re_alloc (n);

    cur = data ();
    std::copy (cur + index, cur + vl_size, cur + index + n);
    std::copy (tmp, tmp + n, cur + index);

    vl_size += n;
    delete[] tmp;
    return {data (), index};
      }
      iterator erase (iterator position)
      {
    T *cur = data ();
    size_t index = 0;
    iterator b = begin ();
    while (b++ != position) ++index;
    std::copy (cur + index + 1, cur + vl_size--, cur + index);
    if (vl_size <= C && arr_d) de_alloc ();
    return {data (), index};
      }
  template<class InputIterator>
  iterator erase (InputIterator first, InputIterator last)
  {
    T *cur = data ();
    size_t index = 0;
    iterator b = begin ();
    while (b++ != first) ++index;
    int n = std::distance (first, last);
    std::copy (cur + index + n, cur + vl_size, cur + index);
    vl_size -= n;
    if (vl_size <= C && arr_d) de_alloc ();
    return {data (), index};
    }

};

#endif //_VL_VECTOR_H_
