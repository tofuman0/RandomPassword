Random Password
---------------

A basic command line random password generator<br />
<br />
It looks for "randompassword.json" in the same folder and if it exists it'll load the strings in that file instead of using<br />
the hardcoded strings.<br />
<br />
basic json file structure:<br />
{<br />
	&nbsp;&nbsp;&nbsp;&nbsp;"digits" : 3,<br />
	&nbsp;&nbsp;&nbsp;&nbsp;"first" : [<br />
	&nbsp;&nbsp;&nbsp;&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;"firstwords",<br />
	&nbsp;&nbsp;&nbsp;&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;"..."<br />
	&nbsp;&nbsp;&nbsp;&nbsp;],<br />
	&nbsp;&nbsp;&nbsp;&nbsp;"second" : [<br />
	&nbsp;&nbsp;&nbsp;&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;"secondwords",<br />
	&nbsp;&nbsp;&nbsp;&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;"..."<br />
	&nbsp;&nbsp;&nbsp;&nbsp;],<br />
	&nbsp;&nbsp;&nbsp;&nbsp;"symbols" : [<br />
	&nbsp;&nbsp;&nbsp;&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;"!",<br />
	&nbsp;&nbsp;&nbsp;&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;"?",<br />
	&nbsp;&nbsp;&nbsp;&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;"%",<br />
	&nbsp;&nbsp;&nbsp;&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;"#"<br />
	&nbsp;&nbsp;&nbsp;&nbsp;]<br />
}<br />
````CommandLine
Usage: randompassword [-n count] [-s seed] [-j jsonfile] [[-t type] [-l length] | [-lower] [-d count] | [-generatejson]]

Options:
    -n count          Number of passwords to generate.
    -t type           Types: standard, o365, gibberish, custom.
                      O365 password (3 letters 5 numbers).
                      Gibberish password (Random characters).
                      Custom password (similar to regex use -? custom for further help).
                      (this switch will cause -lower and -d switches to be ignored).
    -l length         Length of gibberish password.
    -lower            Passwords to be all lowercase.
    -d count          Digit count in password. (6 limit).
    -s seed           RNG Seed. Uses time by default.
    -j jsonfile       Specify a JSON file to use instead of the default "randompassword.json".
    -generatejson     Generates a default JSON file.

Custom password:
    Custom password allows you to specify a random password based on specified expression.
    Similar to regular expressions. This type ignores length, lower and d switches.

    Usage: randompassword -t custom "EXPR"
        [x-x]        Range of characters e.g. [0-9],[a-z],[a-Z].
        [x]          Type of characters e.g. [vowel],[consonant],[symbol].
                     [VOWEL] and [CONSONANT] will produce an uppercase character.
        [word1]      Random word from first array. word1 will produce an lowercase word
                     WORD1 an uppercase word and Word1 a propercase word.
        [word2]      Random word from first array. word2 will produce an lowercase word
                     WORD2 an uppercase word and Word2 a propercase word.
        x            literial character e.g. abc
        {x}          Character count of range e.g. {3}.

    Example: randompassword -t custom "[symbol][a-z]{4}[A-Z]{3}[0-9]{2}-[a-Z]{4}[symbol]{2}"
             Could generate a password of: !efyrEKS48-GHsR?!
````
Example:<br />
Return 1 password:<br />
	&nbsp;&nbsp;&nbsp;&nbsp;randompassword<br />
<br />
Return 100 passwords:<br />
	&nbsp;&nbsp;&nbsp;&nbsp;randompassword -n 100<br />
	&nbsp;&nbsp;&nbsp;&nbsp;<br />
Return 10 passwords in lowercase:<br />
	&nbsp;&nbsp;&nbsp;&nbsp;randompassword -n 10 -lower<br />
	&nbsp;&nbsp;&nbsp;&nbsp;<br />
Return 10 passwords with no digits:<br />
	&nbsp;&nbsp;&nbsp;&nbsp;randompassword -n 10 -d 0<br />
	&nbsp;&nbsp;&nbsp;&nbsp;<br />
Return office 365 password format:<br />
	&nbsp;&nbsp;&nbsp;&nbsp;randompassword -t o365<br />
	&nbsp;&nbsp;&nbsp;&nbsp;<br />
Return gibberish password 16 in length:<br />
	&nbsp;&nbsp;&nbsp;&nbsp;randompassword -t gibberish -l 16<br />
