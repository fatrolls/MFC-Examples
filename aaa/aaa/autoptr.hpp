template<class T>
class auto_ptr
{
public:
    explicit auto_ptr(T *p = 0);            
    template<class U>                         
    auto_ptr(auto_ptr<U>& rhs);               
    
    ~auto_ptr();
    template<class U>                        
    auto_ptr<T>&                             
    operator=(auto_ptr<U>& rhs);      
    T& operator*() const;                   
    T* operator->() const;                   
    T* get() const;     
    T* release();                            
    void reset(T *p = 0);                   
private:
    T *pointee;
    template<class U> friend class auto_ptr;  //??<U>             
};
template<class T>
inline auto_ptr<T>::auto_ptr(T *p)
        : pointee(p)
{}

template<class T>
template<class U> 
inline auto_ptr<T>::auto_ptr(auto_ptr<U>& rhs)
        : pointee(rhs.release())
{}
template<class T>
inline auto_ptr<T>::~auto_ptr()
{
    delete pointee;
}
template<class T>
template<class U>
inline auto_ptr<T>& auto_ptr<T>::operator=(auto_ptr<U>& rhs)
{
    if (this != &rhs) reset(rhs.release());
    return *this;
}
template<class T>
inline T& auto_ptr<T>::operator*() const
{
    return *pointee;
}
template<class T>
inline T* auto_ptr<T>::operator->() const
{
    return pointee;
}
template<class T>
inline T* auto_ptr<T>::get() const
{
    return pointee;
}
template<class T>
inline T* auto_ptr<T>::release()
{
    T *oldPointee = pointee;
    pointee = 0;
    return oldPointee;
}
template<class T>
inline void auto_ptr<T>::reset(T *p)
{
    if (pointee != p) {
        delete pointee;
        pointee = p;
    }
}

