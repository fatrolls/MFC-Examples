
#ifndef _COUNTOBJECT_
#define _COUNTOBJECT_

template<class BeingCounted>
class Counted
{
public:
    class TooManyObjects{};
    static int objectCount() {
        return numObjects;
    }
protected:
    Counted();
    Counted(const Counted& rhs);
    ~Counted() {
        --numObjects;
    }
private:
    static int numObjects;
    static const size_t maxObjects;
    void init();
};
class PrintJob{};

class Printer: private Counted<Printer>
{
public:
    
    static Printer * makePrinter();
    static Printer * makePrinter(const Printer& rhs);
    ~Printer();
    void submitJob(const PrintJob& job);
    void reset();
    void performSelfTest();
    ////...
    using Counted<Printer>::objectCount;
    using Counted<Printer>::TooManyObjects;
private:
    Printer();
    Printer(const Printer& rhs);
};

 //////////////////maxobject///////////////////////
class MPrinter
{
public:
    class TooManyObjects{};
    
    static MPrinter * makePrinter();
    static MPrinter * makePrinter(const MPrinter& rhs);
    ///////...
private:
    static size_t numObjects;
    enum { maxObjects = 10 };     //  static const size_t maxObjects = 10;//??
    MPrinter();
    MPrinter(const MPrinter& rhs);
};

//////////////////maxobject///////////////////////

#endif /* _COUNTOBJECT_ */