#include <functional>
#include <algorithm>
#include <list>
#include <set>
#include <numeric> 
using namespace std;
template<typename InputIterator,                // 一个copy_if的
    typename OutputIterator,        // 正确实现
    typename Predicate>
    OutputIterator copy_if(InputIterator begin,
    InputIterator end,
    OutputIterator destBegin,
    Predicate p) {
        while (begin != end) {
            if (p(*begin))*destBegin++ = *begin;
            ++begin;
        }

        return destBegin;
}


///==
struct Point {
    double x; 
    double y;
    Point(double a,double b):x(a),y(b){}
    Point():x(0.0),y(0.0){}
};                    // 同上
class PointAverage:
    public unary_function<Point, void> {        // 参见条款40
public:
    PointAverage(): xSum(0), ySum(0), numPoints(0) {}
    void operator()(const Point& p)
    {
        ++numPoints;
        xSum += p.x;
        ySum += p.y;
    }
    Point result() const
    {
        return Point(xSum/numPoints, ySum/numPoints);
    }

private:
    size_t numPoints;
    double xSum;
    double ySum;
};

void listPoind()
{
    list<Point> lp;
    ////...
    Point avg = (for_each(lp.begin(), lp.end(), PointAverage())).result();
}
///==
string::size_type                    // string::size_type的内容请看下文
    stringLengthSum(string::size_type sumSoFar,         
    const string& s)
{
    return sumSoFar + s.size();
}
void setPoind()
{
    set<string> ss;                    // 建立字符串的容器，进行一些操作
    ////...                         
    string::size_type lengthSum =            // 把lengthSum设为对 ss中的每个元素调用
        accumulate(ss.begin(), ss.end(), 0, stringLengthSum);         
            // stringLengthSum的结果，使用0作为初始统计值

    ///=
}
template<typename T>                    // 用于修改的BPFC  的新实现类
class BPFCImpl:
    public unary_function<T, void> {        
private:
    //Widget w;                    // 以前在BPFC里的所有数据
    int x;                        // 现在在这里
    ////...
    virtual ~BPFCImpl();                // 多态类需要
    // 虚析构函数
    virtual void operator()(const T& val) const;
    template<class U> friend class BPFC;                // 让BPFC可以访问这些数据
};

template<typename T>
class BPFC:                        // 小的，单态版的BPFC
    public unary_function<T, void> {
private:
    BPFCImpl<T> *pImpl;                // 这是BPFC唯一的数据

public:
    void operator()(const T& val) const        // 现在非虚；
    {                        
        pImpl->operator() (val);// 调用BPFCImpl的
    }
    ////...
};
