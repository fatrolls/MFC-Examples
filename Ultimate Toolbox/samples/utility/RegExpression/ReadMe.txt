COXRegular - new class that implements regular expression functionality.


				Most of us had problems with searching some text in text files.
				Yes, we can use searching capabilities that are provided with
				many programs. But, in case we have to do some generic search
				it is not the case. For such cases COXRegular class is exactly
				what we had to have. This class provided generic search regarding
				the rule you've supplied. To do search, you have to load regular 
				expression that defines what do you want to search. There are
				different formats and different implementation for regular expression.
				This implementation is most close to that one described in
				MSDN that comes with Visual Studio 6.0

	The rules:

  Character				 Description

		\		 Marks the next character as special. All characters that are
				 special but you want to define it for search should be 
				 preceding by this character.
		^		 Matches the begining of input or line. In this implementation this 
				 cannot be defined in charset.
		$		 Matches the end of input or line. In this implementation this 
				 cannot be defined in charset.
		*		 Matches preceding character zero or more times. In this implementation
				 cannot be defined if only one character specified in the regular
				 expression. That means that /zo*/ matches z and zoo, but
				 /z*/ will match nothing because only one character has been specified.
		+		 Matches preceding character one or more times. 
		?		 Matches preceding character zero or one time. In this implementation
				 cannot be defined if only one character specified in the regular
				 expression.
		.		 Matches any single character except '\n'
	(pattern)	 Matches pattern and remembers the match. The matched substring can
				 be retrieved by using '\0'-'\9' in regular expression, where '0'-'9'
				 are number of the pattern. Example:
				 regular expression '(re).*\0s+ion' will match 'regular expression'
				 because first matches pattern 're' and remember the pattern with
				 index 0. '.*' will match 'gular exp' in 'regular expression'.
				 Now we rettrieve pattern with index 0, that has been remembered
				 with index 0, this is 're' that matches 're' in 'regular expression'
				 before 'ssion' and , finally, 's+ion' matches 'ssion'
	   x|y		 Matches either character 'x' or 'y'. You can combine more than two
				 characters like 'x|y|z'
	   {n}		 Means preceding character will match exactly n times (nonnegative, of course)
	  {n,}		 Means preseding character will match at least n times (nonnegative)
	  {n,m}		 Means preceding character will match at keast n times and at 
				 most m times. (n,m - nonnegative)
	  [xyz]		 A character set. Matches any one of enclosed characters
	 [^xyz]		 A non-matching character set. Matches any character that is not in the set.
		\b		 Matches word boundary, that is boundary between any character excluding 
				 space characters (" \f\n\r\t\v") and space characters
		\B		 Matches non-word boundary. Matches any boundary between space 
				 characters or between nonspace characters.
		\d		 Matches any digit /0-9/
		\D		 Matches any non-digit.
		\f		 Matches a formfeed.
		\n		 Matches a new-line character
		\r		 Matches a carridge return character.
		\s		 Matches any white space character
		\S		 Matches any non-white space character
		\t		 Matches a tab character
		\v		 Matches any vertical tab character
		\w		 Matches any word character including underscore. [A-Za-z0-9_]
		\W		 Matches any non-word character (any character that does not match \w)
		\num	 Where num is number between 0 and 9. Matches remmembered pattern.
				 (See description of pattern)
		/n/		 Where n is between 1 and 255. Matches supplied in n ASCII code


	Three easy steps to use:
	1) Create your own derived from COXRegular class and override function OnMatch()
	   This virtual function is always called when a matched substring has been found.
	   When this function is called you can return TRUE to continue search or FALSE
	   if you do not want continue search.
	2) Load your regular expression by function LoadRule()
  	3) Call function Match to do the search in supplied text.


	Now how it works.
	There are two steps in the work -1)load regular expression and 2) search the text

1)load regular expression
  When you are loading regular expression, LoadRule() calls function Parse() that
  has a huge switch. This function do parsing of the rule and create tags of different
  types for every sequences of special characters, depends on the type of special 
  characters. For some special characters founded it calls appropriate functions
  like GetAsciiChar() or GetEither() to do this special parsing. The tags are added
  to the collection of tags. Any tag can be retrieved by GetTag().
  The function Parse is virtual, so, if you need to process some special characters,
  that are not specified here, you can override it. Once Parse() or called subfunction
  found error, Parce stops parsing and returns FALSE. You can retrieve error code
  by GetError() and translate it to description by TranslateError()

2) search the text
  The search text makes function Match() that call recursive function MatchNextTag()
  with start tag number=0. Match() does loop, every time incrementing start position
  in the supplied text for the search untill end of the text has been reached.
  MatchNextTag() does main job and once the tag matches the text at the specified
  position does either, call OnMatch() if the tag was last in the collection of the tags
  or calls MatchNextTag() to match next tag from the collection.

  The function MatchNextTag() like Parse() is virtual, so, it's up to you override it
  if you want to process some special sequences.