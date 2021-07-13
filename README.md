A basic command line random password generator

It looks for "randompassword.json" in the same folder and if it exists it'll load the strings in that file instead of using
the hardcoded strings.

basic json file structure:
{
	"digits" : 3,
	"first" : [
		"firstwords",
		"..."
	],
	"second" : [
		"secondwords",
		"..."
	],
	"symbols" : [
		"!",
		"?",
		"%",
		"#"
	]
}

Command line options:
no switches return a single password.
-n X: number of required passwords
-lower: by default the first letter of each word is in upper case this disables that
-d X: number of digits in passwords
-t X: type of password. standard, o365, gibberish
-l X: lenth of gibberish password

Example:
Return 1 password:
	randompassword

Return 100 passwords:
	randompassword -n 100
	
Return 10 passwords in lowercase:
	randompassword -n 10 -lower
	
Return 10 passwords with no digits:
	randompassword -n 10 -d 0
	
Return office 365 password format:
	randompassword -t o365
	
Return gibberish password 16 in length:
	randompassword -t gibberish -l 16
