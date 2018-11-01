	.data
  .text
; shifting

dsll $a2,$t2,2     ; shift left logical
dsrl $a1,$t2,3     ; shift right logical
dsra $a1,$t2,4     ; shift right arithmetic
halt