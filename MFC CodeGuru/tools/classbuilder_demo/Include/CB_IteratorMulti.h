#ifndef CB_ITERATOR_MULTI_H
#define CB_ITERATOR_MULTI_H

#ifdef _AFXEXT
#define CB_EXT_CLASS       AFX_CLASS_EXPORT
#else
#define CB_EXT_CLASS
#endif

#define ITERATOR_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
	class CB_EXT_CLASS NameTo##Iterator\
	{\
	private:\
		ClassTo* _ref##NameTo;\
		ClassTo* _prev##NameTo;\
		ClassTo* _next##NameTo;\
		ClassFrom* _iter##ClassFrom;\
        \
		NameTo##Iterator* _prev;\
		NameTo##Iterator* _next;\
        \
        int (ClassTo::*_method)();\
        \
		static NameTo##Iterator* _first;\
		static NameTo##Iterator* _last;\
        \
	public:\
		NameTo##Iterator(ClassFrom* iter##ClassFrom,\
                         int (ClassTo::*method)() = 0,\
                         ClassTo* ref##NameTo = 0);\
		NameTo##Iterator(ClassFrom& iter##ClassFrom,\
                         int (ClassTo::*method)() = 0,\
                         ClassTo* ref##NameTo = 0);\
		NameTo##Iterator(const NameTo##Iterator& iterator,\
                         int (ClassTo::*method)() = 0);\
		~NameTo##Iterator();\
        \
		NameTo##Iterator& operator= (const NameTo##Iterator& iterator)\
        {\
			_iter##ClassFrom = iterator._iter##ClassFrom;\
			_ref##NameTo = iterator._ref##NameTo;\
			_prev##NameTo = iterator._prev##NameTo;\
			_next##NameTo = iterator._next##NameTo;\
            _method = iterator._method;\
			return *this;\
		}\
		ClassTo* operator++ ()\
        {\
			_next##NameTo = _iter##ClassFrom->GetNext##NameTo(_next##NameTo);\
            if (_method != 0)\
            {\
                while (_next##NameTo && !(_next##NameTo->*_method)())\
			        _next##NameTo = _iter##ClassFrom->GetNext##NameTo(_next##NameTo);\
            }\
			_ref##NameTo = _prev##NameTo = _next##NameTo;\
			return _ref##NameTo;\
		}\
		ClassTo* operator-- ()\
        {\
			_prev##NameTo = _iter##ClassFrom->GetPrev##NameTo(_prev##NameTo);\
            if (_method != 0)\
            {\
                while (_prev##NameTo && !(_prev##NameTo->*_method)())\
			        _prev##NameTo = _iter##ClassFrom->GetPrev##NameTo(_prev##NameTo);\
            }\
			_ref##NameTo = _next##NameTo = _prev##NameTo;\
			return _ref##NameTo;\
		}\
		operator ClassTo*() { return _ref##NameTo; }\
		ClassTo* operator-> () { return _ref##NameTo; }\
		void Reset() { _ref##NameTo = _prev##NameTo = _next##NameTo = (ClassTo*)0; }\
        \
        int IsLast() { return (_iter##ClassFrom->GetLast##NameTo() == _ref##NameTo); }\
        int IsFirst() { return (_iter##ClassFrom->GetFirst##NameTo() == _ref##NameTo); }\
        \
		static void Check(ClassTo* item##NameTo);\
		static void Check(ClassTo* item##NameTo, ClassTo* newItem##NameTo);\
	};

#define METHODS_ITERATOR_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    ClassFrom##::##NameTo##Iterator* ClassFrom##::##NameTo##Iterator::_first = 0;\
    ClassFrom##::##NameTo##Iterator* ClassFrom##::##NameTo##Iterator::_last = 0;\
    \
    ClassFrom##::##NameTo##Iterator::NameTo##Iterator(\
        ClassFrom* iter##ClassFrom,\
        int (ClassTo::*method)(),\
        ClassTo* ref##NameTo)\
    {\
        assert(iter##ClassFrom);\
    \
	    _iter##ClassFrom = iter##ClassFrom;\
	    _ref##NameTo = _prev##NameTo = _next##NameTo = ref##NameTo;\
	    _prev = (NameTo##Iterator*)0;\
	    _next = (NameTo##Iterator*)0;\
        _method = method;\
	    if (_last)\
	    {\
		    _last->_next = this;\
		    _prev = _last;\
		    _last = this;\
	    }\
	    else\
		    _first = _last = this;\
    }\
    \
    ClassFrom##::##NameTo##Iterator::NameTo##Iterator(\
        ClassFrom& iter##ClassFrom,\
        int (ClassTo::*method)(),\
        ClassTo* ref##NameTo)\
    {\
        assert(&iter##ClassFrom);\
    \
        _iter##ClassFrom = &iter##ClassFrom;\
        _ref##NameTo = _prev##NameTo = _next##NameTo = ref##NameTo;\
        _prev = (NameTo##Iterator*)0;\
        _next = (NameTo##Iterator*)0;\
        _method = method;\
        if (_last)\
        {\
	        _last->_next = this;\
            _prev = _last;\
            _last = this;\
        }\
        else\
		    _first = _last = this;\
    }\
    \
    ClassFrom##::##NameTo##Iterator::NameTo##Iterator(\
        const NameTo##Iterator& iterator,\
        int (ClassTo::*method)())\
    {\
	    _iter##ClassFrom = iterator._iter##ClassFrom;\
	    _ref##NameTo = iterator._ref##NameTo;\
	    _prev##NameTo = iterator._prev##NameTo;\
	    _next##NameTo = iterator._next##NameTo;\
	    _prev = (NameTo##Iterator*)0;\
	    _next = (NameTo##Iterator*)0;\
        _method = method;\
	    if (_last)\
	    {\
		    _last->_next = this;\
		    _prev = _last;\
		    _last = this;\
	    }\
	    else\
		    _first = _last = this;\
    }\
    \
    ClassFrom##::##NameTo##Iterator::~NameTo##Iterator()\
    {\
	    if (_next)\
		    _next->_prev = _prev;\
	    else\
		    _last = _prev;\
    \
	    if (_prev)\
		    _prev->_next = _next;\
	    else\
		    _first = _next;\
    }\
    \
    void ClassFrom##::##NameTo##Iterator::Check(ClassTo* item##NameTo)\
    {\
	    for (NameTo##Iterator* item = _first; item; item = item->_next)\
	    {\
		    if (item->_prev##NameTo == item##NameTo)\
		    {\
			    item->_prev##NameTo = item->_iter##ClassFrom->GetNext##NameTo(item->_prev##NameTo);\
			    item->_ref##NameTo = 0;\
		    }\
		    if (item->_next##NameTo == item##NameTo)\
		    {\
			    item->_next##NameTo = item->_iter##ClassFrom->GetPrev##NameTo(item->_next##NameTo);\
			    item->_ref##NameTo = 0;\
		    }\
	    }\
    }\
    \
    void ClassFrom##::##NameTo##Iterator::Check(ClassTo* item##NameTo, ClassTo* newItem##NameTo)\
    {\
	    for (NameTo##Iterator* item = _first; item; item = item->_next)\
	    {\
		    if (item->_ref##NameTo == item##NameTo)\
		    {\
			    item->_ref##NameTo = item->_prev##NameTo = item->_next##NameTo = newItem##NameTo;\
		    }\
		    if (item->_prev##NameTo == item##NameTo)\
		    {\
			    item->_prev##NameTo = newItem##NameTo;\
			    item->_ref##NameTo = 0;\
		    }\
		    if (item->_next##NameTo == item##NameTo)\
		    {\
			    item->_next##NameTo = newItem##NameTo;\
			    item->_ref##NameTo = 0;\
		    }\
	    }\
    }

#define ITERATOR_NOFILTER_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
	class CB_EXT_CLASS NameTo##Iterator\
	{\
	private:\
		ClassTo* _ref##NameTo;\
		ClassTo* _prev##NameTo;\
		ClassTo* _next##NameTo;\
		ClassFrom* _iter##ClassFrom;\
        \
		NameTo##Iterator* _prev;\
		NameTo##Iterator* _next;\
        \
		static NameTo##Iterator* _first;\
		static NameTo##Iterator* _last;\
        \
	public:\
		NameTo##Iterator(ClassFrom* iter##ClassFrom,\
                         ClassTo* ref##NameTo = 0);\
		NameTo##Iterator(ClassFrom& iter##ClassFrom,\
                         ClassTo* ref##NameTo = 0);\
		NameTo##Iterator(const NameTo##Iterator& iterator);\
		~NameTo##Iterator();\
        \
		NameTo##Iterator& operator= (const NameTo##Iterator& iterator)\
        {\
			_iter##ClassFrom = iterator._iter##ClassFrom;\
			_ref##NameTo = iterator._ref##NameTo;\
			_prev##NameTo = iterator._prev##NameTo;\
			_next##NameTo = iterator._next##NameTo;\
			return *this;\
		}\
		ClassTo* operator++ ()\
        {\
			_next##NameTo = _iter##ClassFrom->GetNext##NameTo(_next##NameTo);\
			_ref##NameTo = _prev##NameTo = _next##NameTo;\
			return _ref##NameTo;\
		}\
		ClassTo* operator-- ()\
        {\
			_prev##NameTo = _iter##ClassFrom->GetPrev##NameTo(_prev##NameTo);\
			_ref##NameTo = _next##NameTo = _prev##NameTo;\
			return _ref##NameTo;\
		}\
		operator ClassTo*() { return _ref##NameTo; }\
		ClassTo* operator-> () { return _ref##NameTo; }\
		void Reset() { _ref##NameTo = _prev##NameTo = _next##NameTo = (ClassTo*)0; }\
        \
        int IsLast() { return (_iter##ClassFrom->GetLast##NameTo() == _ref##NameTo); }\
        int IsFirst() { return (_iter##ClassFrom->GetFirst##NameTo() == _ref##NameTo); }\
        \
		static void Check(ClassTo* item##NameTo);\
		static void Check(ClassTo* item##NameTo, ClassTo* newItem##NameTo);\
	};

#define METHODS_ITERATOR_NOFILTER_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
    ClassFrom##::##NameTo##Iterator* ClassFrom##::##NameTo##Iterator::_first = 0;\
    ClassFrom##::##NameTo##Iterator* ClassFrom##::##NameTo##Iterator::_last = 0;\
    \
	ClassFrom##::##NameTo##Iterator::NameTo##Iterator(\
        ClassFrom* iter##ClassFrom, ClassTo* ref##NameTo)\
    {\
        assert(iter##ClassFrom);\
    \
		_iter##ClassFrom = iter##ClassFrom;\
		_ref##NameTo = _prev##NameTo = _next##NameTo = ref##NameTo;\
		_prev = (NameTo##Iterator*)0;\
		_next = (NameTo##Iterator*)0;\
		if (_last)\
		{\
			_last->_next = this;\
			_prev = _last;\
			_last = this;\
		}\
		else\
			_first = _last = this;\
	}\
    \
	ClassFrom##::##NameTo##Iterator::NameTo##Iterator(\
        ClassFrom& iter##ClassFrom, ClassTo* ref##NameTo)\
    {\
        assert(&iter##ClassFrom);\
    \
		_iter##ClassFrom = &iter##ClassFrom;\
		_ref##NameTo = _prev##NameTo = _next##NameTo = ref##NameTo;\
		_prev = (NameTo##Iterator*)0;\
		_next = (NameTo##Iterator*)0;\
		if (_last)\
		{\
			_last->_next = this;\
			_prev = _last;\
			_last = this;\
		}\
		else\
			_first = _last = this;\
	}\
    \
	ClassFrom##::##NameTo##Iterator::NameTo##Iterator(\
        const NameTo##Iterator& iterator)\
    {\
		_iter##ClassFrom = iterator._iter##ClassFrom;\
		_ref##NameTo = iterator._ref##NameTo;\
		_prev##NameTo = iterator._prev##NameTo;\
		_next##NameTo = iterator._next##NameTo;\
		_prev = (NameTo##Iterator*)0;\
		_next = (NameTo##Iterator*)0;\
		if (_last)\
		{\
			_last->_next = this;\
			_prev = _last;\
			_last = this;\
		}\
		else\
			_first = _last = this;\
	}\
    \
	ClassFrom##::##NameTo##Iterator::~NameTo##Iterator()\
    {\
		if (_next)\
			_next->_prev = _prev;\
		else\
			_last = _prev;\
    \
		if (_prev)\
			_prev->_next = _next;\
		else\
			_first = _next;\
	}\
    \
	void ClassFrom##::##NameTo##Iterator::Check(ClassTo* item##NameTo)\
    {\
		for (NameTo##Iterator* item = _first; item; item = item->_next)\
		{\
			if (item->_prev##NameTo == item##NameTo)\
			{\
				item->_prev##NameTo = item->_iter##ClassFrom->GetNext##NameTo(item->_prev##NameTo);\
				item->_ref##NameTo = 0;\
			}\
			if (item->_next##NameTo == item##NameTo)\
			{\
				item->_next##NameTo = item->_iter##ClassFrom->GetPrev##NameTo(item->_next##NameTo);\
				item->_ref##NameTo = 0;\
			}\
		}\
	}\
    \
	void ClassFrom##::##NameTo##Iterator::Check(ClassTo* item##NameTo, ClassTo* newItem##NameTo)\
    {\
		for (NameTo##Iterator* item = _first; item; item = item->_next)\
		{\
			if (item->_ref##NameTo == item##NameTo)\
			{\
				item->_ref##NameTo = item->_prev##NameTo = item->_next##NameTo = newItem##NameTo;\
			}\
			if (item->_prev##NameTo == item##NameTo)\
			{\
				item->_prev##NameTo = newItem##NameTo;\
				item->_ref##NameTo = 0;\
			}\
			if (item->_next##NameTo == item##NameTo)\
			{\
				item->_next##NameTo = newItem##NameTo;\
				item->_ref##NameTo = 0;\
			}\
		}\
	}

#define METHODS_ITERATOR_BINARYBITTREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
        METHODS_ITERATOR_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)

#define METHODS_ITERATOR_NOFILTER_BINARYBITTREE_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo) \
        METHODS_ITERATOR_NOFILTER_MULTI_ACTIVE(ClassFrom, NameFrom, ClassTo, NameTo)
#endif