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
<br />
Command line options:<br />
no switches return a single password.<br />
-n X: number of required passwords<br />
-lower: by default the first letter of each word is in upper case this disables that<br />
-d X: number of digits in passwords<br />
-t X: type of password. standard, o365, gibberish<br />
-l X: lenth of gibberish password<br />
<br />
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
