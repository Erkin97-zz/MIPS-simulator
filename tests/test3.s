	.data
  .text
; conditions sets

slti  $a1,$t5,5    ; set if less than immediate
sltiu $a1,$t5,7    ; set if less than immediate unsigned
slti  $a1,$t5,3    ; set if less than immediatet equal
sltiu $a1,$t5,20   ; set if less than immediate unsignedual
beq   $a1,$t5,end    ; branch if pair of registers are equal
beq   $a1,$t5,end  ; branch if pair of registers are eq
bne   $a1,$t5,end  ; branch if pair of registers are no
bne   $a1,$t5,end  ; branch if pair of registers are not equal
end: halt