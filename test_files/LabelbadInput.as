;first command is good
a: mov a,a

;bad .data line
.data "bad  input"

;bad .string line
.string 1,2,3

;nothing to put in string
.string 

;nothing to put in data
.data 

;bad input for .data line
.data .data

;bad input for .data line
.data a

;bad input for .data line
.data 2,3,4,a

;bad input for .data line
.data 2,3,4,5 a

;good input with spaces
.string    "good"

;missing end quote
.string "bad input

;missing end quote
.string "bad

;missing end quote
.string "bad 

;extranieous text;;;	
.string "bad input" "  "

;extranieous text
.string "bad inpu'?t"

;comma after command;;;
.string ,"text"

;no error here!
.string ""

;bad input for .string line
.string 5,6,9

;should bad label name
label: .entry 1badlabelName

;should bad label name
label: .extern 1badlabelName


