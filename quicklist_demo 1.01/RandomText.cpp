// RandomText.cpp: implementation of the RandomText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RandomText.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int RandomText::GetRand(const int top, int& last)
{
	int r=0;
	do
	{
		r=rand()%top;
	}while(r==last);

	last=r;
	return r;
}

CString RandomText::Animal(bool plural)
{
	//From: http://www.namestatistics.com/
	CString names[]	= {	_T("cat"), _T("dog"), _T("wolf"), _T("tiger"), _T("lion"), _T("fish"), _T("crocodile"), _T("moose"), _T("pig"), _T("bird"), _T("shark"), _T("whale"), _T("killer fish"), _T("bear"), _T("snail"), _T("worm"), _T("zebra"), _T("horse"), _T("cow"), _T("ant"), _T("bug"), _T("fly"), _T("beetle"), _T("ladybird"), _T("duck"), _T("fox")};

	static int prev=-1;

	CString temp = names[ GetRand(sizeof(names)/sizeof(CString), prev) ];

	if(plural)
		temp +=_T("s");

	return temp;
}

CString RandomText::Cute()
{
	//From: http://www.namestatistics.com/
	CString names[]	= {	_T("cute"), _T("charming"), _T("frightening"), _T("scary"), _T("spooky")};

	static int prev=-1;

	return names[ GetRand(sizeof(names)/sizeof(CString), prev) ];
}

CString RandomText::Size()
{
	//From: http://www.namestatistics.com/
	CString names[]	= {	_T("small"), _T("large"), _T("minor"), _T("big")};

	static int prev=-1;

	return names[ GetRand(sizeof(names)/sizeof(CString), prev) ];
}


CString RandomText::Name()
{
	//From: http://www.namestatistics.com/
	CString names[]	= {	_T("James"), _T("John"), _T("Robert"), _T("Michael"), _T("William"), _T("David"), _T("Richard"), _T("Charles"), _T("Joseph"), _T("Thomas"), _T("Christopher"), _T("Daniel"), _T("Paul"), _T("Mark"), _T("Donald"), _T("George"), _T("Kenneth"), _T("Steven"), _T("Edward"), _T("Brian"), _T("Ronald"), _T("Anthony"), _T("Kevin"), _T("Jason"), _T("Matthew"), _T("Gary"), _T("Timothy"), _T("Jose"), _T("Larry"), _T("Jeffrey"), _T("Mary"), _T("Patricia"), _T("Linda"), _T("Barbara"), _T("Elizabeth"), _T("Jennifer"), _T("Maria"), _T("Susan"), _T("Margaret"), _T("Dorothy"), _T("Lisa"), _T("Nancy"), _T("Karen"), _T("Betty"), _T("Helen"), _T("Sandra"), _T("Donna"), _T("Carol"), _T("Ruth"), _T("Sharon"), _T("Michelle"), _T("Laura"), _T("Sarah"), _T("Kimberly"), _T("Deborah"), _T("Jessica"), _T("Shirley"), _T("Cynthia"), _T("Angela"), _T("Melissa")};

	static int prev=-1;

	return names[ GetRand(sizeof(names)/sizeof(CString), prev) ];
}

CString RandomText::SurName()
{
	//From: http://genealogy.about.com/library/weekly/aa_common_surnames.htm
	CString names[]	= {	_T("Smith"), _T("Johnson"), _T("Williams"), _T("Jones"), _T("Brown"), _T("Davis"), _T("Miller"), _T("Wilson"), _T("Moore"), _T("Taylor"), _T("Anderson"), _T("Thomas"), _T("Jackson"), _T("White"), _T("Harris"), _T("Martin"), _T("Thompson"), _T("Garcia"), _T("Martinez"), _T("Robinson"), _T("Clark"), _T("Rodriguez"), _T("Lewis"), _T("Lee"), _T("Walker"), _T("Hall"), _T("Allen"), _T("Young"), _T("Hernandez"), _T("King"), _T("Wright"), _T("Lopez"), _T("Hill"), _T("Scott"), _T("Green"), _T("Adams"), _T("Baker"), _T("Gonzalez"), _T("Nelson"), _T("Carter"), _T("Mitchell"), _T("Perez"), _T("Roberts"), _T("Turner"), _T("Phillips"), _T("Campbell"), _T("Parker"), _T("Evans"), _T("Edwards"), _T("Collins"), _T("Stewart"), _T("Sanchez"), _T("Morris"), _T("Rogers"), _T("Reed"), _T("Cook"), _T("Morgan"), _T("Bell"), _T("Murphy"), _T("Bailey"), _T("Rivera"), _T("Cooper"), _T("Richardson"), _T("Cox"), _T("Howard"), _T("Ward"), _T("Torres"), _T("Peterson"), _T("Gray"), _T("Ramirez"), _T("James"), _T("Watson"), _T("Brooks"), _T("Kelly"), _T("Sanders"), _T("Price"), _T("Bennett"), _T("Wood"), _T("Barnes"), _T("Ross"), _T("Henderson"), _T("Coleman"), _T("Jenkins"), _T("Perry"), _T("Powell"), _T("Long"), _T("Patterson"), _T("Hughes"), _T("Flores"), _T("Washington"), _T("Butler"), _T("Simmons"), _T("Foster"), _T("Gonzales"), _T("Bryant"), _T("Alexander"), _T("Russell"), _T("Griffin"), _T("Diaz"), _T("Hayes") };

	static int prev=-1;

	return names[ GetRand(sizeof(names)/sizeof(CString), prev) ];
}

