template<typename T>
class Counter
{
public:
    Counter();
    Counter(const Counter&);
    ~Counter();
    static size_t howMany();
private:
    static size_t count;
};
template<typename T>
size_t Counter<T>::count = 0;

class Widget
{
public:
    ////.....

    static size_t howMany() {
        return Counter<Widget>::howMany();
    }
private:
    ////.....

    Counter<Widget> c;
};
//
//////////
class Widget2: private Counter<Widget2>
{
public:
    ////.....

    using Counter<Widget2>::howMany;
private:
    ////.....

};
