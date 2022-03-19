;cmd right after ';'
a:stop

;GOOD LINE ,NO ERROR HERE
a: stop

cmp a,a

stop
stop a
stop;
stop ;
stop 1


cmp a
cmp ,a
cmp #
cmp cmp
cmp a,,a
cmp a,a,a
cmp ,,a
cmp a,mov
cmp mov,a
cmp a,#a

;extraneous text
stop a
stop stop
stop ,
stop ;

;all bad parameters
cmp 1[15],a
cmp a[],#5
cmp r [r15],a

mov a
mov ,a
mov #
mov cmp
mov a,,a
mov a,a,a
mov ,,a
mov a,mov
mov mov,a
mov a,#a


