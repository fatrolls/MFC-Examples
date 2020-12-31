class Pool{
    struct Link{Link* next;};
    struct Chunk{
        enum{size=8*1024-16};
        char mem[size];
        Chunk* next;
    };
    Chunk* chunks;
    const unsigned int esize;
    Link* head;
    Pool(Pool&);
    void operator=(Pool&);
    void grow();
public:
    Pool(unsigned int n);
    ~Pool();
    void* alloc();
    void free(void* b);

};

inline void* Pool::alloc()
{
    if(head==0)grow();
    Link* p=head;
    head=p->next;
    return p;
    
}

inline void Pool::free(void* b)
{
    Link* p=static_cast<Link* >(b);
    p->next=head;
    head=p;    
}

Pool::Pool(unsigned int sz):esize(sz<sizeof(Link)?sizeof(Link):sz)
{
    head=0;
    chunks=0;
}

Pool::~Pool()
{
    Chunk* n=chunks;
    while(n){
        Chunk* p=n;
        n=n->next;
        delete p;
    }
}

void Pool::grow()
{
    Chunk* n=new Chunk;
    n->next=chunks;
    chunks=n;
    
    const int nelem=Chunk::size/esize;
    char* start=n->mem;
    char* last=&start[(nelem-1)*esize];
    for(char* p=start; p<last; p+=esize)
        reinterpret_cast<Link*>(p)->next=reinterpret_cast<Link*>(p+esize);
    reinterpret_cast<Link*>(last)->next=0;
    head=reinterpret_cast<Link*>(start);
}