CString RandomText::Person(const bool itome)
{
	CString names[]	= {	_T("I"), _T("you"), _T("someone"), _T("anyone"), _T("no one"), _T("everyone")};

	if(itome)
		names[0] = _T("me");

	static int prev=-1;

	return names[ GetRand(sizeof(names)/sizeof(CString), prev) ];
}

CString RandomText::LikeHate()
{
	CString names[]	= {	_T("like"), _T("hate"), _T("dislike"), _T("love") };

	static int prev=-1;

	return names[ GetRand(sizeof(names)/sizeof(CString), prev) ];
}

CString RandomText::Goodie(bool plural)
{
	CString names[]	= {	_T("donout"), _T("muffin"), _T("chicken"), _T("ice cream"), _T("cake"), _T("bum"), _T("pretzel") };

	static int prev=-1;

	CString ret = names[ GetRand(sizeof(names)/sizeof(CString), prev) ];

	if(plural)
		ret += _T("s");

	return ret;
}

CString RandomText::GoodBad()
{
	CString names[]	= {	_T("OK"), _T("good"), _T("bad"), _T("excellent"), _T("terrible"), _T("very good"), _T("very bad") };

	static int prev=-1;

	return names[ GetRand(sizeof(names)/sizeof(CString), prev) ];
}

CString RandomText::DoDont()
{
	CString names[]	= {	_T("do"), _T("don't")};

	static int prev=-1;

	return names[ GetRand(sizeof(names)/sizeof(CString), prev) ];
}

CString RandomText::Happy()
{
	CString names[]	= {	_T("happy"), _T("unhappy"), _T("glad"), _T("sad")};

	static int prev=-1;

	return names[ GetRand(sizeof(names)/sizeof(CString), prev) ];
}

CString RandomText::CommonRare()
{
	CString names[]	= {	_T("common"), _T("rare")};

	static int prev=-1;

	return names[ GetRand(sizeof(names)/sizeof(CString), prev) ];
}

void RandomText::AddWord(CString& sent, const CString& word)
{
	if(sent.IsEmpty()==FALSE)
		sent += _T(" ");

	sent += word;
}

CString RandomText::GetName()
{
	return Name() + _T(" ") + SurName();
}


CString RandomText::GetSlogan()
{
	CString moto;

	int r=rand()%8;

	if(r == 0)
	{
		AddWord(moto, _T("If"));
		AddWord(moto, Person());
		AddWord(moto, LikeHate());
		AddWord(moto, Goodie(true));
		AddWord(moto, _T(", that's"));
		AddWord(moto, GoodBad());
	}
	else if(r==1)
	{
		moto = Person();
		if(moto == _T("I"))
			moto += _T(" am");
		else
			moto += _T(" is");

		AddWord(moto, GoodBad());
	}
	else if(r==2)
	{
		moto = Person();
		AddWord(moto, DoDont());
		AddWord(moto, LikeHate());
		AddWord(moto, Person(true));
	}
	else if(r==3)
	{
		if(rand()%2 == 0)
		{
			AddWord(moto, _T("eat"));
			AddWord(moto, Goodie(true));
		}
		else
		{
			AddWord(moto, LikeHate());
			AddWord(moto, Person(true));
		}

		AddWord(moto, _T("and be"));
		AddWord(moto, Happy());
	}
	else if(r==4)
	{
		moto = Goodie(true);
		AddWord(moto, _T("makes"));
		AddWord(moto, Person(true));

		if(rand()%2==0)
			AddWord(moto, Happy());
		else
		{
			AddWord(moto, LikeHate());
			AddWord(moto, Person(true));
		}
	}
	else if(r==5)
	{
		moto = GoodBad();
		AddWord(moto, Goodie(true));
		AddWord(moto, _T("is"));
		AddWord(moto, CommonRare());
	}
	else if(r==6)
	{
		CString a[] = {_T("free"), _T("kill"), _T("eat")};
		static int temp=-1;
		moto = a[ GetRand(sizeof(a)/sizeof(CString), temp)];

		AddWord(moto, _T("all"));
		AddWord(moto, Animal(true));
	}
	else if(r==7)
	{
		moto = _T("Seeing a");
		AddWord(moto, Animal(false) );
		AddWord(moto, _T("eating"));

		if(rand()%2==0)
		{
			AddWord(moto, Animal(true));
		}
		else
			AddWord(moto, Goodie(true));

		AddWord(moto, _T("is"));
		
		AddWord(moto, Cute());
	}
	else if(r==8)
	{
		moto = _T("an");
		AddWord(moto, Animal(false));
		AddWord(moto, _T("ate my"));

		if(rand()%2==0)
		{
			AddWord(moto, Animal(false));
		}
		else
			AddWord(moto, Goodie());
	}

	moto.Replace(_T(" ,"), _T(","));
	moto.Replace(_T(" ."), _T("."));
	moto.Replace(_T(" :"), _T(":"));
	moto.Replace(_T(" ;"), _T(";"));

	ASSERT(!moto.IsEmpty());

	CString first;
	first=moto.GetAt(0);
	first.MakeUpper();
	moto.SetAt(0, first.GetAt(0));

	return moto;
}
