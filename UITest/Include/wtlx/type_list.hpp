//
// type_list.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//  Copyright © 2000, 2001 Sofus Mortensen, Michael Geddes
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef TYPE_LIST_HPP
#define TYPE_LIST_HPP

#ifdef _MSC_VER
#	pragma warning( push )
#	pragma warning( disable : 4786 )
#endif // _MSC_VER

#ifndef ATL_NO_VTABLE
#	if _MSC_VER >= 1200
#		define ATL_NO_VTABLE __declspec(novtable)
#	else
#		define ATL_NO_VTABLE
#	endif
#endif

/////////////////////////////////////////////////////////////////////////////

#define LIST_TMPL \
	typename T00 = nil, typename T01 = nil, typename T02 = nil, typename T03 = nil, typename T04 = nil, \
	typename T05 = nil, typename T06 = nil, typename T07 = nil, typename T08 = nil, typename T09 = nil, \
	typename T10 = nil, typename T11 = nil, typename T12 = nil, typename T13 = nil, typename T14 = nil, \
	typename T15 = nil, typename T16 = nil, typename T17 = nil, typename T18 = nil, typename T19 = nil, \
	typename T20 = nil, typename T21 = nil, typename T22 = nil, typename T23 = nil, typename T24 = nil, \
	typename T25 = nil, typename T26 = nil, typename T27 = nil, typename T28 = nil, typename T29 = nil, \
	typename T30 = nil, typename T31 = nil, typename T32 = nil, typename T33 = nil, typename T34 = nil, \
	typename T35 = nil, typename T36 = nil, typename T37 = nil, typename T38 = nil, typename T39 = nil, \
	typename T40 = nil, typename T41 = nil, typename T42 = nil, typename T43 = nil, typename T44 = nil, \
	typename T45 = nil, typename T46 = nil, typename T47 = nil, typename T48 = nil, typename T49 = nil, \
	typename T50 = nil, typename T51 = nil, typename T52 = nil, typename T53 = nil, typename T54 = nil, \
	typename T55 = nil, typename T56 = nil, typename T57 = nil, typename T58 = nil, typename T59 = nil, \
	typename T60 = nil, typename T61 = nil, typename T62 = nil

#define LIST_TMPL_SHIFT \
	T01, T02, T03, T04, T05, T06, T07, T08, T09, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
	T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
	T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54, T55, T56, T57, T58, T59, T60, \
	T61, T62

/////////////////////////////////////////////////////////////////////////////

namespace wtlx
{

// nil
struct nil {};

// node
template<typename T, typename U> struct node { 
	typedef T head;
	typedef U tail;
};

// make_list
template<LIST_TMPL> struct make_list {
	typedef node<T00, typename make_list<LIST_TMPL_SHIFT>::result> result;
};
template<> struct make_list<> {
	typedef nil result;
};

namespace typelist {

	// length_bytes
	template<typename L> struct length_bytes {
		enum { value = sizeof(L::head) + length_bytes< typename L::tail>::value };
	};
	template<> struct length_bytes<nil> {
		enum { value = 0 };
	};

	// length
    template<typename L> struct length { enum { value = 1 + length< typename L::tail>::value }; };
    template<> struct length<nil> { enum { value = 0 }; };

	// type_at forward declaration
	template<typename L, unsigned Idx> struct type_at;

	// type_at_aux
	template<typename L> struct type_at_aux {
        template<unsigned Idx> struct X {
			typedef type_at<L::tail, Idx-1>::result result;
        };
        template<> struct X<0> {
            typedef L::head result;
        };
    };
	template<> struct type_at_aux<nil> {
        template<unsigned Idx> struct X {
            typedef nil result;
        };       
    };

	// type_at
    template<typename L, unsigned Idx> struct type_at {
        typedef type_at_aux<L>::X<Idx>::result result;
    };

	// index_of forward declaration
	template<typename L, typename T> struct index_of;

	// index_of_aux
    template<typename Head> struct index_of_aux {
        template<typename Tail> struct X {
            template<typename T> struct X {
				enum { value = 1 + index_of<Tail, T>::value };
            };
            template<> struct X<Head> {
                enum { value = 0 };
            };
        };
    };

	// index_of
    template<typename L, typename T> struct index_of {
        enum { value = index_of_aux<L::head>::X<L::tail>::X<T>::value };
    };

	// append forward declaration
	template<typename L1, typename L2> struct append;

	//
	namespace impl {
		template<typename L1> struct append_aux {
			template<typename L2> struct with {
				typedef typename L1::head head;
				typedef typename append<L1::tail, L2> tail;
			};
			template<> struct with<nil> {
				typedef typename L1::head head;
				typedef typename L1::tail tail;
			};
		};
		template<> struct append_aux<nil> {
			template<typename L2> struct with {
				typedef typename L2::head head;
				typedef typename L2::tail tail;
			};
		};
    }

	// append
	template<typename L1, typename L2> struct append {
		typedef typename impl::append_aux<L1>::with<L2>::head head;
		typedef typename impl::append_aux<L1>::with<L2>::tail tail;
    };

	// append_element
	template<typename L, typename T> struct append_element {
		typedef typename impl::append_aux<L>::with< make_list<T>::result >::head head;
		typedef typename impl::append_aux<L>::with< make_list<T>::result >::tail tail;
	};

	// inherit_all
	template<typename List>	struct ATL_NO_VTABLE inherit_all : 
		public List::head, 
		public inherit_all<typename List::tail> {
	};
	template<> struct inherit_all<nil> {};

	// select
	//template<const int Idx, LIST_TMPL> struct select {
	//   typedef typelist::type_at< make_list<T00, LIST_TMPL_SHIFT>::result, Idx>::result result;
    //};

} // typelist

} // wtlx

#ifdef _MSC_VER
//#	pragma warning( pop ) 
#endif // _MSC_VER

#endif // TYPE_LIST_HPP
