
template<class T>
class auto_ptr2
{
public:
    explicit auto_ptr2(T *p = 0): pointee(p) {}
    template<class U>
    auto_ptr2(auto_ptr2<U>& rhs): pointee(rhs.release()) {}
    ~auto_ptr2() {
        delete pointee;
    }
    template<class U>
    auto_ptr2<T>& operator=(auto_ptr2<U>& rhs) {
        if (this != &rhs) reset(rhs.release());
        return *this;
    }
    T& operator*() const {
        return *pointee;
    }
    T* operator->() const {
        return pointee;
    }
    T* get() const {
        return pointee;
    }
    T* release() {
        T *oldPointee = pointee;
        pointee = 0;
        return oldPointee;
    }
    void reset(T *p = 0) {
        if (pointee != p) {
            delete pointee;
            pointee = p;
        }
    }
private:
    T *pointee;
    template<class U> friend class auto_ptr2;//<U>
};
