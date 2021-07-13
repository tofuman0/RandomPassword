A basic command line random password generator<br />
<br />
It looks for "randompassword.json" in the same folder and if it exists it'll load the strings in that file instead of using<br />
the hardcoded strings.<br />
<br />
basic json file structure:<br />
{<br />
	"digits" : 3,<br />
	"first" : [<br />
		"firstwords",<br />
		"..."<br />
	],<br />
	"second" : [<br />
		"secondwords",<br />
		"..."<br />
	],<br />
	"symbols" : [<br />
		"!",<br />
		"?",<br />
		"%",<br />
		"#"<br />
	]<br />
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
	randompassword<br />
<br />
Return 100 passwords:<br />
	randompassword -n 100<br />
	<br />
Return 10 passwords in lowercase:<br />
	randompassword -n 10 -lower<br />
	<br />
Return 10 passwords with no digits:<br />
	randompassword -n 10 -d 0<br />
	<br />
Return office 365 password format:<br />
	randompassword -t o365<br />
	<br />
Return gibberish password 16 in length:<br />
	randompassword -t gibberish -l 16<br />
