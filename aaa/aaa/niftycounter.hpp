//Stream.hpp
class StreamInitializer;

class Stream {
   friend class StreamInitializer;
public:
   Stream () {
      // Constructor must be called before use.
   }
};
static class StreamInitializer {
public:
   StreamInitializer ();
   ~StreamInitializer ();
} initializer; //Note object here in the header.
