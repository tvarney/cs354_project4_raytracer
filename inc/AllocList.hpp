
#ifndef CS354_PROJECT4_ALLOC_LIST_HPP
#define CS354_PROJECT4_ALLOC_LIST_HPP

namespace cs354 {
    template <class T, class deleter = delete>
    class AllocList {
    public:
        AllocList();
        ~AllocList();
        
        void append(T *item) {
            ptrs.push_back(item);
        }
        void remove(T *item) {
            size_t len = ptrs.size();
            for(size_t i = 0; i < len; ++i) {
                if(ptrs[i] == item) {
                    ptrs.erase(ptrs.begin() + i);
                    break;
                }
            }
            delete item;
        }
    protected:
        std::vector<T*> ptrs;
    };
    typedef AllocList<Object> ObjectList;
}

#endif
