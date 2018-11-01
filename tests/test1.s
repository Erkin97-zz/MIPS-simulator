	.data
  .text
; store and load instructions
ld $t5, 1($t5)  ; load 64-bit double-word
lw $t6, 1($t5)  ; load 32-bit word
sd $a1, 1($t5)  ; store 64-bit double-word
sd $a1, 10($t5)  ; store 64-bit double-word
lui $a1, 30 ; load upper half of register immediate
lw $a1, 1($t5)  ; load 32-bit word
lwu $a1,1($t5)  ; load 32-bit word unsigned
sw  $a1,1($t5)  ; store 32-bit word
sw  $a1,15($t5)  ; store 32-bit word
lui $a1, 20 ; load upper half of register immediate